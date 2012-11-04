/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-15 11:44 (EST)
  Function: 
 
  $Id$

*/

#ifndef __msdosfs_h__
#define __msdosfs_h__

struct MSDOSFS_BPB {
    u_char	 jmp_boot[3];
    u_char	 oem_name[8];
    u_char       BytesPerSec[2]; /* bytes per sector: must be 512,1024,2048,4096 */
    u_char       SecPerClust; 	 /* sectors per cluster: must be a power of 2 */
    u_char       ResSecCnt[2];   /* number of reserved sectors */
    u_char       NumFATs;        /* number of FATs */
    u_char       RootDirCnt[2];  /* number of root directory entries */
    u_char       TotSec16[2];    /* total number of sectors, see also: TotSec32  */
    u_char       Media;          /* media descriptor: 0xF0 - 0xFF */
    u_char       FATSec16[2];    /* number of sectors per FAT, seel also: FATSec32 */
    u_char       SecPerTrack[2]; /* sectors per track */
    u_char       NumHeads[2];    /* number of heads */
    u_char       HiddenSecs[4];  /* # of hidden sectors */
    u_char       TotSec32[4];    /* # of sectors if TotSec16 == 0 */

    /* FAT32 only: */
    u_char       FATSec32[4];    /* like FATSec16 for FAT32 */
    u_char       ExtFlags[2];    /* extended flags: */
#define FATNUM          0xf             /* mask for numbering active FAT */
#define FATMIRROR       0x80            /* FAT is mirrored (like it always was) */
    u_char       FSVers[2];      /* filesystem version */
#define FSVERS          0               /* currently only 0 is understood */
    u_char       RootClust[4];   /* start cluster for root directory */
    u_char       FSInfo[2];      /* filesystem info structure sector */
    u_char       Backup[2];      /* backup boot sector */

};

struct MSDOSFS_FSInfo {
    u_char		StructSig[4];
#define FSINFO_STRUCTSIG	0x61417272
    u_char		FreeCount[4];	/* number of free clusters */
    u_char		NextFree[4];	/* next free cluster number */
};


struct MSDSOFS_Dirent {
    u_char        Name[8];      /* filename, blank filled */
#define SLOT_EMPTY      0x00            /* slot has never been used */
#define SLOT_E5         0x05            /* the real value is 0xe5 */
#define SLOT_DELETED    0xe5            /* file in this slot deleted */
    u_char        Extension[3]; /* extension, blank filled */
    u_char        Attributes;   /* file attributes */
#define ATTR_NORMAL     0x00            /* normal file */
#define ATTR_READONLY   0x01            /* file is readonly */
#define ATTR_HIDDEN     0x02            /* file is hidden */
#define ATTR_SYSTEM     0x04            /* file is a system file */
#define ATTR_VOLUME     0x08            /* entry is a volume label */
#define ATTR_DIRECTORY  0x10            /* entry is a directory name */
#define ATTR_ARCHIVE    0x20            /* file is new or modified */
    u_char        Reserved;     /* reserved */
    u_char        CHundredth;   /* hundredth of seconds in CTime */
    u_char        CTime[2];     /* create time */
    u_char        CDate[2];     /* create date */
    u_char        ADate[2];     /* access date */
    u_char        HighClust[2]; /* high bytes of cluster number */
    u_char        MTime[2];     /* last update time */
    u_char        MDate[2];     /* last update date */
    u_char        StartCluster[2]; /* starting cluster of file */
    u_char        FileSize[4];  /* size of file in bytes */
};



#endif /* __msdosfs_h__ */
