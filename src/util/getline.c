/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: text input with edit + history
*/


#ifndef TESTING
#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <alloc.h>
#define NEWLINE	"\n"
#else
#include <stdio.h>
#include "../include/conf.h"
#define puts(x)	fputs(x, stdout)
#define NEWLINE	"\r\n"
#define alloc malloc
#endif



#define VERSION "Getline 2.1"


#define META(x) ( (x) | 0x80 )
#define BRKT(x)	( (x) | 0x100 )
#define CTRL(x)	( (x) - 'a' + 1 )

#define G_CONT	0	/* continue with more input */
#define G_DONE	1	/* done getting input */
#define G_NEXT	2	/* go to next history entry */
#define G_PREV	3	/* go to prev history entry */

#ifdef GETLINEHIST
#define NHISTORY 10	/* how many lines of history */

struct History {
    unsigned char n, p;
    char *lines[NHISTORY];
};

#ifndef USE_PROC
struct History history = {
    0, 0
};
#endif
#endif

#ifndef GETLINE_SMALL
/* used to find word-boundaries for word-by-word moving */
int
isnonword(char c){

    return strchr(" \t\n\r.,-;:|!@/&(){}[]", c) ? 1 : 0;
}
#endif

/* move cursor */
static void
move(const char *s, int max, int *i, int from, int to, int beepp){

    if( from < to ){
        for( ; from<max && s[from] && from != to; from++){
            putchar(s[from]);
        }
        *i = from;
    }else{
        for( ; from && from != to; from--){
            putchar('\b');
        }
        *i = from;
    }
    if( beepp && from!=to)
        putchar('\a');
}

/* insert char */
static void
insert(char *s, int max, int *i, char c, u_long flags){
    int j, x;

    j = *i;
    if( j >=max-1 ){
        putchar('\a');
        return;
    }
    do{
        x = s[j];
        s[j] = c;
        putchar( (flags & GLF_STARS) ? '*' : c);
        c = x;
        j++;
    }while(c && j<max-1);
    s[j]=0;
    (*i)++;
    move(s, max, i, j, *i, 0);
}

#ifndef GETLINE_SMALL
/* SOOPER-SECRET UNDOCUMENTED FUNCTION!!! */
static int
tty_debug(char *s, int max, int *i, char c){
    int j;
    char buf[32];

    j = 0;
    printf(NEWLINE "i=%d [", *i);

    while( s[j] ){
        if( s[j] >= ' ' && s[j] <= 0x7E )
            putchar(s[j]);
        else
            putchar('.');
        j++;
    }

    printf("] len=%d" NEWLINE, j);
    return G_CONT;
}
#endif

/* quote the next char */
static int
tty_quote(char*s, int max, int *i, char c){

    putchar('^');
    putchar('\b');
    s[(*i)++] = c = getchar();
    putchar(c);

    return G_CONT;
}

#ifndef GETLINE_SMALL
/* send SIGSUSPEND */
static int
tty_stop(char*s, int max, int *i, char c){

    puts(NEWLINE "Job control not supported" );
    return G_CONT;
}
#endif

#ifndef GETLINE_SMALL
/* reprint the input buffer */
static int
tty_rprnt(char *s, int max, int *i, char c){

    fputs(NEWLINE, STDOUT);
    fputs(s, STDOUT);

    for(*i=0; s[*i]; (*i)++)
        ;
    return G_CONT;
}
#endif

/* abort input */
static int
tty_quit(char *s, int max, int *i, char c){

    *i = 0;
    s[*i] = 0;
    fputs("\a^C", STDOUT);
    return G_DONE;
}

/* end of input */
static int
tty_eol(char *s, int max, int *i, char c){

    fputs(NEWLINE, STDOUT);
    return G_DONE;
}

#ifndef GETLINE_SMALL
/* display version */
static int tty_version(char *s, int max, int *i, char c){

    puts(NEWLINE VERSION);
    return G_CONT;
}
#endif

/* move to the beginning of the input buffer */
static int
tty_toleftend(char *s, int max, int *i, char c){

    move(s, max, i, *i, 0, 0);
    return G_CONT;
}

/* move to the far end of the input buffer */
static int
tty_torightend(char *s, int max, int *i, char c){

    move(s, max, i, *i, max, 0);
    return G_CONT;
}

/* move one char to the left */
static int
tty_toleft(char *s, int max, int *i, char c){

    move(s, max, i, *i, *i-1, 1);
    return G_CONT;
}

/* move one char to the right */
static int
tty_toright(char *s, int max, int *i, char c){

    move(s, max, i, *i, *i+1, 1);
    return G_CONT;
}

