/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-23 13:55 (EDT)
  Function: i2c
*/

#ifndef __i2c_h__
#define __i2c_h__


typedef struct i2c_msg {
    int		slave;
    u_long	flags;
#define I2C_MSGF_READ           0x1

    int 	clen;
    int		dlen;
    char	*data;
    char	cdata[4];

    int		cpos, dpos;
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


#endif /* __i2c_h__ */

