/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-19 14:04 (EDT)
  Function: usb/cdc virtual com port

*/

#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <msgs.h>
#include <queue.h>
#include <dev.h>
#include <usbd.h>
#include <usbdef.h>
#include <usbcdc.h>
#include <userint.h>

#if defined(USB_VCP_TRACE) || defined(USB_TRACE)
# define TRACE
#endif
#include <trace.h>



#define CDC_FSSIZE    64
#define CDC_HSSIZE    512

#define CDC_RXD_EP  0x01
#define CDC_TXD_EP  0x81
#define CDC_NTF_EP  0x82
#define CDC_COMM_IFACE 0
#define CDC_DATA_IFACE 1

#define CDC_NTF_SZ  CDC_FSSIZE

#define RX_QUEUE_SIZE	CDC_HSSIZE

#ifndef VCP_QUEUE_SIZE
# define TX_QUEUE_SIZE	CDC_FSSIZE
#else
# define TX_QUEUE_SIZE	VCP_QUEUE_SIZE
#endif

#ifndef VCP_RXBUF_SIZE
# define VCP_RXBUF_SIZE CDC_HSSIZE
#endif

#ifndef VCP_TXBUF_SIZE
# define VCP_TXBUF_SIZE CDC_FSSIZE
#endif

#ifndef VCP_NTBUF_SIZE
# define VCP_NTBUF_SIZE CDC_FSSIZE
#endif


#define ALIGN2 __attribute__ ((aligned (2)))

static const usb_device_descriptor_t cdc_dev_desc ALIGN2  = {
    .bLength            = sizeof(usb_device_descriptor_t),
    .bDescriptorType    = USB_DTYPE_DEVICE,
    .bcdUSB             = UD_USB_2_0,
    .bDeviceClass       = USB_CLASS_CDC,
    .bDeviceSubClass    = 0,
    .bDeviceProtocol    = 0,
    .bMaxPacketSize     = CONTROLSIZE,
    .idVendor           = USB_VENDOR,
    .idProduct          = USB_PRODUCT,
    .bcdDevice          = USB_DEVICE,
    .iManufacturer      = 1,
    .iProduct           = 2,
    .iSerialNumber      = SERIALNO_IDX,
    .bNumConfigurations = 1,
};

struct cdc_config {
    usb_config_descriptor_t     config;
    usb_interface_descriptor_t  comm;
    usb_cdc_header_descriptor_t cdc_hdr;
    usb_cdc_cm_descriptor_t     cdc_mgmt;
    usb_cdc_acm_descriptor_t    cdc_acm;
    usb_cdc_union_descriptor_t  cdc_union;
    usb_endpoint_descriptor_t   comm_ep;
    usb_interface_descriptor_t  data;
    usb_endpoint_descriptor_t   data_eprx;
    usb_endpoint_descriptor_t   data_eptx;
};

