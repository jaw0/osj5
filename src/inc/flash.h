
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: flash.h,v 1.3 2001/10/31 18:09:10 jaw Exp $ */

#ifndef __flash_h__
#define __flash_h__

#include <locks.h>

struct Flash_Conf {
        u_char *addr;
	int size;		/* will autoconf if left 0, can be multiple or partial devs */
	u_long flags;		/* will try to autoconf, RAM+ROM must be specified */
	int blksz;		/* will autoconf if left 0 */
	const char *mntpt;	/* will autoconf if left 0 */
	const char *fstype;	/* type of fs */
};

#define FLM_NONE	0x00
#define FLM_AMD		0x01
#define FLM_INTEL	0x89
#define FLM_ATMEL	0x1F
#define FLM_SSTI	0xBF

#define FLD_AMD29F010	0x20
#define FLD_AMD29F040	0xA4
#define FLD_AMD29F080	0xD5
#define FLD_AMD29F016	0xAD
#define FLD_AMD29F017	0x3D
#define FLD_AMD29F032	0x41

#define FLD_AT29C010	0xD5
#define FLD_AT29C020	0xDA
#define FLD_AT29C040	0xA4

#define FLD_SSTI39F020	0xB6
#define FLD_SSTI39F040	0xD7
#define FLD_SSTI39F080	0xD8
#define FLD_SSTI39F016	0xD9


struct Flash_Command {
	int n;
	struct {
		int addr;
		int data;
	} c[8];
};

#define CMD_READ	((struct Flash_Command) {3, { {0x5555, 0xAA}, {0xAAAA, 0x55}, {0x5555, 0xF0} }})
#define CMD_READID	((struct Flash_Command) {3, { {0x5555, 0xAA}, {0xAAAA, 0x55}, {0x5555, 0x90} }})
#define CMD_BYTEWRITE	((struct Flash_Command) {3, { {0x5555, 0xAA}, {0xAAAA, 0x55}, {0x5555, 0xA0} }})
#define CMD_SECTERASE	((struct Flash_Command) {5, { {0x5555, 0xAA}, {0xAAAA, 0x55}, {0x5555, 0x80}, \
						{0x5555, 0xAA}, {0xAAAA, 0x55} }})


#endif /* __flash_h__ */

