/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-15 17:10 (EDT)
  Function: usb device

*/

#ifndef __usbd_h__
#define __usbd_h__

#include <usb_conf_impl.h>


#define MAX_RESPONSE	64
#define SERIALNO_IDX	0xFE

#define USBD_STATE_INACTIVE	0
#define USBD_STATE_CONNECT	1
#define USBD_STATE_RESET	2
#define USBD_STATE_ADDRESS	3
#define USBD_STATE_ACTIVE	4

#define USBD_STATE_SUSPEND	0x80


struct usbd_config_dmap {
    uint16_t	num;
    uint16_t    len;
    const void *desc;
};

struct _usbd;

typedef struct {
    // callbacks
    void (*cb_reset)(struct _usbd *);
    void (*cb_configure)(struct _usbd *);
    int  (*cb_recv_setup)(struct _usbd *, const char *, int);
    void (*cb_tx_complete)(struct _usbd *, int);
    void (*cb_recv[NUMENDPOINTS])(struct _usbd *, int, const char *, int);

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
    char wzlp;

};

typedef struct _usbd {
    void      *dev;

    uint8_t curr_state;
    uint8_t curr_config;

    int setaddrreq;
    usbd_config_t *cf;

    struct usbd_epd epd[NUMENDPOINTS];

    char ctlreq[8];
    char ctlres[MAX_RESPONSE];

} usbd_t;


#define usbd_isactive(u)	((u)->curr_state == USBD_ACTIVE)

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
