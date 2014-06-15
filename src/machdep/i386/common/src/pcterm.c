/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function:

  $Id$

*/

/* screen and keyboard handling */
/* screen output implements a subset of ANSI X3.64 */

#include <sys/types.h>
#include <sys/param.h>
#include <nstdio.h>
#include <proc.h>
#include <error.h>
#include <arch.h>
#include <pio.h>
#include <pcterm.h>
#include <dev.h>
#include <bootflags.h>
#include <msgs.h>

#define PCTERM_QUEUE_SIZE	64		/* keyboard input buffer size */

static int term_putchar(FILE*, char);
static int term_getchar(FILE*);
static int term_noop(FILE*);
static int term_flush(FILE*);
static int term_status(FILE*);
void move_cursor(FILE*, int, int);
void clear_screen(FILE*);
void kbdirq(struct intrframe *);

const struct io_fs term_fs = {
    term_putchar,
    term_getchar,
    term_noop,	/* no close */
    term_flush,
    term_status,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0

};

#define MAXARG	5
struct Screen {
    u_char x, y;
    u_char attr;
    u_char mn;
    u_char arg[MAXARG];
    u_short mode;
#define GOTESC		0x100
#define GOTBRACK	0x200
    u_short *d;
};

struct Kbd {
    char queue[ PCTERM_QUEUE_SIZE ];
    short head, tail, len;
    u_char state;
    u_short port;
};

struct Term {
    FILE file;
    struct Screen scr;
    struct Kbd kbd;
} term;
/* if we want to support multiple screens/kbds, this can
   easily be made term[N] ... */

extern u_long k_paddr;

FILE *pcterm_port;



/* for \e[...m */

const u_char ansicolors[] = { 0, 4, 2, 6, 1, 5, 3, 7 };

void
ansiof(struct Term *t, int a){

    if( a >= 30 && a <= 37 ){
        t->scr.attr &= ~7;
        t->scr.attr |= ansicolors[ a - 30 ];
    }
    if( a >= 40 && a <= 47 ){
        t->scr.attr &= ~0x70;
        t->scr.attr |= ansicolors[ a - 40 ] << 4;
    }
    if( a >= 0 && a <= 8 ){
        switch( a ){
        case 0:	t->scr.attr = 7;	break;
        case 1:	t->scr.attr |= 0x8;	break;
        case 5:	t->scr.attr |= 0x80;	break;
        case 7:	t->scr.attr = 0x70;	break;
        case 8:	t->scr.attr = 0;	break;
        }
    }
}

/*
  initialize the terminal
*/

FILE *
pcterm_init(struct Device_Conf *dev){

    finit( & term.file );
    term.file.fs = &term_fs;
    term.file.d = (void*)&term;
    term.file.codepage = CODEPAGE_PC437;
    term.scr.x = term.scr.y = 0;

    if( dev->addr )
        term.scr.d = (u_short*)(dev->addr - k_paddr);
    else
        term.scr.d = (u_short*)(0xB8000 - k_paddr);

    if( dev->flags )
        term.scr.attr = dev->flags;
    else
        term.scr.attr = 7;

    if( dev->port )
        term.kbd.port = dev->port;
    else
        term.kbd.port = KBD_PORT;

    term.kbd.head = term.kbd.tail = term.kbd.len = 0;
    term.kbd.state = 0;

    if( install_interrupt(dev->irq, IPL_TTY, kbdirq, dev->name) ){
        PANIC("could not install kbd irq");
    }

#ifndef PLATFORM_EMUL
    /* config h/w */
    clear_screen( &term.file );
    move_cursor( &term.file, 0, 0 );
#endif
    pcterm_port = &term.file;

    kprintf("%s scrn at mem 0x%x (0x%x) kbd at io 0x%x irq %d\n",
            dev->name, term.scr.d, (int)term.scr.d + (int)k_paddr, term.kbd.port, dev->irq);
    return pcterm_port;

}


/* move the cursor */
void
move_cursor(FILE *f, int x, int y){
    int pos;
    struct Term *t;
    int plx;

    t = (struct Term*)f->d;

    pos = y * CRT_COLS + x;

    plx = splterm();
    t->scr.x = x;
    t->scr.y = y;

    outb(CRTC_COMMAND, CRTC_CURLO);
    outb(CRTC_DATA, (u_char)pos);

    outb(CRTC_COMMAND, CRTC_CURHI);
    pos >>= 8;
    outb(CRTC_DATA, (u_char)pos);

    splx(plx);
}

