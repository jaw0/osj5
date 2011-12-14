/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-06 13:08 (EST)
  Function: 
 
  $Id$

*/

#include <sys/types.h>
#include <conf.h>
#include <fs.h>

struct MSDOSFS {
    int devno;
    struct MountEntry *me;
};

struct MSDOSFS msdosfs[ N_FLASHDEV + N_DISK ];
static int devno;

const struct io_fs msdosfs_iofs = {
    msdosfs_putchar,
    msdosfs_getchar,
    msdosfs_close,
    msdosfs_noop,	/* flush */
    msdosfs_status,
    msdosfs_read,
    msdosfs_write,
    0, 0, 		/* bread, bwrite */
    0, 0,		/* seek, tell */
    msdosfs_stat
};

int
msdosfs_init(MountEntry *me){

    msdosfs[devno].devno = devno;
    msdosfs[devno].me    = me;


    devno ++;
}

int
msdosfs_diskread(int unit, u_long off, char *buf, int len){
    return fbread(msdosfs[unit].me->f, buf, len, off);
}
int
msdosfs_diskwrite(int unit, u_long off, char *buf, int len){
    return fbwrite(msdosfs[unit].me->f, buf, len, off);
}

msdosfs_init
msdosfs_open
msdosfs_ops

msdosfs_disk_read
msdosfs_disk_write
msdosfs_disk_ioctl
msdosfs_disk_initialize
msdosfs_disk_status

msdosfs_get_fattime
