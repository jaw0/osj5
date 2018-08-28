/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-15 22:29 (EDT)
  Function: usb otg full-speed + high-speed

*/

#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <dev.h>
#include <stm32.h>
#include <gpio.h>
#include <usbdef.h>
#include <usbotg_impl.h>
#include <usbotg.h>
#include <usbd.h>
#include <userint.h>

//#define TRACE
#include <trace.h>


#define CONTROL_SIZE	64
#define RX_FIFO_SIZE	256



typedef struct {
    usbd_t *usbd;
    USB_OTG_t *otg;

    int bufsize;
    int bufnext;

    char readflag;

} usbotg_t;

static usbotg_t usb[N_USBD];

// unit 0 -> FS, 1 -> HS

void *
usb_init(struct Device_Conf *dev, usbd_t *usbd){
    int i    = dev->unit;
    int irq;
    const char *name;

    bzero(usb + i, sizeof(usbotg_t));
    usb[i].usbd = usbd;

    switch(i){
    case 0: // FS
        usb[i].otg = USB_OTG_FS_PERIPH_BASE;
        usb[i].bufsize = USB_FS_FIFOSIZE;
        irq = USB_FS_IRQN;
        _usb_otg_fs_init();
        name = "full-speed";
        break;
    case 1: // HS
        usb[i].otg = USB_OTG_HS_PERIPH_BASE;
        usb[i].bufsize = USB_HS_FIFOSIZE;
        irq = USB_HS_IRQN;
        _usb_otg_hs_init();
        name = "high-speed";
        // QQQ - using: FS PHY, ULPI (FS or HS), I2C (FS) ?
        break;
    }


    USB_OTG_t *otg = usb[i].otg;

    /* select Internal PHY */
    otg->g.GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL;
    /* wait for idle */
    while( otg->g.GRSTCTL & USB_OTG_GRSTCTL_AHBIDL == 0 ) {}
    /* reset */
    otg->g.GRSTCTL |= USB_OTG_GRSTCTL_CSRST;
    while( otg->g.GRSTCTL & USB_OTG_GRSTCTL_CSRST ) {}
    /* set device mode */
    otg->g.GUSBCFG = USB_OTG_GUSBCFG_FDMOD | USB_OTG_GUSBCFG_PHYSEL |
        (6 << 10); /* trdt = minimum */

    /* override Vbus sense */
    otg->g.GOTGCTL |= USB_OTG_GOTGCTL_BVALOEN | USB_OTG_GOTGCTL_BVALOVAL;
    /* activate transceiver */
    otg->g.GCCFG = USB_OTG_GCCFG_PWRDWN
#ifdef NOVBUSSENS
        // the newer + older usb peripherals have inverse behaviour of this bit
        | (1 << 21)  // AKA - VBDEN(newer periph) or NOVBUSSENS(older periph)
        // NB - several other bits in this register also vary, but not used in this code
#endif
        ;

    /* restart phy */
    otg->PCGCCTL = 0;
    /* soft disconnect device */
    otg->d.DCTL |= USB_OTG_DCTL_SDIS;
    /* Setup USB FS speed and frame interval */
    otg->d.DCFG = (otg->d.DCFG & ~(USB_OTG_DCFG_PERSCHIVL | USB_OTG_DCFG_DSPD))
        | (0 << USB_OTG_DCFG_PERSCHIVL_Pos)
        | (3 << USB_OTG_DCFG_DSPD_Pos); /* full-speed */

    /* unmask interrupts */
    otg->d.DIEPMSK = USB_OTG_DIEPMSK_XFRCM;
    otg->g.GINTMSK  = USB_OTG_GINTMSK_USBRST |
        // USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_WUIM |
        USB_OTG_GINTMSK_IEPINT | USB_OTG_GINTMSK_RXFLVLM;

    /* clear pending interrupts */
    otg->g.GINTSTS = 0xFFFFFFFF;
    /* unmask global interrupt */
    otg->g.GAHBCFG = USB_OTG_GAHBCFG_GINT;

    // QQQ - fifo sizes?
    /* setting max RX FIFO size */
    otg->g.GRXFSIZ = (RX_FIFO_SIZE >> 2);
    /* setting up EP0 TX FIFO SZ */
    otg->g.DIEPTXF0_HNPTXFSIZ = (RX_FIFO_SIZE >> 2) | ((CONTROL_SIZE >> 2) << 16);

    usb[i].bufnext = RX_FIFO_SIZE + CONTROL_SIZE;


    nvic_enable( irq, IPL_DISK );

    bootmsg("usb otg device %s\n", name);

    trace_init( 8 * 1024 ); // XXX

    return usb + i;
}

