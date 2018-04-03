/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: log structured file system for flash memory
*/

#include <sys/types.h>
#include <sys/param.h>
#include <stdarg.h>
#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <alloc.h>
#include <error.h>
#include <fs.h>
#include <flfs2.h>
#include <locks.h>
#include <ioctl.h>
#include <userint.h>


#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif


#define fsmsg(f, args...)		fprintf(STDERR, f , ## args )
#define debug(f, args...)		fprintf(STDERR, f , ## args )

typedef char bool;


struct FLFS {
    MountEntry *me;
    offset_t total_size;
    offset_t block_size;			/* MAX( device read size, fblocksize ) */
    offset_t write_size;
    offset_t erase_size;

    lock_t lock;			/* we need to lock areas when the fs is in an inconsistant state */
    struct FileData *openforwrite;	/* list of files open for write */

    offset_t idxoff;
    struct FSIndex *idxbuf;
    bool   idxdirty;

    offset_t dirpos;			/* current active dir. 0=unknown, -1=need new one */

    offset_t lastfreeoffset;         	/* cache location of last available space found */
    offset_t firstfileoffset;
    u_long flags;

    int    ndirent;
    int    nidxent;
};


struct FileData {
    int how;
#define FDH_READ	0
#define FDH_WRITE	1

    struct FLFS	*flfs;
    u_long   attr;
    utime_t  ctime;
    char     name[FLFS_NAMELEN];

    offset_t filestart;
    offset_t filepos;		/* current offset in file */
    offset_t filelen;		/* length of file */
    offset_t cnkstart;		/* offset of start of chunk */
    offset_t cnknext;

    char *buffer;
    int bufsize;		/* allocate size */
    int bufpos;			/* current offset in buffer */
    int buflen;			/* amount of data currently in buffer */

    struct FileData *next, *prev;	/* open for writing list */
};

struct FLFSBuf {
    struct FLFS	*flfs;
    char *buffer;
    offset_t offset;
};

static int flfs2_putchar(FILE*, char);
static int flfs2_getchar(FILE*);
static int flfs2_close(FILE*);
static int flfs2_noop(FILE*);
static int flfs2_status(FILE*);
static int flfs2_read(FILE*, char*, int);
static int flfs2_write(FILE*, const char*, int);
static int flfs2_stat(FILE *, struct stat*);
static int flfs2_deletefile(MountEntry *, const char *);

static int write_flush_and_grow(struct FileData *);


const struct io_fs flfs2_iofs = {
    flfs2_putchar,
    flfs2_getchar,
    flfs2_close,
    flfs2_noop,		/* flush */
    flfs2_status,
    flfs2_read,
    flfs2_write,
    0, 0, 		/* bread, bwrite */
    0, 0,		/* seek, tell */
    flfs2_stat
};



int
flfs2_init(MountEntry *me){

    struct FLFS *flfs = alloc(sizeof(struct FLFS));
    bzero(flfs, sizeof(struct FLFS));

    flfs->me  = me;
    me->fsdat = flfs;

    struct stat s;
    fstat( me->fdev, &s );
    flfs->total_size = s.size;
    flfs->flags      = s.flags;

    flfs->block_size = FBLOCKSIZE;	// MAX( FBLOCK, write_size )
    flfs->write_size = 8;
    flfs->erase_size = 2048;

    flfs->ndirent = (flfs->block_size - sizeof(struct FSChunk)) / sizeof(struct FSDirEnt);
    flfs->nidxent = (flfs->block_size - sizeof(struct FSChunk)) / sizeof(fs2_t);
    flfs->idxbuf  = alloc(flfs->block_size);
    flfs->idxoff  = -1;

    // RSN - fsck

    return 0;
}

int
flfs2_unmount(MountEntry *me){
    struct FLFS * flfs = me->fsdat;

    free(flfs->idxbuf, flfs->block_size);
    free(flfs, sizeof(struct FLFS));
}

static int
flfs_erase_notneeded(struct FLFS *flfs){
    // eg. ram disk
    if( flfs->erase_size == 0 )     return 1;
    if( flfs->flags & SSF_NOERASE ) return 1;
    return 0;
}

static int
diskread(struct FLFS *flfs, offset_t off, char *buf, int len){
    int r = fbread(flfs->me->fdev, buf, len, off);
    if( r < 0 )
        fsmsg("read %s @0x%x failed\n", flfs->me->name, off);
    return r;
}

static int
diskwrite(struct FLFS *flfs, offset_t off, const char *buf, int len){
    int r = fbwrite(flfs->me->fdev, buf, len, off);
    if( r < 0 )
        fsmsg("write %s @0x%x failed\n", flfs->me->name, off);
    return r;
}

