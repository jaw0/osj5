/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: 
 
  $Id$

*/


#include <sys/types.h>
#include <sys/param.h>
#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <dev.h>
#include <bootflags.h>

#define QUEUE_SIZE	64
#define INTERVAL	PROC_TIME
/* 250000 */

int emulcon_putchar(FILE*, char);
int emulcon_getchar(FILE*);
int emulcon_noop(FILE*);
int emulcon_flush(FILE*);
int emulcon_status(FILE*);
void emulcon_irq(struct intrframe *);

const struct io_fs emulcon_fs = {
    emulcon_putchar,
    emulcon_getchar,
    emulcon_noop,	/* no close */
    emulcon_flush,
    emulcon_status,
    0,0,0,0,0,0
};

struct Screen {
    int x;
};

struct Kbd {
    char queue[ QUEUE_SIZE ];
    short head, tail, len;
    u_char state;
};

struct Term {
    FILE file;
    int fd;
    struct Screen scr;
    struct Kbd kbd;
} emulterm[1];


FILE *emulcon_port, *console_port, *kconsole_port;
void kbdsighandler();
void sighandler();

extern long k_paddr;
extern u_long bootflags;


asm("kbdsighandler:\n"
    "pushl $0\n"
    "call sigsetmask\n"
    "pushl $34\n");
PUSHALOT();
asm("call intr_handler");
POPALOT();
asm("addl $8, %esp\n");
asm("cmpb $0, yieldflag");
asm("je 1f");
asm("cmpb $0, cpl");
asm("jne 1f");
asm("movb $0, yieldflag");
asm("call _yield");
asm("1:");
asm("ret");


FILE *
emulcon_init(struct Device_Conf * dev){
    int i = dev->unit;

    finit( & emulterm[i].file );
    emulterm[i].file.fs = &emulcon_fs;
    emulterm[i].file.d = (void*)&emulterm;
    emulterm[i].kbd.head = emulterm[i].kbd.tail = emulterm[i].kbd.len = 0;
    emulterm[i].kbd.state = 0;

    if( !i ){
        emulcon_port = &emulterm[i].file;

        system("stty raw -echo");
        signal(23, kbdsighandler);
        emulterm[i].fd = 0;
    }
#define F_SETFL         4               /* set file status flags */
#define F_SETOWN        6               /* set SIGIO/SIGURG proc/pgrp */
#define O_ASYNC         0x0040          /* signal pgrp when data ready */
#define O_NONBLOCK      0x0004          /* no delay */

    fcntl(emulterm[i].fd, F_SETOWN, getpid());
    fcntl(emulterm[i].fd, F_SETFL, O_ASYNC|O_NONBLOCK);

    install_interrupt(2, IPL_TTY, emulcon_irq, "emul/term");

    kprintf("%s on UNIX /dev/tty irq %d\n", dev->name, 2);

    return & emulterm[i].file;
}

int
emulcon_noop(FILE *f){
    return 1;
}

int
emulcon_status(FILE *f){
    struct Term *t;

    t = (struct Term*)f->d;

    /* always ready for output */

    if( t->kbd.len )
        return FST_I | FST_O;
    return FST_O;
}


int
emulcon_putchar(FILE*f, char c){
    struct Term *t;
    int plx;
    int i;

    t = (struct Term*)f->d;

    c &= 0xFF;
    plx = splterm();
    write(t->fd, &c, 1);
    splx(plx);
    return 1;
}


int
emulcon_getchar(FILE *f){
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
            tsleep(&t->kbd, currproc->prio, "kbd", 0);
#endif
        }
    }

    ch = t->kbd.queue[ t->kbd.tail++ ];
    t->kbd.tail %= QUEUE_SIZE;
    t->kbd.len --;

    splx(plx);
    return (int)ch & 0xFF;
}

int
emulcon_flush(FILE *f){
    int plx;
    struct Term *t;

    t = (struct Term*)f->d;
    plx = splterm();
    t->kbd.head = t->kbd.tail = t->kbd.len = 0;
    splx(plx);

    return 1;
}


void
emulcon_irq(struct intrframe *fr){
    int l;
    char buf[16];

    const char *cs=0;
    struct Kbd *k = &emulterm[0].kbd;	/* we only support one, for now */
    struct Term *t = &emulterm[0];

    l = read(t->fd, buf, 16);
    cs = buf;

    /* enqueue chars */
    while( l-- > 0 ){
        if( *cs == 03 ){
            system("stty -raw echo");
            _exit(0);
        }
        if( k->len < QUEUE_SIZE ){
            k->queue[ k->head++ ] = *cs;
            k->head %= QUEUE_SIZE;
            k->len ++;
        }
        cs++;
    }
    wakeup(k);
    /* else just drop it */

}

