/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Aug-28 19:17 (EDT)
  Function: usb mass storage

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
#include <userint.h>

#if defined(USB_MSC_TRACE) || defined(USB_TRACE)
# define TRACE
#endif
#include <trace.h>

#define MSC_BUFSIZE	16384			// must be a multiple of 512

#define MSC_SIZE    64
#define MSC_RXD_EP  0x03
#define MSC_TXD_EP  0x83

#define STATE_READY	0
#define STATE_DATARX	1
#define STATE_DATATX	2
#define STATE_STATUS	3


#ifndef USB_MSC_VENDOR
# define USB_MSC_VENDOR USB_VENDOR
#endif

#ifndef USB_MSC_PRODUCT
# define USB_MSC_PRODUCT USB_PRODUCT
#endif

#ifndef USB_MSC_DEVICE
# define USB_MSC_DEVICE USB_DEVICE
#endif


#define REV32(x) __builtin_bswap32(x)
#define REV16(x) __builtin_bswap16(x)
#define ALIGN2 __attribute__ ((aligned (2)))

static const usb_device_descriptor_t msc_dev_desc ALIGN2  = {
    .bLength            = sizeof(usb_device_descriptor_t),
    .bDescriptorType    = USB_DTYPE_DEVICE,
    .bcdUSB             = UD_USB_2_0,
    .bDeviceClass       = 0,
    .bDeviceSubClass    = 0,
    .bDeviceProtocol    = 0,
    .bMaxPacketSize     = CONTROLSIZE,
    .idVendor           = USB_MSC_VENDOR,
    .idProduct          = USB_MSC_PRODUCT,
    .bcdDevice          = USB_MSC_DEVICE,
    .iManufacturer      = 1,
    .iProduct           = 2,
    .iSerialNumber      = SERIALNO_IDX,
    .bNumConfigurations = 1,
};

struct msc_config {
    usb_config_descriptor_t     config;
    usb_interface_descriptor_t  iface;
    usb_endpoint_descriptor_t   eprx;
    usb_endpoint_descriptor_t   eptx;
};

