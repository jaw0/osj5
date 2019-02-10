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

#ifdef FLFS2_TRACE
#  define TRACE
#endif
#include <trace.h>


#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif


#define fsmsg(f, args...)		//fprintf(STDERR, f , ## args )
#define debug(f, args...)		//fprintf(STDERR, f , ## args )

typedef char bool;

#define USE_INDEX
#define USE_INTENT


struct FLFS {
    MountEntry *me;
    offset_t total_size;
    offset_t block_size;		/* MAX( device read size, fblocksize ) */
    offset_t write_size;
    offset_t erase_size;

    offset_t cleaning_size;
    offset_t cleaningregion;		/* erase region currently being cleaned */

    lock_t lock;
    struct FileData *openforwrite;	/* list of files open for write */

#ifdef USE_INDEX
    offset_t idxoff;
    struct FSIndex *idxbuf;
    bool   idxdirty;
    int    nidxent;
#endif

    int block_shift;
    offset_t dirpos;			/* current active dir */
#define DIRPOS_UNKNOWN	-2
#define DIRPOS_INVALID	-1

    offset_t lastfreeoffset;         	/* cache location of last available space found */
    u_long flags;
    u_long diruid;

    int    ndirent;
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
static offset_t find_available(struct FLFS *);
static int get_open_dir_slot(struct FLFSBuf *);
static int release_block(struct FLFSBuf *);
static int deletefile_from(struct FLFSBuf *, struct FSDirEnt *);
static void learn_diruid(struct FLFS*);
static int get_index_type(struct FLFS *, offset_t);

#define DIRENT_IS_DELETED( e )	((e).attr == 0)
#define DIRENT_IS_VALID( e )	((e).attr & FLFS_FDAF_MASK == FDA_VALID)
#define DIRENT_IS_EMPTY( e )	((e).attr == FDA_EMPTY)


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
    int nidx = 0;

    struct FLFS *flfs = alloc(sizeof(struct FLFS));
    bzero(flfs, sizeof(struct FLFS));

    flfs->me  = me;
    me->fsdat = flfs;

    struct stat s;
    offset_t o[2];
    o[0] = o[1] = 0;
    fstat( me->fdev, &s );
    fioctl(me->fdev, IOC_FLINFO, (void*)o);

    flfs->total_size = s.size;
    flfs->write_size = o[0] ? o[0] : 1;
    flfs->erase_size = o[1];
    flfs->block_size = FBLOCKSIZE;
    flfs->flags      = s.flags;
    flfs->dirpos     = DIRPOS_UNKNOWN;

    if( flfs->write_size > flfs->block_size ) flfs->block_size = flfs->write_size;

    flfs->ndirent = (flfs->block_size - sizeof(struct FSDir)) / sizeof(struct FSDirEnt);

    flfs->cleaning_size  = flfs->erase_size;
    if( flfs->cleaning_size < flfs->block_size ) flfs->cleaning_size = flfs->block_size;
    flfs->cleaningregion = -1;

    int x = flfs->block_size;
    while(x>1){
        x >>= 1;
        flfs->block_shift ++;
    }


#ifdef USE_INDEX
    flfs->nidxent = flfs->block_size / sizeof(fs2_t);

    // make sure there at least 4 index blocks - so we can gc
    while( flfs->nidxent * flfs->block_size > flfs->total_size/4 )
        flfs->nidxent /= 2;

    nidx = flfs->nidxent;
    flfs->idxbuf  = alloc(flfs->block_size);
    flfs->idxoff  = -1;

    if( flfs->nidxent * flfs->block_size > flfs->cleaning_size )
        flfs->cleaning_size = flfs->nidxent * flfs->block_size;

#else

    if( (flfs->cleaning_size < 4096) && (flfs->total_size >= 12*1024) ){
        flfs->cleaning_size = 4096;
    }

    if( (flfs->cleaning_size < 2048) && (flfs->total_size >= 6*1024) ){
        flfs->cleaning_size = 2048;
    }

#endif

    while( (flfs->total_size / flfs->cleaning_size) > 64 && (flfs->cleaning_size < 64*1024) )
        flfs->cleaning_size *= 2;

