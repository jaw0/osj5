/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-05 20:57 (EDT)
  Function: fatfs glue
*/


#include <sys/types.h>
#include <sys/param.h>
#include <stdarg.h>
#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <alloc.h>
#include <error.h>
#include <disk.h>
#include <fs.h>
#include <locks.h>
#include <ioctl.h>
#include <userint.h>

#include "fatfs/ff.h"
#include "fatfs/diskio.h"


#define MAXDISK 1



struct FatFS {
    MountEntry *me;
    int     	n;
    long long	size;

    FATFS	ff;
};

struct FileData {
    struct FatFS *ffs;
    FIL	fil;

};

int fatfs_putchar(FILE*, char);
int fatfs_getchar(FILE*);
int fatfs_close(FILE*);
int fatfs_noop(FILE*);
int fatfs_status(FILE*);
int fatfs_read(FILE*, char*, int);
int fatfs_write(FILE*, const char*, int);
int fatfs_stat(FILE *, struct stat*);

const struct io_fs fatfs_iofs = {
    fatfs_putchar,
    fatfs_getchar,
    fatfs_close,
    fatfs_noop,		/* flush */
    fatfs_status,
    fatfs_read,
    fatfs_write,
    0, 0, 		/* bread, bwrite */
    0, 0,		/* seek, tell */
    fatfs_stat,
    0,			/* ioctl */
};



static struct FatFS fsinfo[MAXDISK];
static int nfs = 0;


int
fatfs_init(MountEntry *me){
    struct stat s;

    if( nfs >= MAXDISK ){
        PANIC("too many FATFS");
    }

    struct FatFS *f = & fsinfo[nfs];
    f->me     = me;
    f->n      = nfs;
    me->fsdat = f;

    fstat(me->fdev, &s);
    f->size = s.size;

    f_mount( nfs, & f->ff );

    char buff[13];
    DWORD sno;
    if( f_getlabel("", buff, &sno)==FR_OK ){
        bootmsg("%s fatfs volume '%s' s/n %x\n",
                me->name, buff, sno);
    }

    nfs ++;

    return 0;
}

int
fatfs_unmount(MountEntry *me){
    return -1;
}


FILE *
fatfs_open(MountEntry *me, const char *name, const char *how){
    struct FileData *fd;
    FILE *f;
    int r;

    kprintf("fatfs open %s\n", name );
    fd = alloc(sizeof(struct FileData));
    fd->ffs = me->fsdat;

    if( *how == 'r' ){
        r = f_open( & fd->fil, name, FA_READ | FA_OPEN_EXISTING);
    }else{
        r = f_open( & fd->fil, name, FA_WRITE | FA_CREATE_ALWAYS );
    }

    if( r != FR_OK ){
        free(fd, sizeof(struct FileData));
        return 0;
    }

    f = alloc(sizeof(FILE));
    finit( f );
    f->flags = 0;
    f->fs = &fatfs_iofs;
    f->d  = fd;

    return f;
}


int
fatfs_ops(int what, MountEntry *me, ...){
    va_list ap;
    char *name;
    struct FatFS *fs = me->fsdat;
    char buf[13];
    FILE *f;
    int a,n;

    va_start(ap, me);

    switch (what){
    case FSOP_FORMAT:
        n = f_mkfs(fs->n, 1, 0);
        snprintf(buf, sizeof(buf), "OSJ5 %s", me->name);
        buf[strlen(buf)-1] = 0;	// remove trailing :
        f_setlabel(buf);
        return n;

    case FSOP_RENAME:
        //f_chdrive( fs-> n );
        name = va_arg(ap, char*);
        return f_rename( name, va_arg(ap, char*));

    case FSOP_DELETE:
        //f_chdrive( fs-> n );
        return f_unlink( va_arg(ap, char*) );

    case FSOP_MKDIR:
        //f_chdrive( fs-> n );
        return f_mkdir( va_arg(ap, char*) );

    case FSOP_DIR:
        n = va_arg(ap, int);
        return fatfs_dir(me, n, va_arg(ap, const char*));

    case FSOP_CHMOD:
        //f_chdrive( fs-> n );
        name = va_arg(ap, char*);
        n    = va_arg(ap, int);
        a    = ((n & FFA_HIDDEN)?AM_HID:0) | ((n & FFA_READONLY)?AM_RDO:0);

        return f_chmod(name, a, AM_HID|AM_RDO);

    case FSOP_GLOB: {
        char *name = va_arg(ap, char*);
        int (*fnc)(const char *, void*) = va_arg(ap, void*);
        return fatfs_glob(me, name, fnc, va_arg(ap, void*) );
    }
#if 0
    case FSOP_FCHMOD:
        f = va_arg(ap, FILE*);
        return fatfs_fchmod(f, va_arg(ap, int));

#endif
    default:
        return -1;
    }
}


