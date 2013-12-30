/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function:

  $Id$

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
#include <flfs.h>
#include <locks.h>
#include <ioctl.h>
#include <userint.h>


#ifndef ENOUGHALREADYHEURISTIC
#  define ENOUGHALREADYHEURISTIC	64
#endif

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#define NEEDERASE(fd)			((fd)->cnkstat != FCT_BLANK)

/* GCC varargs macro */
#define fsmsg(f, args...)		fprintf(STDERR, f , ## args )


struct FLFS {
    MountEntry *me;
    u_long totalsize;              /* total space */
    u_long lastfreeoffset;         /* cache location of last available space found */
    u_long pblksize;
    u_long fblksize;
    u_long flags;
};


struct FileData {
    int how;
#define FDH_READ	0
#define FDH_WRITE	1

    struct FLFS	*flfs;
    long long ctime;
    u_long attr;
    u_long filestart;		/* offset of start of 1st chunk of file */
    u_long filepos;		/* current offset in file */
    u_long filelen;		/* length of file */

    u_long cnkstart;		/* offset of start of chunk */
    u_long cnkpos;		/* current offset in chunk */
    u_long cnkdlen;		/* length of data portion of chunk */
    u_long cnktlen;		/* total length of chunk */
    u_long cnknext;
    u_long cnkstat;

    int bufpos;			/* current offset in buffer */
    int buflen;			/* size of data currently in buffer */

    struct FileData *next, *prev;	/* open for writing list */
    char *buffer;
    char *buffer2;

};

int flfs_putchar(FILE*, char);
int flfs_getchar(FILE*);
int flfs_close(FILE*);
int flfs_noop(FILE*);
int flfs_status(FILE*);
int flfs_read(FILE*, char*, int);
int flfs_write(FILE*, const char*, int);
int flfs_stat(FILE *, struct stat*);

const struct io_fs flfs_iofs = {
    flfs_putchar,
    flfs_getchar,
    flfs_close,
    flfs_noop,		/* flush */
    flfs_status,
    flfs_read,
    flfs_write,
    0, 0, 		/* bread, bwrite */
    0, 0,		/* seek, tell */
    flfs_stat
};


static lock_t filesystemlock = 0;		/* we need to lock areas when the fs is in an inconsistant state */
static struct FileData *openforwrite = 0;	/* list of files open for write */

int
flfs_init(MountEntry *me){

    struct FLFS *flfs = alloc(sizeof(struct FLFS));

    flfs->me  = me;
    me->fsdat = flfs;

    struct stat s;
    fstat( me->fdev, &s );
    flfs->pblksize  = s.blksize;
    flfs->totalsize = s.size;
    flfs->fblksize  = FBLOCKSIZE;
    flfs->flags     = s.flags;
    flfs->lastfreeoffset = 0;

    return 0;
}

int
flfs_unmount(MountEntry *me){
    struct FLFS * flfs = me->fsdat;

    free(flfs, sizeof(struct FLFS));
}

static int
diskread(struct FLFS *flfs, u_long off, char *buf, int len){
    int i;

    return fbread(flfs->me->fdev, buf, len, off);
}

static int
diskwrite(struct FLFS *flfs, u_long off, const char *buf, int len, int erasep){
    int i;

    if( flfs->flags & SSF_READONLY ){
        fsmsg("write to read-only device (%s)\n", flfs->me->name);
        return -1;
    }

    /* erase device */
    if( erasep && !(flfs->flags & SSF_NOERASE) ){
        if( flfs->pblksize > flfs->fblksize ){
            /* if pblk is larger than fblk, then we need to:
               read pblk
               erase it
               write back valid portions of it
            */

            if( flfs->flags & SSF_BLKWRITE ){
                kprintf("config data for %s is invalid and should be corrected\n",
                        flfs->me->name);
                PANIC("pblksz > fblksz not permitted with blkwrite devices");
            }

            /* read pblk */
            char * tbuf = alloc(flfs->pblksize);
            int toff = off & ~(flfs->pblksize-1);

            if( fbread(flfs->me->fdev, tbuf, flfs->pblksize, toff) != flfs->pblksize ){
                DIAG("read %s,%d failed\n", flfs->me->name, toff);
                free(tbuf, flfs->pblksize);
                return -1;
            }

            /* erase pblk, copy data, write back */
            fioctl(flfs->me->fdev, IOC_ERASE, (void*)toff);
            memcpy(tbuf + (off - toff), buf, len);

            i = fbwrite(flfs->me->fdev, tbuf, flfs->pblksize, toff);
            free(tbuf, flfs->pblksize);

            if( i != flfs->pblksize ){
                DIAG("rewrite %s,%d failed\n", flfs->me->name, toff);
                return -1;
            }
            return i;

        }else{
            /* fblk may be several pblks, erase them all */
            for(i=0; i< flfs->fblksize/flfs->pblksize; i++){
                fioctl(flfs->me->fdev, IOC_ERASE, (void*)( off + i * flfs->pblksize ) );
            }
        }
    }

    return fbwrite(flfs->me->fdev, buf, len, off);
}


