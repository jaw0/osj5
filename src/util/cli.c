/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Function: command line interface
*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <ctype.h>
#include <nstdio.h>
#include <proc.h>
#include <get.h>
#include <fs.h>
#include <cli.h>
#include <misc.h>
#include <msgs.h>
#include <bootflags.h>
#include "defproto.h"

#ifndef USE_NSTDIO
#error "cli requires feature NSTDIO"
#endif

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

static int show(int, const char**, struct cli_env*);
static int set (int, const char**, struct cli_env*);
static int help(int, const char**, struct cli_env*);
int shell_eval(int, const char**, struct cli_env*);
void fshell(FILE*, int);
void shell(void);

extern char *strchr(const char*, char);
extern double atof(const char*);


typedef long long quad;
typedef unsigned long long u_quad;

char gprompt[32] = "$[35;1m$v$g$[39;0m ";     // 35 = purple

#ifdef PLATFORM_I386
extern long k_paddr, bootmem0, bootmem1;
#endif
#ifdef N_RTC
extern utime_t boottime;
#endif

static const struct Cmd {
    const char *name;
    const char *help;
    int (*fnc)(int, const char**, struct cli_env*);
} cmds[] = {
    { "exit",     "exit",                         0 },

#define DEFUN(name, doc)                                        \
    { QUOTIFY(name),	doc,		CONCAT(ui_f_, name) },

#define DEFALIAS(name, alias)                                   \
    { QUOTIFY(alias), 	0,		CONCAT(ui_f_, name) },

#include "defun.list"
    { 0,0,0 }
};

static const struct Var {
    const char *name;
    const char *help;
    const void *addr;
    u_int type;

#define IN_ENV(a, b)	(void*)offsetof(struct cli_env, a), UV_TYPE_ENV | b
#define IN_PROC(a, b)	(void*)offsetof(struct Proc, a), UV_TYPE_PROC | b

} vars[] = {
    { "prompt",  "the prompt",               IN_ENV(prompt,  UV_TYPE_STR32) },
    { "verbose", "echo commands in scripts", IN_ENV(verbose, UV_TYPE_UC) },
    { "noglob",  "disable file globbing",    IN_ENV(noglob,  UV_TYPE_UC) },

    { "gprompt", "default system prompt",    gprompt,       UV_TYPE_STR32 },
    { "time",    "temporal displacement",    &systime,      UV_TYPE_TIME },
    { "itime",   "temporal displacement",    &systime,      UV_TYPE_UQ },

    { "tsl",     "process timeslice",        IN_PROC(timeslice, UV_TYPE_UC) },
    { "currproc",0,                          &currproc,  UV_TYPE_ULX | UV_TYPE_RO },
    { "ident",   "system identity",          ident,      UV_TYPE_STR32 | UV_TYPE_RO },
    { "arch",    "system arch",              archid,     UV_TYPE_STR32 | UV_TYPE_RO },


#define DEFVAR(proto, name, init, type, docstr)	\
    { QUOTIFY(name),	docstr,		     &name, type },
#define DEFCONFUNC(name, f) /* */


#include "defvar.list"

    {0,0,0,0}
};

#undef DEFUN
#undef DEFALIAS
#undef DEFVAR
#undef DEFCONFUNC

static const struct {
    int (*func)(FILE *);
} confuncs[] = {
#define DEFVAR(proto, name, init, type, docstr) /* */
#define DEFCONFUNC(name, f)	{ name },

#include "defvar.list"
    { 0 }
};

/****************************************************************/

#undef DEFUN
#undef DEFALIAS
#undef DEFVAR
#undef DEFCONFUNC
#include <userint.h>


void
f_error(const char *m){
    fprintf(STDERR, "ERROR: %s\n", m);
}

DEFUN(version, "display version information")
DEFALIAS(version, vers)
DEFALIAS(version, ver)
{

    printf("%s\n", version);

    /* uptime, image name, devices, memory, ... */
    return 0;
}

static inline const struct Var *
find_var(struct cli_env *env, const char *var){
    short i;

    for(i=0; vars[i].name; i++)
        if( !strcmp(vars[i].name, var)) return vars + i;
    return 0;
}