/* clear the screen */
void
clear_screen(FILE *f){
    struct Term *t;
    int plx;
    int i;

    t = (struct Term*)f->d;

    plx = splterm();
    for(i=0; i< CRT_ROWS * CRT_COLS; i++){
        t->scr.d[ i ] = ' ' | (t->scr.attr<<8);
    }
    splx(plx);
}

static int
term_noop(FILE *f){
    return 1;
}

/* return status */
static int
term_status(FILE *f){
    struct Term *t;

    t = (struct Term*)f->d;

    /* always ready for output */

    if( t->kbd.len )
        return FST_I | FST_O;
    return FST_O;
}

/* output a character */
static int
term_putchar(FILE*f, char c){
    struct Term *t;
    int plx;
    int i;

    t = (struct Term*)f->d;

    c &= 0xFF;
    plx = splterm();

    /* handle some simple esc.seqs */
    if( t->scr.mode == GOTESC )
        if( c == '[' ){
            t->scr.mode = GOTBRACK;
            t->scr.mn = 0;
            bzero( t->scr.arg, MAXARG );
            splx(plx);
            return 1;
        }else{
            t->scr.mode = 0;
            c = 0x80 | c;
        }

    switch(c | t->scr.mode){
    case '\e':
        t->scr.mode = GOTESC;
        goto done;
    case '\n':
        t->scr.y ++;
        break;
    case '\r':
        t->scr.x = 0;
        break;
    case '\t':
        t->scr.x += 8 - (t->scr.x % 8);
        break;
    case '\b':
        if( t->scr.x ) t->scr.x--;
        break;
    case '\a':
        /* beep */
        break;

    case ';' | GOTBRACK:
        t->scr.mn ++;
        goto done;

    case '0' | GOTBRACK: case '1' | GOTBRACK: case '2' | GOTBRACK: case '3' | GOTBRACK:
    case '4' | GOTBRACK: case '5' | GOTBRACK: case '6' | GOTBRACK: case '7' | GOTBRACK:
    case '8' | GOTBRACK: case '9' | GOTBRACK:
        t->scr.arg[ t->scr.mn ] *= 10;
        t->scr.arg[ t->scr.mn ] += c - '0';
        goto done;

    case 'J' | GOTBRACK:
        clear_screen(f);
        break;

    case 'H' | GOTBRACK:
        move_cursor(f, t->scr.arg[0], t->scr.arg[1]);
        break;

    case 'm' | GOTBRACK:
        for(i=0; i<t->scr.mn+1; i++){
            ansiof(t, t->scr.arg[i]);
        }
        break;

    default:
        t->scr.d[ t->scr.x++ + t->scr.y * CRT_COLS ] = c | (t->scr.attr<<8);
        break;
    }

    t->scr.mode = 0;
    if( t->scr.x > CRT_COLS ){
        t->scr.x = 0;
        t->scr.y ++;
    }

    if( t->scr.y >= CRT_ROWS ){
        bcopy( t->scr.d + CRT_COLS, t->scr.d, CRT_COLS * (CRT_ROWS - 1) * sizeof(short) );

        for(i=0; i<CRT_COLS; i++){
            t->scr.d[ i + CRT_COLS * (CRT_ROWS - 1) ] = ' ' | (t->scr.attr<<8);
        }
        t->scr.y --;
    }

    move_cursor(f, t->scr.x, t->scr.y);

done:
    splx(plx);
    return 1;
}


/*****************************************************************
  	keyboard
*****************************************************************/

/* get a character from keyboard */
int
term_getchar(FILE *f){
    char ch;
    int i, plx;
    struct Term *t;

    t = (struct Term*)f->d;
    while( 1 ){
        if( t->kbd.len ){
            /* make sure some one else didn't already take the char */
            plx = splterm();
            if( t->kbd.len )
                break;
            else
                splx(plx);
        }
        if( f->flags & F_NONBLOCK ){
            /* halt ??? */
        }else{
#ifdef USE_PROC
            tsleep( &t->kbd, currproc->prio, "kbd", 0);
#endif
        }
    }

    ch = t->kbd.queue[ t->kbd.tail++ ];
    t->kbd.tail %= PCTERM_QUEUE_SIZE;
    t->kbd.len --;

    splx(plx);
    return (int)ch & 0xFF;
}

