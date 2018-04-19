/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-15 22:56 (EDT)
  Function: usb device

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

#define CRUMBS "usbd"
#define NR_CRUMBS 128
#include <crumbs.h>


static usbd_t usbd[N_USBD];

static const usb_device_descriptor_t x_test_dev_desc = {
    .bLength            = sizeof(usb_device_descriptor_t),
    .bDescriptorType    = USB_DTYPE_DEVICE,
    .bcdUSB             = UD_USB_2_0,
    .bDeviceClass       = 0xFF, // 00 means each interface defines its own class; FF means vendor-defined class; Any other value must be a class code
    .bDeviceSubClass    = 0,
    .bDeviceProtocol    = 0,
    .bMaxPacketSize     = CONTROLSIZE,
    .idVendor           = 0xA791,
    .idProduct          = 0x01,
    .bcdDevice          = 0x01,
    .iManufacturer      = 1,
    .iProduct           = 2,
    .iSerialNumber      = SERIALNO_IDX,
    .bNumConfigurations = 1,
};
static const usb_config_descriptor_t x_test_conf_desc = {
    .bLength             = sizeof(usb_config_descriptor_t),
    .bDescriptorType     = USB_DTYPE_CONFIGURATION,
    .wTotalLength        = sizeof(usb_config_descriptor_t),
    .bNumInterface       = 1,
    .bConfigurationValue = 0,
    .iConfiguration      = 2,
    .bmAttributes        = 0x80,
    .bMaxPower           = 250,
};

static const usb_wdata_descriptor_t lang_desc    = { 4,  USB_DTYPE_STRING, 0x0409 };
static const usb_wdata_descriptor_t x_manuf_desc = { 12, USB_DTYPE_STRING, u"OS/J5" };
static const usb_wdata_descriptor_t x_prod_desc  = { 10, USB_DTYPE_STRING, u"test"  };

 const usbd_config_t x_test_config = {
    .dmap = {
        { (USB_DTYPE_DEVICE<<8),	&x_test_dev_desc },
        { (USB_DTYPE_CONFIGURATION<<8),	&x_test_conf_desc },
        { (USB_DTYPE_STRING<<8) | 0,    &lang_desc },
        { (USB_DTYPE_STRING<<8) | 1,	&x_manuf_desc },
        { (USB_DTYPE_STRING<<8) | 2,	&x_prod_desc },
        {0, 0},
    }
};

int
usbd_init(struct Device_Conf *dev){
    int i    = dev->unit;

    bzero(usbd+i, sizeof(usbd_t));
    void *usb = usb_init(dev, usbd + i);

    usbd[i].dev = usb;
    usbd[i].cf = &x_test_config;	// XXX
}


static const char serialdigits[] = "0123456789abcdefghjkmnprstuvwxyz";
static int
usbd_serial_descr(char *buf){
    usb_wdata_descriptor_t *d = buf;
    uint16_t *dst = d->wData;
    int i;

    d->bLength = 14;
    d->bDescriptorType = USB_DTYPE_STRING;

    unsigned int sn = usb_serialnumber();

    for(i=0; i<6; i++){
        *dst ++ = serialdigits[ sn & 0x1F ];
        sn >>= 5;
    }

    return d->bLength;
}

DEFUN(usbserialtest, "test")
{
    char buf[32];

    int l = usbd_serial_descr(buf);
    hexdump(buf, l);
    return 0;
}

/****************************************************************/

void
usbd_cb_reset(usbd_t *u){
    int i;

    for(i=0; i<NUMENDPOINTS; i++){
        u->epd[i].wpending = 0;
    }
}

void
usbd_cb_suspend(usbd_t *u){

}
void
usbd_cb_wakeup(usbd_t *u){

}

void
usbd_cb_recv(usbd_t *u, int ep, const char *buf, int len){


}

/****************************************************************/
static int
usbd_reply_descr(usbd_t *u, const char *buf){
    usb_device_request_t *req = buf;
    int i;

    if( ! u->cf ) return 0;

    // search for requested descriptor
    while(1){
        struct usbd_config_dmap *dm = u->cf->dmap + i;
        DROP_CRUMB("dm", dm->num, dm->desc);
        if( ! dm->desc ) break;
        if( dm->num == req->wValue ){
            usb_descriptor_t *d = dm->desc;

            usbd_reply(u, 0, d, d->bLength, req->wLength);
            return 1;
        }

        i++;
    }

    DROP_CRUMB("!descr", req->wValue, 0);
    return 0;
}

/****************************************************************/