static const struct msc_config msc_config ALIGN2 = {

    .config                  = {
        .bLength             = sizeof(usb_config_descriptor_t),
        .bDescriptorType     = USB_DTYPE_CONFIGURATION,
        .wTotalLength        = sizeof(struct msc_config),
        .bNumInterface       = 1,
        .bConfigurationValue = 1,
        .iConfiguration      = 0,
        .bmAttributes        = 0x80,
        .bMaxPower           = 50,
    },
    .iface                    = {
        .bLength             = sizeof(usb_interface_descriptor_t),
        .bDescriptorType     = USB_DTYPE_INTERFACE,
        .bInterfaceNumber    = 0,
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


static const usb_wdata_descriptor_t lang_desc      ALIGN2 = { 4,  USB_DTYPE_STRING, USB_LANG_EN_US };
static const usb_wdata_descriptor_t msc_manuf_desc ALIGN2 = { 2 + 2*sizeof(USB_MANUF_DESC), USB_DTYPE_STRING,
                                                              CONCAT(u, USB_MANUF_DESC) };
static const usb_wdata_descriptor_t msc_prod_desc  ALIGN2 = { 2 + 2 * sizeof(USB_PROD_DESC), USB_DTYPE_STRING,
                                                              CONCAT(u, USB_PROD_DESC)  };
static const umass_bbb_inquiry_t msc_inquiry_res = {
    {
        0x00, // Peripheral qualifier & device type
        0x80, // Removable medium
        0x05, // Version of the standard (5=SPC-3)
        0x02, // No NormACA, No HiSup, data format=2
        0x1F, // No extra parameters
        0x00, // No flags
        0x80, // Basic Task Management supported
        0x00, // No flags
    },
    "OSJ5    ",		// len=8,  space padded
    "Mass Storage    ", // len=16, space padded
    "0001"		// len=4
};

static const uint8_t msc_mode6_res[]  = {0,0,0,0,0,0,0,0};
static const uint8_t msc_mode10_res[] = {0,6,0,0,0,0,0,0};


struct MSC;
void msc_reset(struct MSC *);
void msc_configure(struct MSC *);
void msc_tx_complete(struct MSC *, int);
void msc_recv_data(struct MSC*, int, int);
int  msc_recv_setup(struct MSC*, const char *, int);
static void msc_run(void);

static const usbd_config_t msc_usbd_config = {
    .cb_reset       = msc_reset,
    .cb_configure   = msc_configure,
    .cb_tx_complete = { [MSC_TXD_EP & 0x7f] = msc_tx_complete },
    .cb_recv_setup  = msc_recv_setup,
    .cb_recv = { [MSC_RXD_EP & 0x7f] = msc_recv_data },

    .dmap = {
        { (USB_DTYPE_DEVICE<<8),	0, &msc_dev_desc },
        { (USB_DTYPE_CONFIGURATION<<8),	sizeof(msc_config), &msc_config },
        { (USB_DTYPE_STRING<<8) | 0,    0, &lang_desc },
        { (USB_DTYPE_STRING<<8) | 1,	0, &msc_manuf_desc },
        { (USB_DTYPE_STRING<<8) | 2,	0, &msc_prod_desc },
        {0, 0, 0},
    }
};


struct Sense {
    uint8_t key, asc, ascq;
};


static struct MSC {
    usbd_t          *usbd;
    usb_msc_iocf_t  *conf;
    int8_t           state;
    int8_t           maxlun;
    int              datalen;
    struct Sense     sense;
    umass_bbb_cbw_t  cbw;
    umass_bbb_csw_t  csw;
    char             resbuf[64]; // for results
    char             xbuf[MSC_BUFSIZE];
    int              bufpos;

} mscd[ 1 ];


int
msc_init(struct Device_Conf *dev){

    struct MSC *v = mscd + 0;

    bzero(v, sizeof(struct MSC));

    usbd_t *u = usbd_get(0);
    v->usbd = u;
    v->state = STATE_READY;
    //usbd_configure( u, &cdc_usbd_config, vcom + i );
    //usb_connect( u );

    bootmsg("%s msc/scsi on usb\n", dev->name);
    start_proc( 1024, msc_run, "usbmsc" );

    return 0;

}

void
msc_reconnect(int n){
    struct MSC *v = mscd + n;

    usbd_t *u = v->usbd;

    usbd_configure( u, &msc_usbd_config, v );
    usb_connect( u );
}

struct MSC *
msc_get(int i){
    struct MSC *v = mscd + i;
    return v;
}

void *
msc_set_conf(int n, int maxlun, usb_msc_iocf_t* cf){
    struct MSC *v = mscd + n;

    v->maxlun = maxlun;
    v->conf   = cf;

    trace_crumb1("msc", "setconf", maxlun);
    return v;
}


static usb_msc_iocf_t*
lun_conf(struct MSC *p){

    if( !p->conf ) return 0;
    int lun = p->cbw.bCBWLUN;
    if( lun > p->maxlun ) return 0;

    return p->conf + lun;
}

static inline void
msc_sense(struct MSC *p, int key, int asc, int ascq){
    p->sense.key  = key;
    p->sense.asc  = asc;
    p->sense.ascq = ascq;
}

void
msc_reset(struct MSC *p){
    trace_crumb0("msc", "reset");
    p->state = STATE_READY;
}

void
msc_configure(struct MSC *p){
    trace_crumb0("msc", "conf");
    usb_config_ep( p->usbd, MSC_RXD_EP, UE_BULK, MSC_SIZE );
    usb_config_ep( p->usbd, MSC_TXD_EP, UE_BULK, MSC_SIZE );
    p->state = STATE_READY;
}


int
msc_recv_setup(struct MSC *p, const char *buf, int len){
    usb_device_request_t *req = buf;

    if( (req->bmRequestType & 0x7F) != (USB_REQ_TYPE_INTERFACE | USB_REQ_TYPE_CLASS)) return 0;

    switch (req->bRequest) {
    case UR_BBB_RESET:
        trace_crumb0("msc", "req/reset");
        msc_reset(p);
        usbd_reply(p->usbd, 0, "", 0, 0);
        // ...
        return 1;

    case UR_BBB_GET_MAX_LUN:
        trace_crumb0("msc", "get/maxlun");
        usbd_reply(p->usbd, 0, & p->maxlun, 1, req->wLength);
        return 1;

    }

    trace_crumb2("msc", "ctl", req->bmRequestType, req->bRequest);
    kprintf("msc/ctl %x %x\n", req->bmRequestType, req->bRequest);

    return 0;
}

static int
msc_send_result(struct MSC *p, char *buf, int len){

    p->state = STATE_DATATX;
    usbd_write(p->usbd, MSC_TXD_EP, buf, len, 0);
    tsleep( p, -1, "usb/txc", 10000 );
    return 0;
    // RSN - handle send failed
}

static void
msc_send_csw(struct MSC *p, int status){

    trace_crumb1("msc", "csw", status);

    p->csw.dCSWSignature   = CSWSIGNATURE;
    p->csw.dCSWTag         = p->cbw.dCBWTag;
    p->csw.dCSWDataResidue = 0; // XXX
    p->csw.bCSWStatus      = status;

    p->state = STATE_READY;
    usbd_write(p->usbd, MSC_TXD_EP, &p->csw, sizeof(p->csw), 0);
}

/****************************************************************/

static int
msc_send_unitready(struct MSC *p){

    usb_msc_iocf_t *cf = lun_conf(p);
    if( !cf || !cf->ready() ){
        msc_sense(p, SKEY_NOT_READY, SASC_MEDIUM_NOT_PRESENT, 0);
        return -1;
    }

    return 0;
}

static int
msc_send_inquiry(struct MSC *p){

    usb_msc_iocf_t *cf = lun_conf(p);
    if( !cf || !cf->ready() ){
        msc_sense(p, SKEY_NOT_READY, SASC_MEDIUM_NOT_PRESENT, 0);
        return -1;
    }

    memcpy(p->resbuf, &msc_inquiry_res, sizeof(msc_inquiry_res));

    if( cf->prod ){
        // copy name, space pad
        int i;
        umass_bbb_inquiry_t *in = (umass_bbb_inquiry_t *)p->resbuf;
        for(i=0; i<16; i++) in->prod[i] = ' ';
        strncpy(in->prod, cf->prod, 16);
    }

    return msc_send_result(p, p->resbuf, sizeof(msc_inquiry_res));
}

static int
msc_send_mode6(struct MSC *p){

    usb_msc_iocf_t *cf = lun_conf(p);
    if( !cf || !cf->ready() ){
        msc_sense(p, SKEY_NOT_READY, SASC_MEDIUM_NOT_PRESENT, 0);
        return -1;
    }

    memcpy(p->resbuf, msc_mode6_res, sizeof(msc_mode6_res));

    if( cf->readonly )
        p->resbuf[2] |= 0x80;

    return msc_send_result(p, p->resbuf, sizeof(msc_mode6_res) );
}

static int
msc_send_mode10(struct MSC *p){

    usb_msc_iocf_t *cf = lun_conf(p);
    if( !cf || !cf->ready() ){
        msc_sense(p, SKEY_NOT_READY, SASC_MEDIUM_NOT_PRESENT, 0);
        return -1;
    }

    memcpy(p->resbuf, msc_mode10_res, sizeof(msc_mode10_res));

    if( cf->readonly )
        p->resbuf[3] |= 0x80;

    return msc_send_result(p, p->resbuf, sizeof(msc_mode10_res) );

}

static int
msc_send_sense(struct MSC *p){
    uint8_t *b = p->resbuf;

    bzero(b, 18);
    b[0]  = 0x70;
    b[7]  = 18 - 6;
    b[2]  = p->sense.key;
    b[12] = p->sense.asc;
    b[13] = p->sense.ascq;

    return msc_send_result(p, b, 18);
}

static int
msc_send_capacity10(struct MSC *p){
    uint32_t *b = p->resbuf;
    struct stat s;

    usb_msc_iocf_t *cf = lun_conf(p);
    if( !cf || !cf->ready() ){
        msc_sense(p, SKEY_NOT_READY, SASC_MEDIUM_NOT_PRESENT, 0);
        trace_crumb0("msc", "capac!cf");
        return -1;
    }

    fstat( cf->fio, &s );

    bzero(b, 8);
    uint32_t size = (s.size >> 9) - 1;

    b[0] = REV32(size);
    b[1] = REV32(512);

    trace_crumb1("msc", "capacity", b[0]);

    p->state = STATE_DATATX;
    usbd_write(p->usbd, MSC_TXD_EP, b, 8, 0);
    tsleep( p, -1, "usb/txc", 10000 );
    return 0;
}

static int
msc_scsi_read10(struct MSC *p){

    usb_msc_iocf_t *cf = lun_conf(p);
    umass_bbb_rw10_t *cbd = (umass_bbb_rw10_t*)p->cbw.CBWCDB;

    if( !cf || !cf->ready() ){
        msc_sense(p, SKEY_NOT_READY, SASC_MEDIUM_NOT_PRESENT, 0);
        trace_crumb0("msc", "read!cf");
        return -1;
    }

    int totlen = p->cbw.dCBWDataTransferLength;
    int cbdlen = REV16(cbd->len) << 9;

    if( totlen != cbdlen ){
        msc_sense(p, SKEY_ILLEGAL_REQUEST, SASC_INVALID_CDB, 0);
        trace_crumb2("msc", "read!len", totlen, cbd->len);
        return -1;
    }

    int err = 0;
    offset_t pos = REV32(cbd->lba) << 9;
    p->state = STATE_DATATX;

    trace_crumb3("msc", "read", (int)pos, totlen, cbdlen );

    while( totlen > 0 ){
        // read from device, send to usb

        if( cf->activity ) cf->activity();

        int len = totlen;
        if( len > MSC_BUFSIZE ) len = MSC_BUFSIZE;

        int r = fbread( cf->fio, p->xbuf, len, pos );

        if( r <= 0 ){
            trace_crumb3("msc", "readerr", pos, len, r);
            err = 1;
            bzero(p->xbuf, len);
        }

        usbd_write(p->usbd, MSC_TXD_EP, p->xbuf, len, 0);
        tsleep( p, -1, "usb/txc", 10000 );
        if( p->state != STATE_DATATX ) return 0;

        totlen -= len;
        pos    += len;
    }

    if( err )
        msc_sense(p, SKEY_MEDIUM_ERROR, SASC_UNRECOVERED_READ_ERROR, 0);

    return err;
}

static int
msc_scsi_write10(struct MSC *p){
    usb_msc_iocf_t *cf = lun_conf(p);
    umass_bbb_rw10_t *cbd = (umass_bbb_rw10_t*)p->cbw.CBWCDB;

    if( !cf || !cf->ready() ){
        msc_sense(p, SKEY_NOT_READY, SASC_MEDIUM_NOT_PRESENT, 0);
        trace_crumb0("msc", "write!cf");
        return -1;
    }

    if( cf->readonly ){
        msc_sense(p, SKEY_MEDIUM_ERROR, SASC_WRITE_PROTECTED, 0);
        trace_crumb0("msc", "write/ro");
        return -1;
    }

    int totlen = p->cbw.dCBWDataTransferLength;
    int cbdlen = REV16(cbd->len) << 9;

    if( totlen != cbdlen ){
        msc_sense(p, SKEY_ILLEGAL_REQUEST, SASC_INVALID_CDB, 0);
        trace_crumb2("msc", "write!len", totlen, cbd->len);
        return -1;
    }

    int err = 0;
    offset_t pos = REV32(cbd->lba) << 9;
    p->state = STATE_DATARX;
    p->datalen = totlen;
    p->bufpos = 0;

    trace_reset();
    trace_crumb3("msc", "write", (int)pos, totlen, cbdlen );

    usb_recv_ack( p->usbd, MSC_RXD_EP );

    while( p->datalen > 0 ){
        // read from usb, send to device

        if( cf->activity ) cf->activity();

        tsleep( p, -1, "usb/rxc", 10000 );
        if( p->state != STATE_DATARX ) return 0;

        int len = p->bufpos;
        trace_crumb2("msc", "recv", pos, len);

        if( len <= 0 ){
            err = 1;
            break;
        }

        if( !err ){
            int r = fbwrite( cf->fio, p->xbuf, len, pos );

            if( r <= 0 ){
                trace_crumb3("msc", "writeerr", pos, len, r);
                err = 1;
            }
        }

        totlen -= len;
        pos    += len;
        p->bufpos = 0;

        usb_recv_ack( p->usbd, MSC_RXD_EP );

    }

    if( err ){
        msc_sense(p, SKEY_MEDIUM_ERROR, SASC_WRITE_FAULT, 0);
    }

    return err;
}

/****************************************************************/

static int
msc_process_scsi(struct MSC *p){

    uint8_t *cdb = & p->cbw.CBWCDB;
    uint8_t cmd  = cdb[0];

    trace_crumb1("msc", "scsi", cmd);

    // delay ack on write cmds
    // so we don't start recving data before we're ready
    switch(cmd){
    case SCSI_WRITE10:
        break;
    default:
        usb_recv_ack( p->usbd, MSC_RXD_EP );
    }

    switch(cmd){
    case SCSI_SEND_DIAGNOSTIC:
        return 0;
    case SCSI_ALLOW_MEDIUM_REMOVAL:
        return 0;
    case SCSI_START_STOP_UNIT:
        return 0;

    case SCSI_TEST_UNIT_READY:
        return msc_send_unitready(p);
    case SCSI_INQUIRY:
        return msc_send_inquiry(p);
    case SCSI_REQUEST_SENSE:
        return msc_send_sense(p);
    case SCSI_MODE_SENSE10:
        return msc_send_mode10(p);
    case SCSI_MODE_SENSE6:
        return msc_send_mode6(p);
    case SCSI_READ_CAPACITY10:
        return msc_send_capacity10(p);
    case SCSI_READ10:
        return msc_scsi_read10(p);
    case SCSI_WRITE10:
        return msc_scsi_write10(p);

    default:
        play(4, "bbb");
        msc_sense(p, SKEY_ILLEGAL_REQUEST, SASC_INVALID_CDB, 0);
        return -1;

    }
}

static inline int
cbw_is_valid(struct MSC *p, int len){
    if( len != sizeof(umass_bbb_cbw_t) ) return 0;
    if( p->cbw.dCBWSignature != CBWSIGNATURE ) return 0;
    return 1;
}

static inline int
cbw_is_meaningful(struct MSC *p, int len){
    if( p->cbw.bCBWLUN > p->maxlun ) return 0;
    if( p->cbw.bCDBLength > CBWCDBLENGTH ) return 0;
    return 1;
}


static void
msc_process_cbw(struct MSC *p, int len){

    if( len == 0 ){
        // MSC 6.7.3 - The host shall not send zero length packets
        // but I see them. ignore stray zlp
        usb_recv_ack( p->usbd, MSC_RXD_EP );
        return;
    }

    // verify cbw
    if( !cbw_is_valid(p, len) ){
        // MSC 6.6.1
        trace_crumb0("msc", "cbw/invalid");
        usb_stall( p->usbd, MSC_RXD_EP );
        usb_stall( p->usbd, MSC_TXD_EP );
        return -1;
    }
    if( !cbw_is_meaningful(p, len) ){
        // MSC 6.4 - The response of a device to a CBW that is not meaningful is not specified.
        trace_crumb2("msc", "cbw/meaningless", p->cbw.bCBWLUN, p->cbw.bCDBLength);
        msc_sense(p, SKEY_ILLEGAL_REQUEST, SASC_INVALID_FIELD_IN_COMMAND, 0);
        msc_send_csw(p, CSWSTATUS_FAILED);
        return -1;
    }

    // bottom half task will continue with processing the request
    // by calling msc_bottom_proccess_cbw
    trace_crumb0("msc", "wakeup");
    wakeup( p );

}

static void
msc_bottom_proccess_cbw(struct MSC *p){

    if( msc_process_scsi(p) ){
        // error
        msc_send_csw(p, CSWSTATUS_FAILED);
        return;
    }

    msc_send_csw(p, CSWSTATUS_GOOD);
    trace_crumb1("msc", "state", p->state);
}


void
msc_tx_complete(struct MSC *p, int ep){

    trace_crumb1("msc", "tx/c", ep);

    switch(p->state){
    case STATE_DATATX:
        wakeup(p);
        break;

    case STATE_READY:
        // csw was sent
        break;
    default:
        // should not happen - ignore?
        break;
    }
}

void
msc_recv_data(struct MSC *p, int ep, int len){
    int l=0;

    trace_crumb2("msc", "recv", ep, len);

    switch(p->state){
    case STATE_READY:
        // read cbw
        l = usb_read(p->usbd, ep, & p->cbw, sizeof(p->cbw));
        msc_process_cbw(p, l);
        break;

    case STATE_DATARX:
        trace_crumb2("msc", "recv", p->datalen, p->bufpos);

        if( p->bufpos + MSC_SIZE > MSC_BUFSIZE ){
            trace_crumb0("msc", "recv/ovf");
            usb_stall( p->usbd, MSC_RXD_EP );
            usb_stall( p->usbd, MSC_TXD_EP );
            p->state = STATE_READY;
            return; // botched
        }

        // process data
        l = usb_read(p->usbd, ep, p->xbuf + p->bufpos, MSC_BUFSIZE - p->bufpos);

        if( l <= 0 ){
            trace_crumb1("msc", "recv/len?", l);
            usb_stall( p->usbd, MSC_RXD_EP );
            usb_stall( p->usbd, MSC_TXD_EP );
            p->state = STATE_READY;
            return; // botched
        }

        p->datalen -= l;
        p->bufpos  += l;

        //  buffer full or done reading - process the buffer
        // else ack and get more
        if( (p->bufpos >= MSC_BUFSIZE) || ! p->datalen )
            wakeup(p);
        else
            usb_recv_ack( p->usbd, ep );

        break;
    case STATE_DATATX:
    case STATE_STATUS:
    default:
        // phase error
        msc_send_csw(p, CSWSTATUS_PHASE);
        break;
    }

}

/****************************************************************/
void
msc_run(void){
    struct MSC *p = mscd + 0;

    currproc->flags |= PRF_REALTIME | PRF_IMPORTANT;
    currproc->prio  = 2;

    while(1){
        trace_crumb0("msc", "tsleep");
        tsleep( p, -1, "usb/i", 0 );
        msc_bottom_proccess_cbw( p );
    }
}

/****************************************************************/
static usb_msc_iocf_t usbconf[2];

static int is_ready(void){ return 1; }
static int not_ready(void){ return 0; }
static void active_blink(void){ set_led1_rgb(0xFFFF00); }

void msc_test(void){

    usbd_t *u = usbd_get(0);

    usbconf[0].ready = is_ready;
    usbconf[0].readonly = 0;
    usbconf[0].fio = fopen("dev:sd0", "rw");
    usbconf[0].prod = "Crypto Jawn";
    usbconf[0].activity = active_blink;

    if( ! usbconf[0].fio ){
        printf("cannot open sd0\n");
        return 0;
    }

    // disconnect vcp (if connected) + connect msc
    usb_disconnect( u );
    msc_set_conf(0, 0, usbconf);

    sleep(1);
    trace_reset();
    trace_crumb0("msc", "start");

    set_blinky(3);
    msc_reconnect(0);

    // run msc until button press
    while( ! get_button() ){
        usleep(1000);
    }
    play(4, "a4b4b4");
    sleep(1);

    trace_crumb0("msc", "/start");

    // disconnect msc, reconnect vcp
    usb_disconnect( u );
    sleep(1);
    vcp_reconnect(0);
    set_blinky(5);


    return 0;
}

DEFUN(msctest, "msc test")
{
    msc_test();
}