static int
diskerase(struct FLFS *flfs, offset_t off, char *buf, int len){
    offset_t i;

    memset(buf, 0xFF, flfs->block_size);

    if( flfs_erase_notneeded(flfs) ){
        for(i=0; i<len; i += flfs->block_size){
            diskwrite(flfs, off + i, buf, sizeof(struct FSChunk));
        }
    }else{
        for(i=0; i<len; i += flfs->erase_size ){
            fioctl(flfs->me->fdev, IOC_ERASE, (void*)(off + i) );
        }
    }
}


static void
buffer_alloc(struct FileData *fd, int size){
    fd->buffer  = alloc( size );
    fd->bufsize = size;
}

static void
buffer_free(struct FileData *fd){

    if( fd->buffer && fd->bufsize )
        free( fd->buffer, fd->bufsize);
}

static struct FileData *
new_filedata(struct FLFS * flfs){
    struct FileData *fd;

    fd = alloc(sizeof(struct FileData));
    bzero(fd, sizeof(struct FileData));
    buffer_alloc(fd, flfs->block_size);

    fd->flfs = flfs;

    return fd;
}

static void
free_filedata(struct FileData *fd){

    if( fd->next || fd->prev ){
        // remove from open file list
        struct FLFS * flfs = fd->flfs;

        sync_lock( &flfs->lock, "flfs.L" );

        if( fd->next ) fd->next->prev = fd->prev;
        if( fd->prev ) fd->prev->next = fd->next;

        if( flfs->openforwrite == fd )
            flfs->openforwrite = fd->next;

        sync_unlock( &flfs->lock );
    }

    buffer_free(fd);
    free(fd, sizeof(struct FileData));
}

static FILE*
new_file(struct FileData *fd){

    FILE *f = alloc(sizeof(FILE));
    finit( f );
    f->flags = 0;
    f->fs = &flfs2_iofs;
    f->d  = fd;

    return f;
}

static int
check_block_pending(struct FLFS *flfs, offset_t off){
    struct FileData *fd;

    for(fd=flfs->openforwrite; fd; fd=fd->next){
        if( (fd->filestart == off) || (fd->cnkstart == off) ){
            return 1;
        }
    }

    return 0;
}

/****************************************************************/

static inline offset_t
index_offset_for(struct FLFS *flfs, offset_t off){
    return ((off / flfs->block_size) / flfs->nidxent) * flfs->block_size * flfs->nidxent;
}
static inline offset_t
index_pos_for(struct FLFS *flfs, offset_t off){
    return (off / flfs->block_size) % flfs->nidxent;
}

static int
flush_index(struct FLFS *flfs){

    if( flfs->idxoff == -1 ) return 0;
    if( diskwrite(flfs, flfs->idxoff, flfs->idxbuf, flfs->block_size) <= 0 ) return -1;
    flfs->idxdirty = 0;
    debug("flush idx %x\n", (int)flfs->idxoff);

    return 0;
}

static int
read_index(struct FLFS *flfs, offset_t off){
    off = index_offset_for(flfs, off);

    if( off == flfs->idxoff ) return 0;
    if( flfs->idxdirty ) flush_index(flfs);

    flfs->idxoff = -1;

    debug("read idx %x\n", (int)off);
    if( diskread(flfs, off, flfs->idxbuf, flfs->block_size) <= 0 ) return -1;
    flfs->idxoff = off;

    return 0;
}


static int
update_index(struct FLFS *flfs, offset_t off, fs2_t type){

    if( read_index(flfs, off) ) return -1;

    int pos = index_pos_for(flfs, off);

    flfs->idxbuf->cktype[pos] = type;
    flfs->idxbuf->cktype[0] = FCT_INDEX;
    flfs->idxdirty = 1;

    debug("idx off %x -> pos %x [%x] -> t %d [%16, 4H]\n", (int)off, (int)flfs->idxoff, pos, (int)type, flfs->idxbuf);

    if( type = FCT_DELETED ){
        int i;

        // are all entries deleted?
        for(i=0; i<flfs->nidxent; i++){
            if( flfs->idxbuf->cktype[i] != FCT_DELETED ) return 0;
        }

        flfs->idxbuf->cktype[0] = FCT_DELETED;
    }

    return 0;
}

static int
get_index_type(struct FLFS *flfs, offset_t off){

    if( read_index(flfs, off) ) return FCT_ERROR;

    int pos = index_pos_for(flfs, off);
    fs2_t r = flfs->idxbuf->cktype[pos];

    if( r > 4 && r != ALLONES ){
        hexdump(flfs->idxbuf, 80);
    }

    if( !pos ){
        if( r == FCT_BLANK )   return FCT_EMPTY_INDEX;
        if( r == FCT_DELETED ) return FCT_DELET_INDEX;
    }

    return r;
}