static int
chunklength(struct FLFS *flfs, int offset){
    struct FileData *fd;
    u_long l;

    sync_lock( &filesystemlock, "flfs.L" );
    for(fd=openforwrite; fd; fd=fd->next){
        if( fd->flfs == flfs &&
            ( fd->cnkstart == offset
              || fd->filestart == offset ) ){	/* to catch ssf_blkwrite devs */

            sync_unlock( &filesystemlock );
            return fd->cnktlen;
        }
    }

    sync_unlock( &filesystemlock );
    kprintf("filesystem %s is corrupt\n", flfs->me->name);
    PANIC( "unknown chunk length" );
    return 0;
}

/*
  find file

  passed buffer ought be large enough for 1 disk block
*/

static int
findfile(struct FLFS *flfs, const char *name, char *buffer, int buflen){
    struct FSFile  *ff;
    struct FSChunk *fc;
    int nblnk=0;
    int offset, tlen, n;

    /* strip off devicename */
    name = basenameoffile(name);

    offset = 0;
    fc = (struct FSChunk *)buffer;
    ff = (struct FSFile  *)(buffer + sizeof(struct FSChunk));

    while(1){
        if( diskread(flfs, offset, buffer, flfs->fblksize) <= 0 ){
            fsmsg("read %s @%d failed (line %d)\n", flfs->me->name, offset, __LINE__);
            return -1;
        }

        if( fc->type == FCT_FILE && !strcmp(name, ff->name)){
            /* found it */
            break;
        }

        if( fc->type == FCT_BLANK || fc->type == FCT_UNUSED ){
            offset += flfs->fblksize;
            nblnk ++;
        }else{
            nblnk = 0;
            tlen = fc->totlen;
            if( tlen == 0xFFFFFFFF || tlen == 0 )
                offset += chunklength( flfs, offset );
            else
                offset += tlen;
        }

        if( offset >= flfs->totalsize || nblnk >= ENOUGHALREADYHEURISTIC ){
            /* reached end, not found */
            return -1;
        }
    }

    return offset;
}


FILE *
flfs_open_r(MountEntry *me, const char *name){
    struct FLFS *flfs = me->fsdat;
    struct FileData *fd, *ofd;
    struct FSChunk *fc;
    struct FSFile *ff;
    FILE *f;
    int offset;

    fd = alloc(sizeof(struct FileData));
    /* search disk for file */

    fd->buffer = alloc( flfs->fblksize );
    offset = findfile(flfs, name, fd->buffer, flfs->fblksize);
    if( offset == -1 ){
        /* file not found */
        free(fd->buffer, flfs->fblksize);
        free(fd, sizeof(struct FileData));
        return 0;
    }
    /* make sure it is not open for writing */
    sync_lock( &filesystemlock, "flfs.L" );
    for(ofd=openforwrite; ofd; ofd=ofd->next){
        if( flfs == ofd->flfs && offset == ofd->filestart ){
            sync_unlock( &filesystemlock );
            free(fd->buffer, flfs->fblksize);
            free(fd, sizeof(struct FileData));
            fsmsg("file is already open for writing\n");
            return 0;
        }
    }

    if( diskread(flfs, offset, fd->buffer, flfs->fblksize) <= 0 ){
        sync_unlock( &filesystemlock );
        free(fd->buffer, flfs->fblksize);
        free(fd, sizeof(struct FileData));
        DIAG("read %s,%d failed (line %d)\n", flfs->me->name, offset, __LINE__);
        return 0;
    }
    sync_unlock( &filesystemlock );

    fc = (struct FSChunk *)fd->buffer;
    ff = (struct FSFile  *)(fd->buffer + sizeof(struct FSChunk));

    fd->how       = FDH_READ;
    fd->ctime     = ff->ctime;
    fd->attr      = ff->attr;
    fd->flfs      = flfs;

    fd->filestart = offset;
    fd->filelen   = ff->filelen;
    fd->filepos   = 0;

    fd->cnkstart  = offset;
    fd->cnkpos    = sizeof(struct FSChunk) + sizeof(struct FSFile);
    fd->cnkdlen   = fc->cnklen;
    fd->cnktlen   = fc->totlen;
    fd->cnknext   = fc->next;

    fd->bufpos    = 0;
    fd->buflen    = 0;

    f = alloc(sizeof(FILE));
    finit( f );
    f->flags = 0;
    f->fs = &flfs_iofs;
    f->d  = fd;

    return f;
}

