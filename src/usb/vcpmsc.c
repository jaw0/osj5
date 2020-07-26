/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Sep-03 18:00 (EDT)
  Function: composite usb vcp+msc

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
#include <usbmsc.h>
#include <usbcdc.h>
#include <userint.h>

#define MSC_SIZE    64
#define MSC_RXD_EP  0x03
#define MSC_TXD_EP  0x83

#define CDC_SIZE    64
#define CDC_RXD_EP  0x01
#define CDC_TXD_EP  0x81
#define CDC_NTF_EP  0x82

#define CDC_NTF_SZ  8

#define ALIGN2 __attribute__ ((aligned (2)))

static const usb_device_descriptor_t comp_dev_desc ALIGN2  = {
    .bLength            = sizeof(usb_device_descriptor_t),
    .bDescriptorType    = USB_DTYPE_DEVICE,
    .bcdUSB             = UD_USB_2_0,
    .bDeviceClass       = 0,
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

struct comp_config {
    usb_config_descriptor_t     config;
    // vcp
    usb_interface_descriptor_t  comm;
    usb_cdc_header_descriptor_t cdc_hdr;
    usb_cdc_cm_descriptor_t     cdc_mgmt;
    usb_cdc_acm_descriptor_t    cdc_acm;
    usb_cdc_union_descriptor_t  cdc_union;
    usb_endpoint_descriptor_t   comm_ep;
    usb_interface_descriptor_t  data;
    usb_endpoint_descriptor_t   data_eprx;
    usb_endpoint_descriptor_t   data_eptx;
    // msc
    usb_interface_descriptor_t  iface;
    usb_endpoint_descriptor_t   eprx;
    usb_endpoint_descriptor_t   eptx;
};

static const struct comp_config comp_config ALIGN2 = {

    .config                  = {
        .bLength             = sizeof(usb_config_descriptor_t),
        .bDescriptorType     = USB_DTYPE_CONFIGURATION,
        .wTotalLength        = sizeof(struct comp_config),
        .bNumInterface       = 3,
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
        .wMaxPacketSize      = CDC_SIZE,
        .bInterval           = 0,
    },
    .data_eptx               = {
        .bLength             = sizeof(usb_endpoint_descriptor_t),
        .bDescriptorType     = USB_DTYPE_ENDPOINT,
        .bEndpointAddress    = CDC_TXD_EP,
        .bmAttributes        = UE_BULK,
        .wMaxPacketSize      = CDC_SIZE,
        .bInterval           = 0,
    },

    .iface                    = {
        .bLength             = sizeof(usb_interface_descriptor_t),
        .bDescriptorType     = USB_DTYPE_INTERFACE,
        .bInterfaceNumber    = 2,
        .bAlternateSetting   = 0,
        .bNumEndpoints       = 2,
        .bInterfaceClass     = USB_CLASS_MSC,
        .bInterfaceSubClass  = USB_SUBCLASS_SCSI,
        .bInterfaceProtocol  = USB_PROTO_MASS_BBB,
        .iInterface          = USB_NO_DESCRIPTOR,
    },
    .eprx               = {
        .bLength             = sizeof(usb_endpoint_descriptor_t),
        .bDescriptorType     = USB_DTYPE_ENDPOINT,
        .bEndpointAddress    = MSC_RXD_EP,
        .bmAttributes        = UE_BULK,
        .wMaxPacketSize      = MSC_SIZE,
        .bInterval           = 0,
    },
    .eptx               = {
        .bLength             = sizeof(usb_endpoint_descriptor_t),
        .bDescriptorType     = USB_DTYPE_ENDPOINT,
        .bEndpointAddress    = MSC_TXD_EP,
        .bmAttributes        = UE_BULK,
        .wMaxPacketSize      = MSC_SIZE,
        .bInterval           = 0,
    },
};



struct VCP;
struct MSC;
struct COMP;
extern void vcp_tx_complete(struct VCP *, int);
extern void vcp_recv_chars(struct VCP*, int, int);
extern void vcp_reset(struct VCP *);
extern void vcp_configure(struct VCP *);
extern int  vcp_recv_setup(struct VCP*, const char *, int);
extern void msc_reset(struct MSC *);
extern void msc_configure(struct MSC *);
extern void msc_tx_complete(struct MSC *, int);
extern void msc_recv_data(struct MSC*, int, int);
extern int  msc_recv_setup(struct MSC*, const char *, int);

static void comp_reset(struct COMP*);
static void comp_configure(struct COMP*);
static int  comp_recv_setup(struct COMP*, const char *, int);
static void comp_tx_complete(struct COMP*, int);
static void comp_recv_data(struct COMP*, int, int);


static const usb_wdata_descriptor_t lang_desc      ALIGN2 = { 4,  USB_DTYPE_STRING, USB_LANG_EN_US };

USB_DESCR(comp_manuf_desc, USB_MANUF_DESC);
USB_DESCR(comp_prod_desc,  USB_PROD_DESC);

static const usbd_config_t comp_usbd_config = {
    .cb_reset       = comp_reset,
    .cb_configure   = comp_configure,
    .cb_tx_complete = { [CDC_TXD_EP & 0x7f] = comp_tx_complete, [MSC_TXD_EP & 0x7f] = comp_tx_complete },
    .cb_recv_setup  = comp_recv_setup,
    .cb_recv = { [CDC_RXD_EP & 0x7f] = comp_recv_data, [MSC_RXD_EP & 0x7f] = comp_recv_data },

    .dmap = {
        { USB_SPEED_ANY,  (USB_DTYPE_DEVICE<<8),	0, &comp_dev_desc },
        { USB_SPEED_ANY,  (USB_DTYPE_CONFIGURATION<<8),	sizeof(comp_config), &comp_config },
        { USB_SPEED_ANY,  (USB_DTYPE_STRING<<8) | 0,    0, &lang_desc },
        { USB_SPEED_ANY,  (USB_DTYPE_STRING<<8) | 1,	0, &comp_manuf_desc },
        { USB_SPEED_ANY,  (USB_DTYPE_STRING<<8) | 2,	0, &comp_prod_desc },
        {0, 0, 0, 0},
    }
};

static struct COMP {
    usbd_t          *usbd;
    struct VCP *vcp;
    struct MSC *msc;

} compd[1];

void
vcpmsc_init(struct Device_Conf *dev){
    struct COMP *v = compd + 0;

    bzero(v, sizeof(struct COMP));

    usbd_t *u = usbd_get(0);
    v->usbd = u;
    v->vcp  = vcp_get(0);
    v->msc  = msc_get(0);

    if( v->msc && v->vcp ){
        usbd_configure( u, &comp_usbd_config, v );
        usb_connect( u );
    }

    bootmsg("%s composite:vcp+msc on usb\n", dev->name);

    return 0;
}

static void
comp_reset(struct COMP*v) {

    vcp_reset( v->vcp );
    msc_reset( v->msc );
}


static void
comp_configure(struct COMP *v){

    vcp_configure( v->vcp );
    msc_configure( v->msc );
}

static int
comp_recv_setup(struct COMP *v, const char *buf, int len){
    usb_device_request_t *req = buf;

    if( (req->bmRequestType & 0x7F) != (USB_REQ_TYPE_INTERFACE | USB_REQ_TYPE_CLASS)) return 0;

    if( req->wIndex == 2 )
        return msc_recv_setup( v->msc, buf, len);

    return vcp_recv_setup( v->vcp, buf, len);
}

static void
comp_tx_complete(struct COMP *v, int ep){

    if( (ep & 0x7F) == (MSC_TXD_EP & 0x7f) )
        return msc_tx_complete( v->msc, ep);

    vcp_tx_complete( v->vcp, ep);
}

static void
comp_recv_data(struct COMP *v, int ep, int len){

    if( (ep & 0x7F) == (MSC_RXD_EP & 0x7f) )
        return msc_recv_data( v->msc, ep, len);

    vcp_recv_chars( v->vcp, ep, len);
}