static int
interp_varref(struct cli_env *env, const struct Var *v, char *buf, int buflen){
    int off = 0;

    if( !v ) return;

    if( v->type & UV_TYPE_ENV ){
        if( !env ) return;
        off = (int)env;
    }
    if( v->type & UV_TYPE_PROC )
        off = (int)currproc;

    switch( v->type & UV_TYPE_MASK ){
    case UV_TYPE_STR16:
    case UV_TYPE_STR32:
        snprintf(buf, buflen, "%s", v->addr + off);
        break;
    case UV_TYPE_UC:
        snprintf(buf, buflen, "%u", *(u_char*)(v->addr + off));
        break;
    case UV_TYPE_US:
        snprintf(buf, buflen, "%u", *(u_short*)(v->addr + off));
        break;
    case UV_TYPE_ULX:
        snprintf(buf, buflen, "0x%x", *(u_long*)(v->addr + off));
        break;
    case UV_TYPE_UL:
        snprintf(buf, buflen, "%u", *(u_long*)(v->addr + off));
        break;
    case UV_TYPE_UQ:
        snprintf(buf, buflen, "%Qu", *(u_quad*)(v->addr + off));
        break;
    case UV_TYPE_SC:
        snprintf(buf, buflen, "%d", *(u_char*)(v->addr + off));
        break;
    case UV_TYPE_SS:
        snprintf(buf, buflen, "%d", *(u_short*)(v->addr + off));
        break;
    case UV_TYPE_SL:
        snprintf(buf, buflen, "%d", *(u_long*)(v->addr + off));
        break;
    case UV_TYPE_SQ:
        snprintf(buf, buflen, "%Qd", *(u_quad*)(v->addr + off));
        break;
    case UV_TYPE_IP:
        snprintf(buf, buflen, "%I", *(u_long*)(v->addr + off));
        break;
    case UV_TYPE_TIME:
        snprintf(buf, buflen, "%#T", *(u_quad*)(v->addr + off));
        break;
    case UV_TYPE_FLOAT:
        snprintf(buf, buflen, "%f", *(float*)(v->addr + off));
        break;
    default:
        return -1;
    }
    return 0;
}

int
interp_var(struct cli_env *env, const char *var, char *buf, int buflen){

    const struct Var *v = find_var(env, var);
    if( !v ) return -1;

    return interp_varref(env, v, buf, buflen);
}


DEFUN(show, "show var")
DEFALIAS(show, sho)
DEFALIAS(show, sh)
{
    char buf[32];
    short i;

    if( argc != 2 ){
        f_error("show what?");
        return -1;
    }

    i = interp_var(env, argv[1], buf, sizeof(buf));
    if( !i ){
        printf("%s = %s\n", argv[1], buf);
#ifdef USE_FILESYS
    }else if( !strcmp(argv[1], "run") ){
        // show run
        ui_f_config(0, 0, env);
#endif
    }else{
        f_error("show: no such var");
        return -1;
    }
    return 0;
}

/* set a b  or  a = b */
DEFUN(set, "set a var")
{
    short i, n;
    const char *var;
    u_long v;
    int off = 0;

    if( argc != 3 ){
        f_error("set what?");
        return -1;
    }
    if( strcmp("set", argv[0])){
        /* we got a = b */
        var = argv[0];
    }else{
        var = argv[1];
    }

    for(i=0; vars[i].name; i++)
        if( !strcmp(vars[i].name, var)) break;
    if( vars[i].name ){
        if( vars[i].type & UV_TYPE_ENV )
            off = (int)env;
        if( vars[i].type & UV_TYPE_PROC )
            off = (int)currproc;
        if( vars[i].type & UV_TYPE_RO ){
            fprintf(STDERR, "%s: read-only\n", var);
            return -1;
        }
        short type = vars[i].type & UV_TYPE_MASK;
        switch( type ){
        case UV_TYPE_STR16:
        case UV_TYPE_STR32:
            n = (type==UV_TYPE_STR16)? 16 : 32;
            strncpy( (char*)(vars[i].addr + off), argv[2], n);
            ((char*)(vars[i].addr + off))[n-1] = 0;
            break;
        case UV_TYPE_UC:
        case UV_TYPE_SC:
            v = atoi( argv[2] );
            *(u_char*)(vars[i].addr + off) = v;
            break;
        case UV_TYPE_US:
        case UV_TYPE_SS:
            v = atoi( argv[2] );
            *(u_short*)(vars[i].addr + off) = v;
            break;
        case UV_TYPE_UL:
        case UV_TYPE_SL:
            v = atoi( argv[2] );
            *(u_long*)(vars[i].addr + off) = v;
            break;
        case UV_TYPE_TIME:
            *(u_quad*)(vars[i].addr + off) = timeiso( argv[2] );
#ifdef USE_RTC
            set_rtc();
#endif
            break;
        case UV_TYPE_SQ:
        case UV_TYPE_UQ: {
            quad val;
            val = strtoq(argv[2], 0, 0);
            *(u_quad*)(vars[i].addr + off) = val;
            break;
        }
#ifndef NOPRINTFFLOAT
        case UV_TYPE_FLOAT:
            *(float*)(vars[i].addr + off) = atof( argv[2] );
            break;
#endif
#if 0
        case UV_TYPE_IP:
            v = inet_aton( argv[2] );
            *(u_long*)(vars[i].addr + off) = v;
            break;
#endif
        }
    }else{
        printf("set %s: no such var\n", var);
        return -1;
    }
    return 0;
}

#ifdef USE_FILESYS

static const char const *_conf_argv[] = { "conf" };