static const struct cdc_config cdc_config ALIGN2 = {

    .config                  = {
        .bLength             = sizeof(usb_config_descriptor_t),
        .bDescriptorType     = USB_DTYPE_CONFIGURATION,
        .wTotalLength        = sizeof(struct cdc_config),
        .bNumInterface       = 2,
        .bConfigurationValue = 1,
        .iConfiguration      = 0,
        .bmAttributes        = 0x80,
        .bMaxPower           = 50,
    },
    .comm                    = {
        .bLength             = sizeof(usb_interface_descriptor_t),
        .bDescriptorType     = USB_DTYPE_INTERFACE,
        .bInterfaceNumber    = 0,
        .bAlternateSetting   = 0,
        .bNumEndpoints       = 1,
        .bInterfaceClass     = USB_CLASS_CDC,
        .bInterfaceSubClass  = UDESCSUB_CDC_ACM,
        .bInterfaceProtocol  = USB_CDC_PROTO_V25TER,
        .iInterface          = USB_NO_DESCRIPTOR,
    },
    .cdc_hdr                 = {
        .bLength             = sizeof(usb_cdc_header_descriptor_t),
        .bDescriptorType     = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubtype  = UDESCSUB_CDC_HEADER,
        .bcdCDC              = 0x0110,
    },
    .cdc_mgmt                = {
        .bLength             = sizeof(usb_cdc_cm_descriptor_t),
        .bDescriptorType     = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubtype  = UDESCSUB_CDC_CM,
        .bmCapabilities      = 0,
        .bDataInterface      = 1,
    },
    .cdc_acm                 = {
        .bLength             = sizeof(usb_cdc_acm_descriptor_t),
        .bDescriptorType     = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubtype  = UDESCSUB_CDC_ACM,
        .bmCapabilities      = 6,
    },
    .cdc_union               = {
        .bLength             = sizeof(usb_cdc_union_descriptor_t),
        .bDescriptorType     = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubtype  = UDESCSUB_CDC_UNION,
        .bMasterInterface    = 0,
        .bSlaveInterface[0]  = 1,
    },
    .comm_ep                 = {
        .bLength             = sizeof(usb_endpoint_descriptor_t),
        .bDescriptorType     = USB_DTYPE_ENDPOINT,
        .bEndpointAddress    = CDC_NTF_EP,
        .bmAttributes        = UE_INTERRUPT,
        .wMaxPacketSize      = CDC_NTF_SZ,
        .bInterval           = 0xFF,
    },
    .data                    = {
        .bLength             = sizeof(usb_interface_descriptor_t),
        .bDescriptorType     = USB_DTYPE_INTERFACE,
        .bInterfaceNumber    = 1,
        .bAlternateSetting   = 0,
        .bNumEndpoints       = 2,
        .bInterfaceClass     = USB_CLASS_CDC_DATA,
        .bInterfaceSubClass  = USB_SUBCLASS_NONE,
        .bInterfaceProtocol  = USB_PROTO_NONE,
        .iInterface          = USB_NO_DESCRIPTOR,
    },
    .data_eprx               = {
        .bLength             = sizeof(usb_endpoint_descriptor_t),
        .bDescriptorType     = USB_DTYPE_ENDPOINT,
        .bEndpointAddress    = CDC_RXD_EP,
        .bmAttributes        = UE_BULK,
        .wMaxPacketSize      = CDC_FSSIZE,
        .bInterval           = 0,
    },
    .data_eptx               = {
        .bLength             = sizeof(usb_endpoint_descriptor_t),
        .bDescriptorType     = USB_DTYPE_ENDPOINT,
        .bEndpointAddress    = CDC_TXD_EP,
        .bmAttributes        = UE_BULK,
        .wMaxPacketSize      = CDC_FSSIZE,
        .bInterval           = 0,
    },

};

static const usb_device_qualifier_t device_qualifier = {
    .bLength            = sizeof(usb_device_qualifier_t),
    .bDescriptorType    = USB_DTYPE_QUALIFIER,
    .bcdUSB             = 0x200,
    .bDeviceClass       = 0,
    .bDeviceSubClass    = 0,
    .bDeviceProtocol    = 0,
    .bMaxPacketSize     = 0,
    .bNumConfigurations = 1,
};

struct VCP;
void vcp_tx_complete(struct VCP *, int);
void vcp_ntf_complete(struct VCP *, int);
void vcp_recv_chars(struct VCP*, int, int);
void vcp_reset(struct VCP *);
void vcp_configure(struct VCP *);
int  vcp_recv_setup(struct VCP*, const char *, int);
static void maybe_tx(struct VCP* p);

static const usb_wdata_descriptor_t lang_desc      ALIGN2 = { 4,  USB_DTYPE_STRING, USB_LANG_EN_US };
USB_DESCR(cdc_manuf_desc, USB_MANUF_DESC);
USB_DESCR(cdc_prod_desc,  USB_PROD_DESC);


