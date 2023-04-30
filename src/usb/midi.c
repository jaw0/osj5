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

typedef uint32_t midi_t;

#define QUEUE_TYPE midi_t
#include <queue.h>


#define USB_BUF_SIZE    64	// bytes

#define RX_QUEUE_SIZE	32	// packets

#ifndef MIDI_QUEUE_SIZE
# define TX_QUEUE_SIZE	32	// packets
#else
# define TX_QUEUE_SIZE	MIDI_QUEUE_SIZE
#endif

#define MIDI_EPSIZE	64	// FS; 512 for HS


struct MIDI;
static void maybe_tx(struct MIDI *);


static struct MIDI {
    usbd_t *usbd;

    struct queue rxq, txq;
    midi_t rxbuf[ USB_BUF_SIZE / sizeof(midi_t) ];
    midi_t txbuf[ USB_BUF_SIZE / sizeof(midi_t) ];

    uint8_t rxep, txep;
    uint8_t rblen, tblen;
    uint8_t ready, corked;

} midiinfo;


void
midi_init(usbd_t *u, int rxep, int txep){

    struct MIDI *v = &midiinfo;
    bzero(&midiinfo, sizeof(midiinfo));
    v->usbd = u;
    v->rxep = rxep;
    v->txep = txep;

    queue_init( &v->txq, TX_QUEUE_SIZE );
    queue_init( &v->rxq, RX_QUEUE_SIZE );

    trace_init();

    v->ready = 1;
}

void
midi_reset(struct MIDI *p){

}

struct MIDI *
midi_get(int i){
    struct MIDI *v = &midiinfo;
    return v;
}

void
midi_configure(struct MIDI *p){
    trace_crumb0("mid", "conf");

    if( usb_speed(p->usbd) == USB_SPEED_HIGH ){
        usb_config_ep( p->usbd, p->rxep, UE_BULK, 512 );
        usb_config_ep( p->usbd, p->txep, UE_BULK, 512 );
    }else{
        usb_config_ep( p->usbd, p->rxep, UE_BULK, MIDI_EPSIZE );
        usb_config_ep( p->usbd, p->txep, UE_BULK, MIDI_EPSIZE );
    }
}

int
midi_recv_setup(struct MIDI *p, const char *buf, int len){
    usb_device_request_t *req = buf;

    kprintf("!midi/req i %x, t %x, r %x, v %x\n",  req->wIndex, req->bmRequestType, req->bRequest, req->wValue);

    return 0;
}

// to send multiple events together
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
    maybe_tx(p);
    splx(plx);
}

static void
maybe_dequeue(struct MIDI* p){
    int i,j;

    if( !p->rblen ) return;
    if( p->rblen > RX_QUEUE_SIZE - p->rxq.len ) return;

    for(i=0; i<p->rblen; i++){
        // machine byte order -> network order
        int m = __builtin_bswap32( p->rxbuf[i] );
        trace_crumb1("mid", "rcvq", m);
        qpush( &p->rxq, m);
    }

    p->rblen = 0;

    usb_recv_ack( p->usbd, p->rxep );

    if( !p->ready ){
        p->ready = 1;
    }
}

midi_t
midi_read(){
    struct MIDI *p = &midiinfo;
    int plx;

    while( 1 ){
        plx = spldisk();
        if( p->rxq.len ) break;

        tsleep( &p->rxq, currproc->prio, "usb/i", 1000000);
    }

    midi_t m = qpop( &p->rxq );

    maybe_dequeue(p);

    splx(plx);
    return m;
}

// non-blocking
midi_t
midi_maybe_read(){
    struct MIDI *p = &midiinfo;
    midi_t m = 0;

    int plx = spldisk();
    if( p->rxq.len ){
        m = qpop( &p->rxq );
        maybe_dequeue(p);
    }

    splx(plx);
    return m;
}

void
midi_recv_chars(struct MIDI *p, int ep, int len){
    trace_crumb2("mid", "rcv", ep, len);

    int l = usb_read(p->usbd, ep, p->rxbuf, sizeof(p->rxbuf));
    p->rblen = l / sizeof(midi_t);

    // kprintf("midi recv %x\n", *(int*)p->rxbuf);

    maybe_dequeue(p);
    maybe_tx(p);
    wakeup( &p->rxq );

}


static void
maybe_tx(struct MIDI *p){
    int i;

    if( !p->ready ) return;
    if( p->txq.len == 0 ) return;
    if( p->tblen ) return; // xmit underway
    if( !usbd_isactive(p->usbd) ) return;

    // copy to buffer
    for(i=0; p->txq.len && (i<TX_QUEUE_SIZE); i++){
        midi_t m = qpop( &p->txq );
        // network byte order -> machine order
        p->txbuf[i] = __builtin_bswap32(m);
    }

    // tx
    p->tblen = i;
    int bytes = i * sizeof(midi_t);

    int plx = spldisk();
    trace_crumb2("mid", "tx", bytes, p->txq.len);
    usbd_write(p->usbd, p->txep, p->txbuf, bytes, !(bytes & (USB_BUF_SIZE - 1)) );
    splx(plx);
}

void
midi_tx_complete(struct MIDI *p, int ep){

    trace_crumb1("mid", "tx/c", ep);
    p->tblen = 0;
    maybe_tx(p);
    wakeup( &p->txq );
}

int
midi_send(uint32_t cmd){
    struct MIDI *p = &midiinfo;

    if( !usbd_isactive(p->usbd) ) return 0;
    if( !p->ready ) return 0;

    int plx = spldisk();

    // drop cmd if buffer is full
    if( p->txq.len != TX_QUEUE_SIZE ){
        qpush(&p->txq, cmd);
    }

    if( (!p->corked) || (p->txq.len == TX_QUEUE_SIZE) ){
        maybe_tx(p);
    }

    splx(plx);

    return 1;
}

#if 0
DEFUN(omidi2, "")
{

    midi_send(0x0BB00101);
    midi_send(0x0BB00102);
    midi_send(0x0BB00103);
    midi_send(0x0BB00104);
    return 0;
}
#endif

