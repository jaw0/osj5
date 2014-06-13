/*
  Copyright (c) 2001
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2001
  Function: ide hard drive
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
#include <ide.h>
#include <msgs.h>
#include <dev.h>
#include <bootflags.h>
#include <locks.h>


int hdc_ioctl(FILE*, int, void*);
int hdc_bread(FILE*, char*, int, offset_t);
int hdc_bwrite(FILE*, const char*, int, offset_t);

const struct io_fs hdc_fs = {
    0, /* putc */
    0, /* getc */
    0, /* close */
    0, /* flush */
    0, /* status */
    0, /* read */
    0, /* write */
    hdc_bread,  /* bread */
    hdc_bwrite, /* bwrite */
    0, /* seek */
    0, /* tell */
    0, /* stat */
    hdc_ioctl
};

struct HDC_Device;

/* the disks */
struct HD_Device {
    FILE file;
    int disk, ncyl, nsect, nhead;
    int blks;
    char is_lba;
    struct HDC_Device *hdc;
};

/* the ide controllers */
struct HDC_Device {
    lock_t lock;
    int port;
    int irq;
    int no;
    const char *name;

    /* each controller has up to 2 disks */
    struct HD_Device hd[2];

} hdc[ N_HDC ];


int hdc_xfer(struct HDC_Device *dev, int writep, int unit, int len, offset_t blk, u_char *buf);
int hdc_command(struct HDC_Device *dev, int unit, offset_t blk, int cnt, int cmd);


extern struct DiskPart_Conf disk_device[];
extern int n_disk;

int
hdc_init(struct Device_Conf *dev){
    int port = dev->port;

    int c = dev->unit;
    hdc[c].lock = 0;
    hdc[c].no   = c;
    hdc[c].port = dev->port;
    hdc[c].name = dev->name;
    hdc[c].irq  = dev->irq;

    bootmsg( "%s at io 0x%x irq %d\n",
	     dev->name, dev->port, dev->irq );

    int dk;
    for(dk=0; dk<2; dk++){

        finit( & hdc[c].hd[dk].file );
        hdc[c].hd[dk].file.d  = (void*)& hdc[c].hd[dk];
        hdc[c].hd[dk].file.fs = & hdc_fs;
        hdc[c].hd[dk].hdc     = hdc + c;
	hdc[c].hd[dk].ncyl    = 0;
	hdc[c].hd[dk].nsect   = 0;
	hdc[c].hd[dk].nhead   = 0;
	hdc[c].hd[dk].disk    = dk;

	if( hdc_probe( &hdc[c], dk ) ){

            dkpart_learn( dev, "hd", c*2 + dk, &hdc[c].hd[dk].file, hdc[c].hd[dk].blks );

	}else{
	    /* no disk present */
	}
    }
}

int
hdc_probe(struct HDC_Device *dev, int unit){
    int port = dev->port;
    int st, n, w, to;
    u_char *buf;
    char info[64];

    buf = (u_char*)alloc(512);

    /* hdc_command(dev, unit, 0, 0, 0, 1, IDE_CMD_IDENTIFY); */
    outb( port + IDE_R_DRHD,  unit<<4 );
    outb( port + IDE_R_CMD,   IDE_CMD_IDENTIFY );

    while( 1 ){
	st = inb( port + IDE_R_STAT );
	if( st & IDE_STAT_DATAREQ ){
	    break;
	}
	if( st & IDE_STAT_ERROR ){
	    n = inb( port + IDE_R_ERROR );
	    kprintf("%s: xfer error %=2\n", dev->name, n);
	    return 0;
	}
	/* RSN need real timeout */
	if( to++ > 1000 ){
	    free(buf);
	    return 0;
	}
    }

    rep_insw(port + IDE_R_DATA, buf, 512/2);

    u_short *sb = (u_short*)buf;

    dev->hd[unit].nhead  = sb[3];
    dev->hd[unit].ncyl   = sb[1];
    dev->hd[unit].nsect  = sb[6];
    dev->hd[unit].is_lba = (sb[49] & (1<<9)) ? 1 : 0;

    int nblk = dev->hd[unit].ncyl * dev->hd[unit].nsect * dev->hd[unit].nhead;

    dev->hd[unit].blks = nblk;

    memcpy(info, buf + 27*2, 40);
    info[40] = 0;
    // byte swap
    for(n=0; n<40; n+=2){
        char c = info[n];
        info[n] = info[n+1];
        info[n+1] = c;
    }

    // truncate padding
    for(n=39; n>0; n--){
        if( info[n] != ' ' ) break;
        info[n] = 0;
    }

    //hexdump(buf, 128);

    bootmsg("%s unit %d <%s> %d cyl, %d sect, %d hd, %dkB %s-mode\n",
            dev->name, unit, info,
            dev->hd[unit].ncyl, dev->hd[unit].nsect, dev->hd[unit].nhead,
            nblk / 2,
            (dev->hd[unit].is_lba ? "LBA" : "CHS")
        );

    free(buf);
    return 1;
}

