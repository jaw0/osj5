
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: flfs.h,v 1.1 2001/11/15 22:56:38 jaw Exp $ */

#ifndef __flfs_h__
#define __flfs_h__

/*
  disk layout:
    chunk, chunk, chunk, ...

    chunk : chunk header, data
          | chunk header, file header, file data

*/

struct FSChunk {
        /* 16 bytes */
	u_short type;
#define FCT_UNUSED	0		/* zero'ed memory */
#define FCT_BLANK	0xFFFF		/* erased flash */
#define FCT_DELETED	1
#define FCT_FILE	3
#define FCT_CONT	5
#define FCT_BIOSEXT	0xAA55		/* dummy1 and cnklen will have romsize, and code in them */

	u_short dummy1;
	u_long cnklen;		/* length of chunk data */
	u_long totlen;		/* length of hdr, data, padding */
	u_long next;		/* offset of next chunk in this file */

};

#define FLFS_NAMELEN	64

struct FSFile {
        /* 80 bytes */
	u_long filelen;		/* length of file */
	u_long attr;		/* file attributes */

	long long ctime;
	char name[FLFS_NAMELEN];		/* null terminated */
};


#endif /* __flfs_h__ */