// output all vars marked as configurable
int
save_config(const char *file){
    short i, r, ml=0;
    char buf[32];
    const struct Var *bv=0, *pv=0;
    FILE *f;

    if( file ){
        f = fopen(file, "w");
        if(!f){
            f_error("cannot open file\n");
            return 1;
        }
    }else{
        f = STDOUT;
    }

    fprintf(f, "# autogenerated config\n# system ident %s\n", ident);

    // measure
    for(i=0; vars[i].name; i++){
        if( !(vars[i].type & UV_TYPE_CONFIG) ) continue;
        short l = strlen(vars[i].name);
        if( l > ml ) ml = l;
    }

    // sort + print
    while(1){
        bv = 0;
        for(i=0; vars[i].name; i++){
            if( !(vars[i].type & UV_TYPE_CONFIG) ) continue;
            if( vars[i].type & UV_TYPE_ENV )       continue;
            if( vars[i].type & UV_TYPE_PROC )      continue;

            if( pv && strcmp(pv->name, vars[i].name) >= 0 ) continue;
            if( bv && strcmp(bv->name, vars[i].name) <  0 ) continue;
            bv = vars + i;
        }
        if( ! bv ) break;
        pv = bv;

        r = interp_varref(0, bv, buf, sizeof(buf));
        if( r ) continue;
        switch(bv->type & UV_TYPE_MASK){
        case UV_TYPE_STR16:
        case UV_TYPE_STR32:
        case UV_TYPE_TIME:
            fprintf(f, "%-*s = '%s'\n", ml, bv->name, buf);
            break;
        default:
            fprintf(f, "%-*s = %s\n",   ml, bv->name, buf);
            break;
        }
    }

    // run all config functions
    for(i=0; confuncs[i].func; i++){
        (* confuncs[i].func)(f);
    }

    if( file ) fclose(f);
    return 0;
}

// also: show run
// config > file
DEFUN(config, "generate config")
{
    save_config(0);
    return 0;
}
#endif


DEFUN(help, "help for commands")
DEFALIAS(help, ?)
{
    short  i;

    /* if no args, show all commands/vars */
    if( argc < 2 ){
        printf("help command|var\ncommands:");
        short cd, pl = 0;
        // 6 columns of short names, 2 columns of longer names, 1 column of untypeable names
        for(cd=1; cd<=4; cd<<=1){
            short cols = 6/cd;
            short ml   = 72 / cols - 2;
            short j    = 0;
            const struct Cmd *b=0, *p=0;

            while(1){
                b = 0;
                for(i=0; cmds[i].name; i++){
                    if( ! cmds[i].help ) continue;
                    int l = strlen(cmds[i].name);
                    if( l > ml )  continue;
                    if( l <= pl ) continue;
                    if( p && strcmp(p->name, cmds[i].name) >= 0 ) continue;
                    if( b && strcmp(b->name, cmds[i].name) <  0 ) continue;
                    b = cmds + i;
                }
                if( !b ) break;
                p = b;

                if( !(j++ % cols) ) printf("\n    ");
                printf("%-*s  ", ml, b->name);
            }

            pl = ml;
        }

        printf("\nvars:");
        pl = 0;
        for(cd=1; cd<=4; cd<<=1){
            short cols = 6/cd;
            short ml   = 72 / cols - 2;
            short j    = 0;
            const struct Var *b=0, *p=0;

            while(1){
                b = 0;
                for(i=0; vars[i].name; i++){
                    if( ! vars[i].help ) continue;
                    int l = strlen(vars[i].name);
                    if( l > ml )  continue;
                    if( l <= pl ) continue;
                    if( p && strcmp(p->name, vars[i].name) >= 0 ) continue;
                    if( b && strcmp(b->name, vars[i].name) <  0 ) continue;
                    b = vars + i;
                }
                if( !b ) break;
                p = b;

                if( !(j++ % cols) ) printf("\n    ");
                printf("%-*s  ", ml, b->name);
            }
            pl = ml;
        }

        printf("\n");
        return 0;
    }

    /* a command ? */
    for(i=0; cmds[i].name; i++)
        if( !strcmp(cmds[i].name, argv[1])) break;
    if( cmds[i].name ){
        printf("%s: %s\n", cmds[i].name, cmds[i].help ? cmds[i].help : "undocumented");
        return 0;
    }

    /* a var */
    for(i=0; vars[i].name; i++)
        if( !strcmp(vars[i].name, argv[1])) break;
    if( vars[i].name ){
        printf("%s: %s\n", vars[i].name, vars[i].help ? vars[i].help : "undocumented");
        return 0;
    }

    fprintf(STDERR, "%s: no such command or variable\n", argv[1]);
    return -1;
}

DEFUN(cli, "start a subshell")
{
    shell();
    return 0;
}

DEFUN(echo, "echo")
{
    char nl=1;

    if( argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n' ){
        nl = 0;
        argc --;
        argv ++;
    }

    while( --argc){
        printf("%s ", *++argv);
    }

    if( nl ) printf("\n");
    return 0;
}

