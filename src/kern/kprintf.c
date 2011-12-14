/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: kernel messages

  $Id$

*/


#include <sys/types.h>
//#include <sys/param.h>
#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <alloc.h>
#include <error.h>
#include <stdarg.h>
#include <userint.h>

/* kprintf

       sends output to kconsole + LCD
       if they are not yet initialized, buffer the output
       and flush it out later
*/


extern FILE *kconsole_port;
#ifdef N_LCD
extern FILE *klcd_port;
#endif

static char *kbuf = 0;
static kbufsz = 0;
static kbuflen = 0;
static kflushp = 0;
static redp = 0;

static int kprintffnc_con(void *, char);
static int kprintffnc_buf(void *, char);
void kflush(int);

/* xterm: 7 = inverse, 1 = bold, 4 = underline, 0 = normal */
/* ANSI:  31 = red, 40 = black bkg */
#ifdef PLATFORM_EMUL
#  define RED	"\e[1;31m"
#else
#  define RED	"\e[1;31;40m"
#endif
#define WHT	"\e[0m"

#define KBUF_MAX	2048	/* no more than this much if the console is up */

void
kflush(int colorp){
    int len = kbuflen;
    int i;

    if( ! kconsole_port )
        PANIC("kflush but no console\n");

    if( kflushp )
        return;

    if( !redp ){
        fputs(RED, kconsole_port);
        redp = 1;
    }

    kflushp = 1;
    for(i=0; i<len; i++){
        kprintffnc_con(0, kbuf[i]);
    }

    if( !colorp ){
        fputs(WHT, kconsole_port);
        redp = 0;
    }
}

static int
kprintffnc_con(void *a, char c){


    if( !redp ){
        fputs(RED, kconsole_port);
        redp = 1;
    }
    fputc(c, kconsole_port);
#ifdef N_LCD
    fputc(c, klcd_port);
#endif

}

static int
kprintffnc_e9(void *a, char c){
    /* outb(0xE9, c); */
}

static int
kprintffnc_buf(void *a, char c){

    if( kbufsz < kbuflen + 2 ){
        char *buf;
        int sz = (kbufsz ? kbufsz : 64) * 2;

        buf = alloc( sz );
        if( kbufsz ){
            memcpy(buf, kbuf, kbufsz);
            free(kbuf, kbufsz);
        }
        kbuf = buf;
        kbufsz = sz;
    }
    kbuf[ kbuflen ++ ] = c;
    kbuf[ kbuflen ] = 0;
}

void
kprintf(const char *fmt, ...){
    va_list ap;

    va_start(ap,fmt);

    if( kconsole_port
#ifdef N_LCD
        && klcd_port
#endif
        ){
        if( kbuflen && !kflushp )
            kflush(1);
        vprintf(kprintffnc_con, 0, fmt, ap);
        if( kbufsz < KBUF_MAX )
            /* also to buffer if room */
            vprintf(kprintffnc_buf, 0, fmt, ap);
    }else{
        vprintf(kprintffnc_buf, 0, fmt, ap);
    }

    if( redp ){
        fputs(WHT, kconsole_port);
        redp = 0;
    }
}

#ifdef USE_CLI
DEFUN(dmesg, "display system messgages")
{
    int i;

    puts(RED);
    for(i=0; i<kbuflen; i++){
        putchar(kbuf[i]);
    }
    puts(WHT);


}
#endif