/* flush any typeahead */
int
term_flush(FILE *f){
    int plx;
    struct Term *t;

    t = (struct Term*)f->d;
    plx = splterm();
    t->kbd.head = t->kbd.tail = t->kbd.len = 0;

    t->scr.mode = 0;
    splx(plx);

    return 1;
}


/*****************************************************************
	keyboard bottom-half
*****************************************************************/

/* NB: scancode table stolen from NetBSD i386/isa/pccons.c */

#define SCROLL          0x0001  /* stop output */
#define NUM             0x0002  /* numeric shift  cursors vs. numeric */
#define CAPS            0x0004  /* caps shift -- swaps case of letter */
#define SHIFT           0x0008  /* keyboard shift */
#define CTL             0x0010  /* control shift  -- allows ctl function */
#define ASCII           0x0020  /* ascii code for this key */
#define ALT             0x0080  /* alternate shift -- alternate chars */
#define FUNC            0x0100  /* function key */
#define KP              0x0200  /* Keypad keys */
#define NONE            0x0400  /* no function */

#define CODE_SIZE       4
typedef struct {
    u_short type;
    char unshift[CODE_SIZE];
    char shift[CODE_SIZE];
    char ctl[CODE_SIZE];
} Scan_def;

const Scan_def scan_codes[] = {
    { NONE, "",             "",             "" },           /* 0 unused */
    { ASCII,"\033",         "\033",         "\033" },       /* 1 ESCape */
    { ASCII,"1",            "!",            "!" },          /* 2 1 */
    { ASCII,"2",            "@",            "\000" },       /* 3 2 */
    { ASCII,"3",            "#",            "#" },          /* 4 3 */
    { ASCII,"4",            "$",            "$" },          /* 5 4 */
    { ASCII,"5",            "%",            "%" },          /* 6 5 */
    { ASCII,"6",            "^",            "\036" },       /* 7 6 */
    { ASCII,"7",            "&",            "&" },          /* 8 7 */
    { ASCII,"8",            "*",            "\010" },       /* 9 8 */
    { ASCII,"9",            "(",            "(" },          /* 10 9 */
    { ASCII,"0",            ")",            ")" },          /* 11 0 */
    { ASCII,"-",            "_",            "\037" },       /* 12 - */
    { ASCII,"=",            "+",            "+" },          /* 13 = */
    { ASCII,"\010",         "\010",         "\177" },       /* 14 backspace */
    { ASCII,"\t",           "\177\t",       "\t" },         /* 15 tab */
    { ASCII,"q",            "Q",            "\021" },       /* 16 q */
    { ASCII,"w",            "W",            "\027" },       /* 17 w */
    { ASCII,"e",            "E",            "\005" },       /* 18 e */
    { ASCII,"r",            "R",            "\022" },       /* 19 r */
    { ASCII,"t",            "T",            "\024" },       /* 20 t */
    { ASCII,"y",            "Y",            "\031" },       /* 21 y */
    { ASCII,"u",            "U",            "\025" },       /* 22 u */
    { ASCII,"i",            "I",            "\011" },       /* 23 i */
    { ASCII,"o",            "O",            "\017" },       /* 24 o */
    { ASCII,"p",            "P",            "\020" },       /* 25 p */
    { ASCII,"[",            "{",            "\033" },       /* 26 [ */
    { ASCII,"]",            "}",            "\035" },       /* 27 ] */
    { ASCII,"\r",           "\r",           "\n" },         /* 28 return */
    { CTL,  "",             "",             "" },           /* 29 control */
    { ASCII,"a",            "A",            "\001" },       /* 30 a */
    { ASCII,"s",            "S",            "\023" },       /* 31 s */
    { ASCII,"d",            "D",            "\004" },       /* 32 d */
    { ASCII,"f",            "F",            "\006" },       /* 33 f */
    { ASCII,"g",            "G",            "\007" },       /* 34 g */
    { ASCII,"h",            "H",            "\010" },       /* 35 h */
    { ASCII,"j",            "J",            "\n" },         /* 36 j */
    { ASCII,"k",            "K",            "\013" },       /* 37 k */
    { ASCII,"l",            "L",            "\014" },       /* 38 l */
    { ASCII,";",            ":",            ";" },          /* 39 ; */
    { ASCII,"'",            "\"",           "'" },          /* 40 ' */
    { ASCII,"`",            "~",            "`" },          /* 41 ` */
    { SHIFT,"",             "",             "" },           /* 42 shift */
    { ASCII,"\\",           "|",            "\034" },       /* 43 \ */
    { ASCII,"z",            "Z",            "\032" },       /* 44 z */
    { ASCII,"x",            "X",            "\030" },       /* 45 x */
    { ASCII,"c",            "C",            "\003" },       /* 46 c */
    { ASCII,"v",            "V",            "\026" },       /* 47 v */
    { ASCII,"b",            "B",            "\002" },       /* 48 b */
    { ASCII,"n",            "N",            "\016" },       /* 49 n */
    { ASCII,"m",            "M",            "\r" },         /* 50 m */
    { ASCII,",",            "<",            "<" },          /* 51 , */
    { ASCII,".",            ">",            ">" },          /* 52 . */
    { ASCII,"/",            "?",            "\037" },       /* 53 / */
    { SHIFT,"",             "",             "" },           /* 54 shift */
    { KP,   "*",            "*",            "*" },          /* 55 kp * */
    { ALT,  "",             "",             "" },           /* 56 alt */
    { ASCII," ",            " ",            "\000" },       /* 57 space */
    { CAPS, "",             "",             "" },           /* 58 caps */
    { FUNC, "\033[M",       "\033[Y",       "\033[k" },     /* 59 f1 */
    { FUNC, "\033[N",       "\033[Z",       "\033[l" },     /* 60 f2 */
    { FUNC, "\033[O",       "\033[a",       "\033[m" },     /* 61 f3 */
    { FUNC, "\033[P",       "\033[b",       "\033[n" },     /* 62 f4 */
    { FUNC, "\033[Q",       "\033[c",       "\033[o" },     /* 63 f5 */
    { FUNC, "\033[R",       "\033[d",       "\033[p" },     /* 64 f6 */
    { FUNC, "\033[S",       "\033[e",       "\033[q" },     /* 65 f7 */
    { FUNC, "\033[T",       "\033[f",       "\033[r" },     /* 66 f8 */
    { FUNC, "\033[U",       "\033[g",       "\033[s" },     /* 67 f9 */
    { FUNC, "\033[V",       "\033[h",       "\033[t" },     /* 68 f10 */
    { NUM,  "",             "",             "" },           /* 69 num lock */
    { SCROLL,"",            "",             "" },           /* 70 scroll lock */
    { KP,   "7",            "\033[H",       "7" },          /* 71 kp 7 */
    { KP,   "8",            "\033[A",       "8" },          /* 72 kp 8 */
    { KP,   "9",            "\033[I",       "9" },          /* 73 kp 9 */
    { KP,   "-",            "-",            "-" },          /* 74 kp - */
    { KP,   "4",            "\033[D",       "4" },          /* 75 kp 4 */
    { KP,   "5",            "\033[E",       "5" },          /* 76 kp 5 */
    { KP,   "6",            "\033[C",       "6" },          /* 77 kp 6 */
    { KP,   "+",            "+",            "+" },          /* 78 kp + */
    { KP,   "1",            "\033[F",       "1" },          /* 79 kp 1 */
    { KP,   "2",            "\033[B",       "2" },          /* 80 kp 2 */
    { KP,   "3",            "\033[G",       "3" },          /* 81 kp 3 */
    { KP,   "0",            "\033[L",       "0" },          /* 82 kp 0 */
    { KP,   ".",            "\177",         "." },          /* 83 kp . */
    { NONE, "",             "",             "" },           /* 84 0 */
    { NONE, "100",          "",             "" },           /* 85 0 */
    { NONE, "101",          "",             "" },           /* 86 0 */
    { FUNC, "\033[W",       "\033[i",       "\033[u" },     /* 87 f11 */
    { FUNC, "\033[X",       "\033[j",       "\033[v" },     /* 88 f12 */
    { NONE, "102",          "",             "" },           /* 89 0 */
    { NONE, "103",          "",             "" },           /* 90 0 */
    { NONE, "",             "",             "" },           /* 91 0 */
    { NONE, "",             "",             "" },           /* 92 0 */
    { NONE, "",             "",             "" },           /* 93 0 */
    { NONE, "",             "",             "" },           /* 94 0 */
    { NONE, "",             "",             "" },           /* 95 0 */
    { NONE, "",             "",             "" },           /* 96 0 */
    { NONE, "",             "",             "" },           /* 97 0 */
    { NONE, "",             "",             "" },           /* 98 0 */
    { NONE, "",             "",             "" },           /* 99 0 */
    { NONE, "",             "",             "" },           /* 100 */
    { NONE, "",             "",             "" },           /* 101 */
    { NONE, "",             "",             "" },           /* 102 */
    { NONE, "",             "",             "" },           /* 103 */
    { NONE, "",             "",             "" },           /* 104 */
    { NONE, "",             "",             "" },           /* 105 */
    { NONE, "",             "",             "" },           /* 106 */
    { NONE, "",             "",             "" },           /* 107 */
    { NONE, "",             "",             "" },           /* 108 */
    { NONE, "",             "",             "" },           /* 109 */
    { NONE, "",             "",             "" },           /* 110 */
    { NONE, "",             "",             "" },           /* 111 */
    { NONE, "",             "",             "" },           /* 112 */
    { NONE, "",             "",             "" },           /* 113 */
    { NONE, "",             "",             "" },           /* 114 */
    { NONE, "",             "",             "" },           /* 115 */
    { NONE, "",             "",             "" },           /* 116 */
    { NONE, "",             "",             "" },           /* 117 */
    { NONE, "",             "",             "" },           /* 118 */
    { NONE, "",             "",             "" },           /* 119 */
    { NONE, "",             "",             "" },           /* 120 */
    { NONE, "",             "",             "" },           /* 121 */
    { NONE, "",             "",             "" },           /* 122 */
    { NONE, "",             "",             "" },           /* 123 */
    { NONE, "",             "",             "" },           /* 124 */
    { NONE, "",             "",             "" },           /* 125 */
    { NONE, "",             "",             "" },           /* 126 */
    { NONE, "",             "",             "" },           /* 127 */
};

