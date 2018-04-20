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
#include <dev.h>
#include <usbd.h>
#include <usbdef.h>
#include <usbcdc.h>
#include <userint.h>

#define CRUMBS "vcp"
#define NR_CRUMBS 128
#include <crumbs.h>


#define CDC_SIZE	      64	/* usb cdc packet size (see also usbd_conf.h) */
#define CDC_RXD_EP  0x01
#define CDC_TXD_EP  0x82
#define CDC_NTF_EP  0x83

#define CDC_NTF_SZ  8


#ifndef USB_VENDOR
# define USB_VENDOR 0xA791
#endif

#ifndef USB_PRODUCT
# define USB_PRODUCT 1
#endif




static const usb_device_descriptor_t cdc_dev_desc = {
    .bLength            = sizeof(usb_device_descriptor_t),
    .bDescriptorType    = USB_DTYPE_DEVICE,
    .bcdUSB             = UD_USB_2_0,
    .bDeviceClass       = USB_CLASS_CDC,
    .bDeviceSubClass    = 0,
    .bDeviceProtocol    = 0,
    .bMaxPacketSize     = CONTROLSIZE,
    .idVendor           = USB_VENDOR,
    .idProduct          = USB_PRODUCT,
    .bcdDevice          = 0x01,
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

static const struct cdc_config cdc_config = {

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
        .bcdCDC              = 0x10,
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
        .bmCapabilities      = 0,
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
        .wMaxPacketSize      = CDC_SIZE,
        .bInterval           = 0x01,
    },
    .data_eptx               = {
        .bLength             = sizeof(usb_endpoint_descriptor_t),
        .bDescriptorType     = USB_DTYPE_ENDPOINT,
        .bEndpointAddress    = CDC_TXD_EP,
        .bmAttributes        = UE_BULK,
        .wMaxPacketSize      = CDC_SIZE,
        .bInterval           = 0x01,
    },

};



static const usb_wdata_descriptor_t lang_desc    = { 4,  USB_DTYPE_STRING, USB_LANG_EN_US };
static const usb_wdata_descriptor_t cdc_manuf_desc = { 12, USB_DTYPE_STRING, u"OS/J5" };
static const usb_wdata_descriptor_t cdc_prod_desc  = { 14, USB_DTYPE_STRING, u"gadget"  };

static const usbd_config_t cdc_usbd_config = {
    .dmap = {
        { (USB_DTYPE_DEVICE<<8),	0, &cdc_dev_desc },
        { (USB_DTYPE_CONFIGURATION<<8),	sizeof(cdc_config), &cdc_config },
        { (USB_DTYPE_STRING<<8) | 0,    0, &lang_desc },
        { (USB_DTYPE_STRING<<8) | 1,	0, &cdc_manuf_desc },
        { (USB_DTYPE_STRING<<8) | 2,	0, &cdc_prod_desc },
        {0, 0, 0},
    }
};



static int vcp_putchar(FILE*, char);
static int vcp_getchar(FILE*);
static int vcp_noop(FILE*);
static int vcp_status(FILE*);

const static struct io_fs vcp_port_fs = {
    0, //vcp_putchar,
    0, //vcp_getchar,
    0,
    0,
    0, //vcp_status,
    0,
    0,
    0,
    0,
    0,
    0
};

struct queue {
    uint8_t head, tail, len;
    char d[CDC_SIZE];
};



static struct VCP {
    FILE file;
    void *pdev;

    struct queue rxq, txq;
    char rxbuf[ CDC_SIZE ];
    char txbuf[ CDC_SIZE ];

    uint8_t rblen, tblen;

    u_char status;
#define COMSTAT_THROTTLED	2	/* queue is full, endpoint is throttled (NAK) */
} vcom[ 1 ];

FILE *vcp0_port = 0;

int
vcp_init(struct Device_Conf *dev){

    int i = 0; // dev->unit;

    bzero( vcom + i, sizeof(struct VCP));

    finit( & vcom[i].file );
    vcom[i].file.fs = &vcp_port_fs;
    vcom[i].file.codepage = CODEPAGE_UTF8;
    vcom[i].file.d  = (void*)&vcom[i];

    usbd_t *u = usbd_get(0);
    usbd_configure( u, &cdc_usbd_config );
    //usb_connect( u );

    bootmsg("%s usb/cdc/vcp\n", dev->name);

    vcp0_port = &vcom[i].file;
    return (int) &vcom[i].file;

}

void
qpush(struct queue *q, int c){

    q->d[ q->head ++ ] = c;
    q->head %= CDC_SIZE;
    q->len ++;
}

int
qpop(struct queue *q){

    int c = q->d[ q->tail ++ ];
    q->tail %= CDC_SIZE;
    q->len --;

    return c;
}

#if 0
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
        qpush(ch);
        
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


void
vcp_recvchars(char *buf, int len){
    int unit = 0;
    short i, j;

    for(i=0; i<len; i++){
        /* special control char ? */
        for(j=0; j<sizeof(vcom[unit].file.cchars); j++){
            if(vcom[unit].file.cchars[j] && buf[i] == vcom[unit].file.cchars[j]){
                sigunblock( vcom[unit].file.ccpid );
                ksendmsg( vcom[unit].file.ccpid, MSG_CCHAR_0 + j );
                goto skip;
            }
        }

        if( vcom[unit].len < VCP_QUEUE_SIZE ){
            /* queue it up */
            vcom[unit].queue[ vcom[unit].head++ ] = buf[i];
            vcom[unit].head %= VCP_QUEUE_SIZE;
            vcom[unit].len ++;
        }
        // else drop
    skip:
        continue;
    }

    // tell other end to stop if buffer is filling
    if( !len || vcom[unit].len < VCP_QUEUE_SIZE - CDC_SIZE ){
        vcp_rx_ack();
    }else{
        vcom[unit].status = COMSTAT_THROTTLED;
    }

    wakeup(&vcom[unit].len);
    return 0;
}
#endif