    learn_diruid(flfs);

    if( flfs->diruid == 0 )
        flfs->diruid = random();

#if 0
    bootmsg("wsize %d, esize %d, csize %d, ndir %d, nidx %d\n", (int)flfs->write_size, (int)flfs->erase_size,
            (int)flfs->cleaning_size, (int)flfs->ndirent, nidx );
    bootmsg("dir uid %x, pos %x, lfo %x\n", (int)flfs->diruid, (int)flfs->dirpos, (int)flfs->lastfreeoffset);
    bootmsg("dir nl %d, sz %d, ent %d\n", FLFS_NAMELEN, sizeof(struct FSDir), sizeof(struct FSDirEnt));
#endif

    trace_init();
    return 0;
}

int
flfs2_unmount(MountEntry *me){
    struct FLFS * flfs = me->fsdat;

#ifdef USE_INDEX
    free(flfs->idxbuf, flfs->block_size);
#endif
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
    trace_crumb2("flfs2", "dwrite", (int)off, len);
    int r = fbwrite(flfs->me->fdev, buf, len, off);
    if( r < 0 )
        fsmsg("write %s @0x%x failed\n", flfs->me->name, off);
    trace_crumb1("flfs2", "/dwrite", r);
    return r;
}

static int
diskerase(struct FLFS *flfs, offset_t off, offset_t len){
    offset_t i;

    trace_crumb2("flfs2", "derase", (int)off, (int)len);

    if( flfs_erase_notneeded(flfs) ){
        int e = ALLONES;
        for(i=0; i<len; i += sizeof(int)){
            diskwrite(flfs, off + i, &e, sizeof(e));
        }
    }else{
        for(i=0; i<len; i += flfs->erase_size ){
            fioctl(flfs->me->fdev, IOC_ERASE, (void*)(off + i) );
        }
    }
    trace_crumb0("flfs2", "/derase");
}

static void
learn_diruid(struct FLFS *flfs){

    struct FSDir dir;

    offset_t off, xoff=0;
    u_long xuid=0;

    for(off=0; off<flfs->total_size; off+= flfs->block_size){
        int t = get_index_type(flfs, off);

        // first free block after best dir
        if( t == FCT_BLANK &&  !flfs->lastfreeoffset ) flfs->lastfreeoffset = off;
        if( t != FCT_DIR ) continue;

        diskread(flfs, off, &dir, sizeof(dir));

        if( dir.uid > xuid ){
            xuid = dir.uid;
            xoff = off;
        }

        if( dir.flag != FDT_ACTIVE ) continue;

        if( dir.uid > flfs->diruid ){
#ifdef FLFS_64BIT
            flfs->diruid = dir.uid >> 32;
#else
            flfs->diruid = dir.uid;
#endif
            flfs->dirpos = off;
            flfs->lastfreeoffset = 0;
        }
    }

    // no dirs with space. use best unusable
    if( flfs->diruid == 0 ){
        flfs->diruid = xuid;
        flfs->dirpos = xoff;
        flfs->lastfreeoffset = xoff;
    }
}


