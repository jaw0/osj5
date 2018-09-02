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

#define MSC_SIZE    64
#define MSC_RXD_EP  0x03
#define MSC_TXD_EP  0x83

#define MAXLUN		0

#define STATE_READY	0
#define STATE_DATARX	1
#define STATE_DATATX	2
#define STATE_STATUS	3
#define STATE_WAIT	4

#define OP_STATUS	0
#define OP_CAPACITY	1
#define OP_READ		2
#define OP_WRITE	3


#ifndef USB_MSC_VENDOR
# define USB_MSC_VENDOR USB_VENDOR
#endif

#ifndef USB_MSC_PRODUCT
# define USB_MSC_PRODUCT USB_PRODUCT
#endif


#define ALIGN2 __attribute__ ((aligned (2)))

static const usb_device_descriptor_t msc_dev_desc ALIGN2  = {
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

/* sandisk:
   09 02 20 00 01 01 00 80 64	// conf desc
   09 04 00 00 02 08 06 50 00	// interface desc
   07 05 81 02 00 02 00		// in  ep desc
   07 05 02 02 00 02 01		// out ep desc
*/

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
    "0000"		// len=4
};

static const uint8_t msc_mode6_res[]  = {0,0,0,0,0,0,0,0};
static const uint8_t msc_mode10_res[] = {0,6,0,0,0,0,0,0};


struct MSC;
static void msc_reset(struct MSC *);
static void msc_configure(struct MSC *);
static void msc_tx_complete(struct MSC *, int);
static void msc_recv_data(struct MSC*, int, int);
static int  msc_recv_setup(struct MSC*, const char *, int);

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



static int msc_putchar(FILE*, char);
static int msc_getchar(FILE*);
static int msc_noop(FILE*);
static int msc_status(FILE*);

const static struct io_fs msc_port_fs = {
    msc_putchar,
    msc_getchar,
    0,
    0,
    msc_status,
    0,
    0,
    0,
    0,
    0,
    0
};

struct Sense {
    uint8_t key, asc, ascq;
};

#define MSC_BUF_SIZE	16384			// must be a multiple of 512

static struct MSC {
    FILE             file;
    usbd_t          *usbd;
    int8_t           state;
    int              datalen;
    int		     status;			// deferred status from async command
    struct Sense     sense;
    umass_bbb_cbw_t  cbw;
    umass_bbb_csw_t  csw;
    char             resbuf[64];		// for results
    char	     xbuf[MSC_BUFSIZE]; 	// QQQ

    int bufpos;
    int buffoff;


} mscd[ 1 ];


int
msc_init(struct Device_Conf *dev){

    struct MSC *v = mscd + 0;

    usbd_t *u = usbd_get(0);
    v->usbd = u;
    v->state = STATE_READY;
    //usbd_configure( u, &cdc_usbd_config, vcom + i );
    //usb_connect( u );

    bootmsg("%s msc/scsi on usb\n", dev->name);

    return 0; // (int) &v->file;

}

static inline void
msc_sense(struct MSC *p, int key, int asc, int ascq){
    p->sense.key  = key;
    p->sense.asc  = asc;
    p->sense.ascq = ascq;
}

static void
msc_reset(struct MSC *p){
    trace_crumb0("msc", "reset");
    p->state = STATE_READY;

}

static void
msc_configure(struct MSC *p){

    trace_crumb0("msc", "conf");
    usb_config_ep( p->usbd, MSC_RXD_EP, UE_BULK, MSC_SIZE );
    usb_config_ep( p->usbd, MSC_TXD_EP, UE_BULK, MSC_SIZE );
    p->state = STATE_READY;

}


static int
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
        usbd_reply(p->usbd, 0, "\0", 1, req->wLength);
        return 1;

    }

    trace_crumb2("msc", "ctl", req->bmRequestType, req->bRequest);
    kprintf("msc/ctl %x %x\n", req->bmRequestType, req->bRequest);

    return 0;
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

static int
msc_send_inquiry(struct MSC *p){
    usbd_write(p->usbd, MSC_TXD_EP, &msc_inquiry_res, sizeof(msc_inquiry_res), 0);
    return 0;
}

static int
msc_send_mode6(struct MSC *p){
    usbd_write(p->usbd, MSC_TXD_EP, msc_mode6_res, sizeof(msc_mode6_res), 0);
    return 0;
}

static int
msc_send_mode10(struct MSC *p){
    usbd_write(p->usbd, MSC_TXD_EP, msc_mode10_res, sizeof(msc_mode10_res), 0);
    return 0;
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

    usbd_write(p->usbd, MSC_TXD_EP, b, 18, 0);
    return 0;
}