static const usbd_config_t cdc_usbd_config = {
    .cb_reset       = vcp_reset,
    .cb_configure   = vcp_configure,
    .cb_tx_complete = { [CDC_TXD_EP & 0x7f] = vcp_tx_complete, [CDC_NTF_EP & 0x7f] = vcp_ntf_complete },
    .cb_recv_setup  = vcp_recv_setup,
    .cb_recv = { [CDC_RXD_EP & 0x7f] = vcp_recv_chars },

    .dmap = {
        { USB_SPEED_ANY,  (USB_DTYPE_DEVICE<<8),	0, &cdc_dev_desc },
        { USB_SPEED_ANY,  (USB_DTYPE_CONFIGURATION<<8),	sizeof(cdc_config), &cdc_config },
        { USB_SPEED_ANY,  (USB_DTYPE_STRING<<8) | 0,	0, &lang_desc },

        { USB_SPEED_ANY,  (USB_DTYPE_QUALIFIER<<8),     0, &device_qualifier },
        { USB_SPEED_ANY,  (USB_DTYPE_OTHERSPEED<<8),	sizeof(cdc_config), &cdc_config },

        { USB_SPEED_ANY,  (USB_DTYPE_STRING<<8) | 1,	0, &cdc_manuf_desc },
        { USB_SPEED_ANY,  (USB_DTYPE_STRING<<8) | 2,	0, &cdc_prod_desc },
        {0, 0, 0, 0},
    }
};



static int vcp_putchar(FILE*, char);
static int vcp_write(FILE*, const char *, int);
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
    vcp_write,
    0,
    0,
    0,
    0
};


static struct VCP {
    FILE file;
    void *pdev;
    usbd_t *usbd;

    usb_cdc_line_state_t line_state;
    struct queue rxq, txq;
    char rxbuf[ VCP_RXBUF_SIZE ];
    char txbuf[ VCP_TXBUF_SIZE ];
    char ntbuf[ VCP_NTBUF_SIZE ];
    char nt2buf[ VCP_NTBUF_SIZE ];

    uint8_t rblen, tblen, ntlen, nt2len;
    uint8_t ready;
    uint8_t is_hs;

} vcom[ N_VCP ];

FILE *vcp0_port = 0;

int
vcp_init(struct Device_Conf *dev){

    int i = dev->unit;
    struct VCP *v = vcom + i;

    bzero( v, sizeof(struct VCP));

    finit( & v->file );
    v->file.fs = &vcp_port_fs;
    v->file.codepage = CODEPAGE_UTF8;
    v->file.d  = (void*)v;
    queue_init( &v->rxq, RX_QUEUE_SIZE );
    queue_init( &v->txq, TX_QUEUE_SIZE );

    v->line_state = (usb_cdc_line_state_t){
        .dwDTERate          = 115200,
        .bCharFormat        = UCDC_STOP_BIT_1,
        .bParityType        = UCDC_PARITY_NONE,
        .bDataBits          = 8,
    };

    usbd_t *u = usbd_get( dev->port );
    v->usbd = u;
    trace_init();

#if !defined(USE_VCPMSC) && !defined(USE_USBCOMP)
    usbd_configure( u, &cdc_usbd_config, vcom + i );
    usb_connect( u );
#endif

    bootmsg("%s cdc/vcp on usb%d\n", dev->name, dev->port);

    vcp0_port = &v->file;
    return (int) &v->file;

}

void
vcp_reconnect(int i){
    struct VCP *v = vcom + i;

    usbd_t *u = v->usbd;

    usb_disconnect( u );
    usbd_configure( u, &cdc_usbd_config, v );
    usb_connect( u );

}

struct VCP *
vcp_get(int i){
    struct VCP *v = vcom + i;
    return v;
}

static void
chkq(struct queue *q){

    if( q->len ) return;
    if( q->head == q->tail ) return;
    kprintf("* %d %d %d\n", q->len, q->head, q->tail);
}

void
vcp_reset(struct VCP *p){
    p->ready = 0;
}

