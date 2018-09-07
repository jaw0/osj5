/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Sep-04 15:13 (EDT)
  Function: read only disk image

*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <ioctl.h>
#include <msgs.h>
#include <dev.h>

#ifndef ROMDISK_SIZE
#  define ROMDISK_SIZE 65536
#endif


int romdsk_ioctl(FILE*, int, void*);
int romdsk_bread(FILE*, char*, int, offset_t);
int romdsk_bwrite(FILE*, const char*, int, offset_t);
int romdsk_stat(FILE *, struct stat *);

const struct io_fs romdsk_fs = {
    0, /* putc */
    0, /* getc */
    0, /* close */
    0, /* flush */
    0, /* status */
    0, /* read */
    0, /* write */
    romdsk_bread,  /* bread */
    romdsk_bwrite, /* bwrite */
    0, /* seek */
    0, /* tell */
    romdsk_stat,
    romdsk_ioctl
};


extern char romdisk_image[ ROMDISK_SIZE ];

/* the ide controllers */
struct ROMDSK_Device {
    FILE file;
} romdsk[ 1 ];


int
romdisk_init(struct Device_Conf *dev){
    int port = dev->port;
    char info[32];

    int c = dev->unit;
    finit( & romdsk[c].file );
    romdsk[c].file.d  = (void*)& romdsk[c];
    romdsk[c].file.fs = & romdsk_fs;

    bootmsg( "%s %d bytes\n", dev->name, ROMDISK_SIZE);

    // set flags=1 to not automount
    if( ! dev->flags ){
        snprintf(info, sizeof(info), "%s:", dev->name);
        fmount( & romdsk[c].file, info, "fatfs" );

        bootmsg( "%s mounted on %s type %s\n",
                 dev->name, info, "fatfs" );
    }

    return (int)& romdsk[c].file;
}

int
romdsk_bread(FILE* f, char *buf, int len, offset_t pos){
    struct ROMDSK_Device *hd = (struct ROMDSK_Device *)(f->d);

    if( pos + len > ROMDISK_SIZE ) return -1;

    memcpy(buf, romdisk_image + pos, len);
    return len;
}

int
romdsk_bwrite(FILE* f, const char *buf, int len, offset_t pos){
    struct ROMDSK_Device *hd = (struct ROMDSK_Device *)(f->d);

    if( pos + len > ROMDISK_SIZE ) return -1;

    memcpy(romdisk_image + pos, buf, len);
    return len;
}

int
romdsk_ioctl(FILE* f, int cmd, void *x){
    struct ROMDSK_Device *hd = (struct ROMDSK_Device *)(f->d);
    struct Disk_Block_Op *op = (struct Disk_Block_Op *)x;

    switch(cmd){

    default:
        kprintf( "romdsk_ioctl: unknown ioctl %d\n", cmd );
        break;
    }
    return -1;
}

int
romdsk_stat(FILE *f, struct stat *s){
    struct ROMDSK_Device *hd = (struct ROMDSK_Device *)(f->d);



    s->dev     = 0;
    s->size    = ROMDISK_SIZE;
    s->blksize = 512;
    s->flags   = SSF_READONLY;
    s->mode    = 0;
    return 0;
}