FILE *
flfs_open_w(MountEntry *me, const char *name){
    struct FLFS *flfs = me->fsdat;
    struct FSFile *ff;
    struct FileData *fd;
    FILE *f;
    int offset = 0;
    int attr = 0;
    int n;

    f  = alloc(sizeof(FILE));
    fd = alloc(sizeof(struct FileData));

    fd->flfs    = flfs;
    fd->buffer  = alloc( flfs->fblksize );
    fd->buffer2 = 0;

    if( findfile(flfs, name, fd->buffer, flfs->fblksize) != -1 ){
        /* delete, rename, ... */

        int n=1;
        char nname[FLFS_NAMELEN], oname[FLFS_NAMELEN], *s;
        struct stat st;
        FILE *fx;

        /* preserve attr */
        fx = flfs_open_r(me, name);
        fstat(fx, &st);
        fclose(fx);
        attr = st.mode;

#ifdef FLFS_DELETEFILE_ON_CREAT
        if( flfs_deletefile(me, name) == -1 ){
            /* read-only file */
            free(f,  sizeof(FILE));
            free(fd, sizeof(struct FileData));
            return 0;
        }
#else
#    ifdef FLFS_RENAMEFILE_ON_CREAT

        strncpy(oname, name, FLFS_NAMELEN-1);
        oname[FLFS_NAMELEN] = 0;
        s = (char*)strrchr(oname, ';');	/* strip off existing ;n */
        if( s ) *s = 0;

        while(1){
            snprintf(nname, FLFS_NAMELEN, "%s;%d", oname, n);
            if( findfile(flfs, nname, fd->buffer, flfs->fblksize) == -1 ){
                renamefile(name, nname);
                break;
            }
            n++;
        }
#    endif
        /* otherwise we keep both files with the same name */
#endif
    }

    /* strip device from name */
    name = basenameoffile(name);

    f->flags = 0;
    f->fs    = &flfs_iofs;
    f->d     = fd;
    fd->how  = FDH_WRITE;

    /* add to open file list */
    sync_lock( &filesystemlock, "flfs.L" );
    fd->cnkstart  = 0xFFFFFFFF;
    fd->filestart = 0xFFFFFFFF;
    fd->next = openforwrite;
    fd->prev = 0;
    openforwrite = fd;
    sync_unlock( &filesystemlock );

    offset = findavailable(f, FCT_FILE);
    if( offset == -1 ){
        flfs->lastfreeoffset = 0;
        offset = findavailable(f, FCT_FILE);
        if( offset == -1 ){
            fsmsg("filesystem %s is full\n", me->name);
            free(f,  sizeof(FILE));
            free(fd, sizeof(struct FileData));

            /* remove from open file list */
            sync_lock( &filesystemlock, "flfs.L" );
            if( fd->next )
                fd->next->prev = fd->prev;
            if( fd->prev )
                fd->prev->next = fd->next;
            if( openforwrite == fd )
                openforwrite = fd->next;
            sync_unlock( &filesystemlock );

            return 0;
        }
    }

    ff = (struct FSFile  *)(fd->buffer + sizeof(struct FSChunk));

    ff->ctime   = get_time();
    ff->filelen = 0xFFFFFFFF;
    ff->attr    = attr;
    strncpy(ff->name, name, sizeof(ff->name));

    fd->attr      = attr;
    fd->filelen   = 0;
    fd->filepos   = 0;
    fd->filestart = offset;

    return f;
}

int
flfs_close(FILE *f){
    struct FileData *fd;
    struct FLFS *flfs;
    int i;

    fd   = f->d;
    flfs = fd->flfs;

    if( fd->how == FDH_WRITE ){

        if( flfs->flags & SSF_BLKWRITE ){
            struct FSChunk *fc = (struct FSChunk *) fd->buffer;
            struct FSFile  *ff;

            /* chunk len == bufferlen == fblksize */
            fc->cnklen = fd->cnkpos;
            fc->totlen = flfs->fblksize;

            /* file header */
            if( fd->buffer2 ){
                ff = (struct FSFile *)( fd->buffer2 + sizeof(struct FSChunk) );
            }else{
                ff = (struct FSFile *)( fd->buffer + sizeof(struct FSChunk) );
            }


            ff->filelen = fd->filelen;

            if( diskwrite(flfs, fd->cnkstart, fd->buffer, flfs->fblksize, NEEDERASE(fd)) <= 0 ){
                fsmsg("write %s,%d failed (line %d)\n", flfs->me->name, fd->cnkstart, __LINE__);
            }

            if( fd->buffer2 ){
                /* XXX neederase is wrong - (not that it matters) */
                if( diskwrite(flfs, fd->filestart, fd->buffer2, flfs->fblksize, NEEDERASE(fd)) <= 0 ){
                    fsmsg("write %s,%d failed (line %d)\n", flfs->me->name, fd->filestart, __LINE__);
                }
                free(fd->buffer2, flfs->fblksize);
            }

        }else{
            /* flush buffer */
            if( fd->bufpos ){
                int a = fd->cnkstart + fd->cnkpos;
                if( fd->cnkpos ) a --;
                a &= ~(fd->flfs->fblksize-1);

                if( diskwrite(flfs, a, fd->buffer, flfs->fblksize, NEEDERASE(fd)) <= 0 ){
                    fsmsg("write %s,%d failed (line %d)\n", flfs->me->name, a, __LINE__);
                }
                fd->bufpos = 0;
            }

            /* update chunk header on disk, possibly chopping it */
            if( diskwrite(flfs, fd->cnkstart + offsetof(struct FSChunk, cnklen),
                          (char*)&fd->cnkpos, sizeof(fd->cnkdlen), 0) <= 0 ){
                fsmsg("write %s,%d failed (line %d)\n", flfs->me->name,
                      fd->cnkstart + offsetof(struct FSChunk, cnklen), __LINE__);
            }

            /* leave next == 0xFFFFFFFF */

            i = (fd->cnkpos + flfs->fblksize - 1) & ~(flfs->fblksize-1);
            if( diskwrite(flfs, fd->cnkstart + offsetof(struct FSChunk, totlen),
                          (char*)&i, sizeof(fd->cnktlen), 0) <= 0 ){
                fsmsg("write %s,%d failed (line %d)\n", flfs->me->name,
                      fd->cnkstart + offsetof(struct FSChunk, totlen));
            }
            if( i != fd->cnktlen ){
                /* chop - if it was uninitialized, leave it so */
                /* otherwise erase it */
                if( fd->cnkstat != FCT_BLANK && fd->cnkstat != FCT_UNUSED ){
                    memset(fd->buffer, 0xFF, flfs->fblksize);
                    if( diskwrite(flfs, fd->cnkstart + i, fd->buffer, flfs->fblksize, 1) <= 0 ){
                        fsmsg("write %s,%d failed (line %d)\n", flfs->me->name,
                              fd->cnkstart + i, __LINE__);
                    }
                }
            }

            /* update file header on disk */
            if( diskwrite(flfs, fd->filestart + sizeof(struct FSChunk) + offsetof(struct FSFile, filelen),
                          (char*)&fd->filelen, sizeof(fd->filelen), 0) <= 0 ){
                fsmsg("write %s,%d failed (line %d)\n", flfs->me->name,
                      fd->filestart + sizeof(struct FSChunk) + offsetof(struct FSFile, filelen),
                      __LINE__);
            }
        }

        fflush( flfs->me->fdev );

        /* remove from open file list */
        sync_lock( &filesystemlock, "flfs.L" );
        if( fd->next )
            fd->next->prev = fd->prev;
        if( fd->prev )
            fd->prev->next = fd->next;
        if( openforwrite == fd )
            openforwrite = fd->next;
        sync_unlock( &filesystemlock );
    }

    free(fd->buffer, flfs->fblksize);
    free( fd, sizeof(struct FileData));
    free( f, sizeof(FILE));

    return 0;
}