/****************************************************************/

/* buffer is a dir block */
static struct FSDirEnt *
findfile_in_dir(struct FLFSBuf *fb, const char *name){
    struct FSDir *db = (struct FSDir*)fb->buffer;
    int i;

    /* nothing here to see */
    if( db->flag == FDT_DELETED ) return 0;

    for(i=0; i<fb->flfs->ndirent; i++){
        if( db->dir[i].start == FDS_EMPTY )   return 0; /* end of entries */
        if( db->dir[i].start == FDS_DELETED ) continue;

        if( !strcmp(name, db->dir[i].name)) return & db->dir[i];
    }

    /* not found */
    return 0;
}


/*
  find file

  passed buffer must be at least flfs->block_size
*/

static struct FSDirEnt *
findfile(struct FLFSBuf *fb, const char *name){
    struct FLFS *flfs = fb->flfs;
    offset_t offset = 0;

    /* strip off devicename */
    name = basenameoffile(name);

    while( offset < flfs->total_size ){
        // debug("[ff %x] ", (int)offset);
        if( get_index_type(flfs, offset) == FCT_DIR ){

            /* read directory */
            if( diskread(flfs, offset, fb->buffer, flfs->block_size) <= 0 ) return -1;

            /* search directory */
            struct FSDirEnt *r = findfile_in_dir(fb, name);
            fb->offset = offset;
            if( r ) return r;
        }

        offset += flfs->block_size;
    }

    fb->offset = 0;
    return 0;
}

static int
is_available(struct FLFS *flfs, offset_t pos ){
    struct FSChunk fc;

    if( check_block_pending(flfs, pos) ) return 0;

    if( get_index_type(flfs, pos) != FCT_BLANK ) return 0;

    /* index says it is ok, verify */
    if( diskread(flfs, pos, &fc, sizeof(struct FSChunk)) <= 0 ) return 0;
    if( fc.type == FCT_BLANK ) return 1;

    /* index is out of wack - fix */
    update_index(flfs, pos, fc.type);

    return 0;
}

static offset_t
find_available(struct FLFS *flfs){
    offset_t pos=flfs->lastfreeoffset;

    while( pos < flfs->total_size ){
        debug(" [%x]", pos);
        if( is_available(flfs, pos) ){
            flfs->lastfreeoffset = pos;
            return pos;
        }

        pos += flfs->block_size;
    }

    return -1;
}

static int
release_block(struct FLFS *flfs, offset_t off, char *buf){
    struct FSChunk *fc = (struct FSChunk*)buf;

    fc->type = FCT_DELETED;

    if( flfs->write_size <= sizeof(fc->type) ){
        diskwrite(flfs, off + offsetof(struct FSChunk, type), &(fc->type), sizeof(fc->type));
    }else{
        diskwrite(flfs, off, fc, flfs->block_size);
    }

    update_index(flfs, off, FCT_DELETED);
    return 0;
}

/****************************************************************/
static int
get_open_dir_slot_from(struct FLFSBuf *fb, offset_t offset){
    struct FSDir *dir = (struct FSDir*)fb->buffer;
    int i;

    // read block
    // check type, flag
    // search

    fb->offset = offset;
    diskread(fb->flfs, offset, fb->buffer, fb->flfs->block_size);
    if( dir->type != FCT_DIR )    return -1;
    if( dir->flag != FDT_ACTIVE ) return -1;

    for(i=0; i<fb->flfs->ndirent; i++){
        if( dir->dir[i].start == FDS_EMPTY ){
            debug("dir slot: %x [%d]\n", (int)offset, i);
            return i;
        }
    }
}

static void
mark_dir_full(struct FLFSBuf *fb){
    struct FSDir *d = (struct FSDir*)fb->buffer;

    fb->flfs->dirpos = -1;
    d->flag = FDT_FULL;
}

static int
get_open_dir_slot(struct FLFSBuf *fb){
    struct FLFS *flfs = fb->flfs;
    offset_t offset;

    // dirpos looks valid? check
    if( (flfs->dirpos != 0) && (flfs->dirpos != -1) ){
        int i = get_open_dir_slot_from(fb, flfs->dirpos);

        if( i == flfs->ndirent - 1 ) mark_dir_full(fb);
        debug("dirpos %x -> %d\n",(int) flfs->dirpos, i);
        if( i >= 0 ) return i;
    }

    // dirpos != -1? search for existing dir
    if( flfs->dirpos != -1 ){
        for(offset=0; offset<flfs->total_size; offset += flfs->block_size){
            if( get_index_type(flfs, offset) == FCT_DIR ){

                int i = get_open_dir_slot_from(fb, offset);
                if( i == flfs->ndirent - 1 ) mark_dir_full(fb);
                flfs->dirpos = offset;
                debug("dir search %x -> %d\n", (int)offset, i);
                if( i >= 0 ) return i;
            }
        }
    }

    // allocate + init new dir block
    offset = find_available(flfs);
    if( offset == -1 ) return -1;

    // init new dir block
    fb->offset = offset;
    flfs->dirpos = offset;
    memset( fb->buffer, 0xFF, flfs->block_size );
    struct FSDir *dir = (struct FSDir*)fb->buffer;
    dir->type = FCT_DIR;
    update_index(flfs, offset, FCT_DIR);

    debug("dir new %x -> 0\n", (int)offset);

    return 0;
}

