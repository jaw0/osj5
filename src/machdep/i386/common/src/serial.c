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
#include <error.h>
#include <pio.h>
#include <timer.h>		/* for clock speed */
#include <serial.h>
#include <msgs.h>
#include <dev.h>
#include <bootflags.h>

/* TODO: check CTS */

#ifndef N_SERIAL
#  define N_SERIAL 0
#endif

#ifndef SERIAL_QUEUE_SIZE
#  define SERIAL_QUEUE_SIZE     64	/* input queue size */
#endif
#ifndef SERIAL_QUEUE_HIWATER
#  define SERIAL_QUEUE_HIWATER	60	/* when to tell the other side to slow down (drop RTS) */
#endif
#ifndef SERIAL_QUEUE_LOWATER
#  define SERIAL_QUEUE_LOWATER	16	/* when to tell the other side to resume (assert RTS) */
#endif


#if 0
#define RATE_CONSTANT	(MHZ * (1000000/(4 * 16)))
#else
#define RATE_CONSTANT	115200
#endif

int serial_putchar(FILE*, char);
int serial_getchar(FILE*);
int serial_noop(FILE*);
int serial_status(FILE*);
void serial_setbaud(int, int);
void serialirq(struct intrframe *);

const struct io_fs serial_port_fs = {
    serial_putchar,
    serial_getchar,
    serial_noop,	/* no close */
    serial_noop,	/* no flush */
    serial_status,
    0,
    0,
    0,
    0,
    0,
    0
};

struct Com {
    FILE file;
    char queue[ SERIAL_QUEUE_SIZE ];
    u_char head, tail, len;
    u_char status;
#define COMSTAT_TXPENDING	1	/* a xmit is in progress */
#define COMSTAT_THROTTLED	2	/* we have dropped RTS */

    int portno, addr;
} com[ N_SERIAL ];

FILE *serial0_port, *serial1_port;


/* initialize the serial ports */
int
serial_init(struct Device_Conf *dev){
    int i = dev->unit;
    int port = dev->port;
    int b;

    finit( & com[i].file );
    com[i].file.fs = &serial_port_fs;
    com[i].head = com[i].tail = com[i].len = 0;
    com[i].status = 0;
    com[i].portno = i;
    com[i].addr = port;

    com[i].file.d  = (void*)&com[i];

    if( install_interrupt(dev->irq, IPL_TTY, serialirq, dev->name) ){
        PANIC("could not install serial irq");
    }

#ifndef PLATFORM_EMUL

    /* make sure - DL not selected */
    outb( port + LCR, (LCR_8BITS | LCR_NO_PARITY | LCR_1STOPBIT));
    /* drop rts */
    outb( port + MCR, (MCR_AUX2 | MCR_DTR) );
    /* stop ints */
    outb( port + IER, 0 );
    /* clear out port state */
    while( !(inb(port + IIR) & 1) ){
        inb( port + LSR );
        inb( port + MSR );
        inb( port );
    }

    /* config h/w : 9600, 8n1 */
    outb( port + LCR, (LCR_8BITS | LCR_NO_PARITY | LCR_1STOPBIT));
    outb( port + MCR, (MCR_RTS | MCR_DTR | MCR_AUX2));

#endif

    if( dev->baud )
        serial_setbaud(i, b=dev->baud);
    else
        serial_setbaud(i, b=9600);

#ifndef PLATFORM_EMUL
    /* enable ints */
    outb( port + IER, (IER_RCVFULL | IER_TXBMT | IER_LINE | IER_MODEM));
#endif
    if( !i ){
        serial0_port = &com[0].file;
#ifdef USE_GDB
        if( bootflags & BOOT_USEGDB ){
            /* stop ints - use polled i/o on this port */
            outb( port + IER, 0 );
            screen_puts("gdb: break\n");
            breakpoint();
        }
#endif
    }
    if( i==1 )
        serial1_port = &com[1].file;

    kprintf("%s at io 0x%x irq %d %d baud\n", dev->name, port, dev->irq, b);

    return (int) &com[i].file;
}

