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



extern struct Disk_Conf disk_device[];
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
	hdc[c].hd[dk].disk    = 0;

	if( hdc_probe( &hdc[i], dk ) ){

	    bootmsg("%s unit %d %d cyl, %d sect, %d hd, %dkB\n",
		    dev->name, dk,
		    hdc[c].hd[dk].ncyl, hdc[c].hd[dk].nsect, hdc[c].hd[dk].nhead,
		    hdc[c].hd[dk].ncyl * hdc[c].hd[dk].nsect * hdc[c].hd[dk].nhead / 2
		);

            disk_learn( dev, &hdc[c].hd[dk].file, hdc[c].hd[dk].blks );

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

    for(n=0; n<512; n+=2){
	w = inw( port + IDE_R_DATA );
	buf[n] = w;
	buf[n+1] = w>>8;
    }

    dev->hd[unit].nhead = ((u_short*)buf)[3];
    dev->hd[unit].ncyl  = ((u_short*)buf)[1];
    dev->hd[unit].nsect = ((u_short*)buf)[6];

    dev->hd[unit].blk = dev->hd[unit].nhead * dev->hd[unit].ncyl * dev->hd[unit].nsect;

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



int hdc_xfer(struct HDC_Device *dev, int writep, int unit, offset_t blk, int len, u_char *buf){
    int port, n, st, plx, w;
    int hd, sec, cyl, cnt;

    XE9('X');
    XE9('<');
    port = dev->port;
    /* E9PRINTF(("\nhdcxfer %c dev %x, prt %x, u %d, blk %d, len %d, nhd %d, ncyl %d, nsec %d, DBS %d\n",
       (writep ? '	w' : 'r'),
       dev, port, unit, blk, len,
       dev->params[unit].nhead, dev->params[unit].nsect, dev->params[unit].ncyl, DISK_BLOCK_SIZE));
       dumpmem(buf, 32, "hdc xfer w ");
    */
    port = dev->port;
    sec = blk % dev->hd[unit].nsect;
    cyl = (blk / dev->hd[unit].nsect) % dev->hd[unit].ncyl;
    hd  = blk / (dev->hd[unit].ncyl * dev->hd[unit].nsect);
    cnt = (len + DISK_BLOCK_SIZE - 1) / DISK_BLOCK_SIZE;

    XE9('a');

    spin_lock( &dev->lock );
    plx = spldisk();
    XE9('b');
    hdc_command( dev, unit, hd, cyl, sec, cnt,
		 writep ? IDE_CMD_WRITE_RETRY : IDE_CMD_READ_RETRY );
    XE9('c');

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
	    spin_unlock( &dev->lock );
	    return n;
	}
    }
    XE9('d');
    XE9('d');

    if( writep ){
	rep_outsw(port + IDE_R_DATA, buf, len/2);
    }else{
	rep_insw(port + IDE_R_DATA, buf, len/2);
    }

    XE9('e');
    XE9('e');
    splx(plx);
    spin_unlock( &dev->lock );
    XE9('>');
    return 0;
}


int
hdc_command(struct HDC_Device *dev, int unit, int hd, int cyl, int sec, int cnt, int cmd){
    int port = dev->port;
    int st, plx;

    XE9('C');
    XE9('<');
    /* E9PRINTF(("\nhdccmd u %d, hd %d, cyl %d, sec %d, cnt %d, cmd %x\n",
       unit, hd, cyl, sec, cnt, cmd)); */

    /* 1. Wait for drive to clear BUSY. */
    while( 1 ){
	st = inb( port + IDE_R_STAT );
	if( !(st & IDE_STAT_BUSY) ){
	    /* E9PRINTF(("\nhdccmd %x %d\n", port, st)); */
	    plx = spldisk();
	    /* recheck */
	    st = inb( port + IDE_R_STAT );
	    if( !(st & IDE_STAT_BUSY) ){
		break;
	    }
	    splx(plx);
	}
    }

    XE9('a');
    /* 2. Load required parameters in the Command Block Registers. */
    outb( port + IDE_R_WCOMP, 0 );
    outb( port + IDE_R_DRHD,  (unit<<4 | hd | 0xA0) );
    outb( port + IDE_R_HCYL,  cyl>>8 );
    outb( port + IDE_R_LCYL,  cyl & 0xFF );
    outb( port + IDE_R_SECT,  sec + 1 );
    outb( port + IDE_R_NSECT, cnt);

    /* 3. Activate the Interrupt Enable (nIEN) bit. */
    /* we are not using interrupt driven i/o here (yet) */
    XE9('b');

    /* 4. Wait for drive to set DRDY. */
    do{
	st = inb( port + IDE_R_STAT );
    }while( !(st & IDE_STAT_READY) );

    XE9('c');
    /* 5. Write the command code to the Command Register. */
    outb( port + IDE_R_CMD,   cmd );
    XE9('d');

    splx(plx);
    XE9('>');
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