//XXXstatic int
//XXXget_open_dir_slot(struct FileData *fd){
//XXX    // NB: fills in cnkstart + buffer
//XXX    return find_open_dir_slot(fd->flfs, fd->buffer, &fd->cnkstart);
//XXX}

/****************************************************************/

FILE *
flfs2_open_r(struct FLFS *flfs, const char *name){
    struct FileData *fd;
    struct FSFile *ff;
    int offset;

    fd = new_filedata(flfs);

    struct FLFSBuf fb = {.flfs = flfs, .buffer = fd->buffer};
    /* search disk for file */
    sync_lock( &flfs->lock, "flfs.L" );
    struct FSDirEnt *de = findfile(&fb, name);
    sync_unlock( &flfs->lock );

    if( de == 0 ){
        /* file not found */
        free_filedata(fd);
        return 0;
    }


    fd->how       = FDH_READ;
    fd->ctime     = de->ctime;
    fd->attr      = de->attr;
    fd->filestart = de->start;
    fd->filelen   = de->filelen;
    fd->filepos   = 0;

    fd->cnkstart  = de->start;
    fd->cnknext   = de->start;
    fd->buflen    = flfs->block_size;
    fd->bufpos    = fd->buflen;

    debug("read start %x, pos %x\n", (int)de->start, fd->bufpos);
    return new_file(fd);

}

FILE *
flfs2_open_w(struct FLFS *flfs, const char *name){
    struct FileData *fd;
    offset_t offset;

    debug("open w '%s'\n", name);
    fd = new_filedata(flfs);

    struct FLFSBuf fb = {.flfs =  flfs, .buffer = fd->buffer};

    /* search disk for file */
    sync_lock( &flfs->lock, "flfs.L" );
    struct FSDirEnt *de = findfile(&fb, name);
    sync_unlock( &flfs->lock );

    if( de != 0 ){

        /* preserve attr */
        fd->attr = de->attr;

        debug("  deleting\n");

        /* delete file */
        if( flfs2_deletefile(flfs->me, name) == -1 ){
            /* read-only file */
            free_filedata(fd);
            return 0;
        }
    }

    name = basenameoffile(name);

    sync_lock( &flfs->lock, "flfs.L" );

    debug("finding");
    offset = find_available(flfs);
    debug(" avail %x\n", offset);

    if( offset == -1 ){
        fsmsg("filesystem %s is full\n", flfs->me->name);
        free_filedata(fd);
        sync_unlock( &flfs->lock );
        return 0;
    }

    fd->filestart = offset;
    fd->cnkstart  = offset;
    fd->next = flfs->openforwrite;
    fd->prev = 0;
    flfs->openforwrite = fd;

    sync_unlock( &flfs->lock );

    // init
    memset(fd->buffer, 0xFF, flfs->block_size);
    strncpy(fd->name, name, FLFS_NAMELEN);


    fd->filelen = 0;
    fd->filepos = 0;
    fd->bufpos  = sizeof(struct FSChunk);
    fd->buflen  = flfs->block_size;
    fd->how     = FDH_WRITE;

    return new_file(fd);
}


static int
write_flush_and_grow(struct FileData *fd){
    struct FLFS *flfs = fd->flfs;

    // get more space
    sync_lock( &flfs->lock, "flfs.L" );
    offset_t more = find_available(flfs);

    if( more == -1 ){
        sync_unlock( &flfs->lock );
        fsmsg("filesystem %s is full\n", flfs->me->name);
        return -1;
    }

    // flush buffer
    struct FSChunk *fc = (struct FSChunk*)fd->buffer;
    fc->type = (fd->filestart == fd->cnkstart) ? FCT_FIRST : FCT_DATA;
    fc->next = more;

    if( diskwrite(flfs, fd->cnkstart, fd->buffer, fd->bufsize) <= 0) return -1;

    offset_t ochunk = fd->cnkstart;

    fd->cnkstart = more;
    fd->bufpos   = sizeof(struct FSChunk);
    sync_unlock( &flfs->lock );

    sync_lock( &flfs->lock, "flfs.L" );
    update_index(flfs, fd->cnkstart, fc->type);
    sync_unlock( &flfs->lock );

    // init new block
    memset(fc, 0xFF, fd->bufsize);

    return 0;
}