static int
pma_alloc(usbotg_t *u, int size){
    int p = u->bufnext;
    u->bufnext += size;

    if( u->bufnext >= u->bufsize ){
        kprintf("usb pma full! size %d, nxt %x\n", size, u->bufnext);
        return -1;
    }
    return p;
}

static inline void
set_pma_tx(usbotg_t *u, int epa, int addr, int cnt){

    // nb. the manual is wrong. size + addr are in units of words
    u->otg->g.DIEPTXF[epa - 1] = ((cnt >> 2) << 16) | (addr >> 2);
    trace_crumb2("usbotg", "pma", epa, addr);
}

int
usb_serialnumber(void){
    return djb2_hash(R_UNIQUE, 12);
}

int
usb_connect(usbd_t *u){
    usbotg_t * usb = u->dev;
    usb->otg->d.DCTL &= ~USB_OTG_DCTL_SDIS;
}

int
usb_disconnect(usbd_t *u){
    usbotg_t * usb = u->dev;
    usb->otg->d.DCTL |= USB_OTG_DCTL_SDIS;
}

void
usb_enable_suspend(usbd_t *u){
    usbotg_t * usb = u->dev;
    usb->otg->g.GINTMSK |= USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_WUIM;
}

void
usb_set_addr1(usbd_t *u, int addr){
    usbotg_t * usb = u->dev;

    usb->otg->d.DCFG = (usb->otg->d.DCFG & ~USB_OTG_DCFG_DAD) | (addr << 4);

    // trace_reset();
    trace_crumb1( "usbotg", "addr", addr );
}

void
usb_set_addr2(usbd_t *u, int addr){
    // nop
}

void
usb_stall(usbd_t *u, int ep){
    usbotg_t * usb = u->dev;
    int epa = ep & 0x7f;

    trace_crumb1("usbotg", "stall", ep);

    if( ep & 0x80 ){
        usb->otg->epi[epa].DIEPCTL |= USB_OTG_DIEPCTL_STALL;
    }else{
        usb->otg->epo[epa].DOEPCTL |= USB_OTG_DOEPCTL_STALL;
    }
}

void
usb_unstall(usbd_t *u, int ep){
    usbotg_t * usb = u->dev;
    int epa = ep & 0x7f;

    if( ep & 0x80 ){
        usb->otg->epi[epa].DIEPCTL = (usb->otg->epi[epa].DIEPCTL & ~USB_OTG_DIEPCTL_STALL) |
            USB_OTG_DIEPCTL_SD0PID_SEVNFRM | USB_OTG_DOEPCTL_SNAK;
    }else{
        usb->otg->epo[epa].DOEPCTL = (usb->otg->epo[epa].DOEPCTL & ~USB_OTG_DOEPCTL_STALL) |
            USB_OTG_DOEPCTL_SD0PID_SEVNFRM | USB_OTG_DOEPCTL_CNAK;
    }
}

int
usb_isstalled(usbd_t *u, int ep){
    usbotg_t * usb = u->dev;
    int epa = ep & 0x7f;

    if( ep & 0x80 ){
        return usb->otg->epi[epa].DIEPCTL & USB_OTG_DIEPCTL_STALL;
    }
    return usb->otg->epo[epa].DOEPCTL & USB_OTG_DOEPCTL_STALL;
}