void
vcp_configure(struct VCP *p){

    if( usb_speed(p->usbd) == USB_SPEED_HIGH ){
        p->is_hs = 1;
        usb_config_ep( p->usbd, CDC_RXD_EP, UE_BULK, CDC_HSSIZE );
        usb_config_ep( p->usbd, CDC_TXD_EP, UE_BULK, CDC_FSSIZE );
        usb_config_ep( p->usbd, CDC_NTF_EP, UE_BULK, CDC_NTF_SZ );

    }else{
        p->is_hs = 0;
        usb_config_ep( p->usbd, CDC_RXD_EP, UE_BULK, CDC_FSSIZE );
        usb_config_ep( p->usbd, CDC_TXD_EP, UE_BULK, CDC_FSSIZE );
        usb_config_ep( p->usbd, CDC_NTF_EP, UE_BULK, CDC_NTF_SZ );
    }

    p->rblen = p->tblen = 0;
    p->ready = 0;
}

int
vcp_recv_setup(struct VCP *p, const char *buf, int len){
    usb_device_request_t *req = buf;

    if( (req->bmRequestType & 0x7F) != (USB_REQ_TYPE_INTERFACE | USB_REQ_TYPE_CLASS)) return 0;

    switch (req->bRequest) {
    case UCDC_SET_CONTROL_LINE_STATE:
        trace_crumb1("vcp", "set/state", req->wValue);
        p->ready = req->wValue & 2;
        usbd_reply(p->usbd, 0, "", 0, 0);
        maybe_tx(p);
        vcp_send_ntf_initial(p);
        return 1;
    case UCDC_SET_LINE_CODING:
        trace_crumb2("vcp", "set/lcod", len, req->wLength);
        memcpy( &p->line_state, buf+8, sizeof(p->line_state) );
        // trace_data("vcp", "linestate", len, buf);
        usbd_reply(p->usbd, 0, "", 0, 0);
        return 1;
    case UCDC_GET_LINE_CODING:
        trace_crumb2("vcp", "get/lcod", len, req->wLength);
        usbd_reply(p->usbd, 0, &p->line_state, sizeof(p->line_state), req->wLength);
        return 1;
    case UCDC_SEND_BREAK:
        usbd_reply(p->usbd, 0, "", 0, 0);
        return 1;
    }


    kprintf("cdc/ctl %x %x\n", req->bmRequestType, req->bRequest);

    return 0;
}


void
vcp_send_notify(struct VCP *p, int code, int value, int len, const char *data, int noblock){
    usb_cdc_notification_t *b = 0;
    char bufn = 0;
    int plx;

    while(1){
        plx = spldisk();

        if( p->ntlen && !p->nt2len ){
            // buf1 is full, buf2 available -> use buf2
            bufn = 2;
            b = (usb_cdc_notification_t*)p->nt2buf;
            p->nt2len = sizeof(usb_cdc_notification_t) + len;
            break;
        }

        if( !p->ntlen && !p->nt2len ){
            // both bufs available -> use buf1
            bufn = 1;
            b = (usb_cdc_notification_t*)p->ntbuf;
            p->ntlen = sizeof(usb_cdc_notification_t) + len;
            break;
        }

        if( noblock ){
            splx(plx);
            return;
        }

        // wait for both to be available
        tsleep( &p->ntbuf, -1, "usb/n", 10000 );

        b = (usb_cdc_notification_t*)p->ntbuf;
    }

    trace_crumb2("vcp", "ntfq", bufn, value);

    bzero(b, sizeof(p->ntbuf));
    b->bmRequestType = UCDC_NOTIFICATION;
    b->bNotification = code;
    b->wValue        = value;
    b->wIndex        = CDC_COMM_IFACE;
    b->wLength       = len;
    bcopy(data, b->data, len);

    splx(plx);

    vcp_send_next_notify(p);
}