DEFUN(stty, "set terminal modes")
{
    int i, m;

    if( argc < 2 ){
        f_error("stty +|-{inlcr,icrnl,igncr,onlcr,istrip,ocrnl,onocr,onlret,ostrip,echo,echoctl} | stty -a");
        return -1;
    }
    while(++argv, --argc){
        if( **argv == '-' )
            i = 1;
        else
            i = 0;
        if( **argv == '-' || **argv == '+' )
            (*argv)++;

        if( !strcmp("inlcr",  *argv)) m = F_INLCR;
        if( !strcmp("icrnl",  *argv)) m = F_ICRNL;
        if( !strcmp("igncr",  *argv)) m = F_IGNCR;
        if( !strcmp("istrip", *argv)) m = F_ISTRIP;
        if( !strcmp("ostrip", *argv)) m = F_OSTRIP;
        if( !strcmp("onlcr",  *argv)) m = F_ONLCR;
        if( !strcmp("ocrnl",  *argv)) m = F_OCRNL;
        if( !strcmp("onocr",  *argv)) m = F_ONOCR;
        if( !strcmp("onlret", *argv)) m = F_ONLRET;
        if( !strcmp("echo",   *argv)) m = F_ECHO;
        if( !strcmp("echoctl",*argv)) m = F_ECHOCTL;

        if( !strcmp("a", *argv)){
            m = 0;
#define F(x)	((STDIN->flags & x) ? '+' : '-')
            printf("    %cinlcr %cicrnl %cigncr %cistrip\n"
                   "    %conlcr %cocrnl %conocr %conlret %costrip\n"
                   "    %cecho %cechoctl\n",
                   F(F_INLCR), F(F_ICRNL), F(F_IGNCR), F(F_ISTRIP),
                   F(F_ONLCR), F(F_OCRNL), F(F_ONOCR), F(F_ONLRET), F(F_OSTRIP),
                   F(F_ECHO), F(F_ECHOCTL));
#undef F
        }else if( !m ){
            printf("mode \"%s\" unknown\n", *argv);
            return -1;
        }

        if( i ){
            STDIN->flags  &= ~m;
            STDOUT->flags &= ~m;
        }else{
            STDIN->flags  |= m;
            STDOUT->flags |= m;
        }
    }
    return 0;
}

static const char * const _codepage[] = {
    "binary",
    "ascii",
    "gfxdpy",
    "utf8",
    "latin1",
    "pc437",
};


DEFUN(codepage, "set/get the current code page")
{
    if( !STDOUT ){
        f_error("stdout is closed\n");
        return -1;
    }
    if( argc < 2 ){
        // display current setting
        if( STDOUT->codepage < ELEMENTSIN(_codepage) )
            printf("codepage %s\n", _codepage[STDOUT->codepage]);
        else
            printf("codepage unknown\n");
        return 0;
    }

    int i;
    // search list
    for(i=0; i<ELEMENTSIN(_codepage); i++){
        // match?
        if( !strcmp(argv[1], _codepage[i]) ){
            STDOUT->codepage = i;
            return 0;
        }
    }

    // so sorry
    fprintf(STDERR, "ERROR: codepage:");
    for(i=0; i<ELEMENTSIN(_codepage); i++){
        fprintf(STDERR, " %s", _codepage[i]);
    }
    fprintf(STDERR, "\n");
    return -1;
}



DEFUN(run, "start a process")
{
    int size;
    u_long addr;
    proc_t pid;

    if( argc != 3 && argc != 2 ){
        f_error("run size addr | run file");
        return -1;
    }

#ifdef USE_FILESYS
    if( argc == 2 ){
        FILE *f;

        f = fopen(argv[1], "r");
        if( f ){
            fshell(f, 0);
            fclose(f);
            return 0;
        }else{
            fprintf(STDERR, "could not open file \"%s\"\n", argv[1]);
            return -1;
        }
    }
#endif

    size = atoi( argv[1] );
    addr = atoi_base(16, argv[2] );

    pid = start_proc(size, (void*)addr, "shell (run)" );

    printf( "pid: %08.8x\n", pid);
    return 0;
}


DEFUN(reboot, "reboot system")
{
    reboot();
}

#ifdef USE_FILESYS
DEFUN(file, 0)
{
    FILE *f;
    int how;
    int c;

    if( argc != 4 ){
        f_error("file put|get txt|uu filename");
        return -1;
    }

    if( !strcmp(argv[1], "put") ){
        how = 0;
        f = fopen(argv[3], "r");
    }else if( !strcmp(argv[1], "get") ){
        how = 1;
        f = fopen(argv[3], "w");
    }else{
        f_error("file put|get txt|uu filename");
        return -1;
    }

    if( !f ){
        fprintf(STDERR, "could not open file \"%s\"\n", argv[3]);
        return -1;
    }

    if( !strcmp(argv[2] , "txt") ){
        if(how){
            while( (c=getchar()) != 4 ){	/* until ^D */
                fputc(c, f);
                if( env && env->verbose )
                    putchar(c);
            }
        }else{
            while( (c=fgetc(f)) != -1 ){
                putchar(c);
            }
        }
    }



    fclose(f);
    return 0;
}

