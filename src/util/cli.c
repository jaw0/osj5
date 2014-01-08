/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Function: command line interface
*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
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

static int show(int, char**, struct cli_env*);
static int set (int, char**, struct cli_env*);
static int help(int, char**, struct cli_env*);
int shell_eval(int, char**, struct cli_env*);
void fshell(FILE*, int);
void shell(void);

extern char *strchr(const char*, char);
extern double atof(const char*);


typedef long long quad;
typedef unsigned long long u_quad;

int verbose = 0;

#ifdef PLATFORM_I386
extern long k_paddr, bootmem0, bootmem1;
#endif
#ifdef N_RTC
extern utime_t boottime;
#endif

static const struct {
    const char *name;
    const char *help;
    int (*fnc)(int, char**, struct cli_env*);
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
    { "prompt",  "the prompt",               IN_ENV(prompt, UV_TYPE_STR32) },
    { "time",    "temporal displacement",    &systime,      UV_TYPE_TIME },
    { "itime",   "temporal displacement",    &systime,      UV_TYPE_UQ },
#ifdef N_RTC
    { "boottime","the time we booted",       &boottime,  UV_TYPE_TIME },
#endif
    { "verbose", "echo commands in scripts", &verbose,   UV_TYPE_UL },
#ifndef PLATFORM_EMUL
#ifdef PLATFORM_I386
    { "kpa",     0,                          &k_paddr,   UV_TYPE_UL },
    { "mem0",    0,                          &bootmem0,  UV_TYPE_UL },
    { "mem1",    0,                          &bootmem1,  UV_TYPE_UL },
#endif
#endif
    { "bootflags","bootflags",               &bootflags, UV_TYPE_UL },

    { "a", 	     0,                          IN_ENV(a, UV_TYPE_STR32) },
    { "b", 	     0,                          IN_ENV(b, UV_TYPE_STR32) },
    { "c", 	     0,                          IN_ENV(c, UV_TYPE_STR32) },
    { "d", 	     0,                          IN_ENV(d, UV_TYPE_STR32) },

    { "tsl",     "process timeslice",        IN_PROC(timeslice, UV_TYPE_UC) },
    { "currproc",0,                          &currproc,  UV_TYPE_ULX | UV_TYPE_RO },
    { "ident",   "system identity",          ident,      UV_TYPE_STR32 | UV_TYPE_RO },
    { "arch",    "system arch",              archid,     UV_TYPE_STR32 | UV_TYPE_RO },


#define DEFVAR(proto, name, init, type, docstr)	\
    { QUOTIFY(name),	docstr,		     &name, type },

#include "defvar.list"

    {0,0,0,0}
};

/****************************************************************/

#undef DEFUN
#undef DEFALIAS
#undef DEFVAR
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

