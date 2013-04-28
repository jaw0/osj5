
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: fs.h,v 1.7 2001/11/15 22:56:38 jaw Exp $ */

#ifndef __fs_h__
#define __fs_h__

#include <nstdio.h>
#include <locks.h>

struct FSType_Conf {
    const char *name;
    int (*init)(struct MountEntry *);
    FILE *(*open)(struct MountEntry *, const char*, const char*);
    int (*ops)(int, struct MountEntry*, ...);
    int (*unmount)(struct MountEntry*);
};
/* #define FSOP_INIT	0 */
#define FSOP_RENAME	1
#define FSOP_DELETE	2
#define FSOP_DIR	3
#define FSOP_CHMOD	4
#define FSOP_FCHMOD	5
#define FSOP_FORMAT	6
#define FSOP_GLOB	7
#define FSOP_MKDIR	8

/* ls flags */
#define LSHOW_ALL	1
#define LSHOW_EXT	2
#define LSHOW_LONG	4
#define LSHOW_FSYS	8
#define LSHOW_DEVS	16

/* file attr */
#define FFA_READONLY	1	/* cannot be deleted */
#define FFA_HIDDEN	2	/* does not appear in dir listing */

typedef struct MountEntry {
    char name[16];
    FILE *fdev;			/* underlying device */
    void *fsdat;

    struct FSType_Conf *fscf;

    u_long flags;
#define MNTE_F_DEV	1
#define MNTE_F_FS	2

#if 0
    void  *pmdata;			/* private data */
    u_long totaldiskspace;		/* total space */
    u_long lastfreeoffset;		/* cache location of last available space found */
    u_long pblksize;
    u_long fblksize;
    u_long flags;

    lock_t lock;
#endif
    struct MountEntry *next, *prev;

} MountEntry;


#define FBLOCKSIZE	512

extern FILE *fopen(const char *, const char *);
extern int deletefile(const char *);
extern int renamefile(const char *, const char *);
extern int fs_format(const char *);
extern int chdir(const char *);
extern int chmod(const char*, int);
extern int fchmod(FILE*, int);

extern int fmount(FILE*, const char *name, const char *type);
extern int devmount(FILE*, const char *name);
extern int mount(const char * dev, const char *name, const char *type);

extern MountEntry *find_mount(const char *);
extern const char *basenameoffile(const char *);

#endif /* __fs_h__ */

