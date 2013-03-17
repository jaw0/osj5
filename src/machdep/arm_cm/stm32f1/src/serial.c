/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 23:25 (EDT)
  Function: 

*/

#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <msgs.h>
#include <dev.h>
#include <bootflags.h>
#include <clock.h>
#include <nvic.h>

/* NB: stm32f1 + f4 are compat, but at different addrs */
#include <stm32f10x.h>

#define SR_TXE	0x80
#define SR_RXNE 0x20

#ifndef SERIAL_QUEUE_SIZE
#  define SERIAL_QUEUE_SIZE     8	/* input queue size */
#endif

int serial_putchar(FILE*, char);
int serial_getchar(FILE*);
int serial_noop(FILE*);
int serial_status(FILE*);
void serial_setbaud(int, int);

extern void blink(int);


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
#define COMSTAT_TXPENDING	1	/* a xmit is in progress */
#define COMSTAT_THROTTLED	2	/* we have dropped RTS */

    int portno;
    USART_TypeDef * addr;
} com[ N_SERIAL ];


FILE *serial0_port = 0;


/* initialize the serial ports */
int
serial_init(struct Device_Conf *dev){
    int i    = dev->unit;
    USART_TypeDef *addr;
    int irq;
    int b;

    finit( & com[i].file );
    com[i].file.fs = &serial_port_fs;
    com[i].head = com[i].tail = com[i].len = 0;
    com[i].status = 0;
    com[i].portno = i;
    com[i].file.d  = (void*)&com[i];

    // enable gpio clock, usart clock, configure pins
    switch(i){
    case 0:
        addr = USART1;
        RCC->APB2ENR |= 0x4005;
        GPIOA->CRH   |= 0x4b0;
        irq           = (int) IRQ_USART1;
        break;
    case 1:
        addr = USART2;
        RCC->APB2ENR |= 0x5;
        RCC->APB1ENR |= 0x20000;
        GPIOA->CRL    = 0x4b00;
        irq           = (int) IRQ_USART2;
        break;
    case 2:
        addr = USART3;
        RCC->APB2ENR |= 0x9;
        RCC->APB1ENR |= 0x40000;
        GPIOB->CRH    = 0x4b00;
        irq           = (int) IRQ_USART3;
        break;
    }

    com[i].addr   = addr;

    if( dev->baud )
        serial_setbaud(i, b=dev->baud);
    else
        serial_setbaud(i, b=9600);

    addr->CR1 |= 0x200C		// enable, no parity, 8 bit, ...
        | 0x20;			// enable RX irq

    // enable ints
    nvic_enable( irq, IPL_TTY );

    if( !i ){
        serial0_port = &com[0].file;
    }

    kprintf("%s unit %d at io 0x%x irq %d %d baud\n", dev->name, i, addr, irq, b);

    return (int) &com[i].file;
}

/* set the baud rate on serial port */
void
serial_setbaud(int port, int baud){
    int d, i;
    int plx;

    // XXX different clocks for different ports
    com[port].addr->BRR = sys_clock_freq() / baud;
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

    while(1){
        plx = spltty();
        if( addr->SR & SR_TXE ) break;
#ifdef USE_PROC
        if( !(f->flags & F_NONBLOCK) ){
            addr->CR1 |= 0x80;	/* enable TXE irq */
            tsleep(addr, currproc->prio, "com/o", 1000000);
        }
#endif
    }

    addr->DR = ch;
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
            /* wait until something is available */
            do {
                i = addr->SR;
            }while( !(i & SR_TXE) );
            ch = addr->DR;
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
    USART_TypeDef *addr = com[unit].addr;

    int sr = addr->SR;

    // kprintf("s %d %x\n", unit, sr);

    if( sr & SR_TXE ){
        /* transmitter empty */
        //blink(1);
        //com[unit].status &= ~ COMSTAT_TXPENDING;
        addr->CR1 &= ~ 0xC0;	// disable TXE irq
        wakeup( addr );
    }

    if( sr & SR_RXNE ){
        /* got a char */
        int ch = addr->DR;
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
    //serial_irq(1);
}
void
USART3_IRQHandler(void){
    //serial_irq(2);
}

