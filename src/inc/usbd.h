/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-15 17:10 (EDT)
  Function: usb device

*/

#ifndef __usbd_h__
#define __usbd_h__

#include <usb_conf_impl.h>


#define MAX_RESPONSE	32
#define MAX_REQUEST	64
#define SERIALNO_IDX	0xFE

#define USBD_STATE_INACTIVE	0
#define USBD_STATE_CONNECT	1
#define USBD_STATE_RESET	2
#define USBD_STATE_ADDRESS	3
#define USBD_STATE_ACTIVE	4

#define USBD_STATE_SUSPEND	0x80

struct usbd_config_dmap {
    uint8_t	speed;
    uint16_t	num;
    uint16_t    len;
    const void *desc;
};

struct _usbd;

typedef struct {
    // callbacks - passed cbarg
    void (*cb_reset)(void *);
    void (*cb_configure)(void *);
    int  (*cb_recv_setup)(void *, const char *, int);
    void (*cb_tx_complete[NUMENDPOINTS])(void *, int);
    void (*cb_recv[NUMENDPOINTS])(void *, int, int);
    void (*cb_sof)(void*);

    // ...

    struct usbd_config_dmap dmap[];
    // terminate with {0, 0}
} usbd_config_t;



struct usbd_epd {
    int  bufsize;
    // data being sent
    const char *wbuf;
    int  wlen;
    char wpending;
    char wbusy;
    char wzlp;

};

typedef struct _usbd {
    void      *dev;

    uint8_t  curr_state;
    uint8_t  curr_config;
    uint8_t  reqlen, reqpos;
    uint8_t  enumspeed;
    uint16_t setaddrreq;

    const usbd_config_t *cf;
    const void *cbarg;

    struct usbd_epd epd[NUMENDPOINTS];

    char ctlreq[MAX_REQUEST];
    char ctlres[MAX_RESPONSE];

} usbd_t;


#define usbd_isactive(u)	((u)->curr_state == USBD_STATE_ACTIVE)
#define usbd_isbusy(u,ep)	((u)->epd[(ep) & 0x7f].wbusy)

// provided by periph driver
extern void *usb_init(struct Device_Conf *, usbd_t *);
extern int  usb_connect(usbd_t *);
extern int  usb_disconnect(usbd_t *);
extern void usb_enable_suspend(usbd_t*);
extern void usb_set_addr1(usbd_t*, int);
extern void usb_set_addr2(usbd_t*, int);
extern void usb_stall(usbd_t*, int);
extern int  usb_isstalled(usbd_t*, int);
extern int  usb_config_ep(usbd_t *, int, int, int);
extern int  usb_send(usbd_t *, int, const char *, int);
extern uint64_t  usb_serialnumber(void);


// provided by usbd.c
extern void usbd_cb_reset(usbd_t *);
extern void usbd_cb_suspend(usbd_t *);
extern void usbd_cb_wakeup(usbd_t *);
extern void usbd_cb_send_complete(usbd_t *, int);
extern void usbd_cb_recv(usbd_t*, int, int);
extern void usbd_cb_recv_setup(usbd_t*, int);

#endif /* __usbd_h__ */
