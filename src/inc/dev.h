

/* $Id: dev.h,v 1.2 1999/07/02 22:03:43 jaw Exp $ */

#ifndef __dev_h__
#define __dev_h__

struct Device_Conf {
	int unit;
	int port;
	u_long addr;
	int irq;
	int baud;
	u_long flags;

	int (*init)(struct Device_Conf*);
	const char *name;
};

#endif /* __dev_h__ */

