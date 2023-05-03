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

#if defined(USBD_TRACE) || defined(USB_TRACE)
# define TRACE
#endif
#include <trace.h>


static usbd_t usbd[N_USBD];


int
usbd_init(struct Device_Conf *dev){
    int i    = dev->unit;

    bzero(usbd+i, sizeof(usbd_t));
    void *usb = usb_init(dev, usbd + i);

    trace_init();
    trace_crumb3("usbd", "init", i, usb, usbd + i);

    usbd[i].dev = usb;
    return 0;
}

usbd_t *
usbd_get(int idx){
    return usbd + idx;
}

void
usbd_configure(usbd_t *u, const usbd_config_t *cf, const void *cbarg){

    u->cf = cf;
    u->cbarg = cbarg;

    trace_crumb2("usbd", "cf", u, u->curr_state);
    if( (u->curr_state & 0x7F) >= USBD_STATE_RESET ){
        if( cf->cb_reset ) cf->cb_reset(u->cbarg);
    }

    if( (u->curr_state & 0x7F) >= USBD_STATE_ACTIVE ){
        if( cf->cb_configure ) cf->cb_configure(u->cbarg);
    }

}


/****************************************************************/

/* USB MSC requires:
   4.1.1 The serial number shall contain at least 12 valid digits
   4.1.2 The following table defines the valid characters that the device shall use for the serial number
         [ 0-9, A-F ]
*/

