
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: disk.h,v 1.3 2001/11/15 22:56:38 jaw Exp $ */

#ifndef __disk_h__
#define __disk_h__


#define DISK_BLOCK_SIZE 512

struct Disk_Conf {
    const char *mntpt;		/* will autoconf if left 0 */
    const char *fstype;		/* type of fs */
    const char *cntrlnm;	/* controller */

    int unit;			/* unit number on controller */
    int part;			/* partition number */
    u_long flags;
};

struct Disk_MBR {
    char code[440];
    char disksig[4];
    char dummy[2];

    struct {
        char status;
        char chs_start[3];
        char type;
        char chs_last[3];
        unsigned int lba_start;
        unsigned int num_blks;
    } part[4];

    unsigned short mbrsig;
#define DISK_MBR_SIG	0x55AA
};



#endif /* __disk_h__ */