static void
flush_final_data(struct FileData *fd){
    struct FLFS *flfs = fd->flfs;

    if( fd->bufpos == 0 ) return;

    struct FSChunk *fc = (struct FSChunk*)fd->buffer;
    fc->type = (fd->filestart == fd->cnkstart) ? FCT_FIRST : FCT_DATA;

    debug("flush %x\n", (int)fd->cnkstart);
    diskwrite(fd->flfs, fd->cnkstart, fd->buffer, fd->bufsize);

    sync_lock( &flfs->lock, "flfs.L" );
    update_index(fd->flfs, fd->cnkstart, fc->type);
    sync_unlock( &flfs->lock );

}

static void
flush_final_meta(struct FileData *fd){
    struct FLFS *flfs = fd->flfs;

    debug("flush meta len %d\n", fd->filelen);

    sync_lock( &flfs->lock, "flfs.L" );

    // find or allocate dir block
    // NB: fills in cnkstart + buffer
    struct FLFSBuf fb = {.flfs = flfs, .buffer = fd->buffer};
    int di = get_open_dir_slot(&fb);
    debug("meta off %x pos %d\n", (int)fb.offset, di);

    if( di == -1 ){
        fsmsg("filesystem %s is full\n", flfs->me->name);
        sync_unlock( &flfs->lock );
        return;
    }

    // fill in entry
    struct FSDir *dir = (struct FSDir*)fd->buffer;
    struct FSDirEnt *de = & dir->dir[di];
    strncpy(de->name, fd->name, sizeof(de->name));
    de->attr = fd->attr;
    de->filelen = fd->filelen;
    de->ctime = get_time();
    de->start = fd->filestart;

    // write
    diskwrite(fd->flfs, fb.offset, fd->buffer, fd->bufsize);

    flush_index(flfs);
    sync_unlock( &flfs->lock );

}

/****************************************************************/

static int
flfs2_close(FILE *f){
    struct FileData *fd;
    struct FLFS *flfs;
    fs2_t i;

    fd   = f->d;
    flfs = fd->flfs;

    debug("close\n");
    if( fd->how == FDH_WRITE ){
        flush_final_data(fd);
        flush_final_meta(fd);
    }

    free_filedata(fd);
    free(f, sizeof(FILE));

    return 0;
}

/****************************************************************/

static int
read_next_chunk(struct FileData *fd){

    debug("read next %x\n", (int)fd->cnknext);
    if( fd->cnknext == 0 || fd->cnknext == ALLONES )
        return -1;

    if( diskread(fd->flfs, fd->cnknext, fd->buffer, fd->bufsize) <= 0 ) return -1;

    struct FSChunk* fc = (struct FSChunk*)fd->buffer;

    if( (fc->type != FCT_DATA) && (fc->type != FCT_FIRST) ){
        fsmsg("read %s,%d corrupt (type %x)\n", fd->flfs->me->name, (int)fd->cnknext, fc->type);
        return -1;
    }

    fd->cnkstart = fd->cnknext;
    fd->cnknext  = fc->next;
    fd->bufpos   = sizeof(struct FSChunk);

    return 0;
}

/*
  read file
*/

static int
flfs2_read(FILE* f, char* buf, int len){
    struct FileData *fd;
    struct FLFS *flfs;
    offset_t rd = 0;

    fd = f->d;
    flfs = fd->flfs;

    if( len > fd->filelen - fd->filepos ){
        /* attempt to read past EOF - truncate */
        len = fd->filelen - fd->filepos;
    }

    while(len){

        // copy data from current buffer
        if( fd->bufpos < fd->buflen ){
            int l = fd->buflen - fd->bufpos;
            if( l > len ) l = len;

            memcpy(buf, fd->buffer + fd->bufpos, l);
            fd->bufpos  += l;
            fd->filepos += l;
            buf += l;
            len -= l;
            rd  += l;
        }

        if( len ) read_next_chunk(fd);
    }


    if( fd->filepos >= fd->filelen ){
        /* reached eof */
        f->flags |= F_EOF;
    }

    return rd;
}




