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
#include <nvic.h>
#include <gpio.h>
#include <stm32.h>
#include <serial_impl.h>

#define SR_TXE	0x80
#define SR_RXNE 0x20

#define CFFLAGS_ALTPINS	3	// 2 bits of flags - alt set of pins

#ifndef SERIAL_QUEUE_SIZE
#  define SERIAL_QUEUE_SIZE     16	/* input queue size */
#endif

int serial_putchar(FILE*, char);
int serial_getchar(FILE*);
int serial_noop(FILE*);
int serial_status(FILE*);
void serial_setbaud(int, int);


const struct io_fs serial_port_fs = {
    serial_putchar,
    serial_getchar,
    0,
    0,
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

    finit( & com[i].file );
    com[i].file.fs = &serial_port_fs;
    com[i].file.codepage = CODEPAGE_UTF8;
    com[i].head = com[i].tail = com[i].len = 0;
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
        while(1){
            plx = splproc();
            asleep( addr, "com/o" );
            if( SERIAL_STATUS(addr) & SR_TXE ) break;
            addr->CR1 |= 0x80;	/* enable TXE irq */
            await( -1, 100000 );
            if( SERIAL_STATUS(addr) & SR_TXE ) break;
        }
        aunsleep();
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
        if( p->len ) break;

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
            tsleep( &p->len, currproc->prio, "com/i", 0);
#endif
        }
    }


    ch = p->queue[ p->tail++ ];
    p->tail %= SERIAL_QUEUE_SIZE;
    p->len --;
    /* RSN - flow control */

    splx(plx);
    return ch;

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
        addr->CR1 &= ~ 0xC0;	// disable TXE irq
        wakeup( addr );
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

        if( com[unit].len < SERIAL_QUEUE_SIZE ){
            /* queue it up */
            com[unit].queue[ com[unit].head++ ] = ch;
            com[unit].head %= SERIAL_QUEUE_SIZE;
            com[unit].len ++;
            /* flow control */
#if 0
            if( com[unit].len > SERIAL_QUEUE_HIWATER ){
                /* almost full - drop RTS */
                /* com[unit].status |= COMSTAT_THROTTLED; */
            }
#endif
            wakeup( &com[unit].len );
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