/* delete the char at the current position */
static int
tty_delete(char *s, int max, int *i, char c){
    int j;

    j = *i;
    if( s[*i] ){
        while(s[j]){
            s[j] = s[j + 1];
            if( s[j] ) putchar(s[j]);
            j++;
        }
        fputs(" \b", STDOUT);
        /* put cursor back */
        while( j != (*i) + 1 ){
            j--;
            putchar('\b');
        }
    }else{
        putchar('\a');
    }
    return G_CONT;
}

/* delete the previous char */
static int
tty_bksp(char *s, int max, int *i, char c){

    if(!*i){
        putchar('\a');
        return 0;
    }
    (*i)--;
    fputs("\b \b", STDOUT);

    return tty_delete(s, max, i, c);
}

/* delete everything from here to the far right end */
static int
tty_killr(char *s, int max, int *i, char c){
    int j;

    if( s[*i] ){
        for(j=*i; s[j]; j++){
            putchar(' ');
        }
        for(; j!=*i; j--){
            s[j]=0;
            putchar('\b');
        }
        s[j]=0;
    }else{
        putchar('\a');
    }
    return G_CONT;
}

/* delete everything from here to the beginning of the buffer */
static int
tty_killl(char *s, int max, int *i, char c){

    if( *i ){
        while(*i)
            tty_bksp(s, max, i, c);
    }else{
        putchar('\a');
    }

    return G_CONT;
}

#ifndef GETLINE_SMALL
/* delete the word to the left */
static int
tty_wordl(char *s, int max, int *i, char c){

    if( *i ){
        while( *i>0 && !isnonword(s[*i - 1]) )
            tty_bksp(s, max, i, c);
        while( *i>0 && isnonword(s[*i - 1]) )
            tty_bksp(s, max, i, c);
    }else{
        putchar('\a');
    }
    return G_CONT;
}

/* delete the word to the right */
static int
tty_wordr(char *s, int max, int *i, char c){

    if( s[*i] ){
        while( s[*i] && isnonword(s[*i]) )
            tty_delete(s, max, i, c);
        while( s[*i] && !isnonword(s[*i]) )
            tty_delete(s, max, i, c);
    }else{
        putchar('\a');
    }
    return G_CONT;
}

/* move one word to the right */
static int
tty_towordr(char *s, int max, int *i, char c){

    if( s[*i] ){
        while( s[*i] && isnonword(s[*i]) )
            move(s, max, i, *i, *i+1, 0);
        while( s[*i] && !isnonword(s[*i]) )
            move(s, max, i, *i, *i+1, 0);
    }else{
        putchar('\a');
    }
    return G_CONT;
}

/* move one word to the left */
static int
tty_towordl(char *s, int max, int *i, char c){

    if( *i ){
        while( *i>0 && isnonword(s[*i-1]) )
            move(s, max, i, *i, *i-1, 0);
        while( *i>0 && !isnonword(s[*i-1]) )
            move(s, max, i, *i, *i-1, 0);
    }else{
        putchar('\a');
    }
    return G_CONT;
}
#endif

/* honk */
static int
tty_beep(char*s, int max, int *i, char c){

    putchar('\a');
    return G_CONT;
}

#ifndef GETLINE_SMALL
/* move up in history */
static int
tty_uphist(char*s, int max, int *i, char c){
    return G_PREV;
}

/* move down in history */
static int
tty_dnhist(char*s, int max, int *i, char c){
    return G_NEXT;
}
#endif

/* key binding map */
static const struct {
    int c;
    int (*f)(char*, int, int*, char);
} keymap[] = {
    /* bindings for keys to functions */

    /* std. UNIX tty bindings */
    { CTRL('c'), tty_quit       },
    { CTRL('v'), tty_quote      },
    { CTRL('h'), tty_bksp       },
    { CTRL('j'), tty_eol        },
    { CTRL('m'), tty_eol        },
    { CTRL('u'), tty_killl      },
    { 28,        tty_quit       }, /* ^\ */
    { 127,       tty_bksp       },
#ifndef GETLINE_SMALL
    { CTRL('r'), tty_rprnt      },
    { CTRL('z'), tty_stop       },
    { CTRL('w'), tty_wordl      },
#endif

    /* and some emacs-isms */
    { CTRL('a'), tty_toleftend  },
    { CTRL('b'), tty_toleft     },
    { CTRL('d'), tty_delete     },
    { CTRL('e'), tty_torightend },
    { CTRL('f'), tty_toright    },
    { CTRL('k'), tty_killr      },
    { CTRL('q'), tty_quote      },
#ifndef GETLINE_SMALL
    { CTRL('p'), tty_uphist     },
    { CTRL('n'), tty_dnhist     },
    { META('b'), tty_towordl    },
    { META('d'), tty_wordr      },
    { META('f'), tty_towordr    },
#endif

    /* vt100 arrows (ansi X3.64) */
#ifndef GETLINE_SMALL

    { BRKT('A'), tty_uphist     },	/* up */
    { BRKT('B'), tty_dnhist     },	/* down */
#endif
    { BRKT('C'), tty_toright    },
    { BRKT('D'), tty_toleft     },

    /* vt52 arrows */
#ifndef GETLINE_SMALL
    { META('A'), tty_uphist     },	/* up */
    { META('B'), tty_dnhist     },	/* down */
#endif
    { META('C'), tty_toright    },
    { META('D'), tty_toleft     },

#ifndef GETLINE_SMALL
    /* for debugging */
    { META('x'), tty_debug      },
    { META('v'), tty_version    },
#endif

    /* this *must* be last */
    { 0,         0              }
};