/*
  read file
*/

int
flfs_read(FILE* f, char* buf, int len){
    struct FileData *fd;
    struct FLFS *flfs;
    int rd;
    int l;

    rd = 0;
    fd = f->d;
    flfs = fd->flfs;

    if( len > fd->filelen - fd->filepos ){
        /* attempt to read past EOF - truncate */
        len = fd->filelen - fd->filepos;
    }

    while(len){

        if( fd->cnkpos >= fd->cnkdlen + sizeof(struct FSChunk) ){
            /* done this chunk, on to the next */
            struct FSChunk *fc;

            if( fd->cnknext == 0xFFFFFFFF )
                PANIC("corrupt chunk chain");

            if( diskread(flfs, fd->cnknext, fd->buffer, flfs->fblksize) <= 0 ){
                DIAG("read %s,%d failed\n", flfs->me->name, fd->cnknext);
                return -1;
            }
            fc = (struct FSChunk *)fd->buffer;
            fd->cnkstart = fd->cnknext;
            fd->cnkpos   = fd->bufpos = sizeof(struct FSChunk);
            fd->cnkdlen  = fc->cnklen;
            fd->cnktlen  = fc->totlen;
            fd->cnknext  = fc->next;
            fd->buflen   = flfs->fblksize;

            if( fd->cnktlen == 0xFFFFFFFF )
                PANIC("corrupt chunk");
        }

        if( fd->bufpos >= fd->buflen ){
            /* read more of this chunk */
            if( diskread(flfs, fd->cnkstart + fd->cnkpos, fd->buffer, flfs->fblksize) <= 0 ){
                DIAG("read %s,%d failed\n", flfs->me->name, fd->cnkstart + fd->cnkpos);
                return -1;
            }
            fd->bufpos = 0;
            fd->buflen = flfs->fblksize;
        }

        if( len <= fd->buflen - fd->bufpos ){
            /* the rest of what the caller wants */
            l = len;
        }else{
            /* the remainder of this block */
            l = fd->buflen - fd->bufpos;
        }

        /* but not more than is available in this chunk */
        if( l > fd->cnkdlen - fd->cnkpos + sizeof(struct FSChunk) ){
            l = fd->cnkdlen - fd->cnkpos + sizeof(struct FSChunk);
        }

        memcpy(buf, fd->buffer + fd->bufpos, l);
        len -= l;
        buf += l;
        fd->bufpos  += l;
        fd->filepos += l;
        fd->cnkpos  += l;
        rd += l;
    }

    if( fd->filepos >= fd->filelen ){
        /* reached eof */
        f->flags |= F_EOF;
    }

    return rd;
}

/* find an unused or free block
   unused space is prefered (it doesn't need to be erased)
*/

