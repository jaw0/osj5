/*
  Copyright (c) 2001
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2001
  Function:

  $Id$

*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <pio.h>
#include <ioctl.h>
#include <disk.h>
#include <msgs.h>
#include <dev.h>
#include <bootflags.h>
#include <locks.h>

#define DISKSIZE	(2*1024*1024*1024LL)

int udsk_ioctl(FILE*, int, void*);
int udsk_bread(FILE*, char*, int, offset_t);
int udsk_bwrite(FILE*, const char*, int, offset_t);
int udsk_stat(FILE *, struct stat *);

const struct io_fs udsk_fs = {
    0, /* putc */
    0, /* getc */
    0, /* close */
    0, /* flush */
    0, /* status */
    0, /* read */
    0, /* write */
    udsk_bread,  /* bread */
    udsk_bwrite, /* bwrite */
    0, /* seek */
    0, /* tell */
    udsk_stat,
    udsk_ioctl
};



/* the ide controllers */
struct UDSK_Device {
    FILE file;
    int fd;
    int no;
    const char *name;

} udsk[ N_UDSK ];



extern struct DiskPart_Conf disk_device[];
extern int n_disk;

int
udsk_init(struct Device_Conf *dev){
    int port = dev->port;

    int c = dev->unit;
    finit( & udsk[c].file );
    udsk[c].no   = c;
    udsk[c].fd = open("disk_2gb", 2);
    udsk[c].file.d  = (void*)& udsk[c];
    udsk[c].file.fs = & udsk_fs;

    bootmsg( "%s at unix\n",
	     dev->name);

    dkpart_learn( dev, "ud", c, &udsk[c].file, DISKSIZE / 512 );
    return 0;
}

int
udsk_bread(FILE* f, char *buf, int len, offset_t pos){
    struct UDSK_Device *hd = (struct UDSK_Device *)(f->d);

    lseek(hd->fd, pos, 0);
    return read(hd->fd, buf, len);
}

int
udsk_bwrite(FILE* f, const char *buf, int len, offset_t pos){
    struct UDSK_Device *hd = (struct UDSK_Device *)(f->d);

    lseek(hd->fd, pos, 0);
    return write(hd->fd, buf, len);
}

int
udsk_ioctl(FILE* f, int cmd, void *x){
    struct UDSK_Device *hd = (struct UDSK_Device *)(f->d);
    struct Disk_Block_Op *op = (struct Disk_Block_Op *)x;

    switch(cmd){

    default:
        kprintf( "udsk_ioctl: unknown ioctl %d\n", cmd );
        break;
    }
    return -1;
}

int
udsk_stat(FILE *f, struct stat *s){
    struct UDSK_Device *hd = (struct UDSK_Device *)(f->d);



    s->dev     = 0;
    s->size    = DISKSIZE;
    s->blksize = 512;
    s->flags   = SSF_BLKWRITE | SSF_NOERASE;
    s->mode    = 0;
    return 0;
}
