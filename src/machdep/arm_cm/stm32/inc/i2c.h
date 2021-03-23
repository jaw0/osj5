/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-23 13:55 (EDT)
  Function: i2c
*/

#ifndef __i2c_h__
#define __i2c_h__


typedef struct i2c_msg {
    u_char	slave;
    u_char	flags;
#define I2C_MSGF_READ           0x1

    u_short	clen;
    u_short	dlen;
    char	*data;
    char	cdata[4];

    u_short	cpos, dpos;
} i2c_msg;

#define I2C_MSG_DL(sl, fl, dl, d)		{ sl, fl, 0, dl, d }

#define I2C_MSG_C1(sl, fl, d1)			{ sl, fl, 1, 0, 0, { d1 } }
#define I2C_MSG_C2(sl, fl, d1, d2) 		{ sl, fl, 2, 0, 0, { d1, d2 } }
#define I2C_MSG_C3(sl, fl, d1, d2, d3)		{ sl, fl, 3, 0, 0, { d1, d2, d3 } }
#define I2C_MSG_C4(sl, fl, d1, d2, d3, d4)	{ sl, fl, 4, 0, 0, { d1, d2, d3, d4 } }

#define I2C_MSG_DLC1(sl, fl, dl, d, d1)			{ sl, fl, 1, dl, d, { d1 } }
#define I2C_MSG_DLC2(sl, fl, dl, d, d1, d2) 		{ sl, fl, 2, dl, d, { d1, d2 } }
#define I2C_MSG_DLC3(sl, fl, dl, d, d1, d2, d3)		{ sl, fl, 3, dl, d, { d1, d2, d3 } }
#define I2C_MSG_DLC4(sl, fl, dl, d, d1, d2, d3, d4)	{ sl, fl, 4, dl, d, { d1, d2, d3, d4 } }

#define I2C_XFER_TIMEOUT	-1
#define I2C_XFER_OK		0

extern int i2c_xfer(int, int, i2c_msg*, int);
extern int i2c_write1(int, i2c_msg*);
extern int i2c_set_speed(int, int);

static inline int
i2c_get(int unit, int devaddr, int reg, int len){
    static i2c_msg tmpmsg[2];
    u_char buf[4];

    tmpmsg[0].slave    = devaddr;
    tmpmsg[0].flags    = 0;
    tmpmsg[0].clen     = 1;
    tmpmsg[0].dlen     = 0;
    tmpmsg[0].cdata[0] = reg;
    tmpmsg[0].data     = 0;
    tmpmsg[1].slave    = devaddr;
    tmpmsg[1].flags    = I2C_MSGF_READ;
    tmpmsg[1].clen     = 0;
    tmpmsg[1].dlen     = len;
    tmpmsg[1].data     = (char*)buf;

    i2c_xfer(unit, 2, tmpmsg, 100000);

    switch(len){
    case 1:
        return buf[0];
    case 2:
        return (buf[0]<<8) | buf[1];
    case 4:
        return (buf[0]<<24) | (buf[1]<<16) | (buf[2]<<8) | buf[3];
    }

    return 0;
}

static inline int
i2c_set(int unit, int devaddr, int reg, int len, int v){
    static i2c_msg tmpmsg[1];

    tmpmsg[0].slave    = devaddr;
    tmpmsg[0].flags    = 0;
    tmpmsg[0].clen     = 1 + len;
    tmpmsg[0].dlen     = 0;
    tmpmsg[0].cdata[0] = reg;
    tmpmsg[0].data     = 0;

    if( len == 1 )
        tmpmsg[0].cdata[1] = v;
    else{
        tmpmsg[0].cdata[1] = (v >> 8) & 0xFF;
        tmpmsg[0].cdata[2] = v & 0xFF;
    }

    return i2c_xfer(unit, 1, tmpmsg, 100000);
}

static inline int
i2c_setv(int unit, int devaddr, int reg, int len, const char *d){
    static i2c_msg tmpmsg[1];

    tmpmsg[0].slave    = devaddr;
    tmpmsg[0].flags    = 0;
    tmpmsg[0].clen     = 1;
    tmpmsg[0].dlen     = len;
    tmpmsg[0].cdata[0] = reg;
    tmpmsg[0].data     = (char*)d;

    return i2c_xfer(unit, 1, tmpmsg, 100000);
}

#endif /* __i2c_h__ */

