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

#define TRACE
#include <trace.h>


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

static const usb_wdata_descriptor_t lang_desc    = { 4,  USB_DTYPE_STRING, USB_LANG_EN_US };
static const usb_wdata_descriptor_t x_manuf_desc = { 12, USB_DTYPE_STRING, u"OS/J5" };
static const usb_wdata_descriptor_t x_prod_desc  = { 10, USB_DTYPE_STRING, u"test"  };

 const usbd_config_t x_test_config = {
    .dmap = {
        { (USB_DTYPE_DEVICE<<8),	0, &x_test_dev_desc },
        { (USB_DTYPE_CONFIGURATION<<8),	0, &x_test_conf_desc },
        { (USB_DTYPE_STRING<<8) | 0,    0, &lang_desc },
        { (USB_DTYPE_STRING<<8) | 1,	0, &x_manuf_desc },
        { (USB_DTYPE_STRING<<8) | 2,	0, &x_prod_desc },
        {0, 0, 0},
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

usbd_t *
usbd_get(int idx){
    return usbd + idx;
}

void
usbd_configure(usbd_t *u, const usbd_config_t *cf, const void *cbarg){

    u->cf = cf;
    u->cbarg = cbarg;

    if( (u->curr_state & 0x7F) >= USBD_STATE_RESET ){
        if( cf->cb_reset ) cf->cb_reset(u->cbarg);
    }

    if( (u->curr_state & 0x7F) >= USBD_STATE_ACTIVE ){
        if( cf->cb_configure ) cf->cb_configure(u->cbarg);
    }

}


/****************************************************************/

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

/****************************************************************/

void
usbd_cb_reset(usbd_t *u){
    int i;

    for(i=0; i<NUMENDPOINTS; i++){
        u->epd[i].wpending = 0;
        u->epd[i].wbusy    = 0;
    }

    u->curr_config = 0;
    u->curr_state  = USBD_STATE_RESET;

    if( u->cf->cb_reset )
        u->cf->cb_reset(u->cbarg);
}

void
usbd_cb_suspend(usbd_t *u){
    u->curr_state  |= USBD_STATE_SUSPEND;

}
void
usbd_cb_wakeup(usbd_t *u){
    u->curr_state  &= ~USBD_STATE_SUSPEND;

}

void
usbd_cb_recv(usbd_t *u, int ep, int len){

    ep &= 0x7f;
    if( ep >= NUMENDPOINTS ) return;

    if( u->cf->cb_recv[ep] )
        u->cf->cb_recv[ep](u->cbarg, ep, len);
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
        if( ! dm->desc ) break;
        if( dm->num == req->wValue ){
            usb_descriptor_t *d = dm->desc;
            int len = dm->len ? dm->len : d->bLength;

            trace_crumb2("usbd", "got/desc", req->wValue, len);
            usbd_reply(u, 0, d, len, req->wLength);
            return 1;
        }

        i++;
    }

    trace_crumb1("usbd", "!descr", req->wValue);
    return 0;
}

/****************************************************************/

static void
_configure(usbd_t *u){

    if( u->cf->cb_configure )
        u->cf->cb_configure(u->cbarg);
}


static int
usbd_ctl_dev(usbd_t *u, const char *buf, int len){
    usb_device_request_t *req = buf;

    trace_crumb2("usbd", "ctl/dev", req->bRequest, req->wLength);

    switch (req->bRequest) {

    case USB_REQ_GET_DESCRIPTOR:
        //trace_crumb2("usbd", "get/desc", req->wValue, req->wLength);

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
        trace_crumb1("usbd", "addr/set1", req->wValue);
        usb_set_addr1(u, req->wValue);
        u->setaddrreq = req->wValue | 0x8000;
        usbd_reply(u, 0, "", 0, 0);
        return 1;

    case USB_REQ_GET_CONFIG:
        usbd_reply(u, 0, & u->curr_config, 1, req->wLength);
        return 1;
    case USB_REQ_SET_CONFIG:
        u->curr_config = req->wValue;
        u->curr_state  = USBD_STATE_ACTIVE;
        usbd_reply(u, 0, "", 0, 0);
        _configure(u);
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

    trace_crumb2("usbd", "ctl/int", req->bRequest, req->wLength);

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

    trace_crumb2("usbd", "ctl/ept", req->bRequest, req->wLength);

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
usbd_cb_recv_setup(usbd_t *u, int len){
    int i, r = 0;
    char *buf = u->ctlreq;
    usb_device_request_t *req = buf;

    // copy packet + ack
    usb_read(u, 0, buf, sizeof(u->ctlreq));
    usb_recv_ack(u, 0);

    trace_fdata("usbd", "ctl type %x, req %x, len %d, wlen %d", 4, req->bmRequestType, req->bRequest, len, req->wLength);

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
        trace_crumb2("usbd", "ctl/x", req->bmRequestType, req->bRequest);
        break;
    }

    if(r) return;

    if( u->cf->cb_recv_setup )
        r = u->cf->cb_recv_setup(u->cbarg, buf, len);

    if( r ) return;

    trace_crumb2("usbd", "ctl/unk", req->bmRequestType, req->bRequest);
    usbd_write(u, 0, "", 0, 1);
}

/****************************************************************/

static void
usbd_send_more(usbd_t *u, int ep){
    int epa = ep & 0x7F;

    if( ! u->epd[epa].wpending ) return;

    if( (u->epd[epa].wlen != 0) || u->epd[epa].wzlp ){
        int l = usb_send(u, ep, u->epd[epa].wbuf, u->epd[epa].wlen);

        trace_crumb2("usbd", "send", ep, l);

        if( l == -1 ){
            // error
            u->epd[epa].wpending = 0;
            return;
        }

        u->epd[epa].wbuf += l;
        u->epd[epa].wlen -= l;
    }

    if( u->epd[epa].wlen <= 0 ){
        u->epd[epa].wpending = 0;
    }
}


int
usbd_write(usbd_t *u, int ep, const char *buf, int len, int wzlp){
    int epa = ep & 0x7F;

    if( u->epd[epa].wpending ) return -1;	// already underway

    u->epd[epa].wbuf = buf;
    u->epd[epa].wlen = len;
    u->epd[epa].wpending = 1;
    u->epd[epa].wzlp = wzlp;
    u->epd[epa].wbusy = 1;

    usbd_send_more(u, ep);
    return len;
}

/*
  9.3.5 wLength

  This field specifies the length of the data transferred during the
second phase of the control transfer. The direction of data transfer
(host-to-device or device-to-host) is indicated by the Direction bit
of the bmRequestType field. If this field is zero, there is no data
transfer phase.

On an input request, a device must never return more data than is
indicated by the wLength value; it may return less. On an output
request, wLength will always indicate the exact amount of data to be
sent by the host. Device behavior is undefined if the host should send
more data than is specified in wLength.

*/

int
usbd_reply(usbd_t *u, int ep, const char *buf, int len, int rlen){
    int epa = ep & 0x7F;

    if( rlen && (rlen <= len) ){
        // send (possibly truncated) reply, equal to requested size, no zlp
        return usbd_write(u, ep, buf, rlen, 0);
    }

    if( len & (u->epd[epa].bufsize - 1) ){
        // final packet will be partially filled, no zlp
        return usbd_write(u, ep, buf, len, 0);
    }

    // full reply, with zlp
    return usbd_write(u, ep, buf, len, 1);
}

static void
_set_addr(usbd_t *u){

    usb_set_addr2(u, u->setaddrreq & 0xFF);
    trace_crumb1("usbd", "addr/set2", u->setaddrreq & 0xFF);

    u->setaddrreq = 0;
    u->curr_state = USBD_STATE_ADDRESS;
    usb_enable_suspend(u);
}

void
usbd_cb_send_complete(usbd_t *u, int ep){

    trace_crumb2("usbd", "send/c", ep, u->epd[ep].wpending);

    if( ! u->epd[ep].wpending ){
        u->epd[ep].wbusy = 0;

        if( u->setaddrreq ) _set_addr(u);
        if( u->cf->cb_tx_complete[ep] ) u->cf->cb_tx_complete[ep](u->cbarg, ep);

        return;
    }

    usbd_send_more(u, ep);
}


