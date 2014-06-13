/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function:

  $Id$

*/


#include <conf.h>
#include <stdarg.h>
#include <sys/types.h>
#ifndef TESTING
#include <nstdio.h>
#endif
#include <time.h>

// config:
//   NOPRINTF64		- do not include 64bit integer support
//   NOPRINTFFLOAT	- do not include float support
//   NOPRINTFTIME	- do not include support for timestamps %T
//   NOPRINTFIP		- do not include support for ip addresses %I
//   PRINTFFLOATTYPE	- use (float|double) for floating point math


/*
  a minimal implementation of printf
  %<flags><width><.prec><type>

  type::
  c	- char
  s	- string
  %	- %
  &	- magic zero-width character
  x	- lower case hex
  X	- UPPER case hex
  d,D	- decimal
  o	- octal
  f     - float
  p	- spin (prec times, delay of width)
  I	- IP addr as dotted quad
  T       - quad as timestamp
  # - for usec
  =base	- in base
  =*	- base from arglist
  flags::
  0	- pad w/ leading 0 (! spaces)
  #	- use lower case
  -       - left justify
  Q       - arg is quad
*/


enum {
    PF_ZERO,		/* pad w/ leading zeros */
    PF_ALT,		/* use lowercase instead of UPPER */
    PF_SIGNED,		/* arg is signed */
    PF_SHOW_PLS,    	/* arg is signed, show + if positive */
    PF_LEFT,        	/* left justify, not right */
    PF_QUAD,	    	/* arg is a quad */
    PF_FLT_F,
    PF_FLT_E
};

#define B(x)		(1<<(x))
#define isdig(x)	(((x)>='0') && ((x)<='9'))

typedef unsigned long long u_quad;
#ifndef NOPRINTF64
typedef u_quad	u_num_t;
#else
typedef unsigned long u_num_t;
#endif


static const char Set_A[] =	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char Set_a[] =	"0123456789abcdefghijklmnopqrstuvwxyz";
static const char spinchar[] = "|\\-/";

int snprintf(char *, int, const char *, ...);
static int putnum(int (*)(void*, char), void *, u_num_t, int, int, int, int);
int fncprintf(int (*)(void*, char), void *, const char *, ...);

#ifndef NOPRINTFFLOAT
#  ifdef PRINTFFLOATTYPE
typedef PRINTFFLOATTYPE float_num_t;
#  else
typedef float float_num_t;
#  endif
static int putfloat(int (*)(void*, char), void *, float_num_t, int, int, int);
#endif