int
fatfs_dir(MountEntry *me, int how, const char *dname){
    struct FatFS *fs = me->fsdat;
    DIR dir;
    FILINFO fi;
    long long total=0;
    int i, files=0;

    if( f_opendir(&dir, dname) ) return -1;

    while(1){
        int r = f_readdir(&dir, &fi);
        if( r != FR_OK || fi.fname[0]==0 ) break;	// done

        if( (fi.fattrib & AM_HID) && !(how & LSHOW_ALL) )
            continue;

        total += fi.fsize;
        files ++;

        if( how & LSHOW_LONG ){

            printf("%4d-%0.2d-%0.2d ",
                   (fi.fdate>>9) + 1980,
                   (fi.fdate>>5) & 0xF,
                   (fi.fdate) & 0x1F);

            printf("T%0.2d:%0.2d:%0.2d ",
                   (fi.ftime>>11),
                   (fi.ftime>>5) & 0x3F,
                   (fi.ftime) & 0x1F);

            printf("%c%c ",
                   (fi.fattrib&AM_RDO)? 'r' : '-',
                   (fi.fattrib&AM_HID)? 'h' : '-' );
        }

        // lcase
        for(i=0; i<12; i++)
            fi.fname[i] = tolower(fi.fname[i]);

        printf("%7.7d bytes    %s%c\n", fi.fsize, fi.fname, (fi.fattrib & AM_DIR)?'/': ' ');
    }

    printf("========================\n"
           "  %3.3d Files = %8.8qd bytes\n", files, total);

    return 0;
}


int
fatfs_glob(MountEntry *me, const char *pattern, int (*fnc)(const char *, void*), void *args){
    struct FatFS *fs = me->fsdat;
    DIR dir;
    FILINFO fi;
    int i, rv = 0;

    // break pattern into dir + pattern
    extern char *rindex(const char *, int);
    const char *slash = rindex(pattern, '/');
    char *dirname;
    char *filebuf;
    int dirlen, fblen;

    if( slash ){
        dirlen  = slash - pattern;
        dirname = alloc( dirlen + 1 );

        strncpy(dirname, pattern, dirlen);
        pattern = slash + 1;
        fblen   = dirlen + 14;
        filebuf = alloc( fblen );
    }else{
        dirlen  = 0;
        dirname = "";
        filebuf = 0;
    }

    if( f_opendir( &dir, dirname ) != FR_OK ){
        if( dirlen ){
            free(dirname, dirlen);
            free(filebuf, fblen);
        }
        return -1;
    }

    while(1){
        int r = f_readdir(&dir, &fi);
        if( r != FR_OK || fi.fname[0]==0 ) break;	// done
        if( fi.fattrib & AM_DIR ) continue;
        if( fi.fattrib & AM_HID ) continue;

        // lcase
        for(i=0; i<12; i++)
            fi.fname[i] = tolower(fi.fname[i]);

        if( fnmatch(pattern, fi.fname, 0) ) continue;

        if( dirlen ){
            // re-assemble: dir + file
            snprintf(filebuf, fblen, "%s/%s", dirname, fi.fname);
            rv = (fnc)(filebuf, args);
        }else{
            rv = (fnc)(fi.fname, args);
        }
    }

    if( dirlen ){
        free( dirname, dirlen );
        free( filebuf, fblen );
    }

    return rv;
}


/****************************************************************/
// file ops

int
fatfs_close(FILE *f){
    struct FileData *fd = f->d;

    f_close( & fd->fil );
    free( fd, sizeof(struct FileData));
    free( f, sizeof(FILE));

    return 0;
}