static void
usb_config_ep0(usbd_t *u){
    usbotg_t *usb = u->dev;

    /* enabling RX and TX interrupts from EP0 */
    usb->otg->d.DAINTMSK |= 0x00010001;
    /* setting up EP0 TX and RX registers */
    usb->otg->epi[0].DIEPCTL = USB_OTG_DIEPCTL_SNAK;
    /* 1 setup packet, 1 packets total */
    usb->otg->epo[0].DOEPTSIZ = CONTROL_SIZE | (1 << 29) | (1 << 19);
    usb->otg->epo[0].DOEPCTL  = USB_OTG_DOEPCTL_EPENA | USB_OTG_DOEPCTL_CNAK;

    u->epd[0].bufsize = CONTROL_SIZE;

}


int
usb_config_ep(usbd_t *u, int ep, int type, int size){
    usbotg_t *usb = u->dev;
    USB_OTG_t *otg = usb->otg;
    int epa = ep & 0xF;

    u->epd[epa].bufsize = size;

    trace_fdata("usbotg", "epcf %d type %d size %d", 3, ep, type, size);

    if (ep & 0x80) {
        int buf;
        int asize = size;

        if( type == UE_ISOCHRONOUS ){
            asize <<= 1;
        }

        buf = pma_alloc(usb, asize);
        if( buf == - 1 ) return -1;

        set_pma_tx(usb, epa, buf, asize);

        otg->d.DAINTMSK |= (1 << epa);	// enable TX interrupt

        switch( type ){
        case UE_ISOCHRONOUS:
            otg->epi[epa].DIEPCTL = USB_OTG_DIEPCTL_EPENA | USB_OTG_DIEPCTL_CNAK |
                USB_OTG_DIEPCTL_SD0PID_SEVNFRM | USB_OTG_DIEPCTL_USBAEP |
                           (1 << 18) | (epa << 22) | size;
            break;
        case UE_BULK:
            otg->epi[epa].DIEPCTL = USB_OTG_DIEPCTL_SNAK |
                USB_OTG_DIEPCTL_SD0PID_SEVNFRM | USB_OTG_DIEPCTL_USBAEP |
                            (2 << 18) | (epa << 22) | size;
            break;
        default:
            otg->epi[epa].DIEPCTL = USB_OTG_DIEPCTL_SNAK |
                USB_OTG_DIEPCTL_SD0PID_SEVNFRM | USB_OTG_DIEPCTL_USBAEP |
                            (3 << 18) | (epa << 22) | size;
            break;
        }

        trace_crumb2("usbotg", "cftx", ep, otg->epi[epa].DIEPCTL);

    }else{
        int t;
        switch( type ){
        case UE_ISOCHRONOUS:
            t = 1; break;
        case UE_BULK:
            t = 2; break;
        default:
            t = 3; break;
        }

        otg->epo[epa].DOEPCTL = USB_OTG_DOEPCTL_SD0PID_SEVNFRM | USB_OTG_DOEPCTL_CNAK |
            USB_OTG_DOEPCTL_EPENA | USB_OTG_DOEPCTL_USBAEP |
            (t << 18) | size;

    }

    return 0;
}

static uint32_t *
get_fifo(usbotg_t *u, int epa){
    // fifo is uint32[] - <<(12 - 2)
    return u->otg->fifo + (epa << 10);
}

