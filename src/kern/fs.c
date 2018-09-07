/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: file system interface
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


#ifndef DEVPREFIX
#  define DEVPREFIX	"dev:"
#endif

/* GCC varargs macro */
#define fsmsg(f, args...)		fprintf(STDERR, f , ## args )
#define f_error(m)			fprintf(STDERR, "%s\n", m)

MountEntry *mountlist = 0;		/* the mount table */

extern int n_fsys;
extern struct FSType_Conf filesystems[];


static struct FSType_Conf *
find_fstype(const char *type){
    int i;

    /* find fs type in table */
    for(i=0; i<n_fsys; i++){
        if( !strcmp(type, filesystems[i].name) ){
            return filesystems + i;
        }
    }
    return 0;
}

static int
_mount(FILE *fdev, const char *name, const char *type){
    MountEntry *me;
    struct FSType_Conf *fst = 0;

    if( type ){
        fst = find_fstype(type);
        if( !fst ){
            kprintf("unknown fstype '%s' mounting %s\n", type, name);
            return -1;
        }
    }

    for(me=mountlist; me; me=me->next){
        if( me->fdev == fdev && me->fscf == fst ){
            kprintf("attempt to remount %s on %s\n", me->name, name);
            return -1;
        }
    }

    me = alloc(sizeof(MountEntry));

    if( !me ){
        kprintf("cannot alloc me\n");
        return -1;
    }

    me->fdev   = fdev;
    me->fscf   = fst;
    me->fsdat  = 0;

    if( type ){
        strncpy(me->name, name, sizeof(me->name));
        me->flags   = MNTE_F_FS;
        if( me->fscf && me->fscf->init )
            (me->fscf->init)(me);
    }else{
        /* mount special device in dev: */
        strncpy(me->name, DEVPREFIX, sizeof(me->name));
        strncat(me->name, name, sizeof(me->name) - sizeof(DEVPREFIX) );
        // remove a trailing :
        int l = strlen(me->name);
        if( me->name[l-1] == ':' ) me->name[l-1] = 0;

        me->flags   = MNTE_F_DEV;
    }

    int plx = splhigh();
    me->prev = 0;
    if(mountlist) mountlist->prev = me;
    me->next  = mountlist;
    mountlist = me;
    splx(plx);

    return 0;
}

int
unmount(MountEntry *me){

    if(!me) return -1;
    // RSN - open files?
    if( me->fscf && me->fscf->unmount ) me->fscf->unmount(me);

    int plx = splhigh();
    if( me->next ) me->next->prev = me->prev;
    if( me->prev ) me->prev->next = me->next;
    me->prev = me->next = 0;
    splx(plx);

    free(me, sizeof(MountEntry));
    return 0;
}


int
fmount(FILE *fdev, const char *name, const char *type){
    return _mount(fdev, name, type);
}

int
devmount(FILE *fdev, const char *name){
    return _mount(fdev, name, 0);
}

int
mount(const char *dev, const char *name, const char *type){
    MountEntry *me = find_mount(dev);

    if( ! me ) return -1;			// not found
    if( me->flags & MNTE_F_FS ) return -1;	// not a device
    if( ! me->fdev->fs->bread ) return -1;	// not a block device

    return _mount(me->fdev, name, type );
}


MountEntry *
find_mount(const char *name){
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

    dev = find_mount(name);
    if( dev && !strncmp(name, dev->name, n=strlen(dev->name)) ){
        name += n;
    }
    return name;
}

FILE *
fopen(const char *name, const char *how){
    MountEntry *me;

    me = find_mount(name);
    if( me )
        name = basenameoffile(name);
#ifdef USE_PROC
    if( !me )
        me = currproc->cwd;
#endif
    if( !me )
        return 0;

    if( me->flags & MNTE_F_DEV )
        return me->fdev;

    if( me->fscf && me->fscf->open )
        return (me->fscf->open)(me, name, how);
    else
        return me->fdev;
}

#ifdef USE_FILESYS
int
chdir(const char *devname){
    MountEntry *me;
#ifdef USE_PROC
    me = find_mount(devname);
    if( me && (me->flags & MNTE_F_DEV) )
        me = 0;
    if( me ) currproc->cwd = me;

    return me ? 0 : -1;
#else
    return -1;
#endif
}

/*****************************************************************
 *****************************************************************/

#ifdef USE_PROC
#  define ME(me, name)                         \
    me = find_mount(name);                     \
    if( !me )                                  \
        me = currproc->cwd;                    \
    if( !me )                                  \
        return -1;
#else
#  define ME(me, name)                         \
    me = find_mount(name);                     \
    if( !me )                                  \
        return -1;

#endif

#define CHK(me)	( me->fscf && me->fscf->ops )


int
fchmod(FILE * f, int attr){
    struct stat st;

    fstat(f, &st);

    if( st.dev && CHK(st.dev) )
        return (st.dev->fscf->ops)(FSOP_FCHMOD, st.dev, f, attr);
    return -1;
}

int
chmod(const char *name, int attr){
    MountEntry *me;

    ME(me, name);
    if( CHK(me) )
        return (me->fscf->ops)(FSOP_CHMOD, me, basenameoffile(name), attr);

    return -1;
}

int
mkdir(const char *name){
    MountEntry *me;

    ME(me, name);
    if( CHK(me) )
        return (me->fscf->ops)(FSOP_MKDIR, me, basenameoffile(name));

    return -1;
}

int
fs_format(const char *name){
    MountEntry *me;

    fsmsg( "fs_format: %s\n", name);
    ME(me, name);
    if( CHK(me) )
        return (me->fscf->ops)(FSOP_FORMAT, me, name);
    return -1;
}