int
findavailable(FILE *f, int type){
    struct FSFile *ff;
    struct FSChunk *fc;
    struct FileData *fd, *ofd;
    struct FLFS *flfs;
    int freed = -1;
    int offset;
    int cstart;
    int tlen;
    int i;

    fd   = f->d;
    flfs = fd->flfs;
    offset = flfs->lastfreeoffset;

    fc = (struct FSChunk *)fd->buffer;
    ff = (struct FSFile  *)(fd->buffer + sizeof(struct FSChunk));

    while(1){
        if( diskread(flfs, offset, fd->buffer, flfs->fblksize) <= 0 ){
            DIAG("read %s,%d failed\n", flfs->me->name, offset);
            if( freed != -1 )
                break;
            else{
                flfs->lastfreeoffset = 0;
                return -1;
            }
        }

        if( fc->type == FCT_DELETED && freed == -1  && !(flfs->flags & SSF_BIGERASE) ){
            /* a freed chunk, make note and keep looking for unused space */
            freed = offset;
        }

        if( fc->type == FCT_BLANK || fc->type == FCT_UNUSED ){
            /* unused space */
            break;
        }

    lookagain:
        tlen = fc->totlen;
        if( tlen == 0xFFFFFFFF || tlen == 0 )
            offset += chunklength( flfs, offset );
        else
            offset += tlen;

        if( offset >= flfs->totalsize ){
            /* end of space */
            if( freed != -1 )
                break;
            else{
                flfs->lastfreeoffset = 0;
                return -1;
            }
        }
    }

    if( type == FCT_CONT ){
        cstart = fd->cnkstart + fd->cnktlen;
    }

    if( fc->type != FCT_BLANK && fc->type != FCT_UNUSED ){
        /* reused space */
        offset = freed;
        diskread(flfs, offset, fd->buffer, flfs->fblksize);
        tlen = fc->totlen;
    }else{
        /* virgin space */
        tlen = flfs->fblksize;
    }

    /* make sure it is unused */
    sync_lock( &filesystemlock, "flfs.L" );
    for(ofd=openforwrite; ofd; ofd=ofd->next){
        if( fd->flfs == ofd->flfs &&
            ( ofd->cnkstart <= offset && ofd->cnkstart + ofd->cnktlen > offset
              || ofd->filestart == offset )
            ){
            /* someone else has this chunk */
            sync_unlock( &filesystemlock );
            freed = -1;
            goto lookagain;
        }
    }

    if( type == FCT_CONT && cstart == offset
        && !(flfs->flags & SSF_BLKWRITE) ){
        /* contiguous continuation - splice */

        fd->cnktlen += tlen;
        fd->cnkdlen += tlen;
        fd->cnkstat  = fc->type;
        fd->bufpos   = 0;

        sync_unlock( &filesystemlock );
        return fd->cnkstart;

    }

    fd->cnkstart = offset;
    fd->cnktlen  = tlen;
    fd->cnkstat  = fc->type;
    fd->cnkdlen  = fd->cnktlen - sizeof(struct FSChunk);
    fd->cnknext  = 0;
    sync_unlock( &filesystemlock );

    fc->type    = type;
    fc->totlen  = 0xFFFFFFFF;
    fc->cnklen  = 0xFFFFFFFF;
    fc->next    = 0xFFFFFFFF;
    fd->cnkpos  = sizeof(struct FSChunk);
    fd->bufpos  = sizeof(struct FSChunk);
    fd->buflen  = flfs->fblksize;

    if( type == FCT_FILE ){
        fd->cnkpos += sizeof(struct FSFile);
        fd->bufpos += sizeof(struct FSFile);
    }

    flfs->lastfreeoffset = offset;

    return offset;
}


