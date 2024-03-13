
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: flfs.h,v 1.1 2001/11/15 22:56:38 jaw Exp $ */

#ifndef __flfs2_h__
#define __flfs2_h__

/*
  disk layout:
    chunk, chunk, chunk, ...

    chunk : chunk header, data
          | chunk header, file header, file data

*/

#if defined(FLFS_128BIT)
#  define FLFS_64BIT
#  define PAD(x) fs2_t x
#else
#  define PAD(x)
#endif


#if defined(FLFS_64BIT)
typedef u_int64_t fs2_t;
# define ALLONES 	0xFFFFFFFFFFFFFFFF
# ifndef FLFS_NAMELEN
#  define FLFS_NAMELEN	32
# endif

#else
typedef u_long fs2_t;
# define ALLONES 	0xFFFFFFFF
# ifndef FLFS_NAMELEN
#  define FLFS_NAMELEN	36
# endif
#endif



struct FSChunk {
    fs2_t type;
#define FCT_BLANK	ALLONES		/* erased flash */
#define FCT_DELETED	0
#define FCT_FIRST	1		/* first file data block */
#define FCT_DATA	2
#define FCT_DIR		3
#define FCT_INDEX	4
/* used as return values - not stored on device */
#define FCT_EMPTY_INDEX	0xF1
#define FCT_DELET_INDEX	0xF2
#define FCT_ERROR	0xFE
#define FCT_BLANK1	0xFF	/* fct_blank in one byte */

    PAD(type_copy);
    fs2_t cknext;		/* offset of next chunk in this file */
    PAD(cknext_copy);
    fs2_t intent;		/* for crash recovery */
    PAD(_pad1);
};

struct FSIndex {
    /* NB - first entry is the index block itself:
       fct_index if active, fct_blank if empty, fct_deleted if all entries are deleted
    */
    fs2_t cktype[0];
};

struct FSDirEnt {
    utime_t ctime;
    fs2_t   attr;			/* <delete flag: available, valid, deleted><attr 16bit> */
#define FLFS_ATTR_MASK 0xFFFF
#define FLFS_FDAF_MASK 0xFFFF0000
#define FDA_EMPTY	ALLONES		/* slot is available for use */
#define FDA_VALID	0x10000		/* slot is valid file */
#define FDA_DELETED	0		/* slot in no longer valid */
    u_long  start;			/* start offset */
    u_long  filelen;
    PAD(_pad1);
    char    name[FLFS_NAMELEN]; /* null terminated */
} __attribute__((packed)); /* nb. namelen is sized so that sizeof(struct) % FLASH_WRITE_SIZE == 0 */

struct FSDir {
    fs2_t type;
    PAD(type_copy);
    fs2_t flag;
    PAD(flag_copy);

#define FDT_ACTIVE	ALLONES		/* slots are available */
#define FDT_FULL	1		/* all slots are in use */
#define FDT_DELETED	0		/* all slots are deleted */

    fs2_t intent;	/* for crash recovery */
    fs2_t uid;		/* unique id */

    struct FSDirEnt dir[0];
};

#endif /* __flfs2_h__ */
