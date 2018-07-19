/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: kernel messages
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


extern FILE *kconsole_port, *console_port;
#ifdef N_LCD
extern FILE *klcd_port;
#endif

static char *kbuf = 0;
static kbufsz = 0;
static kbuflen = 0;
static kflushp = 0;
static redp = 0;

static int kprintffnc_con(char);
static int kprintffnc_buf(char);
void kflush(int);
extern void blinky(void);

/* xterm: 7 = inverse, 1 = bold, 4 = underline, 0 = normal */
/* ANSI:  31 = red, 40 = black bkg */
#if defined(PLATFORM_EMUL) || defined(PLATFORM_ARM_CM)
#  define RED	"\e[1;31m"
#else
#  define RED	"\e[1;31;40m"
#endif
#define WHT	"\e[0m"

#ifndef KBUF_MAX
#  define KBUF_MAX	2048	/* no more than this much if the console is up */
#endif

static void
red_on(){
    if( redp ) return;
    if(kconsole_port){ fputs(RED, kconsole_port); redp = 1; }
}
static void
red_off(){
    if( !redp ) return;
    if(kconsole_port){ fputs(WHT, kconsole_port); redp = 0; }
}

void
kflush(int colorp){
    int len = kbuflen;
    int i;

#ifndef KBOOTQUIET
    if( ! kconsole_port )
        PANIC("kflush but no console\n");

    if( kflushp )
        return;

    red_on();

    kflushp = 1;
    for(i=0; i<len; i++){
        kprintffnc_con(kbuf[i]);
    }

    if( !colorp ) red_off();
#endif
}


static int
kprintffnc_con(char c){

    fputc(c, kconsole_port);
#ifdef N_LCD
    fputc(c, klcd_port);
#endif

}

static int
kprintffnc_e9(void *a, char c){
    XE9(c);
}

static int
kprintffnc_buf(char c){

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

static int
kprintffnc(void *a, char c){
    if(kconsole_port
#ifdef N_LCD
        && klcd_port
#endif
        ){
        if( kbuflen && !kflushp )
            kflush(1);
        kprintffnc_con(c);
        if( kbufsz < KBUF_MAX )
            /* also to buffer if room */
            kprintffnc_buf(c);
    }else{
        kprintffnc_buf(c);
    }
}

// only to buffer
static int
klogffnc(void *a, char c){

    /* skip leading \n */
    if( (c == '\n') && !kbufsz ) return;

    if( kconsole_port ){
        if( kbufsz < KBUF_MAX )
            /* to buffer if room */
            kprintffnc_buf(c);
    }else{
        kprintffnc_buf(c);
    }
}

static int
kcprintffnc(void *a, char c){

    if(console_port){
        fputc(c, console_port);
    }
}

static int
ktprintffnc(void *a, char c){

    if(currproc && currproc->stderr){
        fputc(c, currproc->stderr);
    }
}


void
kprintf(const char *fmt, ...){
    va_list ap;

    red_on();
    va_start(ap,fmt);
    vxprintf(kprintffnc, 0, fmt, ap);
    va_end(ap);
    red_off();
}

void
bootmsg(const char *fmt, ...){
    va_list ap;

#ifdef KBOOTQUIET
    va_start(ap,fmt);
    vxprintf(klogffnc, 0, fmt, ap);
    va_end(ap);
#else
    red_on();
    va_start(ap,fmt);
    vxprintf(kprintffnc, 0, fmt, ap);
    va_end(ap);
    red_off();
#endif
}

/* output to the console - no buffering, may block */
void
kcprintf(const char *fmt, ...){
    va_list ap;

    if( console_port ) fputs(RED, console_port);
    va_start(ap,fmt);
    vxprintf(kcprintffnc, 0, fmt, ap);
    if( console_port ) fputs(WHT, console_port);
}

/* output to the the current process' stderr */
void
ktprintf(const char *fmt, ...){
    va_list ap;

    va_start(ap,fmt);
    vxprintf(ktprintffnc, 0, fmt, ap);
}

void
e9printf(const char *fmt, ...){
    va_list ap;

    va_start(ap,fmt);
    vxprintf(kprintffnc_e9, 0, fmt, ap);
}

void
hexdump(const unsigned char *d, int len){
    int i;
    int col = 0;
    char txt[17];
    txt[16] = 0;

    for(i=0; i<len; i++){
        if( !col )       kprintf("%08.8X:", d + i);
        if(! (col % 4 )) kprintf(" ");

        kprintf(" %x%x", (d[i]&0xF0) >> 4, (d[i]&0x0F));
        txt[col] = (d[i] >= 0x20 && d[i] <= 0x7e) ? d[i] : '.';

        if( ++col == 16){
            kprintf("  %s\n", txt);
            col = 0;
        }
    }

    if( col ) kprintf("\n");
}

void
diag(const char *file, const char *func, int line, const char *fmt, ...){
    va_list ap;

    red_on();
    va_start(ap,fmt);

    kprintf("%s:%d in %s(): ", file, line, func);
    vxprintf(kprintffnc, 0, fmt, ap);

    red_off();
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

