/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-15 22:29 (EDT)
  Function: usb full-speed

*/

#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <dev.h>
#include <stm32.h>
#include <gpio.h>
#include <usbfs.h>
#include <usbd.h>
#include <usbdef.h>
#include <usbfs_impl.h>
#include <userint.h>


#define CRUMBS "usb"
#define NR_CRUMBS 512
#include <crumbs.h>



#define EP_TOGGLE_SET(epr, bits, mask) (epr) = ((epr) ^ (bits)) & (USB_EPREG_MASK | (mask))

#define EP_TX_STALL(epr)    EP_TOGGLE_SET((epr), USB_EP_TX_STALL,                   USB_EPTX_STAT)
#define EP_RX_STALL(epr)    EP_TOGGLE_SET((epr), USB_EP_RX_STALL,                   USB_EPRX_STAT)
#define EP_TX_UNSTALL(epr)  EP_TOGGLE_SET((epr), USB_EP_TX_NAK,                     USB_EPTX_STAT | USB_EP_DTOG_TX)
#define EP_RX_UNSTALL(epr)  EP_TOGGLE_SET((epr), USB_EP_RX_VALID,                   USB_EPRX_STAT | USB_EP_DTOG_RX)
#define EP_DTX_UNSTALL(epr) EP_TOGGLE_SET((epr), USB_EP_TX_VALID,                   USB_EPTX_STAT | USB_EP_DTOG_TX | USB_EP_DTOG_RX)
#define EP_DRX_UNSTALL(epr) EP_TOGGLE_SET((epr), USB_EP_RX_VALID | USB_EP_DTOG_TX,  USB_EPRX_STAT | USB_EP_DTOG_RX | USB_EP_DTOG_TX)
#define EP_TX_VALID(epr)    EP_TOGGLE_SET((epr), USB_EP_TX_VALID,                   USB_EPTX_STAT)
#define EP_RX_VALID(epr)    EP_TOGGLE_SET((epr), USB_EP_RX_VALID,                   USB_EPRX_STAT)


static const uint16_t* usbepr[NUMENDPOINTS] = {
    &USB->EP0R, &USB->EP1R, &USB->EP2R, &USB->EP3R,
    &USB->EP4R, &USB->EP5R, &USB->EP6R, &USB->EP7R,
};




// NB. all of the devices with the FS usb, have exactly one usb periph.

typedef struct {
    usbd_t *usbd;
    int     bufnext;

} usbfs_t;

static usbfs_t usb[N_USBD];