void getline_cleanup(void){
#if defined(GETLINEHIST) && defined(USE_PROC)
    struct History *hist;
    int n;

    hist = (struct History*)currproc->getlinedata;
    if( !hist )
        return;

    for(n=0; n<hist->n; n++){
        free(hist->lines[n], 0);
    }
    free(hist, sizeof(struct History));

    currproc->getlinedata = 0;
#endif
}

char *
getline2(char *s, int max, u_long flags ){
    int i=0;
    int c, n, r;

#ifdef GETLINEHIST
    int hc;
    struct History *hist;

    if( flags & GLF_HIST ){
#ifdef USE_PROC
        hist = (struct History*)currproc->getlinedata;
        if( !hist ){
            hist = (struct History*)alloc( sizeof(struct History) );
            hist->n = hist->p = 0;
            currproc->getlinedata = hist;
        }
#else
        hist = &history;
#endif
        hc = hist->p;
    }else{
        hist = 0;
        hc = 0;
    }
#endif

#ifdef TESTING
    system("stty raw -echo");
#endif

    if( flags & GLF_USEBUF ){
        /* usep = 0 => clear buffer (else reuse buffer)
           left => cursor at left (else at right)
        */
        fputs(s, STDOUT);
        for(i=0; s[i]; i++)
            ;
        if( flags & GLF_LEFT ){
            move(s, max, &i, i, 0, 0);
        }
    }else{
        *s = 0;
    }
    while( 1 ){
        c = getchar();

        if( c == 0x1b ){
            /* support \ex and \e[x escape seq.s */
            c = 0x80 | getchar() ;
            if( c == META('[') )
                c = 0x100 | getchar() ;
        }

        /* search keymap for key */
        for(n=0; keymap[n].f; n++)
            if (c == keymap[n].c) break;

        if( keymap[n].f ){
            r = (keymap[n].f)(s, max, &i, c);
        }else{
            insert(s, max, &i, c, flags);
            r = 0;
        }

        switch(r){
        case G_DONE:
#ifdef GETLINEHIST
            if( (flags & GLF_HIST) && *s ){
                if( hist->n == NHISTORY )
                    free( hist->lines[hist->p], 0 );

                hist->lines[hist->p] = (char*)alloc( strlen(s) + 1 );
                strcpy(hist->lines[hist->p], s);

                hist->p++;
                hist->p %= NHISTORY;

                if( hist->n < NHISTORY )
                    hist->n++;
            }
#endif
#ifdef TESTING
            system("stty -raw echo");
#endif
            return s;

#ifdef GETLINEHIST
        case G_PREV:
        case G_NEXT:
            if( flags & GLF_HIST ){
                if( hist->n ){
                    if( r == G_PREV )
                        hc --;
                    else
                        hc ++;
                    hc = (hc + hist->n) % hist->n;
                    tty_torightend(s, max, &i, c);
                    if( *s )
                        tty_killl(s, max, &i, c);
                    strncpy(s, hist->lines[ hc ], max);
                    tty_torightend(s, max, &i, c);
                }else{
                    putchar('\a');
                }
            }else{
                putchar('\a');
            }
            break;
#else
        case G_PREV:
        case G_NEXT:
            putchar('\a');
            break;
#endif
        case G_CONT:
        default:
            break;
        }


    } /* eow */

    /* not reached */
    return s;
}

char *
getline(char *s, int max, int usep){
    return getline2(s, max, (usep ? GLF_USEBUF : 0) | GLF_HIST );
}

char *
getpass(char *s, int max){
    return getline2(s, max, GLF_STARS);
}

#ifdef GETLINE_TESTING
int
main(){
    char buffer[1024] = "123.45.67.89";

    while(1){
        fprintf(stderr, "[huh]? ");
        getline(buffer, 1024, 1);
        if( !*buffer )
            break;
        printf("<<%s>>\r\n", buffer);
    }

}
#endif