DEFUN(cat, "cat files")
{
    int i;
    FILE *f;
    char buf[32];

    if( argc < 2 ){
        /* stdin -> stdout */
        while( (i=getchar())!=-1 && i!=4 )
            putchar(i);
        return 0;
    }

    while(++argv, --argc){
        f = fopen( *argv, "r" );
        if( f ){
            while( (i=fread(f, buf, sizeof(buf))) > 0 ){
                fwrite(STDOUT, buf, i);
            }
            fclose(f);
        }else{
            fprintf(STDERR, "could not open file \"%s\"\n", *argv);
        }
    }
    return 0;
}

DEFUN(more, "page through files")
{
    int i, c, n=0;
    FILE *f;

    if( argc < 2 ){
        return 0;
    }

    while(++argv, --argc){
        f = fopen( *argv, "r" );
        if( f ){
            while( (c=fgetc(f)) != -1 ){
                fputc(c, STDOUT);
                if( c == '\n' ){
                    n++;
                    if( n == 23 ){
                        fputs("--More--", STDOUT);
                        while(1){
                            c = getchar();
                            switch(c){
                            case ' ':  n = 0;	break;
                            case '\n': n--;		break;
                            case 'q':  goto done;
                            default:
                                fputc('\a', STDOUT);
                                continue;
                            }
                            break;
                        }
                        fputs("\r        \b\b\b\b\b\b\b\b", STDOUT);
                    }
                }
            }
        done:
            fclose(f);
        }else{
            fprintf(STDERR, "could not open file \"%s\"\n", *argv);
        }
    }
    return 0;
}

DEFUN(copy, "copy files")
DEFALIAS(copy, cp)
{
    MountEntry *dev;
    struct stat st;
    int i;
    FILE *fr, *fw;
    char buf[32];
    const char *name;
    int attr;

    if( argc != 3 && argc != 2 ){
        f_error("copy file [newfile|dev]");
        return -1;
    }

    if( argc == 2 ){
        argv[2] = argv[1];
    }

    if( !(fr=fopen(argv[1], "r")) ){
        fprintf(STDERR, "could not open file \"%s\"\n", argv[1]);
        return -1;
    }
    fstat(fr, &st);
    attr = st.mode;

    dev = find_mount(argv[2]);
    if( dev && !(dev->flags & SSF_SPECIAL) && !strcmp(argv[2], dev->name)){
        /* cp file dev */
        snprintf(buf, sizeof(buf), "%s%s", argv[2], basenameoffile(argv[1]));
        name = buf;
    }else{
        name = argv[2];
    }

    if( !(fw=fopen(name, "w")) ){
        fprintf(STDERR, "could not open file \"%s\"\n", name);
        fclose(fr);
        return -1;
    }
    fchmod(fw, attr);

    while( (i=fread(fr, buf, sizeof(buf))) > 0 ){
        fwrite(fw, buf, i);
    }

    fclose(fw);
    fclose(fr);
    return 0;
}
static const char foobuf[] = "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_`abcdefghijklmnopqrstuvwxyz{|}~\n";

DEFUN(mkfile, 0)
{
    int i, len;
    FILE *f;

    if( argc != 3 ){
        f_error("mkfile name len");
        return -1;
    }

    f = fopen( argv[1], "w" );
    len = atoi(argv[2]);
    if( f ){
        for(i=0; i<len/(sizeof(foobuf)-1); i++){
            fwrite(f, foobuf, sizeof(foobuf)-1);
        }
        fwrite(f, foobuf, len - i*(sizeof(foobuf)-1));
        fclose(f);
    }
    return 0;
}

#endif

DEFUN(clear, "clear screen")
DEFALIAS(clear, cls)
{
    printf("\e[H\e[J");
    return 0;
}

DEFUN(msleep, "sleep millisecs")
{
    if( argc < 2 ) return 0;
    usleep( 1000 * atoi(argv[1]) );
    return 0;
}

static void
prompt(struct cli_env *env, int prno){
    const char *p = env->prompt;
    int u;

    for(;*p; *p++){
        if( *p != '$' ){
            putchar(*p);
            continue;
        }
        p ++;
        if( !p ) break;
        switch( tolower(*p) ){
        case '$':	putchar('$');	break;
        case 'e':	putchar('\e');	break;
        case '[':	putchar('\e'); putchar('[');	break;
        case 'n':	printf("%s", currproc->cwd ? currproc->cwd->name : "?"); break;
        case 'v':
            // version or mode
            switch(prno){
            case 0:  printf("%s", ident); break;
            case 1:  printf("\\");        break;
            case 2:  printf("...");       break;
            }
            break;
        case 'g':
            switch( STDOUT->codepage ){
            case CODEPAGE_UTF8:
                printf("%+c", 0x27A1);		break;	// large right arrow
            case CODEPAGE_PC437:
                printf("\x1A");			break;	// right arrow
            case CODEPAGE_GFXDPY:
                printf("\x82");			break;	// right arrow
            default:
                printf("=>");
            }
            break;

        case '{':
            // ${1234} => insert utf-8
            u = strtoul(p + 1, &p, 16);
            printf("%+c", u);
            break;
        }
    }
}