void
kbdirq(struct intrframe *fr){
    int c, i;
    const char *cs=0;
    struct Kbd *k = &term.kbd;	/* we only support one, for now */

    c = inb( k->port );

    /* make or break */
    if( c & 0x80 ){
        /* break */
        c &= 0x7f;

        switch( scan_codes[c].type ){
        case SCROLL:
            k->state &= ~SCROLL;
            break;
        case SHIFT:
            k->state &= ~SHIFT;
            break;
        case ALT:
            k->state &= ~ALT;
            break;
        case CTL:
            k->state &= ~CTL;
            break;
        }
    }else{
        /* make */
        switch( scan_codes[c].type ){

        case SHIFT:
            k->state |= SHIFT;
            break;
        case ALT:
            k->state |= ALT;
            break;
        case CTL:
            k->state |= CTL;
            break;
        case NUM:
            k->state ^= NUM;
            break;
        case CAPS:
            k->state ^= CAPS;
            break;
        case NONE:
            break;
        case ASCII:
        case FUNC:
            if( k->state & CTL )
                cs = scan_codes[c].ctl;
            else if( k->state & (SHIFT | CAPS) )
                cs = scan_codes[c].shift;
            else
                cs = scan_codes[c].unshift;
            break;

        case KP:
            if( c == 83 && k->state & CTL && k->state & ALT ){
                /* ctl-alt-del detected */
#ifdef USE_GDB
                if( bootflags & BOOT_USEGDB )
                    breakpoint();
                else
#endif
                {
                    E9PRINTF(("\n<C-A-Del>\nrebooting\n"));
                    kprintf("\nrebooting...");
                    reboot();
                }

            }
            if( k->state & CTL )
                cs = scan_codes[c].ctl;
            else if( k->state & (SHIFT | NUM) )
                cs = scan_codes[c].shift;
            else
                cs = scan_codes[c].unshift;
            break;


        }

        /* special control char ? */
        for(i=0; i<sizeof(term.file.cchars); i++){
            if(cs && term.file.cchars[i] && *cs == term.file.cchars[i]){
                sigunblock( term.file.ccpid );
                ksendmsg( term.file.ccpid, MSG_CCHAR_0 + i );
                return;
            }
        }

        /* enqueue chars */
        while( cs && *cs ){
            if( k->len < PCTERM_QUEUE_SIZE ){
                k->queue[ k->head++ ] = (k->state & ALT) ? (0x80 | *cs) : *cs;
                k->head %= PCTERM_QUEUE_SIZE;
                k->len ++;
            }
            /* else just drop it */

            cs++;
        }
        wakeup(k);
    }
}