int
flfs_write(FILE* f, const char* buf, int len){
    struct FileData *fd;
    int l;
    int wrt = 0;
    int offset;

    fd = f->d;

    while(len){

        if( fd->flfs->flags & SSF_BLKWRITE ){
            /* chunk len == bufferlen == fblksize */

            if( fd->bufpos >= fd->buflen ){
                struct FSChunk *fc;
                char *buffer;
                int off = fd->cnkstart;

                buffer = alloc(fd->buflen);
                memcpy(buffer, fd->buffer, fd->buflen);
                fc = (struct FSChunk *)buffer;
                fc->cnklen = fd->cnkpos;
                fc->totlen = fd->flfs->fblksize;

                /* get next chunk */
                if( findavailable(f, FCT_CONT) == -1 ){
                    fd->flfs->lastfreeoffset = 0;
                    if( findavailable(f, FCT_CONT) == -1 ){
                        /* disk full */
                        fsmsg("filesystem %s is full\n", fd->flfs->me->name);
                        return -1;
                    }
                }

                fc->next   = fd->cnkstart;

                if( off == fd->filestart ){
                    fd->buffer2 = buffer;
                }else{
                    diskwrite(fd->flfs, off, buffer, fd->flfs->fblksize, NEEDERASE(fd));
                    free(buffer, fd->buflen);
                }
            }

        }else{
            if( fd->bufpos >= fd->buflen ){
                int a = fd->cnkstart + fd->cnkpos;
                if( fd->cnkpos ) a --;
                a &= ~(fd->flfs->fblksize-1);

                /* dump buffer to flfsice */
                diskwrite(fd->flfs, a, fd->buffer, fd->flfs->fblksize, NEEDERASE(fd));
                fd->bufpos = 0;
            }

            if( fd->cnkpos >= fd->cnktlen ){
                /* end of chunk */
                /* update hdr of current chunk */
                offset = fd->cnkstart;
                diskwrite(fd->flfs, fd->cnkstart + offsetof(struct FSChunk, cnklen),
                          (char*)&fd->cnkdlen, sizeof(fd->cnkdlen), 0);
                diskwrite(fd->flfs, fd->cnkstart + offsetof(struct FSChunk, totlen),
                          (char*)&fd->cnktlen, sizeof(fd->cnktlen), 0);

                /* does buffer need to be flushed? */
                /* (should never happen) */
                if( fd->bufpos )
                    PANIC("chunk not aligned with buffer");

                /* get next chunk */
                if( findavailable(f, FCT_CONT) == -1 ){
                    fd->flfs->lastfreeoffset = 0;
                    if( findavailable(f, FCT_CONT) == -1 ){
                        /* disk full */
                        fsmsg("filesystem %s is full\n", fd->flfs->me->name);
                        return -1;
                    }
                }

                /* update hdr of current chunk */
                if( offset != fd->cnkstart ){
                    diskwrite(fd->flfs, offset + offsetof(struct FSChunk, next),
                              (char*)&fd->cnkstart, sizeof(fd->cnkstart), 0);
                }
            }
        }

        l = len;

        /* no more than one buffer at a time */
        if( l > fd->buflen - fd->bufpos ){
            l = fd->buflen - fd->bufpos;
        }

        /* and not past the end of the chunk */
        if( l > fd->cnkdlen - fd->cnkpos + sizeof(struct FSChunk) ){
            l = fd->cnkdlen - fd->cnkpos + sizeof(struct FSChunk);
        }

        memcpy(fd->buffer + fd->bufpos, buf, l);

        len -= l;
        buf += l;
        fd->filepos += l;
        fd->filelen += l;
        fd->cnkpos  += l;
        fd->bufpos  += l;
        wrt += l;

    }
    return wrt;
}

FILE *
flfs_open(MountEntry *me, const char *name, const char *how){
    FILE *f;

    if( *how == 'r' ){
        f = flfs_open_r(me, name);
    }else{
        f = flfs_open_w(me, name);
    }

    return f;
}

int
flfs_getchar(FILE *f){
    char c;

    if( f->flags & F_EOF )
        return -1;

    flfs_read(f, &c, 1);
    return c;
}

int
flfs_noop(FILE *f){
    return 1;
}

int
flfs_putchar(FILE *f, char c){
    return flfs_write(f, &c, 1);
}

int
flfs_status(FILE *f){
    struct FileData *fd;

    fd = f->d;

    if( fd->how == FDH_WRITE ){
        return FST_O;
    }else{
        return FST_I;
    }
}

int
flfs_stat(FILE *f, struct stat *s){
    struct FileData *fd;
    struct FLFS *flfs;

    fd = f->d;
    flfs = fd->flfs;

    s->dev     = flfs->me;
    s->size    = fd->filelen;
    s->ctime   = fd->ctime;
    s->blksize = flfs->fblksize;
    s->mode    = fd->attr;
    s->flags   = flfs->flags;

    return 0;
}

/*****************************************************************/
/* fs_type ops */