/*
  (forward) polish notation

     -f file       True if file exists
     -s file       True if file exists and has a size greater than zero.

     -n string     True if the length of string is nonzero.
     -z string     True if the length of string is zero.

     string        True if string is not the null string.
     -eq s1 s2     True if the strings s1 and s2 are identical.
     -ne s1 s2     True if the strings s1 and s2 are not identical.
     -lt s1 s2     True if string s1 comes before s2 based on the ASCII value
                   of their characters.
     -gt s1 s2     True if string s1 comes after s2 based on the ASCII value
                   of their characters.
     == n1 n2      True if the integers n1 and n2 are algebraically equal.
     != n1 n2      True if the integers n1 and n2 are not algebraically equal.
     > n1 n2       True if the integer n1 is algebraically greater than the
                   integer n2.
     >= n1 n2      True if the integer n1 is algebraically greater than or
                   equal to the integer n2.
     < n1 n2       True if the integer n1 is algebraically less than the
                   integer n2.
     <= n1 n2      True if the integer n1 is algebraically less than or equal
                   to the integer n2.
     ! expression  True if expression is false.
     & expression1 expression2
                   True if both expression1 and expression2 are true.
     | expression1 expression2
                   True if either expression1 or expression2 are true.

*/

static inline const char *
test_pop(const char **stack, short *sp){
    if( *sp <= 0 ) return "";
    return stack[ --*sp ];
}
static inline void
test_push(const char **stack, short *sp, const char *x){
    if(  *sp > 10 ) return;
    stack[ (*sp)++ ] = x;
}
static inline int
test_bool(const char *x){
    if(!x)      return 0;
    if( !x[0] ) return 0;
    // NB: "0" is true
    return 1;
}
static inline int
test_filesize(const char *x){
#ifdef USE_FILESYS
    struct stat s;
    FILE *f = fopen(x, "r");
    if( !f ) return -1;
    fstat(f, &s);
    fclose(f);
    return s.size;
#endif
    return 0;
}

#define PUSH(x)		test_push(stack, &sp, x)
#define POP()		test_pop(stack, &sp)
#define POPINT()	atoi( POP() )
#define POPBOOL()	test_bool(POP())
#define ELIF_ARG_IS(x)	else if( !strcmp(argv[argp], x) )
#define PSTACK() 	\
    fprintf(STDERR, "[");                                                \
    for(i=0; i<sp; i++) fprintf(STDERR, "%s%s", (i?", " : ""), stack[i]&&stack[i][0] ? stack[i] : "."); \
    fprintf(STDERR, "]")


