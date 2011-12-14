/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function:

  $Id$

*/



#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <alloc.h>
#include <error.h>
#include <fs.h>
#include <locks.h>
#include <ioctl.h>
#include <userint.h>

#ifdef USE_FILESYS

#ifndef DEVPREFIX
#  define DEVPREFIX	"dev:"
#endif

/* GCC varargs macro */
#define fsmsg(f, args...)		fprintf(STDERR, f , ## args )
#define f_error(m)			fprintf(STDERR, "%s\n", m)

MountEntry *mountlist = 0;		/* the mount table */

extern int n_fsys;
extern struct FSType_Conf filesystems[];

int
mount(FILE *f, const char *n, int flag, const char *type){
    MountEntry *m;
    struct stat s;
    struct FSType_Conf *fst = 0;
    int i;

    if( !type )
        flag = 1;
    else{
        /* find fs type in table */
        for(i=0; i<n_fsys; i++){
            if( !strcmp(type, filesystems[i].name) ){
                fst = filesystems + i;
                break;
            }
        }
        if( !fst ){
            fsmsg("unknown fstype '%s' mounting %s\n", type, n);
            return -1;
        }
    }

    for(m=mountlist; m; m=m->next){
        if( m->f == f && !flag ){
            fsmsg("attempt to remount %s on %s\n", m->name, n);
            return -1;
        }
    }

    m = alloc(sizeof(MountEntry));

    m->f     = f;
    m->lock  = 0;
    m->lastfreeoffset = 0;
    m->fs    = fst;
    m->pmdata = 0;

    if( flag ){
        /* mount special device in dev: */
        m->name = alloc( strlen(n) + sizeof(DEVPREFIX) );
        strcpy(m->name, DEVPREFIX);
        strcat(m->name, n);

        m->flags    = SSF_SPECIAL;
        m->pblksize = 1;
        m->fblksize = 1;
        m->totaldiskspace = 0;
    }else{
        m->name = alloc( strlen(n) + 1 );
        strcpy(m->name, n);

        fstat(f, &s);
        m->pblksize = s.blksize;
        m->fblksize = FBLOCKSIZE;
        m->flags    = s.flags;
        m->totaldiskspace = s.size;

        m->flags    = s.flags;

        (m->fs->init)(m);
    }

    m->next = mountlist;
    mountlist = m;

    // kprintf("mount &ml %X, m %X\n", &mountlist, m);

    return 0;
}


MountEntry *
deviceofname(const char *name){
    char *p;
    MountEntry *m = mountlist;

    while( m ){
        if( !strncmp(name, m->name, strlen(m->name)) )
            return m;
        m = m->next;
    }
    return 0;
}

const char *
basenameoffile(const char *name){
    char *p;
    MountEntry *dev;
    int n;

    dev = deviceofname(name);
    if( dev && !strncmp(name, dev->name, n=strlen(dev->name)) ){
        name += n;
    }
    return name;
}

FILE *
fopen(const char *name, const char *how){
    MountEntry *dev;

    dev = deviceofname(name);
#ifdef USE_PROC
    if( !dev )
        dev = currproc->cwd;
#endif
    if( !dev )
        return 0;

    if( dev->flags & SSF_SPECIAL )
        return dev->f;

    if( dev->fs && dev->fs->open )
        return (dev->fs->open)(dev, name, how);
    else
        return dev->f;
}

int
chdir(const char *devname){
    MountEntry *dev;
#ifdef USE_PROC
    dev = deviceofname(devname);
    if( dev && (dev->flags & SSF_SPECIAL) )
        dev = 0;
    if( dev ) currproc->cwd = dev;

    return dev ? 0 : -1;
#else
    return -1;
#endif
}


/*****************************************************************
 *****************************************************************/

#ifdef USE_PROC
#  define DEV(dev, name)                        \
    dev = deviceofname(name);                   \
    if( !dev )                                  \
        dev = currproc->cwd;                    \
    if( !dev )                                  \
        return -1;
#else
#  define DEV(dev, name)                        \
    dev = deviceofname(name);                   \
    if( !dev )                                  \
        return -1;

#endif

#define CHK(dev)	( dev->fs && dev->fs->ops )


int
fchmod(FILE * f, int attr){
    struct stat st;

    fstat(f, &st);

    if( st.dev && CHK(st.dev) )
        return (st.dev->fs->ops)(FSOP_FCHMOD, st.dev, f, attr);
    return -1;
}

int
chmod(const char *name, int attr){
    MountEntry *dev;

    DEV(dev, name);
    if( CHK(dev) )
        return (dev->fs->ops)(FSOP_CHMOD, dev, basenameoffile(name), attr);

    return -1;
}

int
fs_format(const char *name){
    MountEntry *dev;

    fsmsg( "fs_format: %s\n", name);
    DEV(dev, name);
    if( CHK(dev) )
        return (dev->fs->ops)(FSOP_FORMAT, dev, name);
    return -1;
}

int
deletefile(const char *name){
    MountEntry *dev;

    DEV(dev, name);
    if( CHK(dev) )
        return (dev->fs->ops)(FSOP_DELETE, dev, basenameoffile(name) );
    return -1;
}

int
renamefile(const char *oname, const char *nname){
    MountEntry *dev;

    DEV(dev, oname);
    if( CHK(dev) )
        return (dev->fs->ops)(FSOP_RENAME, dev, basenameoffile(oname), nname);
    return -1;
}


