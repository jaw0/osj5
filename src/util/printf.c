/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function:
*/


#include <conf.h>
#include <stdarg.h>
#include <sys/types.h>

#ifndef  _PRINTF_TESTING
#include <nstdio.h>
#endif
#include <time.h>

// config:
//   NOPRINTF64		- do not include 64bit integer support
//   NOPRINTFFLOAT	- do not include float support
//   NOPRINTFTIME	- do not include support for timestamps %T
//   NOPRINTFIP		- do not include support for ip addresses %I
//   PRINTFFLOATTYPE	- use (float|double) for floating point math

#ifdef PRINTF_SMALL
#  define NOPRINTF64
#  define NOPRINTFFLOAT
#  define NOPRINTFTIME
#  define NOPRINTFIP
#endif

#ifdef _PRINTF_TESTING
//# define NOPRINTF64
//# define NOPRINTFFLOAT
# define NOPRINTFTIME
#endif


/*
  a minimal implementation of printf
  %<flags><width><.prec><,char digits><type>

  type::
  c	- char
  s	- string
  %	- %
  &	- magic zero-width character
  x	- lower case hex
  X	- UPPER case hex
  d,D	- decimal
  o	- octal
  b     - binary
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
    PF_SPACE,
    PF_LEFT,        	/* left justify, not right */
    PF_QUAD,	    	/* arg is a quad */
    PF_FLT_F,
    PF_FLT_E
};

#define B(x)		(1<<(x))
#define isdig(x)	(((x)>='0') && ((x)<='9'))

typedef unsigned long long u_quad;
typedef unsigned int u_numstd_t;

#ifndef NOPRINTF64
typedef u_quad	u_numfull_t;
#else
typedef u_numstd_t u_numfull_t;
#endif

struct put_args {
    short flags;
    unsigned char base;
    unsigned char width;
    unsigned char prec;
    unsigned char group;
    unsigned char gchar;
};


static const char Set_A[] =	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char Set_a[] =	"0123456789abcdefghijklmnopqrstuvwxyz";
static const char spinchar[] = "|\\-/";

int snprintf(char *, int, const char *, ...);
static int putnum(int (*)(void*, char), void *, u_numfull_t, struct put_args);
static int puthex(int (*)(void*, char), void *, const char *, struct put_args);
static int putstr(int (*)(void*, char), void *, const char *, struct put_args);
int fncprintf(int (*)(void*, char), void *, const char *, ...);

#ifndef NOPRINTFFLOAT
#  ifdef PRINTFFLOATTYPE
typedef PRINTFFLOATTYPE float_num_t;
#  else
typedef float float_num_t;
#  endif
static int putfloat(int (*)(void*, char), void *, float_num_t, struct put_args);
#endif

