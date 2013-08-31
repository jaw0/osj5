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
static int redirin(int, char**, struct cli_env*);
static int redirout(int, char**, struct cli_env*);
int shell_eval(int, char**, struct cli_env*);
void fshell(FILE*, int);
void shell(void);

extern char *strchr(const char*, char);

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
#ifdef USE_FILESYS
    { "<",        "redirect input",               redirin },
    { ">",        "redirect output",              redirout },
#endif
    { "exit",     "exit",                         0 },

#define DEFUN(name, doc)                                        \
    { QUOTIFY(name),	doc,		CONCAT(ui_f_, name) },

#define DEFALIAS(name, alias)                                   \
    { QUOTIFY(alias), 	0,		CONCAT(ui_f_, name) },

#include "defun.list"
    { 0,0,0 }
};


#undef DEFUN
#undef DEFALIAS
#include <userint.h>


static const struct {
    const char *name;
    const char *help;
    const void *addr;
    u_char type;
#define TYPE_STR16      1
#define TYPE_STR32      2
#define TYPE_UC         3
#define TYPE_US         4
#define TYPE_UL         5
#define TYPE_UQ         6
#define TYPE_IP         7
#define TYPE_TIME	8
#define TYPE_ULX        9
#define TYPE_ENV	0x80
#define TYPE_PROC	0x40
#define TYPE_RO		0x20


#define IN_ENV(a, b)	(void*)offsetof(struct cli_env, a), TYPE_ENV | b
#define IN_PROC(a, b)	(void*)offsetof(struct Proc, a), TYPE_PROC | b

} vars[] = {
    { "prompt",  "the prompt",               IN_ENV(prompt, TYPE_STR32) },
    { "time",    "temporal displacement",    &systime,      TYPE_TIME },
    { "itime",   "temporal displacement",    &systime,      TYPE_UQ },
#ifdef N_RTC
    { "boottime","the time we booted",       &boottime,  TYPE_TIME },
#endif
    { "verbose", "echo commands in scripts", &verbose,   TYPE_UL },
#ifndef PLATFORM_EMUL
#ifdef PLATFORM_I386
    { "kpa",     0,                          &k_paddr,   TYPE_UL },
    { "mem0",    0,                          &bootmem0,  TYPE_UL },
    { "mem1",    0,                          &bootmem1,  TYPE_UL },
#endif
#endif
    { "bootflags","bootflags",               &bootflags, TYPE_UL },

    { "a", 	     0,                          IN_ENV(a, TYPE_STR32) },
    { "b", 	     0,                          IN_ENV(b, TYPE_STR32) },
    { "c", 	     0,                          IN_ENV(c, TYPE_STR32) },
    { "d", 	     0,                          IN_ENV(d, TYPE_STR32) },

    { "tsl",     "process timeslice",        IN_PROC(timeslice, TYPE_UC) },
    { "currproc",0,                          &currproc,  TYPE_ULX | TYPE_RO },

    {0,0,0,0}
};


void
f_error(const char *m){
    printf("ERROR: %s\n", m);
}

DEFUN(version, "display version information")
DEFALIAS(version, vers)
DEFALIAS(version, ver)
{
    extern const char *version;

    printf("%s\n", version);

    /* uptime, image name, devices, memory, ... */
    return 0;
}