int
hdc_bread(FILE* f, char *buf, int len, offset_t pos){
    struct HD_Device *hd = (struct HD_Device *)(f->d);

    return hdc_xfer(hd->hdc, 0, hd->disk, len, pos/DISK_BLOCK_SIZE, buf);
}

int
hdc_bwrite(FILE* f, const char *buf, int len, offset_t pos){
    struct HD_Device *hd = (struct HD_Device *)(f->d);

    return hdc_xfer(hd->hdc, 1, hd->disk, len, pos/DISK_BLOCK_SIZE, (char*)buf);
}


int
hdc_xfer(struct HDC_Device *dev, int writep, int unit, int len, offset_t blk, u_char *buf){
    int port, n, st, plx, w;
    int hd, sec, cyl, cnt;

    port = dev->port;
    cnt  = (len + DISK_BLOCK_SIZE - 1) / DISK_BLOCK_SIZE;

    sync_lock( &dev->lock, "ide" );
    plx = spldisk();

    hdc_command( dev, unit, blk, cnt,
		 writep ? IDE_CMD_WRITE_RETRY : IDE_CMD_READ_RETRY );

    /* RSN - DMA */

    /* wait for DRQ */
    while( 1 ){
	st = inb( port + IDE_R_STAT );
	if( st & IDE_STAT_DATAREQ ){
	    st = inb( port + IDE_R_STAT );
	    if( st & IDE_STAT_DATAREQ ){
		break;
	    }
	}
	if( st & IDE_STAT_ERROR ){
	    n = inb( port + IDE_R_ERROR );
	    kprintf("%s: xfer error %=2\n", dev->name, n);
	    splx(plx);
	    sync_unlock( &dev->lock );
	    return n;
	}
    }

    if( writep ){
	rep_outsw(port + IDE_R_DATA, buf, len/2);
    }else{
	rep_insw(port + IDE_R_DATA, buf, len/2);
    }

    splx(plx);
    sync_unlock( &dev->lock );

    return len;
}


#define BYTE(b, s)	(((b)>>(s))&0xFF)

int
hdc_command(struct HDC_Device *dev, int unit, offset_t blk, int cnt, int cmd){
    int port = dev->port;
    struct HD_Device *hd = & dev->hd[unit];
    int st, plx;

    /* 1. Wait for drive to clear BUSY. */
    while( 1 ){
	st = inb( port + IDE_R_STAT );
	if( !(st & IDE_STAT_BUSY) ){
	    plx = spldisk();
	    /* recheck */
	    st = inb( port + IDE_R_STAT );
	    if( !(st & IDE_STAT_BUSY) ){
		break;
	    }
	    splx(plx);
	}
    }

    /* 2. Load required parameters in the Command Block Registers. */
    outb( port + IDE_R_WCOMP, 0 );
    outb( port + IDE_R_NSECT, cnt);

    if( hd->is_lba ){
        // LBA mode
        outb( port + IDE_R_DRHD,  (unit<<4 | (BYTE(blk,24)&0xF) | 0xE0) );
        outb( port + IDE_R_HCYL,  BYTE(blk, 16));
        outb( port + IDE_R_LCYL,  BYTE(blk, 8));
        outb( port + IDE_R_SECT,  BYTE(blk, 0));
    }else{
        // C-H-S mode
        int sec  = blk % hd->nsect;
        int cyl  = (blk / hd->nsect) % hd->ncyl;
        int head = blk / (hd->ncyl * hd->nsect);

        outb( port + IDE_R_DRHD,  (unit<<4 | head | 0xA0) );
        outb( port + IDE_R_HCYL,  cyl>>8 );
        outb( port + IDE_R_LCYL,  cyl & 0xFF );
        outb( port + IDE_R_SECT,  sec + 1 );
    }

    /* 3. Activate the Interrupt Enable (nIEN) bit. */
    /* RSN - we are not using interrupt driven i/o here (yet) */

    /* 4. Wait for drive to set DRDY. */
    do{
	st = inb( port + IDE_R_STAT );
    }while( !(st & IDE_STAT_READY) );

    /* 5. Write the command code to the Command Register. */
    outb( port + IDE_R_CMD,   cmd );

    splx(plx);

    return 0;
}

int hdc_ioctl(FILE* f, int cmd, void *x){
    struct HD_Device *hd = (struct HD_Device *)(f->d);
    struct Disk_Block_Op *op = (struct Disk_Block_Op *)x;

    switch(cmd){

    default:
        kprintf( "hdc_ioctl: unknown ioctl %d\n", cmd );
        break;
    }
    return -1;
}