DEFUN(test, "test a condition")
DEFALIAS(test, [)
{
    const char *stack[10];
    short sp = 0;
    short argp;
    short i;
    char verbose = 0;

    // ignore final ], so we can say "if [ -f foo ]"
    if( argc && !strcmp(argv[argc-1], "]") ) argc --;

    // -V - verbose test mode
    if( argc > 1 && !strcmp("-V", argv[1]) ){
        verbose = 1;
        argc --;
        argv ++;
    }

    // no expr? return false
    if( argc < 2 ) return 1;

    for(argp=argc-1; argp>0; argp--){

        if( verbose ){
            PSTACK();
        }

        if( !argv[argp][0] ) PUSH("");
        ELIF_ARG_IS("==")  PUSH( ( POPINT() == POPINT()) ? "t" : "" );
        ELIF_ARG_IS("!=")  PUSH( ( POPINT() != POPINT()) ? "t" : "" );
        ELIF_ARG_IS(">")   PUSH( ( POPINT() >  POPINT()) ? "t" : "" );
        ELIF_ARG_IS("<")   PUSH( ( POPINT() <  POPINT()) ? "t" : "" );
        ELIF_ARG_IS(">=")  PUSH( ( POPINT() >= POPINT()) ? "t" : "" );
        ELIF_ARG_IS("<=")  PUSH( ( POPINT() <= POPINT()) ? "t" : "" );

        ELIF_ARG_IS("-eq") PUSH( (strcmp(POP(), POP()) == 0) ? "t" : "" );
        ELIF_ARG_IS("-ne") PUSH( (strcmp(POP(), POP()) != 0) ? "t" : "" );
        ELIF_ARG_IS("-lt") PUSH( (strcmp(POP(), POP()) <  0) ? "t" : "" );
        ELIF_ARG_IS("-gt") PUSH( (strcmp(POP(), POP()) >  0) ? "t" : "" );
        ELIF_ARG_IS("-le") PUSH( (strcmp(POP(), POP()) <= 0) ? "t" : "" );
        ELIF_ARG_IS("-ge") PUSH( (strcmp(POP(), POP()) >= 0) ? "t" : "" );

        ELIF_ARG_IS("-n")  PUSH( strlen(POP()) ? "t" : "" );
        ELIF_ARG_IS("-z")  PUSH( strlen(POP()) ? "" : "t" );
        ELIF_ARG_IS("-f")  PUSH( (test_filesize(POP()) != -1) ? "t" : "" );
        ELIF_ARG_IS("-f")  PUSH( (test_filesize(POP()) != -1) ? "t" : "" );
        ELIF_ARG_IS("-s")  PUSH( (test_filesize(POP()) >   0) ? "t" : "" );

        ELIF_ARG_IS("&"){
            char a = POPBOOL(), b = POPBOOL();
            PUSH( (a && b) ? "t" : "" );
        }
        ELIF_ARG_IS("|"){
            char a = POPBOOL(), b = POPBOOL();
            PUSH( (a || b) ? "t" : "" );
        }

        else{
            // a string
            PUSH( argv[argp] );
        }

        if( verbose ){
            fprintf(STDERR, " %s => ", argv[argp]);
            PSTACK();
            fprintf(STDERR, "\n");
        }
    }

    if( verbose ){
        PSTACK();
        fprintf(STDERR, "\n");
    }

    // stack contains different than 1 element - return false
    if( sp != 1 ) return 1;

    if( stack[0] && stack[0][0] ) return 0;
    return 1;
}


int
shell_eval(int argc, const char **argv, struct cli_env *env){
    short i, j, v, n=0;
    char globp=0;

#ifdef USE_FILESYS
    //  need glob?
    if( !env || !env->noglob ){
        for(i=1; i<argc; i++){
            if( contains_globbing( argv[i] ) ){
                globp = 1;
                break;
            }
        }
    }
#endif

    for(i=0; cmds[i].name; i++)
        if( !strcmp(cmds[i].name, argv[0])) break;

    if( !cmds[i].name && argc > 2 && !strcmp("=", argv[1]))
        return ui_f_set(argc, argv, env);

    if( !cmds[i].name ){
        fprintf(STDERR, "command not found: \"%s\"\n", argv[0]);
        return -1;
    }

#ifdef USE_FILESYS

    // redirection:
    //   < file		input
    //   > file		output
    //   >& file	output + error
    //   >> file	output, append
    //   >>& file	output + error, append
    // NB: space is required ( >file is no good)

    const char *ca, *infile=0, *outfile=0;
    FILE *f=0, *s_in=0, *s_out=0, *s_err=0;
    char cai, append=0, anderr=0;

    for(cai=2; cai<=4; cai+=2){
        if( cai > argc - 1 ) break;
        ca = argv[argc-cai];

        if( ca[0] == '<' ){
            infile = argv[argc-cai+1];
        }else if( ca[0] == '>' ){
            outfile = argv[argc-cai+1];

            if( ca[1] == '&' ) anderr = 1;
            if( ca[1] == '>' ){
                append = 1;
                if( ca[2] == '&' ) anderr = 1;
            }
        }else{
            break;
        }
    }

    if( infile ){
        f = fopen( infile, "r" );
        if( !f ){
            fprintf(STDERR, "could not open \"%s\"\n", infile );
            return -1;
        }
        s_in = STDIN;
        STDIN = f;
        argc -= 2;
    }
    if( outfile ){
        f = fopen( outfile, append ? "a" : "w" );
        if( !f ){
            fprintf(STDERR, "could not open \"%s\"\n", outfile );
            if( s_in ) STDIN = s_in;
            return -1;
        }
        s_out = STDOUT;
        s_err = STDERR;
        STDOUT = f;
        if( anderr ) STDERR = f;
        argc -= 2;
    }

    int r;
    if( globp ){
        r = ui_f_glob(argc, argv, env);
    }else{
        r = (*cmds[i].fnc)(argc, argv, env);
    }

    if( s_in ){
        fclose( STDIN );
        STDIN = s_in;
    }
    if( s_out ){
        fclose( STDOUT );
        STDOUT = s_out;
    }
    if( s_err ) STDERR = s_err;

    return r;

#else
    return (*cmds[i].fnc)(argc, argv, env);
#endif
}

#define BUFSIZE 1024
#define ARGLEN  24

static int
shell_next_line(struct cli_env *env, char *buf, int prno){

    int i = 0;

    while(1){
        if( env->interactive ){
            if( i )
                prompt(env, 1);
            else
                prompt(env, prno);
            getline(buf+i, BUFSIZE-i, 0);
        }else{
            if( !fgets(buf+i, BUFSIZE-i, env->f) ){
                // eof
                return -1;
            }
        }
        i = strlen(buf);
        if( buf[i-1] != '\\' )
            break;
        else
            buf[ --i ] = 0;
    }

    if( !env->interactive && env->verbose )
        printf("%s\n", buf);

    return 0;
}

static char *
shell_interp_var(struct cli_env *env, char *buf, char *p, char **argv){
    char tmp[64];
    const struct Var *var=0, *vx;
    int off=0;
    short buflen, varlen, vallen;

    // find longest matching var
    for(vx=vars; vx->name; vx++){
        //printf("  - %s\n", vx->name ? vx->name : "-");
        if( !strncmp(p+1, vx->name, strlen(vx->name)))
            if( !var || strlen(vx->name) > strlen(var->name) ) var = vx;
    }
    if( !var ) return p;	// not found

    switch( var->type & UV_TYPE_MASK ){
    case UV_TYPE_STR16:
    case UV_TYPE_STR32:
        if( p == *argv && strlen(p+1) == strlen(var->name) ){
            // arg is exactly $var, copy pointer into argv
            if( var->type & UV_TYPE_ENV ){
                if( !env ) break;
                off = (int)env;
            }
            if( var->type & UV_TYPE_PROC )
                off = (int)currproc;

            // copy pointer
            *argv = (char*) var->addr + off;
            // move ahead
            return p + strlen(var->name);
        }
    default:
        // interp var to tmp buf
        interp_varref(env, var, tmp, sizeof(tmp));
        // insert tmp into p
        vallen = strlen(tmp);
        varlen = strlen(var->name) + 1;
        buflen = BUFSIZE - (p - buf) - vallen - varlen + 1;
        // slide everything in buf over
        bcopy(p + varlen, p + vallen, buflen);
        // insert value
        bcopy(tmp, p, vallen);

        return p + vallen - 1;
    }

    return p;
}


int
shell_parse_line(struct cli_env *env, char *buf, char **argv){

    int argc = 0;
    char *p = buf;
    char qc;

    while( *p && (argc < ARGLEN) ){

        /* skip white */
        while( *p ==' ' || *p == '\t' ){
        next_token:
            *p++ = 0;
        }

        /* end of input */
        if( ! *p ){
            break;
        }

        /* comment to end-of-line */
        if( *p=='#' ){
            *p = 0;
            break;
        }

        /* single quoted arg */
        if( *p == '\'' ){
            p++;
            argv[argc++] = p;
            while( *p && *p!='\'' ){
                p++;
            }
            /* terminate arg */
            if( *p ) *p++ = 0;
            continue;
        }

        /* double-quoted arg or bare-word until space : $var are expanded */
        if( *p == '"' ){
            qc = 1;
            p ++;
        }else
            qc = 0;

        argv[argc++] = p;
        while( *p && (qc ? (*p!='"') : !isspace(*p)) ){

            if( *p == '$' ){
                p = shell_interp_var(env, buf, p, argv + argc - 1);
            }
            p ++;
        }
        if( *p ) *p++ = 0;
        continue;

    }

    return argc;
}

DEFUN(if, "conditional")
{
    if( argc < 2 ){
        f_error("if command ...\n");
        return -1;
    }
    int cv = shell_eval( argc - 1, argv + 1, env );
    int gotelse = 0;
    int nesting = 0;

    while(1){
        int i = shell_next_line(env, env->buf, 2);
        if( i == -1 ){
            // eof
            return -1;
        }

        argc = shell_parse_line(env, env->buf, env->argv);

        if( !nesting && !strcmp("else", argv[0]) ){
            if( gotelse ){
                f_error("parse error: else unexpected\n");
                return -1;
            }

            gotelse = 1;
            cv = !cv;
            continue;
        }

        if( !strcmp("endif", argv[0]) ){
            if( !nesting ) break;
            nesting --;
            continue;
        }

        if( !strcmp("if", argv[0]) ){
            nesting ++;
            continue;
        }

        if( !nesting && !cv )
            shell_eval(argc, argv, env);


    }

    return 0;
}


void
fshell(FILE *f, int interactivep){
    Catchframe cf;
    char *argv[ARGLEN];
    int  argc;
    int i;

    struct cli_env *env = (struct cli_env*)alloc(sizeof(struct cli_env));
    char *buf = (char*)alloc(BUFSIZE);
    bzero(env, sizeof(struct cli_env));

    strncpy(env->prompt, gprompt, sizeof(env->prompt));
    env->f = f ? f : STDIN;
    env->buf  = buf;
    env->argv = argv;
    env->interactive = interactivep;

    /* handle ^C */
    if( !f ){
        fsetcchar(0, 0, 3);
    }
    if(0){
    xyz:
        UNCATCH(cf);
    }
    CATCHL(cf, MSG_CCHAR_0, xyz);

    while(1){
        i = shell_next_line(env, buf, 0);
        if( i == -1 ){
            // eof
            break;
        }

        argc = shell_parse_line(env, buf, argv);

        if( !argc )
            continue;
        if( !strcmp("exit", argv[0] )) break;

        shell_eval(argc, (const char**)argv, env);
    }

    UNCATCH(cf);
    free(buf, BUFSIZE);
    free(env, sizeof(struct cli_env));
}


#if defined(USE_FILESYS)
int
run_script(const char* file){
    FILE *f;
    f = fopen(file, "r" );
    if( f ){
        fshell(f, 0);
        fclose(f);
        return 0;
    }
    return 1;
}
#endif

void
shell(void){
#if defined(USE_FILESYS) & defined(MOUNT_ROOT)
    if( !(bootflags & BOOT_NORC) )
        run_script(MOUNT_ROOT "shell.rc");
#endif
    fshell(0, 1);
}

