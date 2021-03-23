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

#if defined(USB_OTG_TRACE) || defined(USB_TRACE)
#  define TRACE
#endif
#include <trace.h>



#define CONTROL_SIZE	64

#ifndef RX_FIFO_SIZE
#  define RX_FIFO_SIZE	256
#endif

#define EP_IS_ISO(otg, ep) 	(((otg->epo[ep & 0x7F].DOEPCTL >> 18) & 3) == 1)

static void usb_hs_phyc_init();
static void usb_reset(USB_OTG_t  *);

typedef struct {
    usbd_t *usbd;
    USB_OTG_t *otg;

    int bufsize;
    int bufnext;

    char readflag;

} usbotg_t;

static usbotg_t usbdev[N_USBD];

// unit 0 -> FS, 1 -> HS
// flags:
#define FLAG_HS_INTERNAL	0 // FS or HS
#define FLAG_HS_ULPI		1
#define FLAG_HS_FS		4 // full-speed on HS phy

static void
_wait(int cnt){
    while(cnt-->0){
        __asm("nop");
    }
}

void *
usb_init(struct Device_Conf *dev, usbd_t *usbd){
    int i    = dev->unit;
    int irq, cnt;
    const char *name;
    int mode = dev->flags;
    int phy   = 3; // default: internal FS PHY

    bzero(usbdev + i, sizeof(usbotg_t));
    usbdev[i].usbd = usbd;

    switch(dev->unit){
    case 0: // FS
        usbdev[i].otg = USB_OTG_FS_PERIPH_BASE;
        usbdev[i].bufsize = USB_FS_FIFOSIZE;
        irq = USB_FS_IRQN;
        _usb_otg_fs_init();
        name = "otgfs/fsphy";
        break;
    case 1: // HS
        usbdev[i].otg = USB_OTG_HS_PERIPH_BASE;
        usbdev[i].bufsize = USB_HS_FIFOSIZE;
        irq = USB_HS_IRQN;
        _usb_otg_hs_init();
        name = "otghs/fsphy";

        // is there an internal HS PHY? (F7x3)
#ifdef USBPHYC_BASE
        // XXX F732 has the phyc  but no phy (ulpi only)
        // (is a 732 a 733 that failed QA?)


        if( USBPHYC->LDO & 1 ){
            usb_hs_phyc_init();
            if( mode & FLAG_HS_FS ){
                name = "otghs/hsphy/fs";
                phy = 1; // FS on HS phy
            }else{
                name = "otghs/hsphy/hs";
                phy = 0; // HS on HS phy
            }
        }
#endif
        break;
    }

    USB_OTG_t *otg = usbdev[i].otg;

    /* wait for idle */
    while( otg->g.GRSTCTL & USB_OTG_GRSTCTL_AHBIDL == 0 ) {}


    if( dev->unit == 1 ){ // OTG-HS
        otg->g.GCCFG &= ~USB_OTG_GCCFG_PWRDWN;

        if( phy == 3 ){
            otg->g.GUSBCFG = USB_OTG_GUSBCFG_FDMOD | USB_OTG_GUSBCFG_PHYSEL // enable FS-phy
                //QQQ | (1 << 15) //USB_OTG_GUSBCFG_PHYLPCS
                | (9 << 10) | 4; /* trdt = minimum */
            _wait(168*25000);
        }else{
            // this bit is not documented:
            otg->g.GCCFG |= 1 << 23; // enable HS-phy

            otg->g.GUSBCFG = USB_OTG_GUSBCFG_FDMOD |
                // internal HS via utmi, 480MHz
                (9 << 10) | 4; /* trdt = minimum */
        }

        // XXX - F7 only?
        otg->g.GOTGCTL |= USB_OTG_GOTGCTL_BVALOEN | USB_OTG_GOTGCTL_BVALOVAL;

        if( phy == 3 ){
            otg->g.GCCFG |= USB_OTG_GCCFG_PWRDWN
#ifdef NOVBUSSENS
                // the newer + older usb peripherals have inverse behaviour of this bit
                | (1 << 21)  // AKA - VBDEN(newer periph) or NOVBUSSENS(older periph)
                // NB - several other bits in this register also vary, but not used in this code
#endif
                ;
        }

    }else{ // OTG-FS
        /* select internal PHY, device mode */
        otg->g.GUSBCFG = USB_OTG_GUSBCFG_FDMOD | USB_OTG_GUSBCFG_PHYSEL |
            (9 << 10) | 4; /* trdt = minimum */
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
    }

    usb_reset(otg);

    /* restart phy */
    otg->PCGCCTL &= ~0xFF;
    /* soft disconnect device */
    otg->d.DCTL |= USB_OTG_DCTL_SDIS;
    /* Setup USB FS speed and frame interval */
    otg->d.DCFG = (otg->d.DCFG & ~(USB_OTG_DCFG_PERSCHIVL | USB_OTG_DCFG_DSPD))
        | (0 << USB_OTG_DCFG_PERSCHIVL_Pos)
        | (2 << USB_OTG_DCFG_PFIVL_Pos)		// end-of-frame = 90%
        | (phy << USB_OTG_DCFG_DSPD_Pos);

    /* unmask interrupts */
    otg->d.DIEPMSK = USB_OTG_DIEPMSK_XFRCM;
    otg->g.GINTMSK  = USB_OTG_GINTMSK_USBRST |
        // USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_WUIM |
        USB_OTG_GINTMSK_IISOIXFRM |
        USB_OTG_GINTMSK_IEPINT | USB_OTG_GINTMSK_RXFLVLM |
        USB_OTG_GINTMSK_EOPFM
        //USB_OTG_GINTMSK_SOFM
        ;

    /* clear pending interrupts */
    otg->g.GINTSTS = 0xFFFFFFFF;
    /* unmask global interrupt */
    otg->g.GAHBCFG = USB_OTG_GAHBCFG_GINT | USB_OTG_GAHBCFG_TXFELVL;

    // QQQ - fifo sizes?
    /* setting max RX FIFO size */
    otg->g.GRXFSIZ = (RX_FIFO_SIZE >> 2);
    /* setting up EP0 TX FIFO SZ */
    otg->g.DIEPTXF0_HNPTXFSIZ = (RX_FIFO_SIZE >> 2) | ((CONTROL_SIZE >> 2) << 16);

    usbdev[i].bufnext = RX_FIFO_SIZE + CONTROL_SIZE;

    nvic_enable( irq, IPL_DISK );

    bootmsg("usb%d otg device %s @%x irq %d cid %x\n", i, name, otg, irq, otg->g.CID);

    trace_init();
    trace_crumb1("usbotg", "init", usbdev + i);

    return usbdev + i;
}

