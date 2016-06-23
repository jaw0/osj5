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
#include <dev.h>
#include <bootflags.h>
#include <nvic.h>
#include <gpio.h>
#include <atsam.h>
#include <pmc.h>
#include <serial_impl.h>

#define SR_TXRDY 2
#define SR_RXRDY 1

#define CFFLAGS_ALTPINS	3	// 2 bits of flags - alt set of pins

#ifndef SERIAL_QUEUE_SIZE
#  define SERIAL_QUEUE_SIZE     16	/* input queue size */
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
    int    baudclock;
#define COMSTAT_THROTTLED	2	/* we have dropped RTS */

    int portno;
    Uart * addr;
} com[ N_SERIAL ];


FILE *serial0_port = 0;


/* initialize the serial ports */
int
serial_init(struct Device_Conf *dev){
    int i    = dev->unit;
    Uart *addr;
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

    switch(i){
    case 0:
        addr = UART0;
        irq  = UART0_IRQn;
        break;
    case 1:
        addr = UART1;
        irq  = UART1_IRQn;
        break;
    case 2:
        addr = UART2;
        irq  = UART2_IRQn;
        break;
    case 3:
        addr = UART3;
        irq  = UART3_IRQn;
        break;
    case 4:
        addr = UART4;
        irq  = UART4_IRQn;
        break;

    default:
        PANIC("invalid serial");
        break;

    }

    com[i].baudclock = periph_clock_freq();
    com[i].addr   = addr;

    addr->UART_WPMR = 0x554152 << 8; // write enable
    addr->UART_IDR  = 0xFFFFFFFF;    // disable ints
    addr->UART_CR   = 0x10A;	     // reset
    // addr->UART_MR   = 0x0810;	     // no parity, filter enabled, use periph clock
    addr->UART_MR   = 0x0800;	     // no parity, no filter, use periph clock
    addr->UART_CR   = 0x50; 	     // enable

    if( dev->baud )
        serial_setbaud(i, b=dev->baud);
    else
        serial_setbaud(i, b=9600);

    // enable ints
    addr->UART_IER = 0x01;	// int enable: rxrdy
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

    int div = baud * 16;
    com[port].addr->UART_BRGR = (com[port].baudclock + div/2) / div;
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
    Uart *addr = p->addr;

#ifdef USE_PROC
    if( f->flags & F_NONBLOCK ){
        while(1){
            plx = spltty();
            if( addr->UART_SR & SR_TXRDY ) break;
        }
    }else{
        while(1){
            plx = splproc();
            asleep( addr, "com/o" );
            if( addr->UART_SR & SR_TXRDY ) break;
            addr->UART_IER |= 0x2;	/* enable TX irq */
            await( -1, 100000 );
            if( addr->UART_SR & SR_TXRDY ) break;
        }
        aunsleep();
    }
#else
    while(1){
        plx = spltty();
        if( addr->UART_SR & SR_TXRDY ) break;
    }

#endif

    addr->UART_THR = ch;
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
    Uart *addr = p->addr;

    while( 1 ){
        plx = spltty();
        if( p->len ) break;

        if( f->flags & F_NONBLOCK ){
            /* wait until something is available */
            do {
                i = addr->UART_SR;
            }while( !(i & SR_RXRDY) );
            ch = addr->UART_RHR;
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
    Uart *addr = com[unit].addr;

    int sr = addr->UART_SR;

    // kprintf("s %d %x\n", unit, sr);

    if( sr & SR_TXRDY ){
        /* transmitter empty */
        //blink(1);
        addr->UART_IDR |= 2;		// disable TX irq
        wakeup( addr );
    }

    if( sr & SR_RXRDY ){
        /* got a char */
        int ch = addr->UART_RHR;
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

void UART0_Handler(void){ serial_irq(0); }
void UART1_Handler(void){ serial_irq(1); }
void UART2_Handler(void){ serial_irq(2); }
void UART3_Handler(void){ serial_irq(3); }
void UART4_Handler(void){ serial_irq(4); }