/*****************************************************************
 *****************************************************************/

#ifdef USE_CLI

DEFUN(format, "format device")
{
    if( argc < 2 ){
        f_error("format drive");
        return -1;
    }

    return fs_format(argv[1]);
}

DEFUN(delete, "delete files")
DEFALIAS(delete, del)
DEFALIAS(delete, rm)
{
    int st;

    if( argc < 2 ){
        f_error("delete filename ...");
        return -1;
    }

    while(++argv, --argc){
        st = deletefile( *argv );
        printf( st ? "could not delete file \"%s\"\n"
                : "file \"%s\" deleted\n",
                *argv);
    }

    return st;

}

DEFUN(rename, "rename files")
DEFALIAS(rename, ren)
DEFALIAS(rename, mv)
{
    if( argc != 3 ){
        f_error("rename oldname newname");
        return -1;
    }

    return renamefile( argv[1], argv[2] );
}

DEFUN(cd, "change dir")
DEFALIAS(cd, chdir)
{
    int i;

    if( argc < 2 ){
        return chdir( MOUNT_ROOT );
    }
    i = chdir(argv[1]);
    if( i )
        f_error("no such device");
    return i;
}


#ifdef USE_PROC
DEFUN(pwd, "print current dir")
{
    printf("%s\n", currproc->cwd ? currproc->cwd->name : "cwd not set");
    return 0;
}
#endif

DEFUN(chmod, "change file attributes")
{
    if( argc != 3 ){
        f_error("chmod attr filename");
        return -1;
    }

    return chmod(argv[2], atoi(argv[1]));
}


DEFUN(dir, "list files")
DEFALIAS(dir, ls)
DEFALIAS(dir, ll)
{
    int how=0, i;
    char *what;
    MountEntry *dev;

    if( !strcmp(argv[0], "ll") )
        how = LSHOW_ALL | LSHOW_LONG ;

    if( argc == 1)
        what = "";
    else{
        if( argv[1][0] == '-' ){
            for(i=how=0; argv[1][i]; i++){
                switch( argv[1][i] ){
                case 'a':	how |= LSHOW_ALL;	break;
                case 'd':	how |= LSHOW_DEVS;	break;
                case 'f':	how |= LSHOW_FSYS;	break;
                case 'x':	how |= LSHOW_EXT;	break;
                case 'l':	how |= LSHOW_LONG;	break;
                }
            }
            what = argc>2 ? argv[2] : "";
        }else
            what = argc>1 ? argv[1] : "";
    }

    if( how & LSHOW_FSYS || how & LSHOW_DEVS ){
        /* list all devs */
        dev = mountlist;
        while( dev ){
            if( dev->flags & SSF_SPECIAL && how & LSHOW_DEVS
                || !(dev->flags & SSF_SPECIAL) && how & LSHOW_FSYS )
                printf("\t%s\n", dev->name);
            dev = dev->next;
        }
        return 0;
    }

    dev = deviceofname(what);

    if( *what && !dev || !*what
#ifdef USE_PROC
	&& !currproc->cwd
#endif
        ){
        fsmsg("no such file or device\n");
        return -1;
    }
#ifdef USE_PROC
    if( !dev )
        dev = currproc->cwd;
#endif

    if( dev->fs && dev->fs->ops )
        i = (dev->fs->ops)(FSOP_DIR, dev, how);
    else
        i = -1;

    if( i )
        f_error("ls [-adfxl] [dev]");
    return i;
}

struct GlobArgs {
    struct MountEntry *dev;
    int replc;
    char **argv;
    int argc;

};

int
globfnc(const char *name, struct GlobArgs *ga){
    char buf[128];

    snprintf(buf, sizeof(buf), "%s%s",
#ifdef USE_PROC
             (ga->dev == currproc->cwd) ? "" : ga->dev->name,
#else
             ga->dev->name,
#endif
             name);

    if( ga->replc ){
        ga->argv[ ga->replc ] = buf;
        return shell_eval( ga->argc - 2, ga->argv + 1 );
    }else{
        ga->argv[ ga->argc - 1 ] = buf;
        return shell_eval( ga->argc - 1, ga->argv + 1 );
    }
}

DEFUN(glob, "expand wildcards in filenames")
{
    struct FSFile *ff;
    struct FSChunk *fc;
    char *buffer;
    int nblnk=0;
    int offset, tlen, i, found=0, rv=0;
    char *pattern;
    struct GlobArgs ga;

    ga.replc = 0;

    for(i=0; i<argc; i++){
        if( !strcmp(argv[i], "{}")){
            ga.replc = i;
            break;
        }
    }

    if( argc < 3 ){
        f_error("glob cmd [args...] [{} args...] pattern");
        return -1;
    }

    pattern = argv[argc-1];

    ga.dev = deviceofname(pattern);
#ifdef USE_PROC
    if( !ga.dev )
        ga.dev = currproc->cwd;
#endif
    if( !ga.dev ){
        return -1;
    }

    /* strip off devicename */
    pattern = (char*)basenameoffile(pattern);

    ga.argv = argv;
    ga.argc = argc;
    if( CHK(ga.dev) )
        return (ga.dev->fs->ops)(FSOP_GLOB, ga.dev, pattern, globfnc, &ga);
    return -1;
}

#endif /* USE_CLI */
#endif /* USE_FILESYS */