/* set the baud rate on serial port */
void
serial_setbaud(int port, int baud){
    int d, i;
    int plx;
    int addr;

    if( ! baud )
        return;

    d = RATE_CONSTANT / baud;
    addr = com[port].addr;

    plx = spltty();

#ifndef PLATFORM_EMUL
    i = inb( addr + LCR );
    outb( addr + LCR, (i | 0x80));
    outb( addr + DLL, (d & 0x00FF));
    outb( addr + DLH, ((d >> 8) & 0x00FF));
    outb( addr + LCR, i);
#endif
    splx(plx);
}

int
serial_noop(FILE*f){
    return 1;
}

/* return the status */
int
serial_status(FILE*f){
    int s = 0;
    struct Com *p;

    p = (struct Com*)f->d;
    if( p->len ) s |= FST_I;
    if( !(p->status & COMSTAT_TXPENDING) )
        s |= FST_O;
    return s;
}

/* output a char */
int
serial_putchar(FILE *f, char ch){
    /* outputs a char over the serial line */
    int i;
    struct Com *p;
    int plx;

    p = (struct Com*)f->d;

    if( f->flags & F_NONBLOCK ){
        /* if marked as non-blocking, busy-wait until transmitter is empty */
        plx = spltty();
        do{
            /* we check the hardware directly, as this will be used
               before ints are setup, and from bottom-half routines */
            i = inb( p->addr + LSR );
        }while( !(i & LSR_TXBMT) );
    }else{
        while(1){
            if( !(p->status & COMSTAT_TXPENDING) ){
                /* make sure some one else didn't beat us to it */
                plx = spltty();
                if( !(p->status & COMSTAT_TXPENDING) )
                    break;
                else
                    splx(plx);
            }
#ifdef USE_PROC
            if( tsleep(&p->status, currproc->prio, "com/o", 1000000)){	/* 1 sec */
                /* timed out */
                /* verify with the hardware */
                i = inb( p->addr + LSR );
                if( i & LSR_TXBMT )
                    p->status &= ~ COMSTAT_TXPENDING;
            }
#endif
        }
    }

    p->status |= COMSTAT_TXPENDING;
    outb( p->addr + TBR, ch );
    splx(plx);

    return 1;
}

/* get a char */
int
serial_getchar(FILE *f){
    char ch;
    int i, plx;
    struct Com *p;

    p = (struct Com*)f->d;
    while( 1 ){
        if( p->len ){
            /* make sure some one else didn't already take the char */
            plx = spltty();
            if( p->len )
                break;
            else
                splx(plx);
        }
        if( f->flags & F_NONBLOCK ){
            plx = spltty();
            /* assert RTS */
            if(  p->status & COMSTAT_THROTTLED ){
                i = inb( p->addr + MCR );
                i |= MCR_RTS;
                p->status &= ~COMSTAT_THROTTLED;
                outb( p->addr + MCR, i);
            }
            /* wait until something is available */
            do {
                i = inb( p->addr + LSR );
            }while( !(i & LSR_RCVFULL) );
            ch = inb( p->addr );
            splx(plx);
            return ch;

        }else{
#ifdef USE_PROC
            /* QQQ should we set a timeout? */
            tsleep( &p->len, currproc->prio, "com/i", 0);
#endif
        }
    }

    ch = p->queue[ p->tail++ ];
    p->tail %= SERIAL_QUEUE_SIZE;
    p->len --;

    /* flow control */
    /* if we are throttled and now have room, re-assert RTS */
    if( p->status & COMSTAT_THROTTLED && p->len < SERIAL_QUEUE_LOWATER ){
        i = inb( p->addr + MCR );
        i |= MCR_RTS;
        outb( p->addr + MCR, i);
        p->status &= ~COMSTAT_THROTTLED;
    }

    splx(plx);
    return ch;
}