static void
usb_reset(USB_OTG_t  *otg){
    int cnt;

    /* wait for idle */
    while( (otg->g.GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0 ) {}

    otg->g.GRSTCTL |= USB_OTG_GRSTCTL_CSRST;
    cnt = 0;
    while( otg->g.GRSTCTL & USB_OTG_GRSTCTL_CSRST ) {
        if( cnt++ > 10000 ) break;
    }

}


#ifdef USBPHYC_BASE
static void
usb_hs_phyc_init(){
    int cnt;

    RCC->APB2ENR |= 1 << 31; // HS PHY
    RCC->AHB1ENR |= 1 << 30; // ulpi (NB - must not be enabled if using the FS phy)

    // enable ldo
    // the manual says "1 = disable LDO". the manual is wrong.
    USBPHYC->LDO |= (1 << 2);
    // wait for it
    while( (USBPHYC->LDO & (1<<1)) == 0 ){
        if( cnt++ > 500000 ) break;
    }

#if HSECLOCK == 12000000
    USBPHYC->PLL1 = 0;
#elif HSECLOCK == 12500000
    USBPHYC->PLL1 = 1 << 1;
#elif HSECLOCK == 16000000
    USBPHYC->PLL1 = 3 << 1;
#elif HSECLOCK == 24000000
    USBPHYC->PLL1 = 4 << 1;
#elif HSECLOCK == 25000000
    USBPHYC->PLL1 = 5 << 1;
#else
#  error "unsupported HSE frequency"
#endif

    USBPHYC->TUNE = 0x00000F13;

    // enable pll
    USBPHYC->PLL1 |= 1;
    // wait a "little while" (hardware botch - no bit to test)
    for(cnt=0; cnt<500000; cnt++){
        __asm("nop");
    }
}
#else
static void
usb_hs_phyc_init(){}
#endif

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
usb_speed(usbd_t *u){
    usbotg_t * usb = u->dev;

    switch( (usb->otg->d.DSTS & 6) >> 1 ){
    case 3:
        // this is the only value listed in the documentation (RM0431)
        return USB_SPEED_FULL;
    case 2:
        return USB_SPEED_LOW;
    case 1:
        return USB_SPEED_FULL; // FS on HS phy?
    case 0:
        return USB_SPEED_HIGH;
    }
}

uint64_t
usb_serialnumber(void){
    return fnv64_hash(R_UNIQUE, 12);
}

int
usb_connect(usbd_t *u){
    usbotg_t * usb = u->dev;
    trace_crumb3("usbotg", "connect", u, usb, usb->otg);
    usb->otg->d.DCTL &= ~USB_OTG_DCTL_SDIS;
    u->curr_state = USBD_STATE_CONNECT;
}

int
usb_disconnect(usbd_t *u){
    usbotg_t * usb = u->dev;
    usb->otg->d.DCTL |= USB_OTG_DCTL_SDIS;
    u->curr_state = USBD_STATE_INACTIVE;
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

    trace_crumb0("usbotg", "cf0");

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
            otg->epi[epa].DIEPCTL = /*USB_OTG_DIEPCTL_EPENA |*/ USB_OTG_DIEPCTL_CNAK |
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
            /*USB_OTG_DOEPCTL_EPENA |*/ USB_OTG_DOEPCTL_USBAEP |
            (t << 18) | size;

    }

    return 0;
}