int
deletefile(const char *name){
    MountEntry *me;

    ME(me, name);
    if( CHK(me) )
        return (me->fscf->ops)(FSOP_DELETE, me, basenameoffile(name) );
    return -1;
}

int
renamefile(const char *oname, const char *nname){
    MountEntry *me;

    ME(me, oname);
    if( CHK(me) )
        return (me->fscf->ops)(FSOP_RENAME, me, basenameoffile(oname), nname);
    return -1;
}
#endif

/*****************************************************************
 *****************************************************************/

#ifdef USE_CLI

DEFUN(dir, "list files")
DEFALIAS(dir, l)
DEFALIAS(dir, ls)
DEFALIAS(dir, ll)
{
    int how=0, i;
    const char *what;
    MountEntry *me;

    if( !strcmp(argv[0], "ll") )
        how = LSHOW_ALL | LSHOW_LONG ;
    if( !strcmp(argv[0], "ls") )
        how = LSHOW_SHORT ;

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
                case 's':	how |= LSHOW_SHORT;	break;
                case 'h':
                    printf("-a\tall\n-d\tdevs\n-f\tfilesys\n-l\tlong\n-s\tshort\n");
                    return 0;
                }
            }
            what = argc>2 ? argv[2] : "";
        }else{
            what = argc>1 ? argv[1] : "";

            if( !strcmp(argv[1], DEVPREFIX) ){
                how |= LSHOW_DEVS;
                what = "";
            }
            if( !strcmp(argv[1], ":") ){
                how |= LSHOW_FSYS;
                what = "";
            }
            if( !strcmp(argv[1], "::") ){
                how |= LSHOW_DEVS | LSHOW_FSYS | LSHOW_LONG;
                what = "";
            }

        }
    }

    if( (how & LSHOW_FSYS) || (how & LSHOW_DEVS) ){

        if( how & LSHOW_FSYS ){
            // synthesize a "dev" filesystem
            printf("\tdev:%s\n", (how & LSHOW_LONG) ? "\ttype dev" : "");
        }

        /* list all devs or filesystems */
        me = mountlist;
        while( me ){
            if( (me->flags & MNTE_F_DEV) && (how & LSHOW_DEVS)
                || (me->flags & MNTE_F_FS) && (how & LSHOW_FSYS) ){
                printf("\t%s", me->name);
                if( how & LSHOW_LONG ){
                    if( me->fscf && me->fscf->name )
                        printf("\ttype %s", me->fscf->name);

                }
                printf("\n");
            }
            me = me->next;
        }
        return 0;
    }

#ifdef USE_FILESYS
    me = find_mount(what);
    if( me )
        what = basenameoffile(what);

#ifdef USE_PROC
    if( !me ) me = currproc->cwd;
#endif

    if( !me ){
        fsmsg("no such file or device\n");
        return -1;
    }

    if( me->fscf && me->fscf->ops )
        i = (me->fscf->ops)(FSOP_DIR, me, how, what);
    else
        i = -1;

    if( i )
        f_error("ls [-adfxl] [me]");
    return i;
#else
    f_error("no filesys configured\n");
    return -1;
#endif
}

#ifdef USE_FILESYS
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

DEFUN(chdev, "change device")
DEFALIAS(chdev, cd)
DEFALIAS(chdev, chdir)
{
    int i;

    if( argc < 2 ){
#ifdef MOUNT_ROOT
        return chdir( MOUNT_ROOT );
#else
        f_error("chdir dir");
#endif
    }
    i = chdir(argv[1]);
    if( i )
        f_error("no such device");
    return i;
}

DEFUN(mkdir, "make dir")
{
    if( argc < 2 ){
        f_error("mkdir dirname\n");
        return -1;
    }

    return mkdir( argv[1] );
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

struct GlobArgs {
    struct MountEntry *me;
    struct cli_env *env;
    int replc;
    char **argv;
    int argc;
};

int
globfnc(const char *name, struct GlobArgs *ga){
    char buf[128];

    snprintf(buf, sizeof(buf), "%s%s",
#ifdef USE_PROC
             (ga->me == currproc->cwd) ? "" : ga->me->name,
#else
             ga->me->name,
#endif
             name);

    ga->argv[ ga->replc ] = buf;
    return shell_eval( ga->argc, ga->argv );

}

int
contains_globbing(const char *name){
    short j;
    char bkt=0;

    for(j=0; name[j]; j++){
        if( name[j] == '*' || name[j] == '?' )
            return 1;
        if( name[j] == '[' ) bkt = 1;
        if( name[j] == ']' && bkt ) return 1;
    }
    return 0;
}

DEFUN(glob, "expand wildcards in filenames")
{
    char *buffer;
    short i, j;
    char *pattern=0;
    struct GlobArgs ga;

    ga.replc = 0;
    ga.env   = env;

    if( !strcmp(argv[0], "glob") ){
        argc --;
        argv ++;
    }

    if( argc < 2 ){
        f_error("[glob] cmd pattern");
        return -1;
    }

    // which arg has a pattern?
    for(i=1; i<argc; i++){
        if( contains_globbing( argv[i] ) ){
            pattern  = argv[i];
            ga.replc = i;
            break;
        }
    }

    if( ! pattern )
        return shell_eval(argc, argv, env );


    ga.me = find_mount(pattern);
#ifdef USE_PROC
    if( !ga.me )
        ga.me = currproc->cwd;
#endif
    if( !ga.me ){
        return -1;
    }

    /* strip off devicename */
    pattern = (char*)basenameoffile(pattern);

    ga.argv = argv;
    ga.argc = argc;

    if( CHK(ga.me) )
        return (ga.me->fscf->ops)(FSOP_GLOB, ga.me, pattern, globfnc, &ga);
    return -1;
}

#endif /* USE_FILESYS */
#endif /* USE_CLI */