/* #ifdef USE_GDB */
#if 1
/*****************************************************************
  	gdb hooks
	NB: since ints may be disabled, these poll the hw directly
****************************************************************/
void
putDebugChar(int ch){
    /* outputs a char over the serial line */
    int i;
    struct Com *p;
    int plx;

    p = &com[0];
    plx = spltty();
    do{
        i = inb( p->addr + LSR );
    }while( !(i & LSR_TXBMT) );

    p->status |= COMSTAT_TXPENDING;
    outb( p->addr + TBR, ch );
    splx(plx);
}

int
getDebugChar(){
    char ch;
    int i, plx;
    struct Com *p;

    p = &com[0];
    while( 1 ){
        /* ints may be disabled, so also check the hardware */
        i = inb( p->addr + LSR );
        if( p->len || (i & LSR_RCVFULL) ){
            /* make sure some one else didn't already take the char */
            plx = spltty();
            i = inb( p->addr + LSR );
            if( p->len || (i & LSR_RCVFULL) )
                break;
            else
                splx(plx);
        }
    }

    if( p->len ){
        ch = p->queue[ p->tail++ ];
        p->tail %= SERIAL_QUEUE_SIZE;
        p->len --;
    }else{
        ch = inb(p->addr + RBR);
    }
    /* flow control */
    /* if we are throttled and now have room, re-assert RTS */
    if( p->status & COMSTAT_THROTTLED && p->len < SERIAL_QUEUE_LOWATER ){
        i = inb( p->addr + MCR );
        i |= MCR_RTS;
        outb( p->addr + MCR, i);
        p->status &= ~COMSTAT_THROTTLED;
    }

    splx(plx);
    return ch;
}

#endif

/*****************************************************************
  	top-half/bottom-half dividing line
****************************************************************/

/* handler for serial interrupt */
void
serialirq(struct intrframe *fr){
    int port;
    char c;
    int n, i, nm=0;

    /* which com port ? */
    port = (fr->number == 36) ? 0 : 1;

/*	kprintf("serial irq %d (cpl=%d) (len=%d) (st=%d) ", port,
        (int)cpl, com[port].len, com[port].status);
*/
    while(1){
        n = inb( com[port].addr + IIR );

        switch( n ){
        case IIR_RCVFULL:

            /* got a char, read it */
            c = inb(com[port].addr + RBR);
            //kprintf("in(%c) ", c);

#ifdef USE_GDB
            if( c == 3 && bootflags & BOOT_USEGDB ){
                breakpoint();
                continue;
            }
#endif
            /* special control char ? */
            for(i=0; i<sizeof(com[port].file.cchars); i++){
                if(com[port].file.cchars[i] && c == com[port].file.cchars[i]){
                    sigunblock( com[port].file.ccpid );
                    ksendmsg( com[port].file.ccpid, MSG_CCHAR_0 + i );
                    return;
                }
            }

            if( com[port].len < SERIAL_QUEUE_SIZE ){
                /* queue it up */
                com[port].queue[ com[port].head++ ] = c;
                com[port].head %= SERIAL_QUEUE_SIZE;
                com[port].len ++;
                /* flow control */
                if( com[port].len > SERIAL_QUEUE_HIWATER ){
                    /* almost full - drop RTS */
                    i = inb( com[port].addr + MCR );
                    i &= ~MCR_RTS;
                    outb( com[port].addr + MCR, i);
                    com[port].status |= COMSTAT_THROTTLED;
                }
                wakeup( &com[port].len );
            }
            continue;

        case IIR_TXBMT:
            //kprintf("out ");
            /* transmitter empty */
            com[port].status &= ~ COMSTAT_TXPENDING;
            wakeup( &com[port].status );
            continue;

        case IIR_LINE:
            c = inb( com[port].addr + LSR );
            //kprintf("line(%x) ", 0xFF & (int)c);
            continue;

        case IIR_MODEM:
            c = inb( com[port].addr + MSR );
            //kprintf("modem(%x) ", 0xFF & (int)c);
            /* work around buggy serial port */
            if( nm ++ )
                break;
            continue;

        default:
            //kprintf("none ");
            break;
        }
        //kprintf("\n");
        return;
    }
}

