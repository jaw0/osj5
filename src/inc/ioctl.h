
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: ioctl.h,v 1.3 2001/10/31 18:09:11 jaw Exp $ */

#ifndef __ioctl_h__
#define __ioctl_h__


#define _IOC(x,y)	(((x)<<8) | (y))


#define IOC_ERASE	_IOC('m', 'e')		/* param = offset to erase */
#define IOC_FLINFO	_IOC('m', 'i')		/* get flash info [write size, erase size] */

#define IOC_RDBLK	_IOC('d', 'r')		/* read block */
#define IOC_WRBLK	_IOC('d', 'w')		/* write block */

#define IOC_GFXDPY	_IOC('g', 'g')		/* get graphics object */
#define IOC_GFXSLEEP	_IOC('g', 's')		/* sleep mode */
#define IOC_GFXBUF	_IOC('g', 'b')		/* get buffer */
#define IOC_GFXFONT	_IOC('g', 'f')		/* set font */
#define IOC_GFXFONTNAME	_IOC('g', 'F')		/* set font by name */


#endif /* __ioctl_h__ */