int vprintf(int (*ofnc)(void*, char), void *arg, const char *fmt, va_list ap){
    const char *p = fmt;
    char *s;
    u_num_t val;
#ifndef NOPRINTFFLOAT
    float_num_t fval;
#endif
    int width = 0, prec = 0;
    u_short flags;
    int base;
    int pos = 0;
    int i, n;

    while(*p){
        prec = width = flags = 0;
        base = 10;
        if(*p != '%'){
            (*ofnc)(arg, *p++);
            pos++;
        }else{
        rflag:
            p++;
        reswitch:
            switch(*p){
            case 's':
                /* %s - string */
                s = va_arg(ap, char*);
                if( !s )
                    s = "(null)";

                /* how much padding */
                /* width is minlen, prec is maxlen */
                if( width ){
                    n = strlen(s);
                    if( prec && n > prec ){
                        /* longer than maxlen, no pad */
                        n = width;
                    }
                    if( n >= width )
                        /* longer than minlen, no pad */
                        n = 0;
                    else
                        n = width - n;
                }else{
                    n = 0;
                }

                val = 0;
                if( !(flags & B(PF_LEFT)) && n ){
                    /* add pad */
                    while(n){
                        (*ofnc)(arg, ' ');
                        pos++;
                        n--;
                    }
                }
                while(*s){
                    (*ofnc)(arg, *s++);
                    pos ++;
                    /* no more than prec chars out */
                    /* pad to width */
                    if(prec && (++val>prec)) break;
                }

                if( n ){
                    /* add pad */
                    while(n){
                        (*ofnc)(arg, ' ');
                        pos++;
                        n--;
                    }
                }

                break;
#ifndef NOPRINTFTIME
            case 'T': {
                /* %T - timestamp */
                char buf[32];
                struct tm tr;

                val = va_arg(ap, u_quad);
                gmtime_r(&val, &tr);

                if( flags & B(PF_ALT) )
                    snprintf(buf, sizeof(buf), "%d-%0.2d-%0.2d %d:%0.2d:%0.2d.%0.6d",
                             tr.tm_year, tr.tm_mon, tr.tm_mday, tr.tm_hour, tr.tm_min, tr.tm_sec, tr.tm_usec);
                else
                    snprintf(buf, sizeof(buf), "%d-%0.2d-%0.2d T%0.2d:%0.2d:%0.2d",
                             tr.tm_year, tr.tm_mon, tr.tm_mday, tr.tm_hour, tr.tm_min, tr.tm_sec);

                fncprintf(ofnc, arg, "%*.*s", width, prec, buf);
                break;

            }
#endif
#ifndef NOPRINTFIP
            case 'I': {
                /* %I - IP addy */
                u_char* addr;
                u_long  addrl;

                addrl = va_arg(ap, u_long);
                addr  = (u_char*)&addrl;

                for(i=0; i<4; i++){
                    if( i ){
                        (*ofnc)(arg, '.');
                        pos++;
                    }
                    pos += putnum(ofnc, arg, addr[i], 10, width, prec, flags);
                }
                break;
            }
#endif
            case '&':		/* magic zero-width character */
                break;
            case '%':
                (*ofnc)(arg, '%');
                pos ++;
                break;
            case 'c':
                val = va_arg(ap, int);
                if( (flags & B(PF_SHOW_PLS)) && (val > 0xff) ){
                    // utf-8 encode
                    if( val < 0x800 ){
                        (*ofnc)(arg, 0xC0 | (val>>6));
                        (*ofnc)(arg, 0x80 | (val & 0x3F));
                    }else{
                        (*ofnc)(arg, 0xE0 | (val>>12));
                        (*ofnc)(arg, 0x80 | ((val >> 6) & 0x3F));
                        (*ofnc)(arg, 0x80 | (val & 0x3F));
                    }
                }else{
                    (*ofnc)(arg, val);
                }
                pos ++;
                break;
            case 'd':
            case 'D':
                flags |= B(PF_SIGNED);
                /* fall thru - weeee!!! */
            case 'u':
            case 'U':
                base = 10;
                goto donum;
            case 'o':
                base = 8;
                goto donum;
            case '=':
                /* arbitrary base */
                if(!prec) prec = 16;
                if(*++p == '*'){
                    val = va_arg(ap, int);
                    base = (val<0)?-val:val;
                    goto donum;
                }
                val = 0;
                while( isdig(*p) ){
                    val =  10*val + *p -'0';
                    p++;
                }
                base = val;
                p--; /* push back */
                goto donum;
            case 'x':
                flags |= B(PF_ALT);
                /* fallthru' */
            case 'X':
                base = 0x10;
            donum:
                if( flags & B(PF_QUAD) ){
                    val = va_arg(ap, u_num_t);
                }else{
                    val = va_arg(ap, u_long);
                    /* sign extend */
                    if( flags & B(PF_SIGNED)){
                        if( val & 0x80000000 )
                            val |= 0xFFFFFFFF00000000ULL;
                    }
                }

                pos += putnum(ofnc, arg, val, base, width, prec, flags);
                break;
#ifndef NOPRINTFFLOAT
            case 'f': case 'F':
                flags |= B(PF_FLT_F);
                goto doflt;
            case 'e': case 'E':
                flags |= B(PF_FLT_E);
                /* fall through */
            case 'g': case 'G':
            doflt:
                fval = va_arg(ap, double);
                pos += putfloat(ofnc, arg, fval, width, prec, flags);
                break;
#endif
            case '*':
                width = va_arg(ap,int);
                goto rflag;
            case '.':
                /* set prec */
                if(*++p == '*'){
                    prec = va_arg(ap, int);
                    goto rflag;
                }
                n = 0;
                while( isdig(*p) ){
                    n =  10*n + *p -'0';
                    p++;
                }
                prec = n;
                goto reswitch;
            case '1': case '2': case '3':
            case '4': case '5': case '6':
            case '7': case '8': case '9':
                /* set width */
                n = 0;
                while( isdig(*p) ){
                    n = 10*n + *p - '0';
                    p++;
                }
                width = n;
                goto reswitch;
#if 0
#ifndef TESTING
            case 'p':
                /* spin */
                while(prec--){
                    (*ofnc)(arg, spinchar[prec%4]);
                    msleep(width);
                    (*ofnc)(arg, '\b');
                }
#endif
#endif
                break;
            case '\0':
                return;
            case '#':
                flags |= B(PF_ALT);
                goto rflag;
            case '0':
                flags |= B(PF_ZERO);
                goto rflag;
            case '+':
                flags |= B(PF_SHOW_PLS);
                goto rflag;
            case '-':
                flags |= B(PF_LEFT);
                goto rflag;
#ifndef NOPRINTF64
            case 'Q':
            case 'q':
                flags |= B(PF_QUAD);
                goto rflag;
#endif
            default:
                break;

            }
            p++;
        }
    }
    return pos;
}