static int
flfs2_write(FILE* f, const char* buf, int len){
    struct FileData *fd;
    struct FLFS *flfs;
    offset_t wrt = 0;

    fd = f->d;
    flfs = fd->flfs;

    while(len){

        // copy to buffer
        if( fd->bufpos < fd->buflen ){
            int l = fd->buflen - fd->bufpos;
            if( l > len ) l = len;

            memcpy(fd->buffer + fd->bufpos, buf, l);
            fd->bufpos  += l;
            fd->filepos += l;
            fd->filelen += l;
            buf += l;
            len -= l;
            wrt += l;
        }

        // new block
        if( len ) write_flush_and_grow(fd);
    }

    return wrt;
}

/****************************************************************/

FILE *
flfs2_open(MountEntry *me, const char *name, const char *how){
    struct FLFS *flfs = me->fsdat;
    FILE *f;

    if( *how == 'r' ){
        f = flfs2_open_r(flfs, name);
    }else{
        f = flfs2_open_w(flfs, name);
    }

    return f;
}

static int
flfs2_getchar(FILE *f){
    char c;

    if( f->flags & F_EOF )
        return -1;

    flfs2_read(f, &c, 1);
    return c;
}

static int
flfs2_noop(FILE *f){
    return 1;
}

static int
flfs2_putchar(FILE *f, char c){
    return flfs2_write(f, &c, 1);
}

static int
flfs2_status(FILE *f){
    struct FileData *fd;

    fd = f->d;

    if( fd->how == FDH_WRITE ){
        return FST_O;
    }else{
        return FST_I;
    }
}

static int
flfs2_stat(FILE *f, struct stat *s){
    struct FileData *fd;
    struct FLFS *flfs;

    fd = f->d;
    flfs = fd->flfs;

    s->dev     = flfs->me;
    s->size    = fd->filelen;
    s->ctime   = fd->ctime;
    s->blksize = flfs->block_size;
    s->mode    = fd->attr;
    s->flags   = flfs->flags;

    return 0;
}


/*****************************************************************/
/* fs_type ops */

static int
flfs2_dir(MountEntry *me, int how){
    struct FLFS *flfs = me->fsdat;
    struct FSDir *dir;
    char *buffer;
    offset_t offset = 0;
    int totdata = 0, totalloc = 0;
    int i, nfiles = 0, nhidden = 0;


    if( !me ){
        printf("no such file or device\n");
        return -1;
    }

    buffer = alloc(flfs->block_size);
    dir = (struct FSDir*)buffer;

    sync_lock( &flfs->lock, "flfs.L" );

    debug("dir\n");
    for(offset=0; offset<flfs->total_size; offset += flfs->block_size){

        fs2_t t = get_index_type(flfs, offset);

        if( (t != FCT_BLANK) && (t != FCT_EMPTY_INDEX) )
            totalloc += flfs->block_size;

        if( t != FCT_DIR ) continue;

        if( diskread(flfs, offset, buffer, flfs->block_size) <= 0 ){
            break;
        }

        for(i=0; i<flfs->ndirent; i++){
            struct FSDirEnt *d = dir->dir + i;

            if( d->start == FDS_EMPTY ) continue;

            if( (d->start == FDS_DELETED) && !(how & LSHOW_EXT) ) continue;

            if(how & LSHOW_EXT){
                if( d->start == FDS_DELETED )
                    printf("X");
                else if( d->attr & FFA_HIDDEN ){
                    printf("H");
                    nhidden ++;
                }else{
                    printf(" ");
                    nfiles ++;
                    totdata += d->filelen;
                }

                printf(" %6x ",  (int)d->start);
                printf(" %-20T %3d    %7d %s\n", d->ctime, (int)d->attr, d->filelen, d->name);

            }else if( (d->attr & FFA_HIDDEN) && !(how & LSHOW_ALL) ){
                nhidden ++;
                continue;
            }else{
                if( how & LSHOW_LONG ){
                    printf("%-20T %c%c %7d bytes    %s\n",
                           d->ctime,
                           (d->attr & FFA_READONLY) ? 'r' : '-',
                           (d->attr & FFA_HIDDEN)   ? 'h' : '-',
                           (int)d->filelen, d->name);
                }else{
                    printf("%7d bytes    %s\n", (int)d->filelen, d->name);
                }
                nfiles ++;
                totdata += d->filelen;
            }
        }
    }

    sync_unlock( &flfs->lock );


    printf("========================\n"
           "  %3d Files = %8d bytes\n", nfiles, totdata);
    if( nhidden)
        printf("  %3d Hidden Files\n", nhidden);
    printf("      Total = %8d bytes\n"
           "      Free  = %8d bytes\n\n",
           totalloc, flfs->total_size - totalloc);
    free(buffer, flfs->block_size);
    return 0;
}