int
usb_send(usbd_t *u, int ep, const char *buf, int len){
    usbotg_t *usb = u->dev;
    USB_OTG_t *otg = usb->otg;

    ep &= 0x7F;
    if( len > u->epd[ep].bufsize ) len = u->epd[ep].bufsize;
    if( ep && !(otg->epi[ep].DIEPCTL & USB_OTG_DIEPCTL_USBAEP) ) return 0;	// ep not enabled
    if( ep &&  (otg->epi[ep].DIEPCTL & USB_OTG_DIEPCTL_EPENA) )  return 0;	// ep currently sending

    volatile uint32_t *fifo = get_fifo(usb, ep);

    trace_fdata("usbotg", "send %d len %d; diepint %x, dtxfsts %x, fifo %x", 5, ep, len, otg->epi[ep].DIEPINT, otg->epi[ep].DTXFSTS, fifo);
    trace_crumb3("usbotg", "send", otg->epi[ep].DIEPTSIZ, otg->epi[ep].DIEPCTL, otg->g.DIEPTXF[ep - 1]);

    otg->epi[ep].DIEPTSIZ = 0;
    otg->epi[ep].DIEPTSIZ = (1 << 19) | len;
    otg->epi[ep].DIEPCTL  = (otg->epi[ep].DIEPCTL & ~USB_OTG_DIEPCTL_STALL) | USB_OTG_DIEPCTL_EPENA | USB_OTG_DIEPCTL_CNAK;
    trace_crumb2("usbotg", "send", otg->epi[ep].DIEPTSIZ, otg->epi[ep].DIEPCTL);

    int i;
    for(i=0; i<len; i+=4){
        *fifo = buf[i] | (buf[i+1]<<8) | (buf[i+2]<<16) | (buf[i+3]<<24);
    }

    trace_crumb4("usbotg", "send", otg->epi[ep].DIEPTSIZ, otg->epi[ep].DIEPCTL, otg->epi[ep].DTXFSTS, otg->epi[ep].DIEPINT);
    return len;
}

void
usb_recv_ack(usbd_t *u, int ep){
    usbotg_t *usb = u->dev;
    USB_OTG_t *otg = usb->otg;

    trace_crumb1("usbotg", "ack", ep);
    otg->epo[ep & 0x7f].DOEPCTL |= USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA;
}

int
usb_read(usbd_t *u, int ep, char *buf, int len){
    usbotg_t *usb = u->dev;
    USB_OTG_t *otg = usb->otg;

    ep &= 0x7F;
    uint32_t *fifo = get_fifo(usb, ep); // QQQ

    if( !(otg->g.GINTSTS & USB_OTG_GINTSTS_RXFLVL) ) return -1; // no data in fifo

    uint32_t rxs = otg->g.GRXSTSR;
    if( (rxs & USB_OTG_GRXSTSP_EPNUM) != ep ) return -1; // data is not for this ep

    rxs = otg->g.GRXSTSP;	// same data, pop
    int l = (rxs >> 4) & 0x7FF;

    int i;
    for(i=0; i<l; ){
        uint32_t v = *fifo;
        if( i >= len ) continue; // read and discard if no space
        buf[i++] = v & 0xFF;
        buf[i++] = (v >> 8) & 0xFF;
        buf[i++] = (v >> 16) & 0xFF;
        buf[i++] = (v >> 24) & 0xFF;
    }

    usb->readflag = 1;
    return l;
}

static void
usb_drain(usbotg_t *u, int ep){
    USB_OTG_t *otg = usb->otg;
    ep &= 0x7F;

    uint32_t rxs = otg->g.GRXSTSP;
    uint32_t *fifo = get_fifo(u, ep);
    int l = (rxs >> 4) & 0x7FF;

    int i;
    for(i=0; i<l; i+=4){
        uint32_t v = *fifo;
    }
}


static void
usb_tx_handler(usbotg_t *u){
    int i;

    for(i=0; i<16; i++){
        if( u->otg->epi[i].DIEPINT & USB_OTG_DIEPINT_XFRC ){
            u->otg->epi[i].DIEPINT = USB_OTG_DIEPINT_XFRC;

            trace_crumb1("usbotg", "txc", i);
            usbd_cb_send_complete(u->usbd, i);
        }
    }
}

static const char *rxinfo[] = {
    "rx/0", "rx/NAK", "rx/out", "rx/out!", "rx/setup!", "rx/5", "rx/setup", "rx/7",
    "rx/8", "rx/9", "rx/A", "rx/B", "rx/C", "rx/D", "rx/E", "rx/F"
};

