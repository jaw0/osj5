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

int xxxfs_close(FILE *f);
int xxxfs_read(FILE* f, char* buf, int len);
int xxxfs_write(FILE* f, const char* buf, int len);
int xxxfs_getchar(FILE *f);
int xxxfs_putchar(FILE *f, char c);
int xxxfs_status(FILE *f);
int xxxfs_seek(FILE *f, int, int);
int xxxfs_tell(FILE *f);
int xxxfs_flush(FILE *f);
int xxxfs_stat(FILE *f, struct stat *s);
int xxxfs_ioctl(FILE *f, int, void*);

struct XXXFS {
    struct MountEntry *me;
};

static int devno;

const struct io_fs xxxfs_iofs = {
    xxxfs_putchar,
    xxxfs_getchar,
    xxxfs_close,
    xxxfs_flush,
    xxxfs_status,
    xxxfs_read,
    xxxfs_write,
    0, 0, 		/* bread, bwrite */
    xxxfs_seek,
    xxxfs_tell,
    xxxfs_stat,
    xxxfs_ioctl
};

int xxxfs_init(MountEntry *me){}
int xxxfs_unmount(MountEntry *me){}
FILE * xxxfs_open(MountEntry *me, const char *name){}

int xxxfs_close(FILE *f){ }
int xxxfs_read(FILE* f, char* buf, int len){}
int xxxfs_write(FILE* f, const char* buf, int len){}
int xxxfs_getchar(FILE *f){}
int xxxfs_putchar(FILE *f, char c){}
int xxxfs_status(FILE *f){}
int xxxfs_seek(FILE *f, int, int){}
int xxxfs_tell(FILE *f){}
int xxxfs_flush(FILE *f){}
int xxxfs_stat(FILE *f, struct stat *s){}
int xxxfs_ioctl(FILE *f, int, void*){}

int xxxfs_dir(MountEntry *me, int how){}
int xxxfs_fchmod(FILE * f, int attr){}
int xxxfs_chmod(MountEntry *me, const char *name, int attr){}
int xxxfs_format(MountEntry *me, char *xxxfsname){}
int xxxfs_deletefile(MountEntry *me, const char *name){}
int xxxfs_renamefile(MountEntry *me, const char *oname, const char *nname){}
int xxxfs_glob(MountEntry *me, const char *pattern, int (*fnc)(const char *, void*), void *args){}

int
xxxfs_ops(int what, MountEntry *me, ...){
    va_list ap;
    char *name;
    FILE *f;
    int n;

    va_start(ap, me);

    switch (what){

    case FSOP_RENAME:
        name = va_arg(ap, char*);
        return xxxfs_renamefile(me, name, va_arg(ap, char*));

    case FSOP_DELETE:
        return xxxfs_deletefile(me, va_arg(ap, char*));

    case FSOP_DIR:
        return xxxfs_dir(me, va_arg(ap, int));

    case FSOP_CHMOD:
        name = va_arg(ap, char*);
        return xxxfs_chmod(me, name, va_arg(ap, int));

    case FSOP_FCHMOD:
        f = va_arg(ap, FILE*);
        return xxxfs_fchmod(f, va_arg(ap, int));

    case FSOP_FORMAT:
        return xxxfs_format(me, va_arg(ap, char*));

    case FSOP_GLOB: {
        char *name = va_arg(ap, char*);
        int (*fnc)(const char *, void*) = va_arg(ap, void*);
        return xxxfs_glob(me, name, fnc, va_arg(ap, void*) );
    }
    default:
        return -1;
    }
}