static uint32_t *
get_fifo(usbotg_t *u, int epa){
    // fifo is uint32[] - <<(12 - 2)
    return u->otg->fifo + (epa << 10);
}

static void
_iso_cancel(USB_OTG_t *otg, int ep){

    if( otg->epi[ep].DIEPCTL & USB_OTG_DIEPCTL_EPENA ){
        // cancel pending xfer
        otg->epi[ep].DIEPCTL |= USB_OTG_DIEPCTL_SNAK;
        otg->epi[ep].DIEPCTL |= USB_OTG_DIEPCTL_EPDIS;

        // wait for disabled
        while( (otg->epi[ep].DIEPINT & (1<<1)) == 0 ) {}
        otg->epi[ep].DIEPINT |= 1<<1;

        // flush pending xfer
        otg->g.GRSTCTL = (ep << 6) | USB_OTG_GRSTCTL_TXFFLSH;
    }
}


static void
_iso_prepare(USB_OTG_t *otg, int ep){

    // set even/odd to match most recent SOF
    int frn = (otg->d.DSTS >> 8) & 0x3FFF;
    if( !(frn & 1) ){
        otg->epi[ep].DIEPCTL |= 1 << 29; // -> odd
    }else{
        otg->epi[ep].DIEPCTL |= 1 << 28; // -> even
    }

    if( otg->epi[ep].DIEPINT & (1<<4) ){
        // already missed the in token
        trace_crumb0("usbotg", "IITXFE");
    }
    
}

int
usb_send(usbd_t *u, int ep, const char *buf, int len){
    usbotg_t *usb = u->dev;
    USB_OTG_t *otg = usb->otg;

    ep &= 0x7F;
    if( len > u->epd[ep].bufsize ) len = u->epd[ep].bufsize;

    if( EP_IS_ISO(otg, ep) ){
        _iso_cancel(otg, ep);
        _iso_prepare(otg, ep);
    }

    if( ep && !(otg->epi[ep].DIEPCTL & USB_OTG_DIEPCTL_USBAEP) ) return -3;	// ep not enabled
    if( ep &&  (otg->epi[ep].DIEPCTL & USB_OTG_DIEPCTL_EPENA) )  return -2;	// ep currently sending

    volatile uint32_t *fifo = get_fifo(usb, ep);

    trace_fdata("usbotg", "send %d len %d; diepint %x, dtxfsts %x, fifo %x", 5, ep, len, otg->epi[ep].DIEPINT, otg->epi[ep].DTXFSTS, fifo);
    trace_crumb3("usbotg", "send", otg->epi[ep].DIEPTSIZ, otg->epi[ep].DIEPCTL, otg->g.DIEPTXF[ep - 1]);

    otg->epi[ep].DIEPTSIZ = 0;
    otg->epi[ep].DIEPTSIZ = (1 << 19) | len;
    otg->epi[ep].DIEPCTL  = (otg->epi[ep].DIEPCTL & ~USB_OTG_DIEPCTL_STALL) | USB_OTG_DIEPCTL_EPENA | USB_OTG_DIEPCTL_CNAK;
    trace_crumb4("usbotg", "send", otg->epi[ep].DIEPTSIZ, otg->epi[ep].DIEPCTL, otg->epi[ep].DTXFSTS, otg->epi[ep].DIEPINT);

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

    ep &= 0x7F;

    if( EP_IS_ISO(otg, ep) ){
        // isochronous - need to manually toggle even/odd bit
        if( otg->epo[ep].DOEPCTL & (1 << 16) ){
            otg->epo[ep].DOEPCTL |= 1 << 28; // odd -> even
        }else{
            otg->epo[ep].DOEPCTL |= 1 << 29; // even -> odd
        }
    }

    otg->epo[ep].DOEPCTL |= USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA;
}