static inline void
padding(int (*ofnc)(void*, char), void *arg, int n, int ch){
    while( n-- ){
        (*ofnc)(arg, ch);
    }
}


#ifndef NOPRINTF64
#  define NUMSZMAX 64
#  define NUMTMAX  0x7FFFFFFFFFFFFFFFULL
#else
#  define NUMSZMAX 32
#  define NUMTMAX  0x7FFFFFFFUL
#endif

static int
putnum(int (*ofnc)(void*, char), void *arg, u_num_t val, int base, int width, int prec, int flags){
    /* base must be: 2<=base<=36 */

    const char *chrs;
    char tbuf[NUMSZMAX+2];
    int i=0, l, n, neg=0;

    chrs = flags&B(PF_ALT)?Set_a:Set_A;

    if( prec > NUMSZMAX )
        prec = NUMSZMAX;
    if( width > NUMSZMAX )
        width = NUMSZMAX;
    if( base < 2 || base > 36 )
        base = 10;

    if( flags&B(PF_SIGNED) && (val > NUMTMAX || val < 0) ){
        neg = 1;
        val = 0 - val;
    }

    /* convert to buffer (in reverse order) */
    do{
        n = val % base;
        if( n < 0 || n > 36 )
            tbuf[i++] = '*';
        else
            tbuf[i++] = chrs[ n ];
    }while( val /= base );

    /* add leading zeros */
    while( i < prec ){
        tbuf[i++] = flags&B(PF_ZERO) ? '0' : ' ';
    }

    /* add sign */
    if( neg )
        tbuf[i++] = '-';
    if( !neg && flags&B(PF_SHOW_PLS) )
        tbuf[i++] = '+';

    l = i;
    width -= i;  /* amount of padding needed */

#if 1
    /* pad on left */
    if( width > 0 && ! (flags&B(PF_LEFT)) ){
        l += width;
        n = 0;
        padding(ofnc, arg, width, ' ');
    }
#endif
    /* copy output */
    n = 0;
    while( i ){
        (*ofnc)(arg, tbuf[--i]);
    }

#if 1
    /* pad on right */
    if( width > 0 && (flags&B(PF_LEFT)) ){
        l += width;
        n = 0;
        padding(ofnc, arg, width, ' ');
    }
#endif

    return l;
}


#ifndef NOPRINTFFLOAT