// QQQ - or scan all blocks for current highest on init, and ++
static fs2_t
uniqueid(struct FLFS *flfs){
#ifdef FLFS_64BIT
    return ((++ flfs->diruid) << 32) | random();
#else
    return ++ flfs->diruid;
#endif

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

    // remove from open file list
    struct FLFS * flfs = fd->flfs;

    sync_lock( &flfs->lock, "flfs.L" );

    if( fd->next ) fd->next->prev = fd->prev;
    if( fd->prev ) fd->prev->next = fd->next;

    if( flfs->openforwrite == fd )
        flfs->openforwrite = fd->next;

    fd->prev = fd->next = 0;

    sync_unlock( &flfs->lock );

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
#ifdef USE_INDEX

static inline offset_t
index_offset_for(struct FLFS *flfs, offset_t off){
    return off & ~ ((flfs->nidxent << flfs->block_shift) - 1);
}
static inline offset_t
index_pos_for(struct FLFS *flfs, offset_t off){
    return (off >> flfs->block_shift) & (flfs->nidxent - 1);
}
#endif

static int
flush_index(struct FLFS *flfs){

#ifdef USE_INDEX
    if( flfs->idxoff == -1 ) return 0;
    if( diskwrite(flfs, flfs->idxoff, flfs->idxbuf, flfs->block_size) <= 0 ) return -1;
    flfs->idxdirty = 0;
    debug("flush idx %x\n", (int)flfs->idxoff);
#endif
    return 0;
}

#ifdef USE_INDEX
static int
read_index(struct FLFS *flfs, offset_t off){
    off = index_offset_for(flfs, off);

    if( off == flfs->idxoff ) return 0;
    if( flfs->idxdirty ) flush_index(flfs);

    flfs->idxoff = -1;

    // debug("read idx %x\n", (int)off);
    if( diskread(flfs, off, flfs->idxbuf, flfs->block_size) <= 0 ) return -1;
    flfs->idxoff = off;

    return 0;
}
#endif

static int
update_index(struct FLFS *flfs, offset_t off, fs2_t type){

#ifdef USE_INDEX
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
#endif
    return 0;
}

static int
get_index_type(struct FLFS *flfs, offset_t off){

#ifdef USE_INDEX
    if( read_index(flfs, off) ) return FCT_ERROR;

    int pos = index_pos_for(flfs, off);
    fs2_t r = flfs->idxbuf->cktype[pos];

    if( r > 4 && r != ALLONES ){
        fsmsg("err? off %x pos %x, r = %x\n", (int)off, pos, r);
        hexdump(flfs->idxbuf, 80);
    }

    if( !pos ){
        if( r == FCT_BLANK )   return FCT_EMPTY_INDEX;
        if( r == FCT_DELETED ) return FCT_DELET_INDEX;
    }

    return r;
#else
    fs2_t r;

    if( diskread(flfs, off, &r, sizeof(r)) <= 0 ) return FCT_ERROR;

    return r;

#endif
}

/****************************************************************/
static int
update_intent(struct FLFS *flfs, offset_t off, fs2_t intent){
#ifdef USE_INTENT
    diskwrite(flfs, off + offsetof(struct FSChunk, intent), &intent, sizeof(intent));
#endif
}

/****************************************************************/

static void
fsck(struct FLFS *flfs){



}

/****************************************************************/

static void
revert_relocate_file(struct FLFSBuf *fb, offset_t newstart){
    struct FSChunk  *fc = (struct FSChunk*)fb->buffer;

    while(1){
        int t = get_index_type(fb->flfs, newstart);
        if( t == FCT_BLANK ) break;

        if( diskread(fb->flfs, newstart, fb->buffer, fb->flfs->block_size) <= 0 ) return;
        fb->offset = newstart;
        newstart = fc->next;
        release_block(fb);
    }
}


// are any of this file's blocks in the cleaning region?
static int
file_in_cleaning_region(struct FLFS *flfs, offset_t off){
    fs2_t noff = 0;

    while(1){
        if( (off & ~(flfs->cleaning_size - 1)) == flfs->cleaningregion )
            return 1;

        if( diskread(flfs, off + offsetof(struct FSChunk, next), &noff, sizeof(noff)) <= 0) return -1;
        if( noff == ALLONES ) return 0;
        off = noff;
    }
    return 0;
}

static int
relocate_file(struct FLFSBuf *fb, int de){
    struct FSDir *db = (struct FSDir*)fb->buffer;
    struct FSDirEnt dent = db->dir[de];	// preserve dirent
    struct FSChunk  *fc = (struct FSChunk*)fb->buffer;
    offset_t newstart = ALLONES, newnext = ALLONES, newcurr;
    offset_t oldcurr, oldnext;
    offset_t olddir = fb->offset;
    fs2_t intent = fb->offset + de;


    debug("reloc file %s\n", dent.name);

    if( dent.start != ALLONES ){
        newstart = newnext = find_available(fb->flfs);
        if( newstart == -1 ) return 0;
    }
    oldnext = dent.start;

    // copy data
    while(oldnext != ALLONES){
        oldcurr = oldnext;
        newcurr = newnext;

        if( diskread(fb->flfs, oldcurr, fb->buffer, fb->flfs->block_size) <= 0 ){
            revert_relocate_file(fb, newstart);
            return 0;
        }

        oldnext = fc->next;
        if( oldnext != ALLONES ){
            newnext = find_available(fb->flfs);
            if( newnext == -1 ){
                // device full. cannot relocate
                revert_relocate_file(fb, newstart);
                return 0;
            }
            fc->next = newnext;
        }

        // intent
        if( fc->type == FCT_FIRST )
            fc->intent = intent;

        if( diskwrite(fb->flfs, newcurr, fb->buffer, fb->flfs->block_size) <= 0 ){
                revert_relocate_file(fb, newstart);
                return 0;
        }
        update_index(fb->flfs, newcurr, fc->type);
    }

    // copy + update dir
    int nde = get_open_dir_slot(fb);
    if( nde == -1 ){
        // device full. cannot relocate
        revert_relocate_file(fb, newstart);
        return 0;
    }

    db->dir[nde] = dent;
    db->dir[nde].start = newstart;

    if( diskwrite(fb->flfs, fb->offset, fb->buffer, fb->flfs->block_size) <= 0 ){
        revert_relocate_file(fb, newstart);
        return 0;
    }

    // delete old
    if( diskread(fb->flfs, olddir, fb->buffer, fb->flfs->block_size) <= 0 ){
        revert_relocate_file(fb, newstart);
        return 0;
    }

    debug("delete old %s @ %x + %d\n", dent.name, dent.start, de);
    fb->offset = olddir;
    deletefile_from(fb, &db->dir[de]);

    if( newstart != ALLONES )
        update_intent(fb->flfs, newstart, 0);

    return 1;
}


static int
relocate_dir(struct FLFSBuf *fb){
    struct FSDir *db = (struct FSDir*)fb->buffer;
    offset_t newoff;
    int i,j;

    debug("reloc dir %x", (int)fb->offset);

    // prune deleted entries
    for(i=j=0; i<fb->flfs->ndirent; i++){
        if( DIRENT_IS_DELETED(db->dir[i]) )   continue;
        if( DIRENT_IS_EMPTY(db->dir[i]) )     continue;

        if( i != j )
            db->dir[j] = db->dir[i];

        j++;
    }

    if( j ){
        // clear the remaing direntries
        for(i=j; i<fb->flfs->ndirent; i++){
            memset(db->dir + i, 0xFF, sizeof(struct FSDirEnt));
        }

        db->intent = fb->offset;
        db->uid = uniqueid(fb->flfs);
        newoff = find_available(fb->flfs);
        debug(" -> %x", newoff);

        if( newoff == -1 ){
            // device full. cannot relocate
            return 0;
        }

        if( diskwrite(fb->flfs, newoff, fb->buffer, fb->flfs->block_size) <= 0){
            return 0;
        }

        update_index(fb->flfs, newoff, FCT_DIR);
    }

    debug("\n");

    // delete old
    release_block(fb);

    if( j )
        update_intent(fb->flfs, newoff, 0);

    return 1;
}

// should we clean this?
static int
should_do_level2(struct FLFS *flfs, offset_t region, int *nfile){
    offset_t off;
    int nerase=0, ntot=0, ndel=0, ndir=0;

    for(off=region; off<region+flfs->cleaning_size; off += flfs->block_size){
        int t = get_index_type(flfs, off);
        ntot ++;

        switch(t){
        case FCT_BLANK:
        case FCT_EMPTY_INDEX:
            nerase ++;
            break;
        case FCT_DELETED:
        case FCT_DELET_INDEX:
            ndel ++;
            break;
        case FCT_DIR:
            // ideally, we'd check the content of the dir,
            // but we'd need to allocate a buffer...
            ndir ++;
            break;
        case FCT_FIRST:
        case FCT_DATA:
            (*nfile) ++;
            break;
        }

        // debug("  %x => %x\n", (int)off, t);
    }
    debug("ne %d, nd %d, nf %d, nt %d\n", nerase, ndel, *nfile, ntot);
    if( nerase == ntot )   return 0; // all erased. leave it alone.
    if( ndel ) return 1;
    if( ndir > 1 ) return 1;

    // if we have only valid data - sometimes move it. for better wear-leveling
    if( (random() & 0xF) == 0 ) return 1;

    return 0;
}



// clean level 2 - relocate data + erase
//

static void
clean_level2_region(struct FLFS *flfs, offset_t region){
    offset_t off;
    struct FLFSBuf fb;
    int i, nfile=0;

    debug("gc/2? %x\n", (int)region);
    if( (flfs->erase_size > flfs->total_size/2) || (flfs->erase_size < 0) ) return 0;

    if( !should_do_level2(flfs, region, &nfile) ) return;

    fb.buffer = alloc(flfs->block_size);
    fb.flfs = flfs;
    flfs->cleaningregion = region;

    debug("gc/2...\n");

    struct FSDir *db = (struct FSDir*)fb.buffer;

    // look for files in the cleaning region - move them
    if( nfile ){
        for(off=0; off<flfs->total_size; off+= flfs->block_size){
            int t = get_index_type(flfs, off);
            debug("  %x -> %x\n", (int)off, t);
            if( t != FCT_DIR ) continue;
            if( diskread(flfs, off, fb.buffer, flfs->block_size) <= 0 ) continue;
            if( db->flag == FDT_DELETED ) continue;

            // iter all files.
            for(i=0; i<flfs->ndirent; i++){
                debug("  [%d]\n", i);
                if( DIRENT_IS_DELETED(db->dir[i]) )   continue;
                if( DIRENT_IS_EMPTY(db->dir[i]) )     continue;

                debug("  ? %x %x %s\n", (int)db->dir[i].attr, (int)db->dir[i].start, db->dir[i].name);
                int x = file_in_cleaning_region(flfs, db->dir[i].start);
                debug("  file %s x %d\n", db->dir[i].name, x);
                if( x == -1 ) break;	// error
                if( !x ) continue;	// not in region

                fb.offset = off;
                // move file somewhere else
                relocate_file(&fb, i);
                // dir buffer was overwritten - refetch
                if( diskread(flfs, off, fb.buffer, flfs->block_size) <= 0 ) break;
            }
        }
    }

    // look for dirs in the cleaning region - move or remove them
    // check directories after moving files, moving files may have emptied the dir
    int nactive=0;
    for(off=region; off<region + flfs->cleaning_size; off += flfs->block_size){
        int t = get_index_type(flfs, off);

        if( (t == FCT_FIRST) || (t == FCT_DATA) ) nactive ++;

        if( t != FCT_DIR ) continue;
        if( diskread(flfs, off, fb.buffer, flfs->block_size) <= 0 ) continue;

        if( db->flag == FDT_DELETED ) continue;

        debug("=> dir %x\n", (int)off);
        fb.offset = off;
        // move dir somewhere else
        if( !relocate_dir(&fb) ) nactive ++;
    }

    free(fb.buffer, flfs->block_size);

    if( !nactive ){
        debug("erasing\n");
        diskerase(flfs, region, flfs->cleaning_size);
#ifdef USE_INDEX
        flfs->idxoff = -1;
#endif
    }else{
        debug("nactive %d\n", nactive);
    }

    flfs->cleaningregion = -1;
    debug("/gc2\n");
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
        if( DIRENT_IS_EMPTY(db->dir[i]) )     return 0; /* end of entries */
        if( DIRENT_IS_DELETED(db->dir[i]) )   continue;

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
    fs2_t t;

    /* is it being cleaned ? */
    if( flfs->cleaningregion != -1 ){
        if( (pos & (flfs->cleaning_size - 1)) == flfs->cleaningregion ) return 0;
    }

    if( check_block_pending(flfs, pos) ) return 0;

    t = get_index_type(flfs, pos);
    debug(" [%x %d]", pos, t);
    if( t != FCT_BLANK ) return 0;

#ifdef USE_INDEX
    /* index says it is ok, verify */
    if( diskread(flfs, pos, &t, sizeof(t)) <= 0 ) return 0;
    if( t == FCT_BLANK ) return 1;

    /* index is out of wack - fix */
    update_index(flfs, pos, t);
#endif

    if( t == FCT_BLANK ) return 1;
    return 0;
}

static int
is_first_in_region(struct FLFS *flfs, offset_t off){

    if( flfs->cleaningregion != -1 ) return 0;
    if( (off & ~(flfs->cleaning_size - 1)) == off ) return 1;
    return 0;
}

static offset_t
search_available(struct FLFS *flfs){
    offset_t pos=flfs->lastfreeoffset;

    while( pos < flfs->total_size ){

        if( is_first_in_region(flfs, pos) )
            clean_level2_region(flfs, pos);

        if( is_available(flfs, pos) ){
            flfs->lastfreeoffset = pos;
            debug("got avail %x\n", (int)pos);
            return pos;
        }

        pos += flfs->block_size;
    }

    return -1;
}

static offset_t
find_available(struct FLFS *flfs){
    offset_t r;

    debug("find avail\n");
    r = search_available(flfs);
    if( r != -1 ) return r;

    flfs->lastfreeoffset = 0;
    r = search_available(flfs);
    if( r != -1 ) return r;

#if 0
    for(r=0; r<flfs->total_size; r+=flfs->cleaning_size)
        clean_level2_region(flfs, r);

    r = search_available(flfs);

    if(r == -1) PANIC("full!"); // XXX
#endif

    return r;
}


static int
release_block(struct FLFSBuf *fb){
    struct FSChunk *fc = (struct FSChunk*)fb->buffer;

    fc->type = FCT_DELETED;

    if( fb->flfs->write_size <= sizeof(fc->type) ){
        diskwrite(fb->flfs, fb->offset + offsetof(struct FSChunk, type), &(fc->type), sizeof(fc->type));
    }else{
        diskwrite(fb->flfs, fb->offset, fc, fb->flfs->block_size);
    }

    update_index(fb->flfs, fb->offset, FCT_DELETED);
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
    if( diskread(fb->flfs, offset, fb->buffer, fb->flfs->block_size) <= 0) return -1;
    if( dir->type != FCT_DIR )    return -1;
    if( dir->flag != FDT_ACTIVE ) return -1;

    for(i=0; i<fb->flfs->ndirent; i++){
        if( DIRENT_IS_EMPTY(dir->dir[i]) ){
            debug("dir slot: %x [%d]\n", (int)offset, i);
            return i;
        }
    }
}

static void
mark_dir_full(struct FLFSBuf *fb){
    struct FSDir *d = (struct FSDir*)fb->buffer;

    fb->flfs->dirpos = DIRPOS_INVALID;
    d->flag = FDT_FULL;
}

static int
get_open_dir_slot(struct FLFSBuf *fb){
    struct FLFS *flfs = fb->flfs;
    offset_t offset;

    // dirpos looks valid? check
    if( (flfs->dirpos != DIRPOS_UNKNOWN) && (flfs->dirpos != DIRPOS_INVALID) ){
        int i = get_open_dir_slot_from(fb, flfs->dirpos);

        if( i == flfs->ndirent - 1 ) mark_dir_full(fb);
        debug("dirpos %x -> %d\n",(int) flfs->dirpos, i);
        if( i >= 0 ) return i;
    }

    // dirpos invalid? search for existing dir
    if( flfs->dirpos != DIRPOS_INVALID ){
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
    dir->uid  = uniqueid(flfs);
    update_index(flfs, offset, FCT_DIR);

    debug("dir new %x -> 0\n", (int)offset);

    return 0;
}


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
    fd->attr      = de->attr & FLFS_ATTR_MASK;
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

    offset_t cleanme = (flfs->lastfreeoffset + flfs->cleaning_size - 1) & ~(flfs->cleaning_size - 1);
    cleanme &= flfs->total_size - 1;
    clean_level2_region(flfs, cleanme);

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


    update_index(flfs, ochunk, fc->type);
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
    de->attr = fd->attr | FDA_VALID;
    de->filelen = fd->filelen;
    de->ctime = get_time();
    de->start = fd->filestart;

    // write
    diskwrite(fd->flfs, fb.offset, fd->buffer, fd->bufsize);

    // mark as finished
    update_intent(flfs, fd->filestart, 0);

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

    trace_crumb0("flfs2", "close");
    if( fd->how == FDH_WRITE ){
        flush_final_data(fd);
        flush_final_meta(fd);
    }

    free_filedata(fd);
    free(f, sizeof(FILE));
    trace_crumb0("flfs2", "/close");

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

    if( (fc->type != FCT_DATA) && (fc->type != FCT_FIRST) && (fc->type != FCT_DELETED) ){
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

    trace_crumb1("flfs2", "open", how);
    if( *how == 'r' ){
        f = flfs2_open_r(flfs, name);
    }else{
        f = flfs2_open_w(flfs, name);
    }

    trace_crumb0("flfs2", "/open");
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
    s->mode    = fd->attr & FLFS_ATTR_MASK;
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

    for(offset=0; offset<flfs->total_size; offset += flfs->block_size){

        fs2_t t = get_index_type(flfs, offset);

        if( (t != FCT_BLANK) && (t != FCT_EMPTY_INDEX) )
            totalloc += flfs->block_size;

        if( t != FCT_DIR ) continue;

        if( diskread(flfs, offset, buffer, flfs->block_size) <= 0 ){
            break;
        }

        if(how & LSHOW_EXT){
            printf("dir %x\n", (int)offset);
        }

        for(i=0; i<flfs->ndirent; i++){
            struct FSDirEnt *d = dir->dir + i;

            if( DIRENT_IS_DELETED(*d) ) continue;
            if( DIRENT_IS_DELETED(*d) && !(how & LSHOW_EXT) ) continue;

            if(how & LSHOW_EXT){
                printf("%2d ", i);
                if( DIRENT_IS_DELETED(*d) )
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
                printf(" %-20T %3d    %7d %s\n", d->ctime, (int)d->attr & FLFS_ATTR_MASK, d->filelen, d->name);

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

    diskerase( flfs, 0, flfs->total_size );

#ifdef USE_INDEX
    memset( flfs->idxbuf, 0xFF, flfs->block_size );
    flfs->idxdirty = 0;
#endif
    flfs->dirpos = DIRPOS_INVALID;
    flfs->diruid = random();
    flfs->lastfreeoffset = 0;

    sync_unlock( &flfs->lock );

    free(buffer, flfs->block_size);
    fflush( me->fdev );
    return 0;
}

static void
check_dir_all_deleted(struct FLFS *flfs, offset_t off, struct FSDir *d){
    int i;

    for(i=0; i<flfs->ndirent; i++){
        if( DIRENT_IS_DELETED(d->dir[i]) ) return ;
    }

    d->flag = FDT_DELETED;
    d->type = FCT_DELETED;
    update_index(flfs, off, FCT_DELETED);
}

static void
delete_dir_entry(struct FLFS *flfs, offset_t off, struct FSDir *d, struct FSDirEnt *de){

    debug("rm dirent %x; buf %x de %x\n", (int)off, d, de);
    de->attr = FDA_DELETED;
    check_dir_all_deleted(flfs, off, d);

    diskwrite(flfs, off, d, flfs->block_size);
}

static int
deletefile_from(struct FLFSBuf *fb, struct FSDirEnt *de){
    struct FSChunk *fc;
    struct FSDir *dir;

    dir = (struct FSDir *)fb->buffer;
    fc  = (struct FSChunk*)fb->buffer;

    /* delete dir entry */
    offset_t next = de->start;
    delete_dir_entry(fb->flfs, fb->offset, dir, de);

    offset_t offset = next;

    while(1){

        if( diskread(fb->flfs, offset, fb->buffer, fb->flfs->block_size) <= 0 ){
            return -1;
        }

        next = fc->next;
        fb->offset = offset;
        release_block(fb);
        offset = next;

        if( offset == ALLONES || offset == 0 ){
            break;
        }
    }

    return 0;
}

static int
flfs2_deletefile(MountEntry *me, const char *name){
    struct FLFS *flfs = me->fsdat;
    struct FSDirEnt *de;

    char *buffer;
    int err=0;

    buffer = alloc(flfs->block_size);
    struct FLFSBuf fb = {.flfs = flfs, .buffer = buffer};
    de  =  findfile(&fb, name);

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

    err = deletefile_from( &fb, de );
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
    ne->attr  = attr | (ALLONES & ~FLFS_ATTR_MASK);
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

            if( DIRENT_IS_DELETED(*d) ) continue;
            if( DIRENT_IS_EMPTY(*d) )   continue;

            if( !(d->attr & FFA_HIDDEN)
                && !fnmatch(pattern, d->name, 0)){
                /* found it */

                sync_unlock( &flfs->lock );
                rv = (fnc)(d->name, args);
                sync_lock( &flfs->lock, "flfs.L" );
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

#if 1// XXX def KTESTING

DEFUN(dumpflfs2, "dump flfs2")
{
    if( argc < 2 ) return 0;

    MountEntry *me = find_mount(argv[1]);
    if( !me ) return 0;

    struct FLFS *flfs = me->fsdat;
    char *buffer = alloc(flfs->block_size);

    printf("sizeof     %x\n",  sizeof(fs2_t));
    printf("total_size %qx\n", flfs->total_size);
    printf("block_size %qx\n", flfs->block_size);
    printf("write_size %qx\n", flfs->write_size);
    printf("erase_size %qx\n", flfs->erase_size);
    printf("clean_size %qx\n", flfs->cleaning_size);
    printf("clean_regn %qx\n", flfs->cleaningregion);
    printf("dirpos     %qx\n", flfs->dirpos);
    printf("diruid     %qx\n", flfs->diruid);
    printf("ndirent    %x\n",  flfs->ndirent);
    printf("lastfree   %qx\n", flfs->lastfreeoffset);

#ifdef USE_INDEX
    printf("idxoff     %qx\n", flfs->idxoff);
    printf("nidxent    %x\n",  flfs->nidxent);
#endif


    offset_t off;

    for(off=0; off<flfs->total_size; off+= flfs->block_size){
        int t = get_index_type(flfs, off);

        int repeat=1;
        while( t == get_index_type(flfs, off + repeat * flfs->block_size) )
            repeat ++;

        printf(" %08x * %02x ", (int)off, repeat);
        switch(t){
        case FCT_BLANK:		printf("blank\n"); break;
        case FCT_DELETED:	printf("delet\n"); break;
        case FCT_FIRST:		printf("file1\n"); break;
        case FCT_DATA:		printf("file+\n"); break;
        case FCT_DIR:		printf("dir");     break;
        case FCT_INDEX:		printf("index\n"); break;
        case FCT_EMPTY_INDEX:	printf("index/empty\n"); break;
        case FCT_DELET_INDEX:	printf("index/deled\n"); break;
        default:		printf("<%x>\n", t);
        }

        if( t == FCT_DIR ){
            int i;
            struct FSDir *dir = (struct FSDir*)buffer;

            diskread(flfs, off, buffer, flfs->block_size);

            switch( dir->flag ){
            case FDT_FULL:    printf("/full"); break;
            case FDT_DELETED: printf("/used"); break;
            default:          printf("/actv"); break;
            }

            printf("    id=%x; %x\n", dir->uid, dir->intent);

            for(i=0; i<flfs->ndirent; i++){
                struct FSDirEnt *d = dir->dir + i;
                if( DIRENT_IS_EMPTY(*d) ){
                    continue;
                }
                if( DIRENT_IS_DELETED(*d) )
                    printf("    %2d %8x ---- %s\n", i, d->start, d->name);
                else
                    printf("    %2d %8x %04x %s\n", i, d->start, d->attr & FLFS_ATTR_MASK, d->name);
            }
        }

        off += (repeat - 1) * flfs->block_size;
    }

    free(buffer, flfs->block_size);
    return 0;
}

#endif

