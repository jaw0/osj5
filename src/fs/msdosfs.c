/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-06 13:08 (EST)
  Function: 
 
  $Id$

*/

#include <sys/types.h>
#include <conf.h>
#include <fs.h>

#include <fs/msdosfs/dosfs.h>


int msdosfs_close(FILE *f);
int msdosfs_read(FILE* f, char* buf, int len);
int msdosfs_write(FILE* f, const char* buf, int len);
int msdosfs_getchar(FILE *f);
int msdosfs_putchar(FILE *f, char c);
int msdosfs_status(FILE *f);
int msdosfs_seek(FILE *f, int, int);
int msdosfs_tell(FILE *f);
int msdosfs_flush(FILE *f);
int msdosfs_stat(FILE *f, struct stat *s);
int msdosfs_ioctl(FILE *f, int, void*);

struct MSDOSFS {
    struct MountEntry *me;
};

static int devno;

const struct io_fs msdosfs_iofs = {
    msdosfs_putchar,
    msdosfs_getchar,
    msdosfs_close,
    msdosfs_flush,	/* flush */
    msdosfs_status,
    msdosfs_read,
    msdosfs_write,
    0, 0, 		/* bread, bwrite */
    msdosfs_seek,
    msdosfs_tell,
    msdosfs_stat,
    msdosfs_ioctl
};

int
msdosfs_init(MountEntry *me){

    struct MSDOSFS *msfs = alloc(sizeof(struct MSDOSFS));

    msfs->me = me;


}

int
msdosfs_unmount(MountEntry *me){

}

// interface glue

int
msdosfs_diskread(int unit, u_long off, char *buf, int len){
    return fbread(msdosfs[unit].me->fdev, buf, len, off);
}
int
msdosfs_diskwrite(int unit, u_long off, char *buf, int len){
    return fbwrite(msdosfs[unit].me->fdev, buf, len, off);
}


// nstdio funcs
FILE * msdosfs_open(MountEntry *me, const char *name){}
int msdosfs_close(FILE *f){ }
int msdosfs_read(FILE* f, char* buf, int len){}
int msdosfs_write(FILE* f, const char* buf, int len){}
int msdosfs_getchar(FILE *f){}
int msdosfs_putchar(FILE *f, char c){}
int msdosfs_status(FILE *f){}
int msdosfs_seek(FILE *f, int, int){}
int msdosfs_tell(FILE *f){}
int msdosfs_flush(FILE *f){}
int msdosfs_stat(FILE *f, struct stat *s){}
int msdosfs_ioctl(FILE *f, int, void*){}

// fs funcs
int msdosfs_dir(MountEntry *me, int how){}
int msdosfs_fchmod(FILE * f, int attr){}
int msdosfs_chmod(MountEntry *me, const char *name, int attr){}
int msdosfs_format(MountEntry *me, char *msdosfsname){}
int msdosfs_deletefile(MountEntry *me, const char *name){}
int msdosfs_renamefile(MountEntry *me, const char *oname, const char *nname){}
int msdosfs_glob(MountEntry *me, const char *pattern, int (*fnc)(const char *, void*), void *args){}

int
msdosfs_ops(int what, MountEntry *me, ...){
    va_list ap;
    char *name;
    FILE *f;
    int n;

    va_start(ap, me);

    switch (what){

    case FSOP_RENAME:
        name = va_arg(ap, char*);
        return msdosfs_renamefile(me, name, va_arg(ap, char*));

    case FSOP_DELETE:
        return msdosfs_deletefile(me, va_arg(ap, char*));

    case FSOP_DIR:
        return msdosfs_dir(me, va_arg(ap, int));

    case FSOP_CHMOD:
        name = va_arg(ap, char*);
        return msdosfs_chmod(me, name, va_arg(ap, int));

    case FSOP_FCHMOD:
        f = va_arg(ap, FILE*);
        return msdosfs_fchmod(f, va_arg(ap, int));

    case FSOP_FORMAT:
        return msdosfs_format(me, va_arg(ap, char*));

    case FSOP_GLOB: {
        char *name = va_arg(ap, char*);
        int (*fnc)(const char *, void*) = va_arg(ap, void*);
        return msdosfs_glob(me, name, fnc, va_arg(ap, void*) );
    }
    default:
        return -1;
    }
}