void
vcp_send_next_notify(struct VCP *p){

    trace_crumb2("vcp", "ntf>?", p->ready, p->usbd->curr_state);

    if( !p->ready ) return;
    if( !usbd_isactive(p->usbd) ) return;
    if( usbd_isbusy(p->usbd, CDC_NTF_EP) ) return;

    int plx = spldisk();

    if( p->ntlen ){
        int zp = p->is_hs ? 1 : !(p->ntlen & (CDC_NTF_SZ - 1));
        trace_crumb3("vcp", "ntf>", 1, p->ntlen, zp);
        usbd_write(p->usbd, CDC_NTF_EP, p->ntbuf, p->ntlen, zp );
    }else if( p->nt2len ){
        int zp = p->is_hs ? 1 : !(p->nt2len & (CDC_NTF_SZ - 1));
        trace_crumb3("vcp", "ntf>", 2, p->nt2len, zp);
        usbd_write(p->usbd, CDC_NTF_EP, p->nt2buf, p->nt2len, zp );
    }else{
        trace_crumb2("vcp", "ntf>?0", p->ntlen, p->nt2len);
    }

    splx(plx);
}

void
vcp_ntf_complete(struct VCP *p, int ep){

    trace_crumb2("vcp", "ntfc", p->ntlen, p->nt2len);

    if( p->ntlen ){
        p->ntlen = 0;
        if( p->nt2len ){
            vcp_send_next_notify(p);
            return;
        }
    }else{
        p->nt2len = 0;
    }
    wakeup( &p->ntbuf );
}

void
vcp_send_ntf_initial(struct VCP *p){
    // network connect
    vcp_send_notify(p, UCDC_N_NETWORK_CONNECTION, p->ready ? 1 : 0, 0, 0, 1);

    // speed change : <downlink(to host)speed, uplink(from host)speed>
    uint32_t speeds[2] = { p->line_state.dwDTERate, p->line_state.dwDTERate };
    vcp_send_notify(p, UCDC_N_CONNECTION_SPEED_CHANGE, 0, 8, speeds, 1);
}

static int
vcp_status(FILE*f){
    // RSN - usb connected?
    return 1;
}


static void
maybe_tx(struct VCP* p){
    int i;

    if( !p->ready ) return;
    if( p->txq.len == 0 ) return;
    if( p->tblen ) return;
    if( !usbd_isactive(p->usbd) ) return;
#if 1
    // copy to buffer
    i = qread(&p->txq, p->txbuf, VCP_TXBUF_SIZE);
#else
    for(i=0; p->txq.len && (i<VCP_TXBUF_SIZE); i++){
        p->txbuf[i] = qpop( &p->txq );
    }
#endif
    // tx
    p->tblen = i;
    int plx = spldisk();
    int zp = p->is_hs ? 1 : !(i & (CDC_FSSIZE - 1));
    trace_crumb3("vcp", "tx", p->tblen, p->txq.len, zp);

    usbd_write(p->usbd, CDC_TXD_EP, p->txbuf, i, zp );
    splx(plx);
}

static void maybe_dequeue(struct VCP*);
void
vcp_tx_complete(struct VCP *p, int ep){

    p->tblen = 0;

    //trace_crumb2("vcp", "tx/c", ep, splget());
    maybe_tx(p);
    maybe_dequeue(p);
    wakeup( &p->txq );

    //trace_crumb1("vcp", "/tx/c", ep);
}

static int
vcp_putchar(FILE *f, char ch){
    int i;
    struct VCP *p;
    int plx;

    p = (struct VCP*)f->d;

    //trace_crumb3("vcp", "putchar", p->txq.len, p->txq.head, p->txq.tail);

    while(1){
        plx = spldisk();

        if( p->txq.len != TX_QUEUE_SIZE ){
            qpush(&p->txq, ch);
            maybe_tx(p);
            splx(plx);
            break;
        }

        //trace_crumb1("vcp", "putchar+", plx);
        maybe_tx(p);
        splx(plx);
        if( p->txq.len != TX_QUEUE_SIZE ) continue;

        if( f->flags & F_NONBLOCK ) break;	// drop
        if( !usbd_isactive(p->usbd) ) break;
        if( !p->ready ) break;

        trace_crumb2("vcp", "block", f->flags, plx);

        // wait for buffer to empty
        tsleep( &p->txq, -1, "usb/o", 10000 );
    }

    return 1;
}

