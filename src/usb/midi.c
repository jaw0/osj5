/*
  Copyright (c) 2019
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2019-Jun-23 16:46 (EDT)
  Function: usb midi

*/

#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <dev.h>
#include <usbd.h>
#include <usbdef.h>
#include <userint.h>

#define USB_MIDI_TRACE
#if defined(USB_MIDI_TRACE) || defined(USB_TRACE)
# define TRACE
#endif
#include <trace.h>

#define QUEUE_TYPE uint32_t
#include <queue.h>


#define USB_BUF_SIZE    64
//#define RX_QUEUE_SIZE	64

#ifndef MIDI_QUEUE_SIZE
# define TX_QUEUE_SIZE	32	// packets
#else
# define TX_QUEUE_SIZE	MIDI_QUEUE_SIZE
#endif

static void maybe_tx(usbd_t *u, int ep);


static struct MIDI {
    usbd_t *usbd;
    int ep;

    struct queue /*rxq,*/ txq;
    char rxbuf[ USB_BUF_SIZE ];
    char txbuf[ USB_BUF_SIZE ];

    uint8_t rblen, tblen;
    uint8_t ready, corked;

} midiinfo;


void
midi_init(usbd_t *u, int ep){

    struct MIDI *v = &midiinfo;
    bzero(&midiinfo, sizeof(midiinfo));
    v->usbd = u;
    v->ep   = ep;

    // queue_init( &v->rxq, RX_QUEUE_SIZE );
    queue_init( &v->txq, TX_QUEUE_SIZE );

    v->ready = 1;
}

void
midi_cork(){
    struct MIDI *p = &midiinfo;
    p->corked = 1;
}

void
midi_uncork(){
    struct MIDI *p = &midiinfo;

    p->corked = 0;
    if( p->txq.len == 0 ) return;

    int plx = spldisk();
    maybe_tx(p->usbd, p->ep);
    splx(plx);
}

// is byte reversed
void
midi_recv_chars(usbd_t *u, int ep, int len){
    struct MIDI *p = &midiinfo;
    trace_crumb2("mid", "rcv", ep, len);

    int l = usb_read(u, ep, p->rxbuf, USB_BUF_SIZE);
    kprintf("midi recv %x\n", *(int*)p->rxbuf);
    // ...
    usb_recv_ack( u, ep );

}


static void
maybe_tx(usbd_t *u, int ep){
    int i;

    struct MIDI *p = &midiinfo;

    if( !p->ready ) return;
    if( p->txq.len == 0 ) return;
    if( p->tblen ) return; // xmit underway
    if( !usbd_isactive(u) ) return;

    // copy to buffer
    for(i=0; p->txq.len && (i<USB_BUF_SIZE); i+=4){
        uint32_t m = qpop( &p->txq );
        //  in network byte order
        p->txbuf[i+0] = (m >> 24) & 0xFF;
        p->txbuf[i+1] = (m >> 16) & 0xFF;
        p->txbuf[i+2] = (m >> 8)  & 0xFF;
        p->txbuf[i+3] = (m)       & 0xFF;
    }

    // tx
    p->tblen = i;
    int plx = spldisk();
    trace_crumb2("mid", "tx", i, p->txq.len);
    usbd_write(u, ep, p->txbuf, i, !(i & (USB_BUF_SIZE - 1)) );
    splx(plx);
}

void
midi_tx_complete(usbd_t *u, int ep){

    struct MIDI *p = &midiinfo;
    p->tblen = 0;

    trace_crumb1("mid", "tx/c", ep);
    maybe_tx(u, ep);
    wakeup( &p->txq );
}

int
midi_send(uint32_t cmd){

    struct MIDI *p = &midiinfo;
    int i;

    if( !usbd_isactive(p->usbd) ) return 0;
    if( !p->ready ) return 0;

    int plx = spldisk();

    // drop cmd if buffer is full
    if( p->txq.len != TX_QUEUE_SIZE ){
        qpush(&p->txq, cmd);
    }

    if( (!p->corked) || (p->txq.len == TX_QUEUE_SIZE) ){
        maybe_tx(p->usbd, p->ep);
    }

    splx(plx);

    return 1;
}


DEFUN(omidi2, "")
{

    midi_send(0x0BB00101);
    midi_send(0x0BB00102);
    midi_send(0x0BB00103);
    midi_send(0x0BB00104);
    return 0;
}
