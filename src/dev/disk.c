/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: 
 
  $Id$

*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <alloc.h>
#include <error.h>
#include <msgs.h>
#include <dev.h>
#include <ioctl.h>
#include <disk.h>
#include <fs.h>


extern struct Disk_Conf disk_device[];

struct Disk {
    struct Disk_Conf *conf;
    int 	unit;			/* unit number on controller */
    int 	part;			/* partition number */
    u_long 	flags;

    u_long 	part_offset;		/* offset of partition */
    u_long 	part_len;		/* length of partition */

    u_long 	filepos;

    FILE 	file;			/* this device */
    FILE 	*fcont;			/* underlying device */
} disk [ N_DISK ];

int disk_read(FILE*,char*,int);
int disk_write(FILE*,const char*,int);
int disk_bread(FILE*,char*,int,int);
int disk_bwrite(FILE*,const char*,int,int);
int disk_stat(FILE*, struct stat*);
int disk_seek(FILE*, long, int);
long disk_tell(FILE*);
int disk_ioctl(FILE*, int, void*);
int disk_flush(FILE*);

static const struct io_fs disk_fs = {
    0, /* putc */
    0, /* getc */
    0, /* close */
    0, /* flush */
    0, /* status */
    disk_read,
    disk_write,
    disk_bread,
    disk_bwrite,
    disk_seek,
    disk_tell,
    disk_stat,
    disk_ioctl,
};




int
disk_init(int unit, int start, int len, FILE *cont){
    struct Disk_Conf *cf = disk_device + unit;
    struct Disk      *dk = disk + unit;

    dk->unit  = unit;
    dk->part  = cf->part;
    dk->flags = cf->flags;
    dk->filepos = 0;
    dk->fcont   = cont;
    dk->conf    = cf;

    dk->part_offset = start;
    dk->part_len    = len;

    finit( & dk->file );
    dk->file.d = (void*)dk;
    dk->file.fs = &disk_fs;

    mount( & dk->file, cf->mntpt, 0, cf->fstype );

    bootmsg( "%s unit %d mounted on %s type %s\n",
	     cf->cntrlnm, dk->unit, cf->mntpt, cf->fstype );

    char *buf;
    /* also mount as special device file */
    buf = alloc( strlen(cf->mntpt) + 1 );
    strcpy( buf, cf->mntpt );
    buf[ strlen(cf->mntpt) - 1 ] = 0;
    mount( & dk->file, buf, 1, 0);
    free( buf, strlen(cf->mntpt) + 1 );

    return 1;

}

int
disk_read(FILE *f, char *buf, int len){
    struct Disk *dev;
    int r;

    if(!f) return;
    dev = (struct Disk *)f->d;
    r = disk_bread(f, buf, len, dev->filepos);
    dev->filepos += len;
    return r;
}

int
disk_write(FILE *f, const char *buf, int len){
    struct Disk *dev;
    int r;

    if(!f) return;
    dev = (struct Disk *)f->d;
    r = disk_bwrite(f, buf, len, dev->filepos);
    dev->filepos += len;
    return r;
}

int
disk_bread(FILE *f, char *buf, int len, int pos){
    struct Disk *dev;

    if(!f) return;
    dev = (struct Disk *)f->d;

    if( pos + len > dev->part_len ){
	kprintf("%s unit %d: attempt to read past end of device\n", dev->conf->cntrlnm, dev->unit);
	return -1;
    }

    return fbread(dev->fcont, buf, len, pos + dev->part_offset);
}

int
disk_bwrite(FILE *f, const char *buf, int len, int pos){
    struct Disk *dev;

    if(!f) return;
    dev = (struct Disk *)f->d;

    if( pos + len > dev->part_len ){
	kprintf("%s unit %d: attempt to write past end of device\n", dev->conf->cntrlnm, dev->unit);
	return -1;
    }

    return fbwrite(dev->fcont, buf, len, pos + dev->part_offset);

}


int
disk_seek(FILE *f, long off, int how){
    struct Disk *d;

    d = f->d;

    if( how == 0 ){
        d->filepos = off;
    }else if( how == 1 ){
        d->filepos += off;
    }else{
        d->filepos = d->part_len - off;
    }
    return 0;
}

long
disk_tell(FILE *f){
    struct Disk *d;

    d = f->d;
    return d->filepos;
}

int
disk_stat(FILE *f, struct stat *s){
    struct Disk *d;

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

