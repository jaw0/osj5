/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 23:25 (EDT)
  Function: 

*/

#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <msgs.h>
#include <misc.h>
#include <dev.h>
#include <bootflags.h>
#include <clock.h>
#include <queue.h>
#include <nvic.h>
#include <gpio.h>
#include <stm32.h>
#include <serial_impl.h>

#define SR_TXE	0x80
#define SR_RXNE 0x20

#define CR1_TXEIE (1 << 7)
#define CR1_RXNEIE  (1 << 5)

#define CFFLAGS_ALTPINS	3	// 2 bits of flags - alt set of pins

#ifndef SERIAL_QUEUE_SIZE
#  define SERIAL_QUEUE_SIZE     16	/* input queue size */
#endif

int serial_putchar(FILE*, char);
int serial_getchar(FILE*);
int serial_noop(FILE*);
int serial_status(FILE*);
void serial_setbaud(int, int);
int serial_read(FILE*, char *, int);
int serial_write(FILE*, const char *, int);

const struct io_fs serial_port_fs = {
    serial_putchar,
    serial_getchar,
    0,
    0,
    serial_status,
    serial_read,
    serial_write,
    0,
    0,
    0,
    0
};

struct Com {
    FILE file;
    struct queue rxq, txq;
    char _rbuf[SERIAL_QUEUE_SIZE], _tbuf[SERIAL_QUEUE_SIZE];

    u_char status;
    int    baudclock;
#define COMSTAT_THROTTLED	2	/* we have dropped RTS */

    int portno;
    USART_TypeDef * addr;
} com[ N_SERIAL ];


FILE *serial0_port = 0;

struct serialDevConf {
    USART_TypeDef * addr;
    int irq;
} const dev_conf[] = {
    { USART1, USART1_IRQn },
    { USART2, USART2_IRQn },
#if defined(USART3)
    { USART3, USART3_IRQn },
#else
#  error "no usart3"
#endif
#if defined(UART4)
    { UART4,  UART4_IRQn  },
#endif
#if defined(UART5)
    { UART5,  UART5_IRQn  },
#endif
#if defined(USART6)
    { USART6, USART6_IRQn },
#endif
#if defined(UART7)
    { UART7,  UART7_IRQn  },
#endif
#if defined(UART8)
    { UART8,  UART8_IRQn  },
#endif
};


/* initialize the serial ports */
int
serial_init(struct Device_Conf *dev){
    int i    = dev->unit;
    USART_TypeDef *addr;
    int irq;
    int b;

    int altpins = dev->flags & CFFLAGS_ALTPINS;

    struct Com *v = com + i;
    bzero( v, sizeof(struct Com));

    queue_init_buf( &v->rxq, v->_rbuf, SERIAL_QUEUE_SIZE );
    queue_init_buf( &v->txq, v->_tbuf, SERIAL_QUEUE_SIZE );

    finit( & com[i].file );
    com[i].file.fs = &serial_port_fs;
    com[i].file.codepage = CODEPAGE_UTF8;
    com[i].status  = 0;
    com[i].portno  = i;
    com[i].file.d  = (void*)&com[i];

    // enable gpio clock, usart clock, configure pins
    serial_pins_init( i, altpins );
    com[i].baudclock = serial_baudclock(i);

    if( i < ELEMENTSIN(dev_conf) ){
        addr = dev_conf[i].addr;
        irq  = dev_conf[i].irq;
    }else{
        PANIC("invalid serial");
    }

    com[i].addr   = addr;

    if( dev->baud )
        serial_setbaud(i, b=dev->baud);
    else
        serial_setbaud(i, b=9600);

    addr->CR1 = SERIAL_CR1_EN;

    // enable ints
    nvic_enable( irq, IPL_TTY );

    if( !serial0_port ){
        serial0_port = &com[i].file;
    }

    bootmsg("%s at io 0x%x irq %d %d baud\n", dev->name, addr, irq, b);

    return (int) &com[i].file;
}

/* set the baud rate on serial port */
void
serial_setbaud(int port, int baud){
    int d, i;
    int plx;

    com[port].addr->BRR = (com[port].baudclock + baud/2) / baud;
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

    return 1;
}