static int
flfs2_format(MountEntry *me, char *flfsname){
    struct FLFS *flfs = me->fsdat;
    char *buffer = alloc(flfs->block_size);
    struct FSChunk *fc = (struct FSChunk*)buffer;

    sync_lock( &flfs->lock,    "flfs.L" );

    diskerase( flfs, 0, buffer, flfs->total_size );

    memset( flfs->idxbuf, 0xFF, flfs->block_size );
    flfs->idxdirty = 0;
    flfs->dirpos = -1;
    flfs->lastfreeoffset = 0;
    flfs->firstfileoffset = 0;

    sync_unlock( &flfs->lock );

    free(buffer, flfs->block_size);
    fflush( me->fdev );
    return 0;
}

static void
check_dir_all_deleted(struct FLFS *flfs, offset_t off, struct FSDir *d){
    int i;

    for(i=0; i<flfs->ndirent; i++){
        if( d->dir[i].start != FDS_DELETED ) return;
    }

    d->flag = FDT_DELETED;
    d->type = FCT_DELETED;
    update_index(flfs, off, FCT_DELETED);
}

static void
delete_dir_entry(struct FLFS *flfs, offset_t off, struct FSDir *d, struct FSDirEnt *de){
    int i;

    de->start = FDS_DELETED;
    check_dir_all_deleted(flfs, off, d);

    diskwrite(flfs, off, d, flfs->block_size);
}

static int
flfs2_deletefile(MountEntry *me, const char *name){
    struct FLFS *flfs = me->fsdat;
    struct FSChunk *fc;
    struct FSDir *dir;
    struct FSDirEnt *de;

    char *buffer;
    offset_t offset, next;
    int i, err=0;

    buffer = alloc(flfs->block_size);
    struct FLFSBuf fb = {.flfs = flfs, .buffer = buffer};
    de  =  findfile(&fb, name);
    offset = fb.offset;
    dir = (struct FSDir *)buffer;
    fc  = (struct FSChunk*)buffer;

    if( de == 0 ){
        /* not found */
        free(buffer, flfs->block_size);
        return -1;
    }

    if( de->attr & FFA_READONLY ){
        /* read-only file cannot be deleted */
        free(buffer, flfs->block_size);
        return -1;
    }

    sync_lock( &flfs->lock, "flfs.L" );

    /* delete dir entry */
    next = de->start;
    delete_dir_entry(flfs, offset, dir, de);

    offset = next;

    while(1){

        if( diskread(flfs, offset, buffer, flfs->block_size) <= 0 ){
            err = -1;
            break;
        }

        next = fc->next;
        release_block(flfs, offset, buffer);
        offset = next;

        if( offset == ALLONES || offset == 0 ){
            break;
        }
    }

    flush_index(flfs);
    sync_unlock( &flfs->lock );
    fflush( me->fdev );
    free(buffer, flfs->block_size);
    return err;
}

static int
flfs2_fchmod(FILE * f, int attr){
    struct FSFile *ff;
    struct FileData *fd;

    fd = f->d;

    if( fd->how != FDH_WRITE ){
        return -1;
    }

    fd->attr = attr;

    return 0;
}

static int
flfs2_chmod(MountEntry *me, const char *name, int attr){
    struct FLFS *flfs = me->fsdat;
    struct FSDirEnt *ne;

    char *buffer1 = alloc(flfs->block_size);
    char *buffer2 = alloc(flfs->block_size);

    sync_lock( &flfs->lock, "flfs.L" );

    offset_t offset, avail;
    struct FLFSBuf fb = {.flfs = flfs, .buffer = buffer1 };
    struct FSDirEnt *de  =  findfile(&fb, name);
    offset = fb.offset;

    if( de == 0 ){
        sync_unlock( &flfs->lock );
        free(buffer1, flfs->block_size);
        free(buffer2, flfs->block_size);
        fsmsg("not found '%s'\n", name);
        return -1;
    }

    struct FLFSBuf fb2 = {.flfs = flfs, .buffer = buffer2 };
    int di = get_open_dir_slot(&fb2);
    avail = fb2.offset;

    if( di == -1 ){
        sync_unlock( &flfs->lock );
        free(buffer1, flfs->block_size);
        free(buffer2, flfs->block_size);
        fsmsg("filesystem %s is full\n", flfs->me->name);
        return -1;
    }

    if( offset == avail ){
        ne = ((struct FSDir*)buffer1)->dir + di;
    }else{
        ne = ((struct FSDir*)buffer2)->dir + di;
    }

    // copy
    ne->start = de->start;
    ne->attr  = attr;
    ne->ctime = de->ctime;
    ne->filelen = de->filelen;
    strncpy(ne->name, de->name, sizeof(ne->name));

    // delete old file block
    debug("delete %x\n", offset);

    delete_dir_entry(flfs, offset, buffer1, de);

    if( offset != avail )
        diskwrite(flfs, avail, buffer2, flfs->block_size);

    flush_index(flfs);
    sync_unlock( &flfs->lock );
    free(buffer1, flfs->block_size);
    free(buffer2, flfs->block_size);
    return 0;
}

