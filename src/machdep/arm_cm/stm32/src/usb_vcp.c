/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Mar-22 10:44 (EDT)
  Function: usb virtual comm port

*/

#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <dev.h>
#include <bootflags.h>
#include <stm32.h>
#include <gpio.h>
#include <userint.h>

#ifndef VCP_QUEUE_SIZE
#  define VCP_QUEUE_SIZE     128	/* input queue size */
#endif
#define CDC_SIZE	      64	/* usb cdc packet size (see also usbd_conf.h) */

static int vcp_putchar(FILE*, char);
static int vcp_getchar(FILE*);
static int vcp_noop(FILE*);
static int vcp_status(FILE*);

const static struct io_fs vcp_port_fs = {
    vcp_putchar,
    vcp_getchar,
    0,
    0,
    vcp_status,
    0,
    0,
    0,
    0,
    0,
    0
};


// NB: the ST library only supports one
struct VCP {
    FILE file;
    void *pdev;
    char queue[ VCP_QUEUE_SIZE ];
    u_char head, tail, len;

    u_char status;
#define COMSTAT_THROTTLED	2	/* we have dropped RTS */
} com[ 1 ];

FILE *vcp0_port = 0;


usbvcp_init(struct Device_Conf *dev){

    int i = 0; // dev->unit;

    finit( & com[i].file );
    com[i].file.fs = &vcp_port_fs;
    com[i].file.codepage = CODEPAGE_UTF8;
    com[i].head = com[i].tail = com[i].len = 0;
    com[i].status  = 0;
    com[i].file.d  = (void*)&com[i];

    RCC->AHB2ENR |= 1<<7;

    gpio_init( GPIO_A11, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
    gpio_init( GPIO_A12, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );

    nvic_enable( OTG_FS_IRQn, IPL_TTY );
    com[i].pdev = usb_start();
    bootmsg("%s usb/cdc/vcp on otgfs irq %d\n", dev->name, OTG_FS_IRQn);

    vcp0_port = &com[i].file;
    return (int) &com[i].file;

}

static void
vcp_rx_ack(){
    usbd_cdc_DataOutAck( com[0].pdev );
}

static int
vcp_status(FILE*f){
    // RSN - usb connected?
    return 1;
}

static int
vcp_putchar(FILE *f, char ch){
    int i;
    struct VCP *p;
    int plx;

    p = (struct VCP*)f->d;

    while(1){
        plx = spltty();
        i = VCP_DataTx(&ch, 1);
        splx(plx);
        if( !i ) break;				// char queued
        if( f->flags & F_NONBLOCK ) break;	// drop

        // wait for buffer to empty
        tsleep( p->pdev, -1, "usb/o", 0 );
    }
    return 1;
}

static int
vcp_getchar(FILE *f){
    char ch;
    int i, plx;
    struct VCP *p;

    p = (struct VCP*)f->d;

    while( 1 ){
        plx = spltty();
        if( p->len ) break;

        tsleep( &p->len, currproc->prio, "usb/i", 1000000);
    }

    ch = p->queue[ p->tail++ ];
    p->tail %= VCP_QUEUE_SIZE;
    p->len --;

    if( p->status == COMSTAT_THROTTLED )
        if( p->len < VCP_QUEUE_SIZE - CDC_SIZE ){
            vcp_rx_ack();
            p->status = 0;
        }

    splx(plx);
    return ch;
}

// called from usbd_cdc_if
void
vcp_recvchars(char *buf, int len){
    int unit = 0;
    int i;

    for(i=0; i<len; i++){
        if( com[unit].len < VCP_QUEUE_SIZE ){
            /* queue it up */
            com[unit].queue[ com[unit].head++ ] = buf[i];
            com[unit].head %= VCP_QUEUE_SIZE;
            com[unit].len ++;
        }
        // else drop
    }

    // tell other end to stop if buffer is filling
    if( !len || com[unit].len < VCP_QUEUE_SIZE - CDC_SIZE ){
        vcp_rx_ack();
    }else{
        com[unit].status = COMSTAT_THROTTLED;
    }

    wakeup(&com[unit].len);
    return 0;
}


/*
  usbd_cdc_core:
  And then usbd_cdc_DataOut() returns without calling DCD_EP_PrepareRx().
  In the main loop, picking up this flag, the process of received packet is done.
  When this process finishes, the main-loop task calls DCD_EP_PrepareRx(), for the next packet.


*/