int
fatfs_read(FILE* f, char* buf, int len){
    struct FileData *fd = f->d;
    int rl;
    int r = f_read( &fd->fil, buf, len, &rl );
    if( r != FR_OK )
        return -1;
    return rl;

}
int
fatfs_write(FILE* f, const char* buf, int len){
    struct FileData *fd = f->d;
    int wl;
    int r = f_write( &fd->fil, buf, len, &wl );
    if( r != FR_OK )
        return -1;
    return wl;


}
int
fatfs_getchar(FILE *f){
    struct FileData *fd = f->d;
    int rl;
    char ch;
    int r = f_read( &fd->fil, &ch, 1, &rl );
    if( r != FR_OK )
        return -1;
    return 1;

}

int
fatfs_putchar(FILE *f, char c){
    struct FileData *fd = f->d;
    int wl;
    int r = f_write( &fd->fil, &c, 1, &wl );
    if( r != FR_OK )
        return -1;
    return 1;
}

int
fatfs_status(FILE *f){
    return 0;
}
int
fatfs_flush(FILE *f){
    struct FileData *fd = f->d;
    f_sync( & fd->fil );
    return 0;
}
int fatfs_stat(FILE *f, struct stat *s){
    struct FileData *fd = f->d;
    struct FatFS *fs = fd->ffs;

    s->dev     = fs->me;

    s->size    = fd->fil.fsize;
    s->ctime   = 0;
    s->blksize = 512;
    s->mode    = 0;
    s->flags   = 0;

    return 0;

}

int fatfs_noop(FILE*f){}

/****************************************************************/

#if 0
int fatfs_fchmod(FILE * f, int attr){}
#endif

/****************************************************************/

// disk_read, write

DWORD
get_fattime(void){
    struct tm t;
    gmtime_r(0, &t);
    int ft = 0;

// bit31:25	Year from 1980 (0..127)
// bit24:21	Month (1..12)
// bit20:16	Day in month(1..31)
// bit15:11	Hour (0..23)
// bit10:5	Minute (0..59)
// bit4:0	Second / 2 (0..29)

    if( t.tm_year < 2000 ) t.tm_year = 2000;
    ft |= (t.tm_year - 1980) << 25;
    ft |= (t.tm_mon + 1) << 21;
    ft |= t.tm_mday << 16;
    ft |= t.tm_hour << 11;
    ft |= t.tm_min  << 5;
    ft |= (t.tm_sec / 2);

    return ft;
}



DSTATUS
disk_status(BYTE dev){
    return 0;
}

DSTATUS
disk_initialize(BYTE dev){
    return 0;
}

DRESULT
disk_read(BYTE dev, BYTE *buf, DWORD sect, BYTE cnt){
    struct FatFS *f = & fsinfo[dev];

    //bzero(buf, 512);
    int r = fbread(f->me->fdev, buf, cnt * DISK_BLOCK_SIZE, sect * DISK_BLOCK_SIZE);
    kprintf("fatfs read %x => %d\n", sect, r);
    //hexdump(buf, 512);
    if( r > 0 ) return RES_OK;
    return RES_ERROR;
}

DRESULT
disk_write(BYTE dev, const BYTE *buf, DWORD sect, BYTE cnt){
    struct FatFS *f = & fsinfo[dev];

    int r = fbwrite(f->me->fdev, buf, cnt * DISK_BLOCK_SIZE, sect * DISK_BLOCK_SIZE);
    kprintf("fatfs write %x => %d\n", sect, r);
    if( r > 0 ) return RES_OK;
    return RES_ERROR;
}

DRESULT
disk_ioctl(BYTE dev, BYTE cmd, void *param){
    struct FatFS *f = & fsinfo[dev];
    int *p = (int*)param;

    kprintf("fatfs_ioctl %d\n", cmd);
    switch(cmd){
    case CTRL_SYNC:
        return 0;

    case GET_SECTOR_SIZE:
        *p = 512;
        return 0;

    case GET_SECTOR_COUNT:
        *p = f->size / 512;
        return 0;

    case GET_BLOCK_SIZE:
        *p = 1;
        return 0;

    default:
        return 0;
    }
}