static int
usbd_ctl_dev(usbd_t *u, const char *buf, int len){
    usb_device_request_t *req = buf;

    DROP_CRUMB("ctl/dev", req->bRequest, 0);

    switch (req->bRequest) {

    case USB_REQ_GET_DESCRIPTOR:
        DROP_CRUMB("get/desc", req->wValue, 0);

        if( req->wValue == ((USB_DTYPE_STRING << 8) | SERIALNO_IDX) ){
            int l = usbd_serial_descr(u->ctlres);
            usbd_reply(u, 0, u->ctlres, l, req->wLength);
            return 1;
        }

        if( usbd_reply_descr(u, buf) ) return 1;
        break;
    case USB_REQ_GET_STATUS:
        usbd_reply(u, 0, "\0\0", 2, req->wLength);
        return 1;
    case USB_REQ_SET_ADDRESS:
        DROP_CRUMB("addr", req->wValue, 0);
        u->setaddrreq = req->wValue | 0x8000;
        usbd_reply(u, 0, "", 0, 0);
        return 1;

    case USB_REQ_GET_CONFIG:
        usbd_reply(u, 0, "\0", 1, req->wValue);
        return 1;
    case USB_REQ_SET_CONFIG:
        usbd_reply(u, 0, "", 0, 0);
        return 1;

    case USB_REQ_SET_DESCRIPTOR:
    case USB_REQ_SET_FEATURE:
    case USB_REQ_CLEAR_FEATURE:
        break;
    }

    return 0;
}

static int
usbd_ctl_int(usbd_t *u, const char *buf, int len){
    usb_device_request_t *req = buf;

    DROP_CRUMB("ctl/int", req->bRequest, 0);

    switch (req->bRequest) {
    case USB_REQ_GET_STATUS:
        usbd_reply(u, 0, "\0\0", 2, req->wLength);
        return 1;
    }

    return 0;
}

static int
usbd_ctl_ept(usbd_t *u, const char *buf, int len){
    usb_device_request_t *req = buf;

    DROP_CRUMB("ctl/ept", req->bRequest, 0);

    switch (req->bRequest) {

    case USB_REQ_SET_FEATURE:
        usb_stall(u, req->wIndex);
        usbd_reply(u, 0, "", 0, 0);
        return 1;
    case USB_REQ_CLEAR_FEATURE:
        usb_unstall(u, req->wIndex);
        usbd_reply(u, 0, "", 0, 0);
        return 1;
    case USB_REQ_GET_STATUS:
        usbd_reply(u, 0, usb_isstalled(u, req->wIndex) ? "\0\1" : "\0\0", 2, req->wLength);
        return 1;
    }

    return 0;
}


void
usbd_cb_recv_setup(usbd_t *u, const char *buf, int len){
    int i, r = 0;

    // copy packet to faster memory
    if( len <= sizeof(u->ctlreq)){
        for(i=0; i<len; i++){
            u->ctlreq[i] = buf[i];
        }
        buf = u->ctlreq;
    }

    usb_device_request_t *req = buf;

    DROP_CRUMB("ctl", req->bmRequestType, len);
    hexdump(req, 8);

    switch (req->bmRequestType & ~USB_REQ_TYPE_READ){

    case USB_REQ_TYPE_DEVICE:
        r = usbd_ctl_dev(u, buf, len);
        break;
    case USB_REQ_TYPE_INTERFACE:
        r = usbd_ctl_int(u, buf, len);
        break;
    case USB_REQ_TYPE_ENDPOINT:
        r = usbd_ctl_ept(u, buf, len);
        break;
    default:
        DROP_CRUMB("ctl/x", req->bmRequestType, req->bRequest);

    }

    if(r) return;

    DROP_CRUMB("ctl/unk", req->bRequest, 0);
    usbd_write(u, 0, "", 0, 1);
}

/****************************************************************/

static void
usbd_send_more(usbd_t *u, int ep){

    if( ! u->epd[ep].wpending ) return;

    if( (u->epd[ep].wlen != 0) || u->epd[ep].wzlp ){
        int l = usb_send(u, ep, u->epd[ep].wbuf, u->epd[ep].wlen);
        DROP_CRUMB("send", ep, l);

        if( l == -1 ){
            // error
            u->epd[ep].wpending = 0;
            return;
        }

        u->epd[ep].wbuf += l;
        u->epd[ep].wlen -= l;
    }

    if( u->epd[ep].wlen <= 0 ) u->epd[ep].wpending = 0;
}


int
usbd_write(usbd_t *u, int ep, const char *buf, int len, int wzlp){

    if( u->epd[ep].wpending ) return -1;	// already underway

    u->epd[ep].wbuf = buf;
    u->epd[ep].wlen = len;
    u->epd[ep].wpending = 1;
    u->epd[ep].wzlp = wzlp;

    usbd_send_more(u, ep);
    hexdump(buf, len);
    return len;
}

int
usbd_reply(usbd_t *u, int ep, const char *buf, int len, int rlen){

    if( rlen && (rlen <= len) ){
        // send (possibly truncated) reply, no zlp
        return usbd_write(u, ep, buf, rlen, 0);
    }

    // full reply, with zlp
    return usbd_write(u, ep, buf, len, 1);
}

void
usbd_cb_send_complete(usbd_t *u, int ep){

    DROP_CRUMB("send/c", u->epd[ep].wpending, u->setaddrreq );
    if( u->setaddrreq && ! u->epd[ep].wpending ){
        usb_set_addr(u, u->setaddrreq & 0xFF );
        DROP_CRUMB("addr/set", u->setaddrreq & 0xFF, 0);
        u->setaddrreq = 0;
    }
    usbd_send_more(u, ep);
}



void
usbd_dump_crumbs(){
    DUMP_CRUMBS();
}

void
usbd_reset_crumbs(){
    RESET_CRUMBS();
}

