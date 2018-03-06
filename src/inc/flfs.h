
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

#ifndef FLFS_64BIT
typedef u_long fs2_t;
# define ALLONES 	0xFFFFFFFF
# define FCT_UNUSED	0		/* zero'ed memory */
# define FCT_DELETED	1
#else
typedef u_int64_t fs2_t;
# define ALLONES 	0xFFFFFFFFFFFFFFFF
# define FCT_UNUSED	ALLONES
# define FCT_DELETED	0
#endif


struct FSChunk {
    fs2_t type;
#define FCT_BLANK	ALLONES		/* erased flash */
#define FCT_FILE	3
#define FCT_CONT	5
#define FCT_BIOSEXT	0xAA55		/* dummy1 and cnklen will have romsize, and code in them */


    fs2_t cnklen;	/* length of chunk data */
    fs2_t totlen;	/* length of hdr, data, padding */
    fs2_t next;		/* offset of next chunk in this file */

};


#ifndef FLFS_NAMELEN
# define FLFS_NAMELEN	64
#endif

struct FSFile {
    fs2_t filelen;		/* length of file */
    fs2_t attr;			/* file attributes */
    long long ctime;
    char name[FLFS_NAMELEN];	/* null terminated */
};


#endif /* __flfs_h__ */