static void
usb_rx_handler(usbotg_t *u){

    while( u->otg->g.GINTSTS & USB_OTG_GINTSTS_RXFLVL ){

        uint32_t rxs = u->otg->g.GRXSTSR;
        int ep  = rxs & 0xF;
        int len = (rxs >> 4)  & 0x7FF;
        int pt  = (rxs >> 17) & 0xF;

        //kprintf("rx %x: %x %x %x\n", rxs, ep, pt, len);

        u->readflag = 0;

        trace_crumb2("usbotg", rxinfo[pt], ep, len);

        switch( pt ){
        case 2:
            usbd_cb_recv(u->usbd, ep, len);
            if( !u->readflag ) usb_drain(u, ep);
            break;
        case 6:
            usbd_cb_recv_setup(u->usbd, len);
            if( !u->readflag ) usb_drain(u, ep);
            break;
        default:
            rxs = u->otg->g.GRXSTSP; // pop + discard
        }
    }
}

static void
usb_reset_handler(usbotg_t *u){

    u->otg->g.GRSTCTL |= USB_OTG_GRSTCTL_RXFFLSH; // flush rx

    u->bufnext = RX_FIFO_SIZE + CONTROL_SIZE;
    usb_config_ep0(u->usbd);
    usbd_cb_reset(u->usbd);

    trace_crumb1("usbotg", "reset", 0);
}

static void
usb_suspend_handler(usbotg_t *u){

    if( !(u->otg->g.GINTMSK & USB_OTG_GINTMSK_USBSUSPM) ) return;

    trace_crumb1("usbotg", "susp", 0);
    usbd_cb_suspend(u->usbd);
}

static void
usb_wakeup_handler(usbotg_t *u){

    usbd_cb_wakeup(u->usbd);
}


static void
otg_irq_handler(usbotg_t *u){
    int isr = u->otg->g.GINTSTS;

    trace_crumb1("usbotg",  "irq!", isr);

    if( isr & USB_OTG_GINTSTS_USBRST ){
        usb_reset_handler(u);
        u->otg->g.GINTSTS = USB_OTG_GINTSTS_USBRST;
    }

    if( isr & USB_OTG_GINTSTS_USBSUSP ){
        usb_suspend_handler(u);
        u->otg->g.GINTSTS = USB_OTG_GINTSTS_USBSUSP;
    }

    if( isr & USB_OTG_GINTSTS_WKUINT ){
        usb_wakeup_handler(u);
        u->otg->g.GINTSTS = USB_OTG_GINTSTS_WKUINT;
    }

    if( isr & USB_OTG_GINTSTS_IEPINT ){
        usb_tx_handler(u);
    }
    if( isr & USB_OTG_GINTSTS_RXFLVL ){
        usb_rx_handler(u);
    }

    u->otg->g.GINTSTS = 0xFFFFFFFF;

}


void
USB_FS_IRQ_HANDLER(void){
    otg_irq_handler(usb + 0);
}

void
USB_HS_IRQ_HANDLER(void){
    otg_irq_handler(usb + 1);
}


DEFUN(usbtest, "usb test")
{

    printf("usb: %x pma: %x\n", USB_OTG_FS_PERIPH_BASE, USB_OTG_FS->fifo);

    usb_send(usb[0].usbd, 0x8081, "XYZ=", 3);
    return 0;

    usb_disconnect(usb[0].usbd );
    sleep(1);

    trace_reset();
    usb_connect( usb[0].usbd );

    usleep(10000000);
    printf(".\n");
    usb_disconnect( usb[0].usbd );
    usleep(1000);

    trace_dump(0);

    return  0;
}

DEFUN(usbinfo, "usb test")
{

    trace_dump(0);
    trace_reset();

    return 0;
}

DEFUN(epinfo, "test")
{
    usbotg_t *u = usb;
    USB_OTG_t *otg = u->otg;
    int ep = 1;

    if( argc > 1 )
        ep = atoi( argv[1] );

    printf("ep#: %d\n", ep);

    printf("ctl: %x\n", otg->epi[ep].DIEPCTL);
    printf("siz: %x\n", otg->epi[ep].DIEPTSIZ);
    printf("sts: %x\n", otg->epi[ep].DTXFSTS);	// amount of free space in tx fifo. words
    printf("int: %x\n", otg->epi[ep].DIEPINT);
    printf("txf: %x\n", otg->g.DIEPTXF[ep - 1]);

    return 0;
}
