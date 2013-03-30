/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function:

  $Id$

*/


#include <stdarg.h>
#include <sys/types.h>
#ifndef TESTING
#include <nstdio.h>
#endif
#include <calendar.h>

// use 64bit nums?
#define PRINTF64
// floats?
#define PRINTFFLOAT


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
#ifdef PRINTF64
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

#ifdef PRINTFFLOAT
static int putfloat(int (*)(void*, char), void *, float, int, int, int);
#endif


int vprintf(int (*ofnc)(void*, char), void *arg, const char *fmt, va_list ap){
    const char *p = fmt;
    char *s;
    u_num_t val;
#ifdef PRINTFFLOAT
    float fval;
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
            case 'T': {
                /* %T - timestamp */
                char buf[32];
                int hr, min, sec, usec, dy, mon, yr;
                int i;

                val = va_arg(ap, u_quad);

                usec = val % 1000000;
                val /= 1000000;
                sec  = val % 60;
                val /= 60;
                min  = val % 60;
                val /= 60;
                hr   = val % 24;
                val /= 24;
                /* val is now days */

                dy = val % 365;
                yr = val / 365;

                dy -= leap_years_since_year_1(yr);
                yr ++;
                if( yr > 1752 || (yr == 1752 && dy > 243) )
                    /* gregorian reformation */
                    dy += 11;
                if( dy > (leap_year(yr) ? 366 : 365) ){
                    dy -= leap_year(yr) ? 366 : 365;
                    yr ++;
                }
                while( dy < 0 ){
                    yr --;
                    dy += leap_year(yr) ? 366 : 365;
                }

                mon = 0;
                while( dy >= days_in_month(mon, yr) ){
                    dy -= days_in_month(mon, yr);
                    mon ++;
                }

                mon ++;
                dy ++;

                if( flags & B(PF_ALT) )
                    snprintf(buf, sizeof(buf), "%d-%0.2d-%0.2d %d:%0.2d:%0.2d.%0.6d",
                             yr, mon, dy, hr, min, sec, usec);
                else
                    snprintf(buf, sizeof(buf), "%d-%0.2d-%0.2d %0.2d:%0.2d:%0.2d",
                             yr, mon, dy, hr, min, sec);

                fncprintf(ofnc, arg, "%*.*s", width, prec, buf);
                break;

            }

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
            case '&':		/* magic zero-width character */
                break;
            case '%':
                (*ofnc)(arg, '%');
                pos ++;
                break;
            case 'c':
                val = va_arg(ap, int);
                (*ofnc)(arg, val);
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
#ifdef PRINTFFLOAT
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
#ifdef PRINTF64
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


#ifdef PRINTF64
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


#ifdef PRINTFFLOAT
//    PF_SHOW_PLS,    	/* arg is signed, show + if positive */
//    PF_LEFT,        	/* left justify, not right */

static int
putfloat(int (*ofnc)(void*, char), void *arg, float val, int width, int prec, int flags){
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

    /* RSN - %e, %g */
    int sign = 1;
    if( val < 0 ){ sign = -1; val = - val; }
    int ipart = val;
    int fpart = (val - ipart) * powf(10, prec);
    int iwidth  = width - prec - 1;
    int lwidth  = (flags & B(PF_LEFT)) ? 0 : iwidth;

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
#endif

days_in_month(int m, int y){

        switch(m){
          case 8: case 3: case 5: case 10:
                return 30;
          case 1:
                return leap_year(y) ? 29 : 28;
          default:
                return 31;
        }
}


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


#ifdef PRINTFFLOAT
    printf("%f, %.2f, %8.2f, %.4f.\n", 12.3456789012345, 12.3456789, 12.3456789, 12.0034567);
    printf("%8.2f.\n", 12.3456789);
    printf("%-8.2f.\n", 12.3456789);

#endif

}

#endif