static int
interp_varref(struct cli_env *env, const struct Var *v, char *buf, int buflen){
    int off = 0;

    if( !v ) return;

    if( v->type & UV_TYPE_ENV )
        off = (int)env;
    if( v->type & UV_TYPE_PROC )
        off = (int)currproc;

    switch( v->type & 0xF ){
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
    int i;

    for(i=0; vars[i].name; i++)
        if( !strcmp(vars[i].name, var)) break;
    if( vars[i].name ){
        return interp_varref(env, vars + i, buf, buflen);
    }
    return -1;
}


DEFUN(show, "show var")
DEFALIAS(show, sho)
DEFALIAS(show, sh)
{
    char buf[32];
    int i;

    if( argc != 2 ){
        f_error("show what?");
        return -1;
    }

    i = interp_var(env, argv[1], buf, sizeof(buf));
    if( !i ){
        printf("%s = %s\n", argv[1], buf);
    }else if( !strcmp(argv[1], "run") ){
        // show run
        ui_f_config(0, 0, env);
    }else{
        f_error("show: no such var");
        return -1;
    }
    return 0;
}

/* set a b  or  a = b */
DEFUN(set, "set a var")
{
    int i, n;
    char *var;
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
        switch( vars[i].type & 0xF ){
        case UV_TYPE_STR16:
        case UV_TYPE_STR32:
            n = (vars[i].type==UV_TYPE_STR16)? 16 : 32;
            strncpy( (char*)(vars[i].addr + off), argv[2], n);
            ((char*)(vars[i].addr + off))[n-1] = 0;
            break;
        case UV_TYPE_UC:
            v = atoi( argv[2] );
            *(u_char*)(vars[i].addr + off) = v;
            break;
        case UV_TYPE_US:
            v = atoi( argv[2] );
            *(u_short*)(vars[i].addr + off) = v;
            break;
        case UV_TYPE_UL:
            v = atoi( argv[2] );
            *(u_long*)(vars[i].addr + off) = v;
            break;
        case UV_TYPE_TIME:
            *(u_quad*)(vars[i].addr + off) = timeiso( argv[2] );
            break;
        case UV_TYPE_UQ: {
            quad val;
            val = strtoq(argv[2], 0, 0);
            *(u_quad*)(vars[i].addr + off) = val;
            break;
        }
        case UV_TYPE_FLOAT:
            *(float*)(vars[i].addr + off) = atof( argv[2] );
            break;

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
// output all vars marked as configurable
int
save_config(const char *file){
    int i, r, ml=0;
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
        int l = strlen(vars[i].name);
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
        switch(bv->type){
        case UV_TYPE_STR16:
        case UV_TYPE_STR32:
        case UV_TYPE_TIME:
            fprintf(f, "%-*s = \"%s\"\n", ml, bv->name, buf);
            break;
        default:
            fprintf(f, "%-*s = %s\n",     ml, bv->name, buf);
            break;
        }
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
    int i, j;

    /* if no args, show all commands/vars */
    if( argc < 2 ){
        printf("help command|var\ncommands:\n\t");
        for(i=j=0; cmds[i].name; i++)
            if( cmds[i].help ){
                printf(" %s", cmds[i].name);
                if( !(++j % 10) )
                    printf("\n\t");
            }
        printf("\nvars:\n\t");
        for(i=j=0; vars[i].name; i++)
            if( vars[i].help ){
                printf(" %s", vars[i].name);
                if( !(++j % 10) )
                    printf("\n\t");
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
    int nl=1;

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
                if( verbose )
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
    char buf[32], *name;
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

DEFUN(if, "conditional")
{
    int i, tc, ec, rv;

    if( argc < 4 ){
        f_error("if cmd args... then cmd args... [else cmd args...]\n");
        return -1;
    }

    for(i=tc=ec=0; i<argc; i++){
        if( !strcmp(argv[i], "then")){
            if( tc ){
                f_error("if cmd args... then cmd args... [else cmd args...]\n");
                return -1;
            }else
                tc = i;
        }
        if( !strcmp(argv[i], "else")){
            if( ec ){
                f_error("if cmd args... then cmd args... [else cmd args...]\n");
                return -1;
            }else
                ec = i;
        }
    }
    if( !tc ){
        f_error("if cmd args... then cmd args... [else cmd args...]\n");
        return -1;
    }

    rv = shell_eval( tc - 1, argv + 1, env );
    if( ! rv ){
        /* 0 on sucess */
        return shell_eval( (ec?ec:argc) - tc - 1 , argv + tc + 1, env );
    }else{
        if( ec )
            return shell_eval( argc - ec - 1 , argv + ec + 1, env );
    }
    return 0;
}


static void
prompt(struct cli_env *env){
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
        case 'v':	printf("%s", ident);		break;
        case 'g':	printf("%+c", 0x27A1);		break;	// large right arrow
        case '{':
            // ${1234} => insert utf-8
            u = strtoul(p + 1, &p, 16);
            printf("%+c", u);
            break;
        }
    }
}


int
shell_eval(int argc, char **argv, struct cli_env *env){
    short i, j, v, n=0;
    char globp=0;

#if 0
    char buf[8][32];
    /* expand $var */
    for(i=0; i<argc; i++){
        if( argv[i][0] == '$' ){
            v = interp_var(env, argv[i]+1, buf[n], sizeof(buf[0]));
            if( v ){
                fprintf(STDERR, "no such string var: %s\n", argv[i]);
                return -1;
            }
            argv[i] = buf[n++];
            if( n >= 8 ){
                fprintf(STDERR, "too many vars!\n");
                return -1;
            }
        }
    }
#endif
#ifdef USE_FILESYS
    //  need glob?
    for(i=1; i<argc; i++){
        if( contains_globbing( argv[i] ) ){
            globp = 1;
            break;
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

#define BUFSIZE 256
void
fshell(FILE *f, int interactivep){
    Catchframe cf;
    char *argv[24];
    int  argc;
    char *p;
    char qc;
    int i;

    struct cli_env *env = (struct cli_env*)alloc(sizeof(struct cli_env));
    char *buf = (char*)alloc(BUFSIZE);
    bzero(env, sizeof(env));
    // 35 = purple
    strncpy(env->prompt, "$[35;1m$v$g$[39;0m ", sizeof(env->prompt));

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

        i = 0;
        while(1){
            if( interactivep ){
                if( i )
                    printf("> ");
                else
                    prompt(env);
                getline(buf+i, BUFSIZE-i, 0);
            }else{
                if( !fgets(buf+i, BUFSIZE-i, f) ){
                    UNCATCH(cf);
                    free(buf, BUFSIZE);
                    free(env, sizeof(struct cli_env));
                    return;
                }
            }
            i = strlen(buf);
            if( buf[i-1] != '\\' )
                break;
            else
                buf[ --i ] = 0;
        }

        if( !interactivep && verbose )
            printf("%s\n", buf);

        argc = 0;
        p = buf;

        /* parse cmd line into args */
        while( argc < sizeof(argv)/sizeof(argv[0]) ){

            /* skip white */
            while( *p ==' ' || *p == '\t' ){
            next_token:
                *p++ = 0;
            }

            if( ! *p ){
                break;
            }

            if( *p=='#' ){
                *p = 0;
                break;
            }

            /* we allow "" inside '' and '' inside "" */
            if(*p=='"'||*p=='\''){
                qc = *p;
                p++;
                argv[argc++] = p;
                while( *p && *p!=qc ){
                    p++;
                }
                if( *p )
                    goto next_token;
                break;
            }

            argv[argc++] = p;
            while( *p && *p!=' ' && *p!='\t' && *p!='#' )
                p++;
        }

        if( !argc )
            continue;
        if( !strcmp("exit", argv[0] )){
            UNCATCH(cf);
            free(buf, BUFSIZE);
            free(env, sizeof(struct cli_env));
            return;
        }
        shell_eval(argc, argv, env);
    }
}

#if defined(USE_FILESYS)
void
run_script(const char* file){
    FILE *f;
    f = fopen(file, "r" );
    if( f ){
        fshell(f, 0);
        fclose(f);
    }
}
#endif

void
shell(void){
#if defined(USE_FILESYS) & defined(MOUNT_ROOT)
    run_script(MOUNT_ROOT "shell.rc");
#endif
    fshell(0, 1);
}