int
flfs_dir(MountEntry *me, int how){
    struct FLFS *flfs = me->fsdat;
    struct FSFile *ff;
    struct FSChunk *fc;
    char *buffer;
    int offset = 0;
    int nblnk = 0;
    int total = 0;
    int totinf = 0, nfiles = 0, nhidden = 0;
    int tlen;


    if( !me ){
        printf("no such file or flfsice\n");
        return -1;
    }

    buffer = alloc(flfs->fblksize);
    fc = (struct FSChunk *)buffer;
    ff = (struct FSFile  *)(buffer + sizeof(struct FSChunk));

    while(1){
        if( diskread(flfs, offset, buffer, flfs->fblksize) <= 0 ){
            DIAG("read %s,%d failed\n", flfs->me->name, offset);
            break;
        }
        if( fc->type == FCT_BLANK || fc->type == FCT_UNUSED ){
            if(how & LSHOW_EXT){
                if( !nblnk )
                    printf("U %6.6x", offset);
            }
            nblnk ++;
        }else{
            if( nblnk && (how & LSHOW_EXT) ){
                printf(" %7.7d(%7.7d)\n", 0, nblnk * flfs->fblksize);
            }
            nblnk = 0;
            if( how & LSHOW_EXT ){
                printf("%c %6.6x %7.7d(%7.7d)",
                       (fc->type < 6) ?
                       "UD.F.C"[fc->type] : 'X',
                       offset, fc->cnklen, fc->totlen);
                if( fc->type == FCT_FILE ){
                    printf(" %-20T %3.3d    %s", ff->ctime, ff->attr, ff->name);
                    nfiles ++;
                }
                printf("\n");
            }else{
                if( fc->type == FCT_FILE ){
                    if( (how & LSHOW_ALL) || !(ff->attr & FFA_HIDDEN) ){
                        if( how & LSHOW_LONG ){
                            printf("%-20T %c%c %7.7d bytes    %s\n",
                                   ff->ctime,
                                   (ff->attr & FFA_READONLY) ? 'r' : '-',
                                   (ff->attr & FFA_HIDDEN)   ? 'h' : '-',
                                   ff->filelen, ff->name);
                        }else{
                            printf("%7.7d bytes    %s\n", ff->filelen, ff->name);
                        }
                        nfiles ++;
                    }else{
                        nhidden ++;
                    }
                }
            }
        }
        if( fc->type == FCT_FILE || fc->type == FCT_CONT ){
            total += fc->totlen;
            totinf += fc->cnklen;
        }

        if( fc->type == FCT_BLANK || fc->type == FCT_UNUSED ){
            offset += flfs->fblksize;
        }else{

            tlen = fc->totlen;
            if( tlen == 0xFFFFFFFF || tlen == 0 )
                offset += chunklength( flfs, offset );
            else
                offset += tlen;
        }

        if( offset >= flfs->totalsize || nblnk > ENOUGHALREADYHEURISTIC ){
            /* reached end */
            break;
        }
    }

    if( nblnk && (how & LSHOW_EXT) ){
        printf(" %7.7d(%7.7d)\n", 0, flfs->totalsize - offset + nblnk * flfs->fblksize);
    }

    printf("========================\n"
           "  %3.3d Files = %8.8d bytes\n", nfiles, totinf);
    if( nhidden)
        printf("  %3.3d Hidden Files\n", nhidden);
    printf("      Total = %8.8d bytes\n"
           "      Free  = %8.8d bytes\n\n",
           total, flfs->totalsize - total);
    free(buffer, flfs->fblksize);
    return 0;
}

int
flfs_fchmod(FILE * f, int attr){
    struct FSFile *ff;
    struct FileData *fd;

    fd = f->d;

    if( fd->how != FDH_WRITE || fd->filepos ){
        return -1;
    }

    ff = (struct FSFile  *)(fd->buffer + sizeof(struct FSChunk));
    ff->attr = attr;

    return 0;
}

int
flfs_chmod(MountEntry *me, const char *name, int attr){
    struct FLFS *flfs = me->fsdat;
    struct FSFile *ff;
    char *buffer;
    int offset;
    int n;

    buffer = alloc(flfs->fblksize);
    offset = findfile(flfs, name, buffer, flfs->fblksize);
    ff = (struct FSFile  *)(buffer + sizeof(struct FSChunk));
    if( offset == -1 ){
        free(buffer, flfs->fblksize);
        return -1;
    }

    diskread(flfs, offset, buffer, flfs->fblksize);
    ff->attr = attr;
    diskwrite(flfs, offset, buffer, flfs->fblksize, 1);
    fflush( me->fdev );
    free(buffer, flfs->fblksize);
    return 0;
}

int
flfs_format(MountEntry *me, char *flfsname){
    struct FLFS *flfs = me->fsdat;
    struct FSChunk *fc;
    char *buffer;
    int i;

    printf("flfs format\n");
    buffer = alloc(flfs->fblksize);
    fc = (struct FSChunk *)buffer;

    if( flfs->flags & SSF_BIGERASE ){
        // erase entire device
        printf("formatting...\n");
        fioctl(flfs->me->fdev, IOC_ERASE, (void*)0);
        return 0;
    }

    /* allocate space for boot blocks if called as flfs:<bootsize> */
    flfsname += strlen(flfs->me->name);

    if( *flfsname ){
        i = atoi( flfsname );
        fc->type = FCT_BIOSEXT;
        i = (i + flfs->fblksize - 1) & ~(flfs->fblksize - 1);
        fc->totlen = i;
        fc->cnklen = 0;
        fc->next = 0xFFFFFFFF;
        printf("allocating %d for boot block\n", i);
        diskwrite(flfs, 0, buffer, flfs->fblksize, 1);
    }

    printf("formatting...\n");
    /* skip over any existing boot blocks */
    diskread(flfs, 0, buffer, flfs->fblksize);
    if( fc->type == FCT_BIOSEXT ){
        i = fc->totlen;
        if( !*flfsname )
            printf("preserving %d for boot block\n", i);
    }else{
        i = 0;
    }
    memset(buffer, 0xFF, flfs->fblksize);
    printf("space=%d blk=%d\n", flfs->totalsize, flfs->fblksize);
    printf("   0%%");
    for( ; i<flfs->totalsize; i+=flfs->fblksize){
        diskwrite(flfs, i, buffer, flfs->fblksize, 1);
        printf("\b\b\b\b%3.3d%%", i * 100 / flfs->totalsize);
    }
    printf("\b\b\b\b100%%\n");
    flfs->lastfreeoffset = 0;
    fflush( me->fdev );
    free(buffer, flfs->fblksize);
    return 0;
}

