/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-15 17:10 (EDT)
  Function: usb device

*/

#ifndef __usbd_h__
#define __usbd_h__

#include <usb_conf_impl.h>


#define MAX_RESPONSE	256
#define SERIALNO_IDX	0xFE

struct usbd_config_dmap {
    uint16_t	num;
    const void *desc;
};

typedef struct {
    int _x;
    // callbacks
    // ...

    struct usbd_config_dmap dmap[];
    // terminate with {0, 0}
} usbd_config_t;



struct usbd_epd {
    // data being sent
    const char *wbuf;
    int  wlen;
    char wpending;
    char wzlp;

};

typedef struct {
    void      *dev;

    int setaddrreq;
    usbd_config_t *cf;

    char ctlreq[8];
    char ctlres[MAX_RESPONSE];
    struct usbd_epd epd[NUMENDPOINTS];

} usbd_t;

// provided by periph driver
extern void *usb_init(struct Device_Conf *, usbd_t *);
extern int  usb_connect(usbd_t *);
extern int  usb_disconnect(usbd_t *);
extern void usb_enable_suspend(usbd_t*);
extern void usb_set_addr(usbd_t*, int);
extern void usb_stall(usbd_t*, int);
extern int  usb_isstalled(usbd_t*, int);
extern int  usb_config_ep(usbd_t *, int, int, int);
extern int  usb_send(usbd_t *, int, const char *, int);
extern int  usb_serialnumber(void);


// provided by usbd.c
extern void usbd_cb_reset(usbd_t *);
extern void usbd_cb_suspend(usbd_t *);
extern void usbd_cb_wakeup(usbd_t *);
extern void usbd_cb_send_complete(usbd_t *, int);
extern void usbd_cb_recv(usbd_t*, int, const char *, int);
extern void usbd_cb_recv_setup(usbd_t*, const char *, int);

#endif /* __usbd_h__ */
