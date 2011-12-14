/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: disk partitions
 
  $Id$

*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <alloc.h>
#include <error.h>
#include <misc.h>
#include <msgs.h>
#include <dev.h>
#include <ioctl.h>
#include <disk.h>
#include <fs.h>


extern struct Disk_Conf disk_device[];

struct DiskPart {
    char	name[16];
    u_long 	flags;

    offset_t 	part_offset;		/* offset of partition */
    offset_t 	part_len;		/* length of partition */

    FILE 	file;			/* this device */
    FILE 	*fdev;			/* underlying device */
};

int disk_bread(FILE*,char*,int,offset_t);
int disk_bwrite(FILE*,const char*,int,offset_t);
int disk_stat(FILE*, struct stat*);
int disk_ioctl(FILE*, int, void*);
int disk_flush(FILE*);

static const struct io_fs disk_fs = {
    0, /* putc */
    0, /* getc */
    0, /* close */
    0, /* flush */
    0, /* status */
    0, 0, /* read, write */
    disk_bread,
    disk_bwrite,
    0, 0, /* seek, tell */
    disk_stat,
    disk_ioctl,
};

const struct {
    int mbrtype;
    const char *fstype;
} mbr_types[] = {
    {   1, "msdosfs" },
    {   4, "msdosfs" },
    {   6, "msdosfs" },
    { 0xB, "msdosfs" },
    { 0xC, "msdosfs" },
    { 0xE, "msdosfs" },
};

static const char *
mbr_fs(int mt){
    int i;

    for(i=0; i<ELEMENTSIN(mbr_types); i++){
        if( mt == mbr_types[i].mbrtype ) return mbr_types[i].fstype;
    }
    return 0;
}

int
disk_learn(struct Device_Conf *cf, const char *pfx, int dkno, FILE *fdev, offset_t blks){
    int i;

    // read part table
    struct Disk_MBR *mbr = alloc(512);

    if( mbr->mbrsig != DISK_MBR_SIG ){
        // entire disk
        // determine type from data
        const char *fstype = "flfs";
        disk_init(cf, pfx, dkno, 0, 0, blks * DISK_BLOCK_SIZE, fdev, fstype);
        free(mbr, 512);
        return 0;
    }

    for(i=0; i<4; i++){
        const char *fstype = mbr_fs( mbr->part[i].type );
        disk_init(cf, pfx, dkno, i, mbr->part[i].lba_start * DISK_BLOCK_SIZE, mbr->part[i].num_blks * DISK_BLOCK_SIZE, fdev, fstype);
    }

    free(mbr, 512);
    return 0;
}

int
disk_init(struct Device_Conf *cf, const char *pfx, int dkno, int partno, int start, int len, FILE *cont, const char *fstype){
    struct DiskPart *dkp = alloc(sizeof(struct DiskPart));

    // name this
    snprintf(dkp->name, sizeof(dkp->name), "%s%d%c:", pfx, dkno, partno + 'a');

    dkp->flags       = cf->flags;
    dkp->fdev        = cont;
    dkp->part_offset = start;
    dkp->part_len    = len;

    finit( & dkp->file );
    dkp->file.d = (void*)dkp;
    dkp->file.fs = &disk_fs;

    fmount( & dkp->file, dkp->name, 0);
    if( fstype ) fmount( & dkp->file, dkp->name, fstype );

    bootmsg( "%s unit %d/%d mounted on %s type %s\n",
	     cf->name, dkno, partno, dkp->name, fstype );

    return 0;
}


int
disk_bread(FILE *f, char *buf, int len, offset_t pos){
    struct DiskPart *dev;

    if(!f) return;
    dev = (struct DiskPart *)f->d;

    if( pos + len > dev->part_len ){
	kprintf("%s attempt to read past end of device\n", dev->name);
	return -1;
    }

    return fbread(dev->fdev, buf, len, pos + dev->part_offset);
}

int
disk_bwrite(FILE *f, const char *buf, int len, offset_t pos){
    struct DiskPart *dev;

    if(!f) return;
    dev = (struct DiskPart *)f->d;

    if( pos + len > dev->part_len ){
	kprintf("%s attempt to write past end of device\n", dev->name);
	return -1;
    }

    return fbwrite(dev->fdev, buf, len, pos + dev->part_offset);
}



int
disk_stat(FILE *f, struct stat *s){
    struct DiskPart *d;

    d = f->d;

    s->dev     = 0;
    s->size    = d->part_len;
    s->blksize = DISK_BLOCK_SIZE;
    s->flags   = d->flags;
    s->mode    = 0;
    return 0;
}

int
disk_ioctl(FILE* f, int cmd, void* a){

    if( (cmd >> 8) & 0xF != 'm' )
        return -1;

    switch( cmd & 0xF ){

    case 'e':		/* erase */
        return 0;
        break;

    default:
        kprintf( "disk_ioctl: unknown ioctl %d\n", cmd );
        return -1;
    }
}