int
interp_var(struct cli_env *env, const char *var, char *buf, int buflen){
    int i;
    int off = 0;

    for(i=0; vars[i].name; i++)
        if( !strcmp(vars[i].name, var)) break;
    if( vars[i].name ){
        if( vars[i].type & TYPE_ENV )
            off = (int)env;
        if( vars[i].type & TYPE_PROC )
            off = (int)currproc;

        switch( vars[i].type & 0xF ){
        case TYPE_STR16:
        case TYPE_STR32:
            snprintf(buf, buflen, "%s", vars[i].addr + off);
            break;
        case TYPE_UC:
            snprintf(buf, buflen, "%u", *(u_char*)(vars[i].addr + off));
            break;
        case TYPE_US:
            snprintf(buf, buflen, "%u", *(u_short*)(vars[i].addr + off));
            break;
        case TYPE_ULX:
            snprintf(buf, buflen, "0x%x", *(u_long*)(vars[i].addr + off));
            break;
        case TYPE_UL:
            snprintf(buf, buflen, "%u", *(u_long*)(vars[i].addr + off));
            break;
        case TYPE_UQ:
            snprintf(buf, buflen, "%Qu", *(u_quad*)(vars[i].addr + off));
            break;
        case TYPE_IP:
            snprintf(buf, buflen, "%I", *(u_long*)(vars[i].addr + off));
            break;
        case TYPE_TIME:
            snprintf(buf, buflen, "%#T", *(u_quad*)(vars[i].addr + off));
            break;
        default:
            return -1;
        }
        return 0;
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
        if( vars[i].type & TYPE_ENV )
            off = (int)env;
        if( vars[i].type & TYPE_PROC )
            off = (int)currproc;
        if( vars[i].type & TYPE_RO ){
            fprintf(STDERR, "%s: read-only\n", var);
            return -1;
        }
        switch( vars[i].type & 0xF ){
        case TYPE_STR16:
        case TYPE_STR32:
            n = (vars[i].type==TYPE_STR16)? 16 : 32;
            strncpy( (char*)(vars[i].addr + off), argv[2], n);
            ((char*)(vars[i].addr + off))[n-1] = 0;
            break;
        case TYPE_UC:
            v = atoi( argv[2] );
            *(u_char*)(vars[i].addr + off) = v;
            break;
        case TYPE_US:
            v = atoi( argv[2] );
            *(u_short*)(vars[i].addr + off) = v;
            break;
        case TYPE_UL:
            v = atoi( argv[2] );
            *(u_long*)(vars[i].addr + off) = v;
            break;
        case TYPE_TIME:
        case TYPE_UQ: {
            quad val;
            val = strtoq(argv[2], 0, 0);
            *(u_quad*)(vars[i].addr + off) = val;
            break;
        }
#if 0
        case TYPE_IP:
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
    printf("%s", *(env->prompt) ? env->prompt : ": ");
}

#ifdef USE_FILESYS
static int
redirin(int argc, char **argv, struct cli_env *env){
    FILE *f, *s;
    int r;

    if( argc < 3 ){
        f_error("< file cmd...");
        return -1;
    }
    f = fopen( argv[1], "r" );
    if( !f ){
        fprintf(STDERR, "could not open \"%s\"\n", argv[1] );
        return -1;
    }
    s = STDIN;
    STDIN = f;
    r = shell_eval( argc - 2, argv + 2, env );
    STDIN = s;
    fclose(f);
    return r;
}

static int
redirout(int argc, char **argv, struct cli_env *env){
    FILE *f, *s;
    int r;

    if( argc < 3 ){
        f_error("> file cmd...");
        return -1;
    }
    f = fopen( argv[1], "w" );
    if( !f ){
        fprintf(STDERR, "could not open \"%s\"\n", argv[1] );
        return -1;
    }
    s = STDOUT;
    STDOUT = f;
    r = shell_eval( argc - 2, argv + 2, env );
    STDOUT = s;
    fclose(f);
    return r;
}
#endif

int
shell_eval(int argc, char **argv, struct cli_env *env){
    char buf[8][32];
    int i, v, n=0;

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

    for(i=0; cmds[i].name; i++)
        if( !strcmp(cmds[i].name, argv[0])) break;
    if( cmds[i].name )
        return (*cmds[i].fnc)(argc, argv, env);

    if( argc > 2 && !strcmp("=", argv[1]))
        return ui_f_set(argc, argv, env);

    fprintf(STDERR, "command not found: \"%s\"\n", argv[0]);

    return -1;
}

#define BUFSIZE 256
void
fshell(FILE *f, int interactivep){
    Catchframe cf;
    char *argv[16];
    int  argc;
    char *p;
    char qc;
    int i;

    struct cli_env *env = (struct cli_env*)alloc(sizeof(struct cli_env));
    char *buf = (char*)alloc(BUFSIZE);
    bzero(env, sizeof(env));
    strcpy(env->prompt, "prompt% ");

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

void
shell(void){
    FILE *f;
#if defined(USE_FILESYS) & defined(MOUNT_ROOT) & defined(STARTUPFILE)
    f = fopen( MOUNT_ROOT STARTUPFILE, "r" );
    if( f ){
        fshell(f, 0);
        fclose(f);
    }
#endif
    fshell(0, 1);
}