void
usb_recv_nack(usbd_t *u, int ep){
    usbotg_t *usb = u->dev;
    USB_OTG_t *otg = usb->otg;

    trace_crumb2("usbotg", "nack", ep, otg->epo[ep & 0x7f].DOEPCTL & USB_OTG_DOEPCTL_NAKSTS );
    otg->epo[ep & 0x7f].DOEPCTL |= USB_OTG_DOEPCTL_SNAK;
}
int
usb_epinfo(usbd_t *u, int ep){
    usbotg_t *usb = u->dev;
    USB_OTG_t *otg = usb->otg;

    return otg->epo[ep & 0x7f].DOEPCTL;
}


int
usb_read(usbd_t *u, int ep, char *buf, int len){
    usbotg_t *usb = u->dev;
    USB_OTG_t *otg = usb->otg;

    ep &= 0x7F;
    volatile uint32_t *fifo = get_fifo(usb, ep);

    if( !(otg->g.GINTSTS & USB_OTG_GINTSTS_RXFLVL) ) return -1; // no data in fifo

    uint32_t rxs = otg->g.GRXSTSR;
    if( (rxs & USB_OTG_GRXSTSP_EPNUM) != ep ) return -1; // data is not for this ep

    rxs = otg->g.GRXSTSP;	// same data, pop
    int l = (rxs >> 4) & 0x7FF;

    int i;
    for(i=0; i<l; ){
        uint32_t v = *fifo;
        if( i >= len ){
            i += 4;
            continue; // read and discard if no space
        }
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
    USB_OTG_t *otg = u->otg;
    ep &= 0x7F;

    uint32_t rxs = otg->g.GRXSTSP;
    uint32_t *fifo = get_fifo(u, ep);
    int l = (rxs >> 4) & 0x7FF;

    trace_crumb2("usbotg", "drain", ep, l);

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

static void
usb_iiso_handler(usbotg_t *u){
    USB_OTG_t *otg = u->otg;
    int i;

    for(i=0; i<16; i++){
        if( EP_IS_ISO(otg, i) && (otg->epi[i].DIEPCTL & USB_OTG_DIEPCTL_EPENA) ){
            // iso ep - send did not complete
            _iso_cancel(otg, i);
            u->usbd->epd[i].wpending = 0;

            trace_crumb3("usbotg", "iiso", i, otg->epi[i].DIEPCTL, otg->epi[i].DIEPINT & (1<<4)); // 4=ITTXFE

            if( otg->epi[i].DIEPINT & (1<<4) ){
                int frn = (otg->d.DSTS >> 8) & 0x3FFF;
                kprintf("iitfxe %x\n", frn);
                otg->epi[i].DIEPINT |= (1<<4); // clear iitfxe
            }
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
    trace_crumb2("usbotg", "reset", u, u->usbd);
    usb_config_ep0(u->usbd);
    usbd_cb_reset(u->usbd);

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

    //trace_crumb2("usbotg",  "irq!", isr, isr & u->otg->g.GINTMSK);
    //kprintf("irq %x\n", isr);

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
    if( isr & USB_OTG_GINTSTS_IISOIXFR ){
        usb_iiso_handler(u);
        u->otg->g.GINTSTS = USB_OTG_GINTSTS_IISOIXFR;
    }

    if( isr & USB_OTG_GINTSTS_SOF ){
        //usbd_cb_sof(u->usbd);
        u->otg->g.GINTSTS = USB_OTG_GINTSTS_SOF;
    }

    if( isr & USB_OTG_GINTSTS_EOPF ){
        usbd_cb_sof(u->usbd);
        u->otg->g.GINTSTS = USB_OTG_GINTSTS_EOPF;
    }

    //u->otg->g.GINTSTS = 0xFFFFFFFF;
}


void
USB_FS_IRQ_HANDLER(void){
    otg_irq_handler(usbdev + 0);
}

void
USB_HS_IRQ_HANDLER(void){
    otg_irq_handler(usbdev + 1);
}


#ifdef KTESTING

DEFUN(usbtest, "usb test")
{

    printf("usb: %x pma: %x\n", USB_OTG_FS_PERIPH_BASE, USB_OTG_FS->fifo);

    usb_send(usbdev[0].usbd, 0x8081, "XYZ=", 3);
    return 0;

    usb_disconnect(usbdev[0].usbd );
    sleep(1);

    trace_reset();
    usb_connect( usbdev[0].usbd );

    usleep(10000000);
    printf(".\n");
    usb_disconnect( usbdev[0].usbd );
    usleep(1000);

    trace_dump(0, 0);

    return  0;
}

DEFUN(xusbinfo, "usb test")
{

    trace_dump(0, 0);
    trace_reset();

    return 0;
}

DEFUN(usbinfo, "test")
{
    int n = 0;
    if( argc > 1 ){
        n = atoi( argv[1] );
        argc --;
        argv ++;
    }

    usbotg_t *u = usbdev + n;
    USB_OTG_t *otg = u->otg;

    printf("usb %d (%x)\n", n, otg);
    printf("gccfg:  %08x\n", otg->g.GCCFG);
    printf("rstctl: %08x\n", otg->g.GRSTCTL);
    printf("gotctl: %08x\n", otg->g.GOTGCTL);
    printf("gotint: %08x\n", otg->g.GOTGINT);
    printf("guscfg: %08x\n", otg->g.GUSBCFG);
    printf("intsts: %08x\n", otg->g.GINTSTS);
    printf("devsts: %08x\n", otg->d.DSTS);	// 22,23 = DM,DP
    printf("devctl: %08x\n", otg->d.DCTL);
    printf("rxstsr: %08x\n", otg->g.GRXSTSR);
#ifdef USBPHYC
    printf("phyc: %x\n", USBPHYC);
    printf("pll1: %08x ldo: %08x\n", USBPHYC->PLL1, USBPHYC->LDO);
#endif

    return 0;
}

#ifdef USBPHYC
DEFUN(plltest, "")
{
    int n;
    if( argc > 1 ){
        n = atoi( argv[1] );
    }


    USBPHYC->PLL1 |= 1;
    for(n=0; n<500000; n++){
        if( USBPHYC->PLL1 & 1 ) break;
    }

    printf("n: %d\n", n);

    //USBPHYC->LDO = n;
    //sleep(1);
    printf("pll1: %08x ldo: %08x\n", USBPHYC->PLL1, USBPHYC->LDO);

    return 0;
}
#endif

DEFUN(epinfo, "test")
{
    int n = 0;
    if( argc > 1 ){
        n = atoi( argv[1] );
        argc --;
        argv ++;
    }

    usbotg_t *u = usbdev + n;
    USB_OTG_t *otg = u->otg;
    int ep = 1;

    if( argc > 1 )
        ep = atoi( argv[1] );

    printf("usb %d (%x); ep#: %d\n", n, otg, ep);

    printf("ctl: in %08x out %08x\n", otg->epi[ep].DIEPCTL,  otg->epo[ep].DOEPCTL);
    printf("siz: in %08x out %08x\n", otg->epi[ep].DIEPTSIZ, otg->epo[ep].DOEPTSIZ);
    printf("sts: in %x\n", otg->epi[ep].DTXFSTS);	// amount of free space in tx fifo. words
    printf("int: in %08x out %08x\n", otg->epi[ep].DIEPINT,   otg->epo[ep].DOEPINT);
    printf("txf: in %08x\n", ep ? otg->g.DIEPTXF[ep - 1] : otg->g.DIEPTXF0_HNPTXFSIZ);

    return 0;
}

DEFUN(hstest, "test")
{
    int x;

    USB_OTG_t *otg = USB_OTG_HS_PERIPH_BASE;

#if 0
    RCC->AHB1ENR |= 1 << 29;
    // do not actually config the pins


    /* select Internal PHY */
    otg->g.GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL;
    /* wait for idle */
    printf("waiting...");
    while( otg->g.GRSTCTL & USB_OTG_GRSTCTL_AHBIDL == 0 ) {
        usleep(10000);
    }
    /* reset */
    printf("waiting...");
    otg->g.GRSTCTL |= USB_OTG_GRSTCTL_CSRST;
    while( otg->g.GRSTCTL & USB_OTG_GRSTCTL_CSRST ) {
        usleep(10000);
    }
#endif

    printf("devsts: %08x\n", otg->d.DSTS);	// 22,23 = DM,DP

    gpio_init( GPIO_A11, GPIO_OUTPUT | GPIO_PUSH_PULL );
    gpio_init( GPIO_A12, GPIO_OUTPUT | GPIO_PUSH_PULL );

    gpio_set( GPIO_A11 );
    gpio_set( GPIO_A12 );

    usleep( 10000 );
    printf("devsts: %08x\n", otg->d.DSTS);	// 22,23 = DM,DP
    usleep( 10000 );

    gpio_init( GPIO_A11, GPIO_INPUT );
    gpio_init( GPIO_A12, GPIO_INPUT );

    return 0;
}

#endif

