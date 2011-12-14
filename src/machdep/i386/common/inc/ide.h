
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: ide.h,v 1.2 2001/10/31 18:09:11 jaw Exp $ */

#ifndef __ide_h__
#define __ide_h__


/* registers */
#define IDE_R_DATA	0
#define IDE_R_ERROR	1
#define IDE_R_WCOMP	1
#define IDE_R_NSECT	2
#define IDE_R_SECT	3
#define IDE_R_LCYL	4
#define IDE_R_HCYL	5
#define IDE_R_DRHD	6
#define IDE_R_STAT	7
#define IDE_R_CMD	7

#define IDE_STAT_BUSY		0x80
#define IDE_STAT_READY		0x40
#define IDE_STAT_WRFAULT	0x20
#define IDE_STAT_SEEKOK		0x10
#define IDE_STAT_DATAREQ	0x08
#define IDE_STAT_CORRECTED	0x04
#define IDE_STAT_INDEX		0x02
#define IDE_STAT_ERROR		0x01

#define IDE_ERR_BADSECT		0x80
#define IDE_ERR_BADECC		0x40
#define IDE_ERR_NOMARK		0x10
#define IDE_ERR_BADCMD		0x04
#define IDE_ERR_BADSEEK		0x02
#define IDE_ERR_BADADDR		0x01

#define IDE_CMD_NOP		0x00
#define IDE_CMD_RECAL		0x10
#define IDE_CMD_READ_RETRY	0x20
#define IDE_CMD_READ_NORETRY	0x21

#define IDE_CMD_WRITE_RETRY		0x30
#define IDE_CMD_WRITE_NORETRY		0x31
#define IDE_CMD_WRITE_VERIFY_RETRY	0x40
#define IDE_CMD_WRITE_VERIFY_NORETRY	0x41
#define IDE_CMD_FORMAT_TRK		0x50
#define IDE_CMD_SEEK			0x70
#define IDE_CMD_DIAG			0x90
#define IDE_CMD_INITPARAM		0x91
#define IDE_CMD_IDENTIFY		0xEC


#endif /* __ide_h__ */