static int
putfloat(int (*ofnc)(void*, char), void *arg, float_num_t val, int width, int prec, int flags){
    const char *s = 0;
    int slen = 0;
    if( !prec ) prec = 6;

    if( isnan(val) ){
        s = "NaN";
        slen = 3;
    }
    if( isinf(val) ){
        if( val < 0 ){
            s = "-Inf";
            slen = 4;
        }else{
            s = "Inf";
            slen = 3;
        }
    }

    if( s ){
        int pad = width - slen;
        if( pad < 0 ) pad = 0;
        if( !(flags & B(PF_LEFT)) )
            padding(ofnc, arg, pad, ' ');
        // copy out
        while( *s ) (*ofnc)(arg, *s ++);
        if( flags & B(PF_LEFT) )
            padding(ofnc, arg, pad, ' ');

        return slen + pad;
    }

    int sign = 1;
    if( val < 0 ){ sign = -1; val = - val; }

    // RSN - configurable option: use integer math, float, or double
    // float pmul = powf(10, prec);
    int i;
    int pmul = 1;
    for(i=0; i<prec; i++) pmul *= 10;

    if( !(flags & B(PF_FLT_E)) && !(flags & B(PF_FLT_F)) ){
        /* %g => use %e or %f? */
        if( val < 0.0001 || val > pmul ) flags |= B(PF_FLT_E);
    }

    /* round */
    val += .5 / pmul;


    if( flags & B(PF_FLT_E) ){
        int exp = floorf(log10f(val));
        val *= powf(10, -exp);
        int ipart   = val;
        int fpart   = (val - ipart) * pmul;

        int tlen = putnum(ofnc, arg, sign*ipart, 10, 1, 1, flags);
        (*ofnc)(arg, '.');
        tlen ++;
        int flen = putnum(ofnc, arg, fpart, 10, prec, prec, B(PF_ZERO) | B(PF_SIGNED) | (flags&B(PF_SHOW_PLS)) );
        tlen += flen;
        (*ofnc)(arg, 'e');
        tlen ++;
        tlen += putnum(ofnc, arg, exp, 10, 1, 1, B(PF_SIGNED)| (flags&B(PF_SHOW_PLS)) );

        if( tlen < width ){
            // right pad
            padding(ofnc, arg, width - tlen, ' ');
            tlen = width;
        }

        return tlen;
    }else{
        int ipart   = val;
        int fpart   = (val - ipart) * pmul;
        int iwidth  = width - prec - 1;
        int lwidth  = (flags & B(PF_LEFT)) ? 0 : iwidth;
        //fprintf(STDERR, ">> %d,%d\n", ipart, fpart);
        int tlen = putnum(ofnc, arg, sign*ipart, 10, lwidth, lwidth, flags);
        (*ofnc)(arg, '.');
        tlen ++;

        int flen = putnum(ofnc, arg, fpart, 10, prec, prec, B(PF_ZERO) | B(PF_SIGNED) | (flags&B(PF_SHOW_PLS)) );
        tlen += flen;

        if( tlen < width ){
            // right pad
            padding(ofnc, arg, width - tlen, ' ');
            tlen = width;
        }

        return tlen;
    }
}
#endif


/* **************************************************************** */

static int printffnc(void *a, char c){
    putchar(c);
}

void printf(const char *fmt, ...){
    va_list ap;

    va_start(ap,fmt);
    vprintf(printffnc, 0, fmt, ap);
}

/* **************************************************************** */
#ifndef TESTING

static int fprintffnc(void *f, char c){
    fputc(c, f);
}

void fprintf(FILE *f, const char *fmt, ...){
    va_list ap;

    va_start(ap,fmt);
    vprintf(fprintffnc, f, fmt, ap);
}

#endif
/* **************************************************************** */

struct SNP {
    char *s;
    int  max;
    int  pos;
};

static int snprintffnc(void *a, char c){
    struct SNP *s;
    int p;

    s = (struct SNP*)a;
    p = s->pos;
    if( p < s->max-1){
        s->s[p] = c;
        s->s[p+1] = 0;
        s->pos = p + 1;
    }
}

int snprintf(char *buf, int len, const char *fmt, ...){
    va_list ap;
    struct SNP s;

    va_start(ap, fmt);
    s.s = buf;
    s.pos = 0;
    s.max = len;

    return vprintf(snprintffnc, (void*)&s, fmt, ap);
}

int vsnprintf(char *buf, int len, const char *fmt, va_list ap){
    struct SNP s;

    s.s = buf;
    s.pos = 0;
    s.max = len;

    return vprintf(snprintffnc, (void*)&s, fmt, ap);
}

int
fncprintf(int (*ofnc)(void*, char), void *arg, const char *fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    return vprintf(ofnc, arg, fmt, ap);
}

/* **************************************************************** */


#ifdef TESTING
#include <math.h>
#include <string.h>
void main(void){
    char buffer[128];
    int i;

    for(i=0; i<128; i++) buffer[i]='a';


    snprintf(buffer, 128, "%d %c %s %02.2x\n", (int)324, (int)0x45, "foobar", (int)32);
    puts(buffer);

    //printf("%ld %c %s %02.2x\n",   (int)324, (int)0x45, "foobar", (int)32);
    //printf("%.6ld %c %s %02.2x\n", (int)324, (int)0x45, "foobar", (int)32);


#ifndef NOPRINTFFLOAT

    printf("%f, %.2f, %8.2f, %.4f.\n", 12.3456789012345, 12.3456789, 12.3456789, 12.0034567);
    printf("%8.2f.\n", 12.3456789);
    printf("%-8.2f.\n", 12.3456789);

    printf("%f %f %f %f %f\n", .0012345, .12345, 123.45, 12345.6, 12345678.9);
    printf("%e %e %e %e %e\n", .0012345, .12345, 123.45, 12345.6, 12345678.9);

    printf("%f\n", 123.45);

#endif

}

#endif