static const char serialdigits[] = "0123456789ABCDEF";
static int
usbd_serial_descr(char *buf){
    usb_wdata_descriptor_t *d = buf;
    uint16_t *dst = d->wData;
    int i;

    d->bLength = 12 * 2 + 2;
    d->bDescriptorType = USB_DTYPE_STRING;

    uint64_t sn = usb_serialnumber();

    for(i=0; i<12; i++){
        dst[11-i] = serialdigits[ sn & 0x0F ];
        sn >>= 4;
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
    u->enumspeed   = USB_SPEED_UNKNOWN;

    trace_crumb1("usbd", "reset", u->enumspeed);
    if( u->cf && u->cf->cb_reset )
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
usbd_cb_sof(usbd_t *u){
    if( u->cf && u->cf->cb_sof )
        u->cf->cb_sof(u->cbarg);
}

/****************************************************************/
static int
usbd_reply_descr(usbd_t *u, const char *buf){
    usb_device_request_t *req = buf;
    int i;

    if( ! u->cf ) return 0;

    if( u->enumspeed == USB_SPEED_UNKNOWN ){
        u->enumspeed = usb_speed(u);
        trace_crumb1("usbd", "speed", u->enumspeed);
    }

    // search for requested descriptor
    while(1){
        struct usbd_config_dmap *dm = u->cf->dmap + i;
        if( ! dm->desc ) break;
        if( (dm->speed != USB_SPEED_ANY) && (dm->speed != u->enumspeed) ){

        }
        else if( dm->num == req->wValue ){
            usb_descriptor_t *d = dm->desc;
            int len = dm->len ? dm->len : d->bLength;

            trace_crumb2("usbd", "got/desc", req->wValue, len);
            usbd_reply(u, 0, d, len, req->wLength);
            return 1;
        }

        i++;
    }

    trace_crumb1("usbd", "!descr", req->wValue);
    kprintf("!descr %x\n", req->wValue);
    return 0;
}

/****************************************************************/

static void
_configure(usbd_t *u){

    if( u->cf && u->cf->cb_configure )
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

static void
usbd_process_setup(usbd_t *u){
    int r = 0;
    char *buf = u->ctlreq;
    usb_device_request_t *req = buf;

    trace_fdata("usbd", "ctl type %x, idx %x req %x, wlen %d", 4, req->bmRequestType, req->wIndex, req->bRequest, req->wLength);

    switch (req->bmRequestType & ~USB_REQ_TYPE_READ){

    case USB_REQ_TYPE_DEVICE:
        r = usbd_ctl_dev(u, buf, u->reqlen);
        break;
    case USB_REQ_TYPE_INTERFACE:
        r = usbd_ctl_int(u, buf, u->reqlen);
        break;
    case USB_REQ_TYPE_ENDPOINT:
        r = usbd_ctl_ept(u, buf, u->reqlen);
        break;
    default:
        trace_crumb2("usbd", "ctl/x", req->bmRequestType, req->bRequest);
        break;
    }

    if(r) return;

    if( u->cf && u->cf->cb_recv_setup )
        r = u->cf->cb_recv_setup(u->cbarg, buf, u->reqlen);

    if( r ) return;

    trace_crumb2("usbd", "ctl/unk", req->bmRequestType, req->bRequest);
    usbd_write(u, 0, "", 0, 1);
}


void
usbd_cb_recv_setup(usbd_t *u, int len){
    int r = 0;
    char *buf = u->ctlreq;
    usb_device_request_t *req = buf;

    // copy packet + ack
    usb_read(u, 0, buf, sizeof(u->ctlreq));
    u->reqpos = len;
    u->reqlen = len;
    usb_recv_ack(u, 0);

    // read more?
    if( req->wLength && !(req->bmRequestType & USB_REQ_TYPE_READ) ){
        // read more data...
        u->reqlen += req->wLength;
        trace_fdata("usbd", "setup len %d, want more %d", 2, len, req->wLength);
    }else{
        usbd_process_setup(u);
        u->reqlen = u->reqpos = 0;
    }
}

/****************************************************************/

void
usbd_cb_recv(usbd_t *u, int ep, int len){

    ep &= 0x7f;
    if( ep >= NUMENDPOINTS ) return;

    // data for a pending setup request?
    if( !ep && u->reqlen ){
        char *buf = u->ctlreq;
        usb_read(u, 0, buf + u->reqpos, sizeof(u->ctlreq) - u->reqpos);
        u->reqpos += len;

        usb_recv_ack(u, 0);
        trace_crumb2("usbd", "recv/setup/data", len, u->reqpos);

        if( u->reqpos >= u->reqlen ){
            usbd_process_setup(u);
            u->reqlen = u->reqpos = 0;
        }
        return;
    }

    trace_crumb2("usbd", "recv/data", ep, len);

    if( u->cf && u->cf->cb_recv[ep] )
        u->cf->cb_recv[ep](u->cbarg, ep, len);
}

/****************************************************************/

static void
usbd_send_more(usbd_t *u, int ep){
    int epa = ep & 0x7F;

    if( ! u->epd[epa].wpending ){
        kprintf("usbd  cannot send\n");
        return;
    }

    if( (u->epd[epa].wlen != 0) || u->epd[epa].wzlp ){
        int l = usb_send(u, ep, u->epd[epa].wbuf, u->epd[epa].wlen);

        // trace_crumb2("usbd", "send", ep, l);

        if( l < 0 ){
            // error
            trace_crumb2("usbd", "ERROR", ep, l);
            kprintf("usbd send (ep %d len %d) err %d\n", epa, u->epd[epa].wlen, l);
            u->epd[epa].wpending = 0;
            return;
        }

        u->epd[epa].wbuf += l;
        u->epd[epa].wlen -= l;

        if( l == 0 ) u->epd[epa].wzlp = 0; // zlp has been sent
    }else{
        trace_crumb2("usbd", "send/no", ep, u->epd[epa].wlen);
    }

    if( u->epd[epa].wlen <= 0 && ! u->epd[epa].wzlp ){
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

    int plx = spldisk();
    usbd_send_more(u, ep);
    splx(plx);
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
        if( u->cf && u->cf->cb_tx_complete[ep] ) u->cf->cb_tx_complete[ep](u->cbarg, ep);

        return;
    }

    usbd_send_more(u, ep);
}