/* output a char */
int
serial_putchar(FILE *f, char ch){
    /* outputs a char over the serial line */
    int i;
    struct Com *p;
    int plx;

    p = (struct Com*)f->d;
    USART_TypeDef *addr = p->addr;

#ifdef USE_PROC
    if( f->flags & F_NONBLOCK ){
        while(1){
            plx = spltty();
            if( SERIAL_STATUS(addr) & SR_TXE ) break;
        }
    }else{
        plx = spltty();
        while(1){
            spltty();
            if( ! qfull(&p->txq) ) break;

            asleep( &p->txq, "com/o" );
            if( ! qfull(&p->txq) ) break;
            addr->CR1 |= CR1_TXEIE;	/* enable TXE irq */
            await( -1, 100000 );
            if( ! qfull(&p->txq) ) break;
        }
        aunsleep();
        spltty();
        qpush( &p->txq, ch );
        addr->CR1 |= CR1_TXEIE;	/* enable TXE irq */
        splx(plx);

        return 1;
    }
#else
    while(1){
        plx = spltty();
        if( SERIAL_STATUS(addr) & SR_TXE ) break;
    }

#endif

    SERIAL_PUT(addr, ch);
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
    USART_TypeDef *addr = p->addr;

    while( 1 ){
        plx = spltty();
        if( p->rxq.len ) break;

        if( f->flags & F_NONBLOCK ){
            /* wait until something is available */
            do {
                i = SERIAL_STATUS(addr);
            }while( !(i & SR_RXNE) );
            ch = SERIAL_GET(addr);
            splx(plx);
            return ch;
        }else{
#ifdef USE_PROC
            tsleep( &p->rxq, currproc->prio, "com/i", 0);
#endif
        }
    }


    ch = qpop( &p->rxq );
    /* RSN - flow control */

    splx(plx);
    return ch;

}

int
serial_write(FILE *f, const char *buf, int len){
    int n = 0;
    struct Com *p = (struct Com*)f->d;
    int plx;

    while(len){
        plx = spltty();

        while( !qfull(&p->txq) ){
            int i = qwrite(&p->txq, buf, len);

            buf += i;
            len -= i;
            n   += i;

            if( len == 0 ) break;
        }

        p->addr->CR1 |= CR1_TXEIE;	/* enable TXE irq */
        splx(plx);

        if( !len ) break;
        if( ! qfull(&p->txq) ) continue;

        if( f->flags & F_NONBLOCK )   break;	// drop

#ifdef USE_PROC
        // wait for buffer to empty
        tsleep( &p->txq, -1, "com/w", 10000 );
#endif
    }

    return n;
}

int
serial_read(FILE *f, char *buf, int len){
    int n = 0;
    struct Com *p = (struct Com*)f->d;
    int plx;

    if( !len ) return 0;

    while(1){
        plx = spltty();

        if( p->rxq.len != 0 ){
            // return as much as we can
            n = qread( &p->rxq, buf, len);
            break;
        }

        if( f->flags & F_NONBLOCK )   break;
#ifdef USE_PROC
        tsleep( &p->rxq, -1, "com/r", 10000 );
#endif
    }

    splx(plx);
    return n;
}

/****************************************************************/

static void
serial_irq(int unit){
    volatile USART_TypeDef *addr = com[unit].addr;

    int sr = SERIAL_STATUS(addr);

    // kprintf("s %d %x\n", unit, sr);

    if( sr & SR_TXE ){
        /* transmitter empty */
        //blink(1);

        if( com[unit].txq.len != 0 ){
            int ch = qpop( &com[unit].txq );
            SERIAL_PUT(addr, ch);
        }else{
            addr->CR1 &= ~ CR1_TXEIE;	// disable TXE irq
            wakeup( &com[unit].txq );
        }
    }

    if( sr & SR_RXNE ){
        /* got a char */
        int ch = SERIAL_GET(addr);
        int i;

        /* special control char ? */
        for(i=0; i<sizeof(com[unit].file.cchars); i++){
            if(com[unit].file.cchars[i] && ch == com[unit].file.cchars[i]){
                sigunblock( com[unit].file.ccpid );
                ksendmsg( com[unit].file.ccpid, MSG_CCHAR_0 + i );
                return;
            }
        }

        if( !qfull( &com[unit].rxq) ){
            /* queue it up */
            qpush( &com[unit].rxq, ch );

            /* flow control */
#if 0
            if( com[unit].len > SERIAL_QUEUE_HIWATER ){
                /* almost full - drop RTS */
                /* com[unit].status |= COMSTAT_THROTTLED; */
            }
#endif
            wakeup( &com[unit].rxq );
        }
    }
}

/****************************************************************/
void
USART1_IRQHandler(void){
    serial_irq(0);
}
void
USART2_IRQHandler(void){
    serial_irq(1);
}
void
USART3_IRQHandler(void){
    serial_irq(2);
}

#ifdef UART4
void
UART4_IRQHandler(void){
    serial_irq(3);
}
#endif
#ifdef UART5
void
UART5_IRQHandler(void){
    serial_irq(4);
}
#endif
#ifdef USART6
void
USART6_IRQHandler(void){
    serial_irq(5);
}
#endif
#ifdef UART7
void
UART7_IRQHandler(void){
    serial_irq(6);
}
#endif
#ifdef UART8
void
UART8_IRQHandler(void){
    serial_irq(7);
}
#endif

