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

#define KBUF_MAX	2048	/* no more than this much if the console is up */

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
}


static int
kprintffnc_con(char c){

    fputc(c, kconsole_port);
#ifdef N_LCD
    fputc(c, klcd_port);
#endif

}

static int
kprintffnc_e9(char c){
    /* outb(0xE9, c); */
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

#if 1
void
kprintf(const char *fmt, ...){
    va_list ap;

    red_on();
    va_start(ap,fmt);
    vprintf(kprintffnc, 0, fmt, ap);
    //extern void stm32_putchar(int);
    //vprintf(stm32_putchar, 0, fmt, ap);
    red_off();
}
#else

static void kprintn(unsigned long ul, int base);

void
kprintf(const char *fmt, ...){
        va_list ap;
        va_start(ap,fmt);

	char *p;
	int ch, n;
	unsigned long ul;
	int lflag, set;

	for (;;) {
		while ((ch = *fmt++) != '%') {
			if (ch == '\0')
				return;
			stm32_putchar(ch);
		}
		lflag = 0;
reswitch:	switch (ch = *fmt++) {
                case '0': case '1': case '2': case '3':
                case '4': case '5': case '6': case '7':
                case '8': case '9': case '.': case '-':
                    /* ignore */
                    goto reswitch;

                case '\0':
			/* XXX print the last format character? */
			return;
		case 'l':
			lflag = 1;
			goto reswitch;
		case 'c':
			ch = va_arg(ap, int);
				stm32_putchar(ch & 0x7f);
			break;
		case 's':
			p = va_arg(ap, char *);
			while ((ch = *p++))
				stm32_putchar(ch);
			break;
		case 'd':
			ul = lflag ?
			    va_arg(ap, long) : va_arg(ap, int);
			if ((long)ul < 0) {
				stm32_putchar('-');
				ul = -(long)ul;
			}
			kprintn(ul, 10);
			break;
		case 'o':
			ul = lflag ?
			    va_arg(ap, u_long) : va_arg(ap, u_int);
			kprintn(ul, 8);
			break;
		case 'u':
			ul = lflag ?
			    va_arg(ap, u_long) : va_arg(ap, u_int);
			kprintn(ul, 10);
			break;
		case 'p':
			stm32_putchar('0');
			stm32_putchar('x');
			lflag = 1;
			/* fall through */
		case 'x':
			ul = lflag ?
			    va_arg(ap, u_long) : va_arg(ap, u_int);
			kprintn(ul, 16);
			break;
		default:
			stm32_putchar('%');
			if (lflag)
				stm32_putchar('l');
			stm32_putchar(ch);
		}
	}
}

static void
kprintn(unsigned long ul, int base){
    /* hold a long in base 8 */
	char *p, buf[(sizeof(long) * 8 / 3) + 1];

	p = buf;
	do {
		*p++ = "0123456789abcdef"[ul % base];
	} while (ul /= base);
	do {
		stm32_putchar(*--p);
	} while (p > buf);
}


#endif

void
hexdump(const unsigned char *d, int len){
    int i;
    int col = 0;

    kprintf("\n");

    for(i=0; i<len; i++){
        if( !col )       kprintf("%08.8X:", d + i);
        if(! (col % 4 )) kprintf(" ");

        kprintf(" %x%x", (d[i]&0xF0) >> 4, (d[i]&0x0F));

        if( ++col == 16){
            kprintf("\n");
            col = 0;
        }
    }

    kprintf("\n");
}

void
diag(const char *file, const char *func, int line, const char *fmt, ...){
    va_list ap;

    red_on();
    va_start(ap,fmt);

    kprintf("%s:%d in %s(): ", file, line, func);
    vprintf(kprintffnc, 0, fmt, ap);

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

