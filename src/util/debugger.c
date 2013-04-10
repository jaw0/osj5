/*
  Copyright (c) 2001
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2001
  Function: debugging commands
 
  $Id$

*/


#include <alloc.h>
#include <nstdio.h>
#include <conf.h>
#include <proc.h>
#include <fs.h>
#include <userint.h>
#ifdef PLATFORM_I386
#  include <pio.h>
#endif

#ifndef USE_CLI
#error "debugger requires feature CLI"
#endif

extern void f_error(const char*);


#define BPL     16      /* bytes per line */
#define IGO     4       /* in groups of */
#define isprint(x)	((x)>=' ' && (x)<127)

#ifdef USE_DDB

extern char end[];
static int ddbinit = 0;
static int symlen;

void init_ddb(void){
#if 0
    int x=0;

    if( !ddbinit ){
	x = 1;
	init_ddb_syms();
    }
    kprintf("ddb symbols %d bytes (%d)\n", symlen, x);
#endif
}

void init_ddb_syms(void){
#if 0
    int s=0, x=0;

    if( ddbinit ) return;
    ddbinit = 1;

    if( !strcmp("SYMBOLS", end) ){
	x = 1;
    }

    s = *(int*)(end + 8);
    symlen = s;

    screen_printf("ddb symbols %d bytes @ 0x%x (%d)\n", s, end, x);

    for(s=0;s<100000;s++){ ; }
#endif
}
#endif /* USE_DDB */


DEFUN(dumpmem, "dump memory")
DEFALIAS(dumpmem, d)
{
    int len, i;
    u_char *addr;
    int col = 0;
    char txt[BPL + 1];

    if( argc < 2 ){
        f_error("dump addr [len]");
        return -1;
    }

    addr = (char*)atoi_base(16, argv[1] );

    if( argc > 2 )
        len = atoi_base(16, argv[2] );
    else
        len = 16;


    txt[BPL] = 0;
    for(i=0; i<len; i++){
        if( !col )
            printf("%08.8X: ", addr + i);

        if(! (col % IGO ))
            printf(" ");

        printf("%02.2x", addr[i]);
        txt[col] = (isprint(addr[i])) ? addr[i] : '.';

        if( ++col == BPL){
            printf("  %s\n", txt);
            col = 0;
        }
    }
    if( col ){
        /* do partial last line */
        txt[col] = 0;
        for(; col<BPL; col++){
            printf("  ");
            if(! (col % IGO))
                printf(" ");
        }
        printf("  %s\n", txt);
    }

    return 0;
}
#undef BPL
#undef IGO
#undef isprint

DEFUN(editmem, "edit memory")
DEFALIAS(editmem, e)
{
    int i;
    u_char *addr;
    char buffer[64];

    if( argc < 2 ){
        f_error("edit addr");
        return -1;
    }

    addr = (char*)atoi_base(16, argv[1] );

    /*
      hit return to skip to next byte
      a number to change the value
      . when done
      (this is exactly the 'q' command on your Sun3)
    */
    for( ; ; addr++){
        printf("%08.8X : %02.2x > ", addr, *addr);
        getline(buffer, 64, 0);
        if(! *buffer) continue;
        if(*buffer== '.') break;
        if(*buffer =='?')
            puts("enter a value, return to skip, or . when done\n");

        *addr = atoi_base(16, buffer);
    }

    return 0;
}

#ifdef PLATFORM_I386
DEFUN(inb, "read a byte from io")
{
    int p, v;

    if( argc != 2 ){
        f_error("inp port");
        return -1;
    }

    p = atoi_base( 16, argv[1] );
    v = inb( p );

    printf("0x%x\n", v);
    return 0;
}

DEFUN(outb, "output a byte to io")
{
    int p, v;

    if( argc != 3 ){
        f_error("outp port value");
        return -1;
    }

    p = atoi_base( 16, argv[1] );
    v = atoi_base( 16, argv[2] );
    outb(p, v);

    return 0;
}

struct stackframe {
    struct stackframe *next;
    u_long ret;
    u_long arg[0];
};

DEFUN(trace, "show stack trace")
{
    struct stackframe *bp;
    void *ibp;
    proc_t p;
    int n=0, max=0, sl;

    if( argc < 2 ){
	printf("trace: pid [len]\n");
        return -1;
    }

    p = (proc_t)atoi_base(16, argv[1]);

    if( argc > 2 )
	max = atoi(argv[2]);

    if( p==currproc ){
	asm volatile ("movl %%ebp, %0" : "=r" (ibp));
    }else{
	ibp = (void**)(p->sp) + 9;
    }

    printf( "ibp=%x\n", ibp);

    for(bp=ibp; bp; bp=bp->next){

	printf("ret=%x f(%x, %x, %x, %x, %x, %x)\n",
	       bp->ret, bp->arg[0], bp->arg[1], bp->arg[2],
	       bp->arg[3], bp->arg[4], bp->arg[5]);
	if( max && (++n > max) ) break;
	if( !bp || bp == (void*)0xFFFFFFFF ) break;
    }
    return 0;
}
#endif

DEFUN(dfile, "dump FILE*")
{
    FILE *f;

    if( argc > 1 ){
	f = (FILE*)atoi_base(16, argv[1]);
    }else{
	f = STDIN;
	printf( "STDIN=%x\n", STDIN );
    }
    if(!f){
        printf("no such file\n");
        return -1;
    }

    printf( "  flags=0x%08.8x unc=%d prev=%d fs=0x%08.8x\n",
	    f->flags, f->ungotc, f->prevout, f->fs);
    printf( "  dup=%x d=0x%08.8x pid=0x%08.8x cc=[%d %d %d %d]\n",
	    f->dupped, f->d, f->ccpid, f->cchars[0], f->cchars[1],f->cchars[2],f->cchars[3] );
    return 0;

}


