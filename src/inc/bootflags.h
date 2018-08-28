
/* $Id: bootflags.h,v 1.1 1999/07/02 22:03:42 jaw Exp $ */

#ifndef __bootflags_h__
#define __bootflags_h__

#define BOOT_VERBOSE	1
#define BOOT_SINGLE	2
#define BOOT_ALTCON	4
#define BOOT_USEGDB	8
#define BOOT_NORC	16

extern unsigned long bootflags;

#endif /* __bootflags_h__ */