int
flfs_deletefile(MountEntry *me, const char *name){
    struct FLFS *flfs = me->fsdat;
    struct FSChunk *fc;
    struct FSFile *ff;
    char *buffer;
    int offset;
    int i;

    buffer = alloc(flfs->fblksize);
    offset = findfile(flfs, name, buffer, flfs->fblksize);
    fc = (struct FSChunk *)buffer;
    ff = (struct FSFile  *)(buffer + sizeof(struct FSChunk));
    if( offset == -1 ){
        free(buffer, flfs->fblksize);
        return -1;
    }

    if( ff->attr & FFA_READONLY ){
        /* read-only file cannot be deleted */
        free(buffer, flfs->fblksize);
        return -1;
    }

    while(1){
        if( diskread(flfs, offset, buffer, flfs->fblksize) <= 0 ){
            DIAG("read %s,%d failed\n", flfs->me->name, offset);
            free(buffer, flfs->fblksize);
            return -1;
        }

        if( flfs->flags & SSF_BLKWRITE ){
            /* erase the block */
            memset(buffer, 0xFF, flfs->fblksize);
            diskwrite(flfs, offset, buffer, flfs->fblksize, 1);
        }else{
            i = FCT_DELETED;
            diskwrite(flfs, offset + offsetof(struct FSChunk, type),
                      (char*)&i, sizeof(i), 0);
        }
        offset = fc->next;
        if( offset == 0xFFFFFFFF ){
            break;
        }
    }
    fflush( me->fdev );
    free(buffer, flfs->fblksize);
    return 0;
}

int
flfs_renamefile(MountEntry *me, const char *oname, const char *nname){
    struct FLFS *flfs = me->fsdat;
    struct FSFile *ff;
    char *buffer;
    int offset;
    int n;

    buffer = alloc(flfs->fblksize);
    if( findfile(flfs, nname, buffer, flfs->fblksize) != -1 )
        deletefile(nname);

    offset = findfile(flfs, oname, buffer, flfs->fblksize);
    ff = (struct FSFile *)(buffer + sizeof(struct FSChunk));
    if( offset == -1 ){
        free(buffer, flfs->fblksize);
        return -1;
    }

    /* strip flfsice from name */
    nname = basenameoffile(nname);

    diskread(flfs, offset, buffer, flfs->fblksize);
    strncpy(ff->name, nname, sizeof(ff->name));

    /* RSN - should delete this chunk, and try to find an unused one ??? */
    diskwrite(flfs, offset, buffer, flfs->fblksize, 1);
    free(buffer, flfs->fblksize);
    fflush( me->fdev );
    return 0;
}

int
flfs_glob(MountEntry *me, const char *pattern, int (*fnc)(const char *, void*), void *args){
    struct FLFS *flfs = me->fsdat;
    struct FSFile *ff;
    struct FSChunk *fc;
    char *buffer;
    int nblnk=0;
    int offset, tlen, i, found=0, rv=0;


    offset = 0;
    buffer = alloc(flfs->fblksize);
    fc = (struct FSChunk *)buffer;
    ff = (struct FSFile  *)(buffer + sizeof(struct FSChunk));

    while(1){
        if( diskread(flfs, offset, buffer, flfs->fblksize) <= 0 ){
            DIAG("read %s,%d failed\n", me->name, offset);
            free(buffer, flfs->fblksize);
            return -1;
        }

        if( fc->type == FCT_FILE && !(ff->attr & FFA_HIDDEN)
            && !fnmatch(pattern, ff->name, 0)){
            /* found it */

            rv = (fnc)(ff->name, args);
        }

        if( fc->type == FCT_BLANK || fc->type == FCT_UNUSED ){
            offset += flfs->fblksize;
            nblnk ++;
        }else{
            nblnk = 0;
            tlen = fc->totlen;
            if( tlen == 0xFFFFFFFF || tlen == 0 )
                offset += chunklength( flfs, offset );
            else
                offset += tlen;
        }

        if( offset >= flfs->totalsize || nblnk >= ENOUGHALREADYHEURISTIC ){
            /* reached end, not found */
            break;
        }
    }

    return rv;
}


int
flfs_ops(int what, MountEntry *me, ...){
    va_list ap;
    char *name;
    FILE *f;
    int n;

    va_start(ap, me);

    switch (what){

    case FSOP_RENAME:
        name = va_arg(ap, char*);
        return flfs_renamefile(me, name, va_arg(ap, char*));

    case FSOP_DELETE:
        return flfs_deletefile(me, va_arg(ap, char*));

    case FSOP_DIR:
        return flfs_dir(me, va_arg(ap, int));

    case FSOP_CHMOD:
        name = va_arg(ap, char*);
        return flfs_chmod(me, name, va_arg(ap, int));

    case FSOP_FCHMOD:
        f = va_arg(ap, FILE*);
        return flfs_fchmod(f, va_arg(ap, int));

    case FSOP_FORMAT:
        return flfs_format(me, va_arg(ap, char*));

    case FSOP_GLOB: {
        char *name = va_arg(ap, char*);
        int (*fnc)(const char *, void*) = va_arg(ap, void*); /* XXX gcc bug */
        return flfs_glob(me, name, fnc, va_arg(ap, void*) );
    }
    default:
        return -1;
    }
}