void *
usb_init(struct Device_Conf *dev, usbd_t *usbd){
    int i    = dev->unit;

    bzero(usb + i, sizeof(usbfs_t));
    usb[i].usbd = usbd;

    RCC->APB1ENR1  |= 1<<26;	// usb
    RCC->APB1ENR1  |= 1<<28;	// pwr
    PWR->CR2 |= 1<<10;

    gpio_init( GPIO_A11, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
    gpio_init( GPIO_A12, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );

    USB->CNTR = USB_CNTR_FRES;
    // This circuit has a defined startup time (tSTARTUP specified in the datasheet) during which the behavior
    // of the USB transceiver is not defined. It is thus necessary to wait this time, after setting the PDWN bit
    // in the CNTR register, before removing the reset condition on the USB part (by clearing the FRES bit in the CNTR register).
    // delay ~1us
    int x = 100;
    while( x-- > 0 ){ __asm("nop"); }

    USB->CNTR   = 0;
    USB->ISTR   = 0;
    USB->BTABLE = 0;

    nvic_enable( 67, IPL_DISK );

    bootmsg("usb device full-speed\n");

    return usb + i;
}

int
usb_serialnumber(void){
    return djb2_hash(R_UNIQUE, 12);
}

int
usb_connect(usbd_t *u){
    u->curr_state = USBD_STATE_CONNECT;
    USB->CNTR = USB_CNTR_CTRM | USB_CNTR_RESETM; //QQQ - | USB_CNTR_ERRM | USB_CNTR_PMAOVRM;
    USB->BCDR = USB_BCDR_DPPU;
}

int
usb_disconnect(usbd_t *u){
    USB->CNTR = 0;
    USB->BCDR = 0;
    u->curr_state = USBD_STATE_INACTIVE;
}

void
usb_enable_suspend(usbd_t *u){
    USB->CNTR |= USB_CNTR_SUSPM | USB_CNTR_WKUPM;
}

void
usb_set_addr(usbd_t *u, int addr){
    USB->DADDR = USB_DADDR_EF | (addr & 0x7F);
    RESET_CRUMBS();
}

void
usb_stall(usbd_t *u, int ep){
    uint16_t *epr = usbepr[ep & 7];

    if( ep & 0x80 ){
        EP_TX_STALL(*epr);
    }else{
        EP_RX_STALL(*epr);
    }
}

void
usb_unstall(usbd_t *u, int ep){
    uint16_t *epr = usbepr[ep & 7];

    if( ep & 0x80 ){
        EP_TX_UNSTALL(*epr);
    }else{
        EP_RX_UNSTALL(*epr);
    }
}

int
usb_isstalled(usbd_t *u, int ep){
    uint16_t *epr = usbepr[ep & 7];

    if( ep & 0x80 ){
        return (*epr & USB_EPTX_STAT) == USB_EP_TX_STALL;
    }
    return (*epr & USB_EPRX_STAT) == USB_EP_RX_STALL;

}

static int
pma_alloc(usbfs_t *u, int size){
    int p = u->bufnext;
    u->bufnext += size;
    if( u->bufnext >= USBPMASIZE ) return -1;
    return p;
}

static inline void
set_pma_tx(int epa, int addr, int cnt){
    USBPMA->desc[ epa ].tx.addr  = addr;
    USBPMA->desc[ epa ].tx.count = cnt;
}
static inline void
set_pma_rx(int epa, int addr, int cnt){
    USBPMA->desc[ epa ].rx.addr  = addr;
    USBPMA->desc[ epa ].rx.count = cnt;
}

static inline int
pma_rx_blkr(int size){

    if( size <= 62 )
        return ((size + 1) & 0xFE) << 9;

    return (((size - 1) & ~0x1F) << 5) | 0x8000;
}

static void
pma_copy(const uint16_t *src, uint16_t *dst, int len){
    for(; len>0; len-=2)
        *dst++ = *src++;
}

static int
pma_write(struct bufdesc *b, const char *src, int len){
    pma_copy(src, b->addr + (char*)USB_PMAADDR, len);
    b->count = len;
    return len;
}

static int
pma_read(struct bufdesc *b, char *dst, int len){
    int l = b->count & 0x3FF;
    if( l < len ) len = l;
    pma_copy(b->addr + (char*)USB_PMAADDR, dst, len);
    return l;
}


int
usb_config_ep(usbd_t *u, int ep, int type, int size){
    usbfs_t *fs = u->dev;
    int epa = ep & 7;
    volatile uint16_t *epr = usbepr[epa];

    //DROP_CRUMB("cf/ep", ep, type);
    //DROP_CRUMB("epr", *epr, epr);

    switch(type){
    case UE_CONTROL:
        *epr = USB_EP_CONTROL | epa;
        //DROP_CRUMB("epr/ctl", *epr, 0);
        break;
    case UE_ISOCHRONOUS:
        *epr = USB_EP_ISOCHRONOUS | epa;
        break;
    case UE_BULK:
        *epr = USB_EP_BULK | epa;
        break;
    case UE_INTERRUPT:
        *epr = USB_EP_INTERRUPT | epa;
        break;
    default:
        DROP_CRUMB("err/type", type, 0);
        return -1;
    }

    //DROP_CRUMB("epr/1", *epr, USB->CNTR);
    u->epd[epa].bufsize = size;

    // TX or control
    if( (ep & 0x80) || (type == UE_CONTROL) ){
        int buf = pma_alloc(u->dev, size);
        if( buf == - 1 ) return -1;

        set_pma_tx( epa, buf, 0 );

        if( type == UE_ISOCHRONOUS ){
            buf = pma_alloc(u->dev, size);
            if( buf == -1 ) return -1;

            set_pma_rx( epa, buf, size );

            EP_DTX_UNSTALL(*epr);
        } else {
            EP_TX_UNSTALL(*epr);
        }
    }

    // RX or control
    if( !(ep & 0x80) ){
        int buf = pma_alloc(u->dev, size);
        if( buf == - 1 ) return -1;

        set_pma_rx( epa, buf, pma_rx_blkr(size) );

        if( type == UE_ISOCHRONOUS ){
            buf = pma_alloc(u->dev, size);
            if( buf == -1 ) return -1;

            set_pma_tx( epa, buf, pma_rx_blkr(size) );

            EP_DRX_UNSTALL(*epr);
        } else {
            EP_RX_UNSTALL(*epr);
        }
    }

    return 0;
}


int
usb_send(usbd_t *u, int ep, const char *buf, int len){
    usbfs_t *fs = u->dev;
    int epa = ep & 7;
    volatile uint16_t *epr = usbepr[epa];

    if( len > u->epd[epa].bufsize ) len = u->epd[epa].bufsize;

    int type = *epr & (USB_EPTX_STAT | USB_EP_T_FIELD | USB_EP_KIND);

    switch( type ){

    /* double buffered bulk endpoint */
    case (USB_EP_TX_NAK   | USB_EP_BULK | USB_EP_KIND):
        if (*epr & USB_EP_DTOG_RX) {
            pma_write( & USBPMA->desc[epa].rx, buf, len );
        } else {
            pma_write( & USBPMA->desc[epa].tx, buf, len );
        }
        *epr = (*epr & USB_EPREG_MASK) | USB_EP_DTOG_RX;
        break;

    case (USB_EP_TX_VALID | USB_EP_ISOCHRONOUS):
        if (!(*epr & USB_EP_DTOG_TX)) {
            pma_write( & USBPMA->desc[epa].rx, buf, len );
        } else {
            pma_write( & USBPMA->desc[epa].tx, buf, len );
        }
        break;

    case (USB_EP_TX_NAK | USB_EP_BULK):
    case (USB_EP_TX_NAK | USB_EP_CONTROL):
    case (USB_EP_TX_NAK | USB_EP_INTERRUPT):
        pma_write( & USBPMA->desc[epa].tx, buf, len );
        EP_TX_VALID(*epr);
        break;
    /* invalid or not ready */
    default:
        return -1;
    }

    return len;
}

static void
usb_recv(usbfs_t *u, int ep){
    uint16_t *epr = usbepr[ep];
    struct bufdesc *bd;

    if( (*epr & USB_EP_T_FIELD) == USB_EP_ISOCHRONOUS ){
        if( *epr & USB_EP_DTOG_TX )
            bd = & USBPMA->desc[ep].tx;
        else
            bd = & USBPMA->desc[ep].rx;
    }else{
        bd = & USBPMA->desc[ep].rx;
    }

    if( (*epr & USB_EP_SETUP) && !ep )
        usbd_cb_recv_setup(u->usbd, (char*)USB_PMAADDR + bd->addr, bd->count & 0x3FF );
    else
        usbd_cb_recv(u->usbd, ep, (char*)USB_PMAADDR + bd->addr, bd->count & 0x3FF );
}

void
usb_recv_ack(usbd_t *u, int ep){
    uint16_t *epr = usbepr[ep & 7];

    EP_RX_VALID(*epr);
}

int
usb_read(usbd_t *u, int ep, const char *buf, int len){
    uint16_t *epr = usbepr[ep & 7];
    struct bufdesc *bd;

    if( (*epr & USB_EP_T_FIELD) == USB_EP_ISOCHRONOUS ){
        if( *epr & USB_EP_DTOG_TX )
            bd = & USBPMA->desc[ep].tx;
        else
            bd = & USBPMA->desc[ep].rx;
    }else{
        bd = & USBPMA->desc[ep].rx;
    }

    return pma_read(bd, buf, len);
}


static void
usb_ctr_handler(usbfs_t *u){
    int i;

    for(i=0; i<N_ENDPOINT; i++){
        uint16_t *epr = usbepr[i];

        if( *epr & USB_EP_CTR_TX ){
            *epr &= USB_EPREG_MASK & ~USB_EP_CTR_TX;
            usbd_cb_send_complete(u->usbd, i);
        }

        if( *epr & USB_EP_CTR_RX ){
            *epr &= USB_EPREG_MASK & ~USB_EP_CTR_RX;
            usb_recv(u, i);
        }
    }
}

static void
usb_reset_handler(usbfs_t *u){
    int i;

    for(i=0; i<512; i++){
        ((short*)USB_PMAADDR)[i] = 0;
    }

    USB->BTABLE = 0;
    USB->CNTR &= ~USB_CNTR_FSUSP;

    u->bufnext = sizeof(USB_BufferDescr);

    USB->DADDR = USB_DADDR_EF;
    usb_config_ep(u->usbd, 0, UE_CONTROL, CONTROLSIZE);

    usbd_cb_reset(u->usbd);
    DROP_CRUMB("reset", USB->EP0R, USB->CNTR); // USBPMA->desc[0].rx.count );
}

static void
usb_suspend_handler(usbfs_t *u){

    if( !(USB->CNTR & USB_CNTR_SUSPM) ) return;

    DROP_CRUMB("susp", 0, 0);
    usbd_cb_suspend(u->usbd);
    USB->CNTR |= USB_CNTR_FSUSP;
    // QQQ - LPMODE ?
}
static void
usb_wakeup_handler(usbfs_t *u){

    usbd_cb_wakeup(u->usbd);
}


void
OTG_FS_IRQHandler(void){
    int isr = USB->ISTR;
    usbfs_t *u = usb + 0;

    DROP_CRUMB( "irq!", isr, 0 );

    if( isr & USB_ISTR_RESET ){
        usb_reset_handler(u);
        USB->ISTR = ~USB_ISTR_RESET;
    }

    if( isr & USB_ISTR_CTR ){
        usb_ctr_handler(u);
        USB->ISTR = ~USB_ISTR_CTR;
    }

    if( isr & USB_ISTR_SUSP ){
        usb_suspend_handler(u);
        USB->ISTR = ~USB_ISTR_SUSP;
    }
    if( isr & USB_ISTR_WKUP ){
        usb_wakeup_handler(u);
        USB->ISTR = ~USB_ISTR_WKUP;
    }


    // errors?

    USB->ISTR = 0;
}


DEFUN(usbtest, "usb test")
{
    printf("usb: %x pma: %x\n", USB, USBPMA, usb);

    usb_disconnect(usb[0].usbd );
    sleep(1);

    RESET_CRUMBS();
    usbd_reset_crumbs();
    usb_connect( usb[0].usbd );

    usleep(10000000);
    printf(".\n");
    usb_disconnect( usb[0].usbd );
    usleep(1000);

    printf("ncr %d\n", cur_crumb);
    usbd_dump_crumbs();
    DUMP_CRUMBS();

    return  0;
}

// 8408 =>len = 8
// 40006C80:  00 05  05 00  00 00 00 00   ea ea 00 00  00 00 00 00  ................
//          type req value  index leng
//40006C80:   80 06  00 01  00 00 08 00
// get descr