int vxprintf(int (*ofnc)(void*, char), void *arg, const char *fmt, va_list ap){
    const char *p = fmt;
    char *s;
    u_numfull_t val;
#ifndef NOPRINTFFLOAT
    float_num_t fval;
#endif
    struct put_args pa;
    int pos = 0;
    int i, n;

    while(*p){
        pa.width = pa.prec = pa.group = pa.flags = 0;
        pa.gchar = ',';
        pa.base = 10;
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
                pos += putstr(ofnc, arg, s, pa);

                break;
#ifndef NOPRINTFTIME
            case 'T': {
                /* %T - timestamp */
                char buf[32];
                struct tm tr;

                val = va_arg(ap, u_quad);
                gmtime_r(&val, &tr);

                if( pa.flags & B(PF_ALT) )
                    snprintf(buf, sizeof(buf), "%d-%0.2d-%0.2d T%d:%0.2d:%0.2d.%0.6d",
                             tr.tm_year, tr.tm_mon, tr.tm_mday, tr.tm_hour, tr.tm_min, tr.tm_sec, tr.tm_usec);
                else
                    snprintf(buf, sizeof(buf), "%d-%0.2d-%0.2d T%0.2d:%0.2d:%0.2d",
                             tr.tm_year, tr.tm_mon, tr.tm_mday, tr.tm_hour, tr.tm_min, tr.tm_sec);

                fncprintf(ofnc, arg, "%*.*s", pa.width, pa.prec, buf);
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
                    pos += putnum(ofnc, arg, addr[i], pa);
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
                if( (pa.flags & B(PF_SHOW_PLS)) && (val > 0xff) ){
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
                pa.flags |= B(PF_SIGNED);
                /* fall thru - weeee!!! */
            case 'u':
            case 'U':
                pa.base = 10;
                goto donum;
            case 'o':
                pa.base = 8;
                goto donum;
            case 'b':
                pa.base = 2;
                goto donum;
            case '=':
                /* arbitrary base */
                if(!pa.prec) pa.prec = 16;
                if(*++p == '*'){
                    val = va_arg(ap, int);
                    pa.base = (val<0)?-val:val;
                    goto donum;
                }
                val = 0;
                while( isdig(*p) ){
                    val =  10*val + *p -'0';
                    p++;
                }
                pa.base = val;
                p--; /* push back */
                goto donum;
            case 'x':
                pa.flags |= B(PF_ALT);
                /* fallthru' */
            case 'X':
                pa.base = 0x10;
            donum:
                if( pa.flags & B(PF_QUAD) ){
                    val = va_arg(ap, u_numfull_t);
                }else{
                    val = va_arg(ap, u_numstd_t);
                    /* sign extend */
                    if( pa.flags & B(PF_SIGNED)){
                        if( val & 0x80000000 )
                            val |= 0xFFFFFFFF00000000ULL;
                    }
                }

                pos += putnum(ofnc, arg, val, pa);
                break;
            case 'h':
                pa.flags |= B(PF_ALT);
                /* fallthru' */
            case 'H':
                s = va_arg(ap, char*);
                pos += puthex(ofnc, arg, s, pa);
                break;
#ifndef NOPRINTFFLOAT
            case 'f': case 'F':
                pa.flags |= B(PF_FLT_F);
                goto doflt;
            case 'e': case 'E':
                pa.flags |= B(PF_FLT_E);
                /* fall through */
            case 'g': case 'G':
            doflt:
                fval = va_arg(ap, double);
                pos += putfloat(ofnc, arg, fval, pa);
                break;
#endif
            case '*':
                pa.width = va_arg(ap,int);
                goto rflag;
            case ',':
                /* group digits with seperator ,<char><numchars|*> */
                /* %09,_4x   => '0_1234_5678' */
                pa.gchar = *++p;
                if(*++p == '*'){
                    pa.group = va_arg(ap, int);
                    goto rflag;
                }
                n = 0;
                while( isdig(*p) ){
                    n =  10*n + *p -'0';
                    p++;
                }
                pa.group = n > 0 ? n : 3;
                goto reswitch;
            case '.':
                /* set prec */
                if(*++p == '*'){
                    pa.prec = va_arg(ap, int);
                    goto rflag;
                }
                n = 0;
                while( isdig(*p) ){
                    n =  10*n + *p -'0';
                    p++;
                }
                pa.prec = n;
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
                pa.width = n;
                goto reswitch;
#if 0
#ifndef TESTING
            case 'p':
                /* spin */
                while(pa.prec--){
                    (*ofnc)(arg, spinchar[pa.prec%4]);
                    msleep(pa.width);
                    (*ofnc)(arg, '\b');
                }
#endif
#endif
                break;
            case '\0':
                return pos;
            case '#':
                pa.flags |= B(PF_ALT);
                goto rflag;
            case '0':
                pa.flags |= B(PF_ZERO);
                goto rflag;
            case '+':
                pa.flags |= B(PF_SHOW_PLS);
                goto rflag;
            case '-':
                pa.flags |= B(PF_LEFT);
                goto rflag;
            case ' ':
                pa.flags |= B(PF_SPACE);
                goto rflag;
#ifndef NOPRINTF64
            case 'Q':
            case 'q':
                pa.flags |= B(PF_QUAD);
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
    while( n-- > 0 ){
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
putnum(int (*ofnc)(void*, char), void *arg, u_numfull_t val, struct put_args pa){
    /* base must be: 2<=base<=36 */

    const char *chrs;
    char tbuf[NUMSZMAX+2];
    short i=0, vl, l, n, neg=0;

    chrs = pa.flags&B(PF_ALT)?Set_a:Set_A;

    if( pa.prec  > NUMSZMAX ) pa.prec  = NUMSZMAX;
    if( pa.width > NUMSZMAX ) pa.width = NUMSZMAX;
    if( pa.base < 2 || pa.base > 36 )
        pa.base = 10;

    if( pa.flags&B(PF_SIGNED) && (val > NUMTMAX || val < 0) ){
        neg = 1;
        val = 0 - val;
    }

    /* convert to buffer (in reverse order) */
    do{
        n = val % pa.base;
        val = val / pa.base;
        if( n < 0 || n > 36 )
            tbuf[i++] = '*';
        else
            tbuf[i++] = chrs[ n ];
    }while( val );

    /* add leading zeros */
    while( i < pa.prec ){
        tbuf[i++] = '0';
    }

    if( pa.flags & B(PF_ZERO) ){
        while( i < pa.width ){
            tbuf[i++] = '0';
        }
    }

    vl = i;

    /* add sign */
    if( neg ){
        tbuf[i++] = '-';
    }else{
        if( pa.flags & B(PF_SHOW_PLS) )
            tbuf[i++] = '+';
        else if( pa.flags & B(PF_SPACE) )
            tbuf[i++] = ' ';
    }

    l = i;
    if( i >= pa.width ) pa.width = 0;
    if( pa.width > 0 ) pa.width -= i;  /* amount of padding needed */

    if( pa.group && pa.width > 0 ){
        int ngc = vl / pa.group;
        if( ngc >= pa.width ) pa.width = 0;
        if( pa.width > 0 ) pa.width -= ngc;
    }


    /* pad on left */
    if( pa.width > 0 && ! (pa.flags&B(PF_LEFT)) ){
        l += pa.width;
        padding( ofnc, arg, pa.width, ' ');
    }

    /* copy output */
    n = 0;
    while( i ){
        (*ofnc)(arg, tbuf[--i]);

        if( pa.group && i && (i < vl) && (i % pa.group == 0) ){
            (*ofnc)(arg, pa.gchar);
            l ++;
        }
    }

    /* pad on right */
    if( pa.width > 0 && (pa.flags&B(PF_LEFT)) ){
        l += pa.width;
        padding( ofnc, arg, pa.width, ' ');
    }

    return l;
}

static int
putstr(int (*ofnc)(void*, char), void *arg, const char *s, struct put_args pa){

    short n=0, l=0;

    if( !s )
        s = "(null)";

    /* how much padding */
    /* width is minlen, prec is maxlen */
    if( pa.width ){
        n = strlen(s);
        if( pa.prec && (n > pa.prec) ){
            /* longer than maxlen, no pad */
            n = 0;
        }else if( n >= pa.width )
            /* longer than minlen, no pad */
            n = 0;
        else
            n = pa.width - n;
    }else{
        n = 0;
    }


    if( !(pa.flags & B(PF_LEFT)) && n ){
        /* add pad */
        padding(ofnc, arg, n, ' ');
        l += n;
        n = 0;
    }
    while(*s){
        (*ofnc)(arg, *s++);
        l ++;
        /* no more than prec chars out */
        /* pad to width */
        if(pa.prec && (l>=pa.prec)) break;
    }

    if( n ){
        /* add pad */
        padding(ofnc, arg, n, ' ');
        l += n;
        n = 0;
    }

    return l;
}


/* mini-hexdump width bytes */
static int
puthex(int (*ofnc)(void*, char), void *arg, const char *buf, struct put_args pa){
    short i, n, l=0;

    if( pa.width <= 0 ) pa.width = 1;
    const char *chrs = pa.flags&B(PF_ALT) ? Set_a : Set_A;

    for(i=n=0; i<pa.width; i++){
        l += 2;

        (*ofnc)(arg, chrs[ (buf[i]>>4) & 0xF ]);
        n ++;
        if( pa.group && (n % pa.group == 0) ){
            (*ofnc)(arg, pa.gchar);
            l ++;
        }

        (*ofnc)(arg, chrs[ buf[i] & 0xF ]);
        n ++;
        if( pa.group && (i != pa.width-1) && (n % pa.group == 0) ){
            (*ofnc)(arg, pa.gchar);
            l ++;
        }
    }

    return l;
}




#ifndef NOPRINTFFLOAT

static int
putfloat(int (*ofnc)(void*, char), void *arg, float_num_t val, struct put_args pa){
    const char *s = 0;
    int slen = 0;
    if( !pa.prec ) pa.prec = 6;

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
        int pad = pa.width - slen;
        if( pad < 0 ) pad = 0;
        if( !(pa.flags & B(PF_LEFT)) )
            padding(ofnc, arg, pad, ' ');
        // copy out
        while( *s ) (*ofnc)(arg, *s ++);
        if( pa.flags & B(PF_LEFT) )
            padding(ofnc, arg, pad, ' ');

        return slen + pad;
    }

    int sign = 1;
    if( val < 0 ){ sign = -1; val = - val; }

    // RSN - configurable option: use integer math, float, or double
    // float pmul = powf(10, pa.prec);
    int i;
    int pmul = 1;
    for(i=0; i<pa.prec; i++) pmul *= 10;

    if( !(pa.flags & B(PF_FLT_E)) && !(pa.flags & B(PF_FLT_F)) ){
        /* %g => use %e or %f? */
        if( val < 0.0001 || val > pmul ) pa.flags |= B(PF_FLT_E);
    }

    /* round */
    val += .5 / pmul;


    if( pa.flags & B(PF_FLT_E) ){
        int exp = floorf(log10f(val));
        val *= powf(10, -exp);
        int ipart   = val;
        int fpart   = (val - ipart) * pmul;

        int tlen = putnum(ofnc, arg, sign*ipart, (struct put_args){.base = 10, .width = 1, .prec = 1, .flags = pa.flags});
        (*ofnc)(arg, '.');
        tlen ++;
        int flen = putnum(ofnc, arg, fpart, (struct put_args){.base = 10, .width = pa.prec, .prec = pa.prec, .flags = B(PF_ZERO) | B(PF_SIGNED) | (pa.flags&B(PF_SHOW_PLS)) } );
        tlen += flen;
        (*ofnc)(arg, 'e');
        tlen ++;
        tlen += putnum(ofnc, arg, exp, (struct put_args){.base = 10, .width = 1, .prec = 1, .flags = B(PF_SIGNED)| (pa.flags&B(PF_SHOW_PLS))} );

        if( tlen < pa.width ){
            // right pad
            padding(ofnc, arg, pa.width - tlen, ' ');
            tlen = pa.width;
        }

        return tlen;
    }else{
        int ipart   = val;
        int fpart   = (val - ipart) * pmul;
        int iwidth  = pa.width - pa.prec - 1;
        if( pa.flags & B(PF_LEFT) ) iwidth = 0;
        if( iwidth < 0 ) iwidth = 0;

        // dprintf(2, ">> %d,%d; lw %d; f %x\n", ipart, fpart, iwidth, pa.flags);
        int tlen = putnum(ofnc, arg, sign*ipart, (struct put_args){.base = 10, .width = iwidth, .prec = 0, .flags = pa.flags});
        (*ofnc)(arg, '.');
        tlen ++;

        int flen = putnum(ofnc, arg, fpart, (struct put_args){.base = 10, .width = pa.prec, .prec = pa.prec, .flags = B(PF_ZERO) | B(PF_SIGNED) | (pa.flags&B(PF_SHOW_PLS))} );
        tlen += flen;

        if( tlen < pa.width ){
            // right pad
            padding(ofnc, arg, pa.width - tlen, ' ');
            tlen = pa.width;
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
    vxprintf(printffnc, 0, fmt, ap);
    va_end(ap);
}

void vprintf(const char *fmt, va_list ap){

    vxprintf(printffnc, 0, fmt, ap);
}

/* **************************************************************** */
#ifndef _PRINTF_TESTING

static int fprintffnc(void *f, char c){
    fputc(c, f);
}

void fprintf(FILE *f, const char *fmt, ...){
    va_list ap;

    va_start(ap,fmt);
    vxprintf(fprintffnc, f, fmt, ap);
    va_end(ap);
}
void vfprintf(FILE *f, const char *fmt, va_list ap){
    vxprintf(fprintffnc, f, fmt, ap);
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
    if(len) *buf = 0;

    int r = vxprintf(snprintffnc, (void*)&s, fmt, ap);
    va_end(ap);
    return r;
}

int vsnprintf(char *buf, int len, const char *fmt, va_list ap){
    struct SNP s;

    s.s = buf;
    s.pos = 0;
    s.max = len;

    return vxprintf(snprintffnc, (void*)&s, fmt, ap);
}

int
fncprintf(int (*ofnc)(void*, char), void *arg, const char *fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    int r = vxprintf(ofnc, arg, fmt, ap);
    va_end(ap);
    return r;
}

/* **************************************************************** */


#ifdef _PRINTF_TESTING
#include <math.h>
#include <string.h>

void main(void){
    char buffer[128];
    int i;


    for(i=0; i<128; i++) buffer[i]='a';

    snprintf(buffer, 128, "%d %c %s %02X", (int)324, (int)0x45, "foobar", (int)32);
    puts(buffer);

    printf("%d\n", 123);
    printf("%08x;\n", 0x12);
    printf("%08,_3x;\n", 0x12);
    printf("%032,_4b;\n", 0x12345678);
    //printf(">%0=2 %04=2\n", 0x1234, 0x5);
    printf("[%8,:4H]\n", "foobarbar");
    printf("%5s;\n", "foo");
    printf("%-5.5s;\n", "foo");
    printf("%-5.5s;\n", "foobar");

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