static int
vcp_write(FILE *f, const char *buf, int len){
    int n = 0;
    struct VCP *p = (struct VCP*)f->d;
    int plx;

    while(len){
        plx = spldisk();

        while( p->txq.len < TX_QUEUE_SIZE ){
            int i = qwrite(&p->txq, buf, len);

            buf += i;
            len -= i;
            n   += i;

            if( len == 0 ) break;
        }

        maybe_tx(p);
        splx(plx);

        if( !len ) break;
        if( p->txq.len != TX_QUEUE_SIZE ) continue;

        if( f->flags & F_NONBLOCK )   break;	// drop
        if( !usbd_isactive(p->usbd) ) break;
        if( !p->ready ) break;

        trace_crumb2("vcp", "block", f->flags, plx);

        // wait for buffer to empty
        tsleep( &p->txq, -1, "usb/o", 10000 );
    }

    return n;
}


static void
maybe_dequeue(struct VCP* p){
    int i,j;

    if( !p->rblen ) return;
    if( p->rblen > RX_QUEUE_SIZE - p->rxq.len ) return;

    for(i=0; i<p->rblen; i++){
        int c = p->rxbuf[i];
        // trace_crumb1("vcp", "recvchar", c);

        /* special control char ? */
        for(j=0; j<sizeof(p->file.cchars); j++){
            if(p->file.cchars[j] && c == p->file.cchars[j]){
                sigunblock( p->file.ccpid );
                ksendmsg( p->file.ccpid, MSG_CCHAR_0 + j );
                goto skip;
            }
        }

        qpush( &p->rxq, c);
    skip:
        continue;
    }

    p->rblen = 0;

    usb_recv_ack( p->usbd, CDC_RXD_EP );

    if( !p->ready ){
        vcp_send_ntf_initial(p);
        p->ready = 1;
    }
}

static int
vcp_getchar(FILE *f){
    char ch;
    int i, plx;
    struct VCP *p;

    p = (struct VCP*)f->d;

    while( 1 ){
        plx = spldisk();
        if( p->rxq.len ) break;

        tsleep( &p->rxq, currproc->prio, "usb/i", 1000000);
    }

    ch = qpop( &p->rxq );

    maybe_dequeue(p);

    splx(plx);
    return ch;
}

void
vcp_recv_chars(struct VCP *p, int ep, int len){

    // copy to buffer
    int l = usb_read(p->usbd, ep, p->rxbuf, sizeof(p->rxbuf));
    p->rblen = l;

    maybe_dequeue(p);
    maybe_tx(p);
    wakeup( &p->rxq );

}

#ifdef KTESTING

DEFUN(vcpinfo, "test")
{
    struct VCP *v = vcom + 0;

    printf("rxq %d; %d - %d\n", v->rxq.len, v->rxq.head, v->rxq.tail);
    printf("txq %d; %d - %d\n", v->txq.len, v->txq.head, v->txq.tail);
    printf("rxb %d\n", v->rblen);
    printf("txb %d\n", v->tblen);


    return 0;
}

DEFUN(vcpreset, "")
{
    struct VCP *v = vcom + 0;
    v->txq.len = v->txq.head = v->txq.tail = 0;
    v->tblen = 0;

    return 0;
}

#endif

DEFUN(ntftest, "")
{
    struct VCP *v = vcom + 0;

    // network connect
    vcp_send_notify(v, UCDC_N_NETWORK_CONNECTION, 1, 0, 0, 0);

    // speed change : <downlink(to host)speed, uplink(from host)speed>
    uint32_t speeds[2] = { v->line_state.dwDTERate, v->line_state.dwDTERate };
    vcp_send_notify(v, UCDC_N_CONNECTION_SPEED_CHANGE, 0, 8, speeds, 0);


    // bits: <overrun,parity,framing,inging,break,TXcarrier,RXcarrier>
    // UCDC_N_SERIAL_STATE             0x20    ACM/optional

}