static int
msc_send_capacity10(struct MSC *p){
    uint32_t *b = p->resbuf;

    b[0] = 1024 * 1024;	// XXX
    b[1] = 512;

    usbd_write(p->usbd, MSC_TXD_EP, b, 8, 0);
    return 0;
}

static int
msc_scsi_read10(struct MSC *p){

    // XXX
    bzero(p->xbuf, 512);
    usbd_write(p->usbd, MSC_TXD_EP, p->xbuf, 512, 1);
    return 0;
}

static int
msc_scsi_write10(struct MSC *p){

    return 0;
}

static int
msc_process_scsi(struct MSC *p){

    uint8_t *cdb = & p->cbw.CBWCDB;
    uint8_t cmd  = cdb[0];

    trace_crumb1("msc", "scsi", cmd);

    switch(cmd){
    case SCSI_TEST_UNIT_READY:
        // RSN - check media
        // ok? send csw(ok)
        // else: sense={NOT_READY, MEDIUM_NOT_PRESENT}, return -1 (send csw);
        return 0;

    case SCSI_SEND_DIAGNOSTIC:
        return 0;
    case SCSI_ALLOW_MEDIUM_REMOVAL:
        return 0;
    case SCSI_START_STOP_UNIT:
        return 0;

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

    case SCSI_VERIFY10:
    case SCSI_READ_FORMAT_CAPACITIES:
    case SCSI_FORMAT_UNIT:

    default:
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
    if( p->cbw.bCBWLUN > MAXLUN ) return 0;
    if( p->cbw.bCDBLength > CBWCDBLENGTH ) return 0;
    return 1;
}


static int
msc_process_cbw(struct MSC *p, int len){

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

    if( msc_process_scsi(p) ){
        // error
        msc_send_csw(p, CSWSTATUS_FAILED);
        return -1;
    }

    // next state
    p->datalen = p->cbw.dCBWDataTransferLength;
    if( p->cbw.dCBWDataTransferLength ){
        if( p->cbw.bCBWFlags & CBWFLAGS_IN )
            p->state = STATE_DATATX;
        else
            p->state = STATE_DATARX;
    }else{
        p->state = STATE_STATUS;
    }

    trace_crumb1("msc", "state", p->state);

    return 0;
}

static void
msc_tx_complete(struct MSC *p, int ep){

    trace_crumb1("msc", "tx/c", ep);

    switch(p->state){
    case STATE_DATATX:
        p->state = STATE_STATUS;
        msc_send_csw(p, CSWSTATUS_GOOD);
        break;

    case STATE_READY:
        // csw was sent
        break;
    default:
        // should not happen - ignore?
        break;
    }
}

static void
msc_recv_data(struct MSC *p, int ep, int len){
    int l=0;

    trace_crumb2("msc", "recv", ep, len);

    switch(p->state){
    case STATE_READY:
        // read cbw
        l = usb_read(p->usbd, ep, & p->cbw, sizeof(p->cbw));
        usb_recv_ack( p->usbd, ep );
        // hexdump(&p->cbw, l);
        msc_process_cbw(p, l);
        break;

    case STATE_DATARX:
        // process data
        l = usb_read(p->usbd, ep, & p->xbuf + x->bufpos, MSC_BUF_SIZE - p->bufpos);
        p->datalen -= l;
        p->bufpos  += l;

        if( (MSC_BUF_SIZE - p->bufpos > MSC_SIZE) || ! p->datalen )
            usb_recv_ack( p->usbd, ep );
        // RSN - handle short read

        // wakeup(...
        
        
        break;
    case STATE_DATATX:
    case STATE_STATUS:
    default:
        // phase error
        msc_send_csw(p, CSWSTATUS_PHASE);
        break;
    }

    if( p->state == STATE_STATUS ){
        msc_send_csw(p, CSWSTATUS_GOOD);
    }

}

/****************************************************************/
void
msc_run(int n, struct usb_msc_io *ioa){

    // init
    // start
    while(1){
        // tsleep()
        // process
    }

}


/****************************************************************/

DEFUN(msctest, "msc test")
{

    usbd_t *u = usbd_get(0);

    usb_disconnect( u );
    sleep(1);
    trace_reset();
    trace_crumb0("msc", "start");

    set_blinky(3);
    usbd_configure( u, &msc_usbd_config, mscd );
    usb_connect( u );

    while( ! get_button() ){
        usleep(1000);
    }
    play(4, "a4b4b4");
    sleep(1);

    trace_crumb0("msc", "/start");
    usb_disconnect( u );
    vcp_reconnect(0);
    set_blinky(5);
    sleep(1);


    return 0;
}