static int
flfs2_renamefile(MountEntry *me, const char *oname, const char *nname){
    struct FLFS *flfs = me->fsdat;
    struct FSDirEnt *ne;

    char *buffer1 = alloc(flfs->block_size);
    char *buffer2 = alloc(flfs->block_size);

    sync_lock( &flfs->lock, "flfs.L" );

    offset_t offset, avail;
    struct FLFSBuf fb = {.flfs = flfs, .buffer = buffer1 };
    struct FSDirEnt *de  =  findfile(&fb, oname);
    offset = fb.offset;
    debug("found existing off %x\n", (int)offset);

    if( de == 0 ){
        sync_unlock( &flfs->lock );
        free(buffer1, flfs->block_size);
        free(buffer2, flfs->block_size);
        fsmsg("not found '%s'\n", oname);
        return -1;
    }

    struct FLFSBuf fb2 = {.flfs = flfs, .buffer = buffer2};
    int di = get_open_dir_slot(&fb2);
    avail = fb2.offset;
    debug("found new space %x + %d\n", (int)avail, di);

    if( di == -1 ){
        sync_unlock( &flfs->lock );
        free(buffer1, flfs->block_size);
        free(buffer2, flfs->block_size);
        fsmsg("filesystem %s is full\n", flfs->me->name);
        return -1;
    }

    if( offset == avail ){
        ne = ((struct FSDir*)buffer1)->dir + di;
    }else{
        ne = ((struct FSDir*)buffer2)->dir + di;
    }

    // copy
    ne->start = de->start;
    ne->attr  = de->attr;
    ne->ctime = de->ctime;
    ne->filelen = de->filelen;
    strncpy(ne->name, nname, sizeof(ne->name));

    // delete old file block
    debug("delete %x\n", offset);

    delete_dir_entry(flfs, offset, buffer1, de);

    if( offset != avail )
        diskwrite(flfs, avail, buffer2, flfs->block_size);

    flush_index(flfs);
    sync_unlock( &flfs->lock );
    free(buffer1, flfs->block_size);
    free(buffer2, flfs->block_size);
    return 0;
}

static int
flfs2_glob(MountEntry *me, const char *pattern, int (*fnc)(const char *, void*), void *args){
    struct FLFS *flfs = me->fsdat;
    offset_t offset = 0;
    int rv=0, i;

    char *buffer = alloc(flfs->block_size);
    struct FSDir *dir = (struct FSDir*)buffer;

    sync_lock( &flfs->lock, "flfs.L" );

    for(offset=0; offset<flfs->total_size; offset += flfs->block_size){
        int t = get_index_type(flfs, offset);
        if( t != FCT_DIR ) continue;

        if( diskread(flfs, offset, buffer, flfs->block_size) <= 0 ){
            break;
        }

        for(i=0; i<flfs->ndirent; i++){
            struct FSDirEnt *d = dir->dir + i;

            if( d->start == FDS_EMPTY )   continue;
            if( d->start == FDS_DELETED ) continue;


            if( !(d->attr & FFA_HIDDEN)
                && !fnmatch(pattern, d->name, 0)){
                /* found it */

                rv = (fnc)(d->name, args);
            }
        }
    }

    sync_unlock( &flfs->lock );
    free(buffer, flfs->block_size);

    return rv;
}


int
flfs2_ops(int what, MountEntry *me, ...){
    va_list ap;
    char *name;
    FILE *f;
    int n;

    va_start(ap, me);

    switch (what){

    case FSOP_RENAME:
        name = va_arg(ap, char*);
        return flfs2_renamefile(me, name, va_arg(ap, char*));

    case FSOP_DELETE:
        return flfs2_deletefile(me, va_arg(ap, char*));

    case FSOP_DIR:
        return flfs2_dir(me, va_arg(ap, int));

    case FSOP_CHMOD:
        name = va_arg(ap, char*);
        return flfs2_chmod(me, name, va_arg(ap, int));

    case FSOP_FCHMOD:
        f = va_arg(ap, FILE*);
        return flfs2_fchmod(f, va_arg(ap, int));

    case FSOP_FORMAT:
        return flfs2_format(me, va_arg(ap, char*));

    case FSOP_GLOB: {
        char *name = va_arg(ap, char*);
        int (*fnc)(const char *, void*) = va_arg(ap, void*); /* XXX gcc bug */
        return flfs2_glob(me, name, fnc, va_arg(ap, void*) );
    }
    default:
        return -1;
    }
}


