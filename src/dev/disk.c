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

#define MBR_PART_START	446
#define MBR_PART_LEN	16
#define MBR_PART_TYPE_OFF	4
#define MBR_PART_STARTSEC_OFF	8
#define MBR_PART_NUMSEC_OFF	12

extern int n_disk;
extern struct DiskPart_Conf dkpart_device[];
extern const struct DiskPart_Conf disk_device[];

struct DiskPart {
    char	name[16];
    u_long 	flags;

    offset_t 	part_offset;		/* offset of partition */
    offset_t 	part_len;		/* length of partition */

    FILE 	file;			/* this device */
    FILE 	*fdev;			/* underlying device */
};

static int dkpart_init(struct Device_Conf *, const char *, int, int, offset_t, offset_t, FILE *, const char *, const char *);

int dkpart_bread(FILE*,char*,int,offset_t);
int dkpart_bwrite(FILE*,const char*,int,offset_t);
int dkpart_stat(FILE*, struct stat*);
int dkpart_ioctl(FILE*, int, void*);
int dkpart_flush(FILE*);

static const struct io_fs dkpart_fs = {
    0, /* putc */
    0, /* getc */
    0, /* close */
    0, /* flush */
    0, /* status */
    0, 0, /* read, write */
    dkpart_bread,
    dkpart_bwrite,
    0, 0, /* seek, tell */
    dkpart_stat,
    dkpart_ioctl,
};

const struct {
    int mbrtype;
    const char *fstype;
} mbr_types[] = {
    {   1, "fatfs" },
    {   4, "fatfs" },
    {   6, "fatfs" },
    { 0xB, "fatfs" },
    { 0xC, "fatfs" },
    { 0xE, "fatfs" },
};

static const char *
mbr_fs(int mt){
    int i;

    for(i=0; i<ELEMENTSIN(mbr_types); i++){
        if( mt == mbr_types[i].mbrtype ) return mbr_types[i].fstype;
    }
    return 0;
}

static int
is_an_mbr(const u_char *buf){

    if( buf[510] != 0x55 ) return 0;
    if( buf[511] != 0xAA ) return 0;
    if( buf[446] & 0x7f  ) return 0;	// status of 1st partition: 80|00
    if( buf[462] & 0x7f  ) return 0;	// status of 2nd partition: 80|00
    if( buf[478] & 0x7f  ) return 0;	// status of 3rd partition: 80|00
    if( buf[494] & 0x7f  ) return 0;	// status of 4th partition: 80|00

    if( !strncmp(buf + 0x52, "FAT", 3) ) return 0;

    return 1;
}

// mbr data is unaligned + little-endian
static u_int
mbr_val(unsigned char *buf, int partno, int valoff){

    return (
        buf[MBR_PART_START + partno * MBR_PART_LEN + valoff]
        | (buf[MBR_PART_START + partno * MBR_PART_LEN + valoff + 1]<<8)
        | (buf[MBR_PART_START + partno * MBR_PART_LEN + valoff + 2]<<16)
        | (buf[MBR_PART_START + partno * MBR_PART_LEN + valoff + 3]<<24)
       );
}

static inline int
dkpart_configured(struct Device_Conf *cf, const char *pfx, int dkno, int part, FILE *fdev, offset_t start, offset_t blks){
    int partno = (part==-1) ? 0 : part;
    int i;

    // is this in the conf table?
    for(i=0; i<n_disk; i++){
        if( strcmp(pfx, disk_device[i].cntrlnm) ) continue;
        if( disk_device[i].unit != dkno ) continue;
        if( disk_device[i].part != part )   continue;

        dkpart_init(cf, pfx, dkno, partno, start, blks, fdev, disk_device[i].fstype, disk_device[i].mntpt);
        return 1;
    }

    return 0;
}


int
dkpart_learn(struct Device_Conf *cf, const char *pfx, int dkno, FILE *fdev, offset_t blks){
    int i;

    // is this in the conf table?
    if( dkpart_configured(cf, pfx, dkno, -1, fdev, 0, blks)) return 0;

    // read part table
    char *buf = alloc(512);
    fbread(fdev, buf, DISK_BLOCK_SIZE, 0);

    // RSN - is this an mbr? check more

    if( ! is_an_mbr(buf) ){
        // entire disk
        // RSN - determine type from data or config table
        const char *fstype = "fatfs";

        dkpart_init(cf, pfx, dkno, 0, 0, blks, fdev, fstype, 0);
        free(buf, 512);
        return 0;
    }

    // init all partitions
    for(i=0; i<4; i++){
        offset_t start = mbr_val(buf, i, MBR_PART_STARTSEC_OFF);
        offset_t len   = mbr_val(buf, i, MBR_PART_NUMSEC_OFF);

        // configured ?
        if( dkpart_configured(cf, pfx, dkno, i, fdev, start, len)) continue;

        // use fs type in mbr
        const char *fstype = mbr_fs( buf[MBR_PART_START + i * MBR_PART_LEN + MBR_PART_TYPE_OFF] );

        if( fstype ){
            dkpart_init(cf, pfx, dkno, i, start, len, fdev, fstype, 0);
        }
        // else ?
    }

    free(buf, 512);
    return 0;
}

static int
dkpart_init(struct Device_Conf *cf, const char *pfx, int dkno, int partno, offset_t start, offset_t len,
            FILE *cont, const char *fstype, const char *mntpt){
    struct DiskPart *dkp = alloc(sizeof(struct DiskPart));

    // name this
    if( mntpt ){
        snprintf(dkp->name, sizeof(dkp->name), "%s", mntpt);
    }else{
        snprintf(dkp->name, sizeof(dkp->name), "%s%d%c:", pfx, dkno, partno + 'a');
    }

    dkp->flags       = cf->flags;
    dkp->fdev        = cont;
    dkp->part_offset = start * DISK_BLOCK_SIZE;
    dkp->part_len    = len   * DISK_BLOCK_SIZE;

    finit( & dkp->file );
    dkp->file.d = (void*)dkp;
    dkp->file.fs = &dkpart_fs;

    fmount( & dkp->file, dkp->name, 0);
    if( fstype ) fmount( & dkp->file, dkp->name, fstype );

    bootmsg( "%s unit %d/%d %d blocks mounted on %s type %s\n",
	     cf->name, dkno, partno, len, dkp->name, fstype );

    return 0;
}


int
dkpart_bread(FILE *f, char *buf, int len, offset_t pos){
    struct DiskPart *dev;

    if(!f) return;
    dev = (struct DiskPart *)f->d;

    if( pos + len > dev->part_len ){
	kprintf("%s attempt to read past end of device (%d @%d)\n", dev->name, len, pos);
	return -1;
    }

    return fbread(dev->fdev, buf, len, pos + dev->part_offset);
}

int
dkpart_bwrite(FILE *f, const char *buf, int len, offset_t pos){
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
dkpart_stat(FILE *f, struct stat *s){
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
dkpart_ioctl(FILE* f, int cmd, void* a){

    if( (cmd >> 8) & 0xF != 'm' )
        return -1;

    switch( cmd & 0xF ){

    case 'e':		/* erase */
        return 0;
        break;

    default:
        kprintf( "dkpart_ioctl: unknown ioctl %d\n", cmd );
        return -1;
    }
}

