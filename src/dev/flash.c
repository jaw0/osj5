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
#include <arch.h>
#include <proc.h>
#include <alloc.h>
#include <locks.h>
#include <ioctl.h>
#include <flash.h>
#include <dev.h>
#include <fs.h>

extern struct Flash_Conf flash_device[];
extern FILE *flfs_open(MountEntry *, const char *, const char *);
extern int n_flashdev;


struct Flash_Disk {
    FILE 	file;
    struct Flash_Conf	*conf;
    lock_t 	lock;
    int 	manuf;
    int 	devid;
    u_long 	offset;

    u_char 	*addr;
    int 	size;
    int 	blksz;
    u_long	flags;

} fldsk[ N_FLASHDEV ];


int flash_putchar(FILE *, char);
int flash_getchar(FILE*);
int flash_noop(FILE*);
int flash_read(FILE*,char*,int);
int flash_write(FILE*,const char*,int);
int flash_bread(FILE*,char*,int,int);
int flash_bwrite(FILE*,const char*,int,int);
int flash_stat(FILE*, struct stat*);
int flash_seek(FILE*, long, int);
long flash_tell(FILE*);
int flash_ioctl(FILE*, int, void*);
static int flash_learn(int);
static int erase(struct Flash_Disk *, int);
static void send_cmd(struct Flash_Disk *, struct Flash_Command);

static const struct io_fs flash_port_fs = {
    flash_putchar,
    flash_getchar,
    flash_noop, /* close */
    flash_noop, /* flush */
    0, /* status */
    flash_read,
    flash_write,
    flash_bread,
    flash_bwrite,
    flash_seek,
    flash_tell,
    flash_stat,
    flash_ioctl
};

int
flash_init(struct Device_Conf *dev){
    int i;
    const char *nm;
    const char *type;
    char mntpt[16];

    for (i=0; i<n_flashdev; i++ ){
        fldsk[i].conf   = flash_device + i;
        fldsk[i].size   = flash_device[i].size;
        fldsk[i].blksz  = flash_device[i].blksz;
        fldsk[i].addr   = flash_device[i].addr;
        fldsk[i].flags  = flash_device[i].flags;
        fldsk[i].offset = 0;

        if( ! flash_learn( i ) ){
            finit( & fldsk[i].file );
            fldsk[i].file.d = (void*)& fldsk[i];
            fldsk[i].file.fs = & flash_port_fs;
            fldsk[i].offset = 0;

            if( fldsk[i].flags & SSF_NOERASE ){
                /* RAM - alloc and format it */
                if( ! fldsk[i].addr )
                    fldsk[i].addr = alloc( fldsk[i].size );
                memset((char*)fldsk[i].addr, 0xFF, fldsk[i].size);
            }

            if( flash_device[i].fstype )
                type = flash_device[i].fstype;
            else
                type = "flfs";

            /* mount filesystem */
            if( flash_device[i].mntpt ){
                mount( & fldsk[i].file, nm=flash_device[i].mntpt, 0, type );
            }else{
                /* mount point not specified, use mem# */
                snprintf(mntpt, 16, "mem%d:", i);
                mount( & fldsk[i].file, nm=mntpt, 0, type );
            }

            /* also create special device file */
            snprintf(mntpt, 16, "mem%d", i);
            mount( & fldsk[i].file, mntpt, 1, 0 );

            if( fldsk[i].addr ){
                bootmsg("mem%d %d bytes @ 0x%X mounted on %s type %s\n",
                        i, fldsk[i].size, fldsk[i].addr, nm, type);
            }
#ifdef PLATFORM_EMUL
            else{
                bootmsg("mem%d %d bytes @ UNIX ./disk mounted on %s type %s\n",
                        i, fldsk[i].size, nm, type);
            }
#endif
        }
    }

    return 0;
}

int flash_stat(FILE *f, struct stat *s){
    struct Flash_Disk *d;

    d = f->d;

    s->dev     = 0;
    s->size    = d->size;
    s->blksize = d->blksz;
    s->flags   = d->flags;
    s->mode    = 0;
    return 0;
}

int flash_seek(FILE *f, long off, int how){
    struct Flash_Disk *d;

    d = f->d;

    if( how == 0 ){
        d->offset = off;
    }else if( how == 1 ){
        d->offset += off;
    }else{
        d->offset = d->size - off;
    }
    return 0;
}

long flash_tell(FILE *f){
    struct Flash_Disk *d;

    d = f->d;

    return d->offset;
}

#ifdef PLATFORM_EMUL
//extern int lseek(int, off_t, int);
#endif

int
flash_read(FILE *f, char *buf, int len){
    struct Flash_Disk *d = f->d;
    int i = flash_bread(f, buf, len, d->offset);
    if(i>0) d->offset += i;
    return i;
}

int
flash_write(FILE *f, const char *buf, int len){
    struct Flash_Disk *d = f->d;
    int i = flash_bwrite(f, buf, len, d->offset);
    if(i>0) d->offset += i;
    return i;
}

int
flash_bread(FILE *f, char *buf, int len, int offset){
    struct Flash_Disk *d;
    int fd, i;

    d = f->d;

    if( offset >= d->size )
        return 0;

#ifdef PLATFORM_EMUL
    if( ! d->addr ){
        fd = open("disk", 2);
        lseek(fd, offset, 0);
        i = read(fd, buf, len);
        close(fd);
        return i;
    }
#endif
    memcpy(buf, (char*)d->addr + offset, len);
    return len;
}

int
flash_bwrite(FILE *f, const char *b, int len, int offset){
    struct Flash_Disk *d;
    const u_char *buf = b;
    int fd, i;

    d = f->d;

    if( offset >= d->size )
        return 0;

#ifdef PLATFORM_EMUL
    if( ! d->addr ){
        fd = open("disk", 2);
        lseek(fd, offset, 0);
        i = write(fd, buf, len);
        close(fd);
        return i;
    }
#endif

    switch( d->manuf ){
    case FLM_NONE:
        memcpy((char*)d->addr + offset, buf, len);
        break;

    case FLM_AMD:
    case FLM_SSTI:
        /* ~ 7 us per byte */
        spin_lock( & d->lock );
        for(i=0; i<len; i++){
            send_cmd(d, CMD_BYTEWRITE);
            d->addr[ offset + i ] = buf[i];

            while( d->addr[ offset + i ] & 0x80 != buf[i] & 0x80 ){
                if( d->addr[ offset + i ] & 0x20 &&
                    d->addr[ offset + i ] & 0x80 != buf[i] & 0x80 ){
                    spin_unlock( & d->lock );
                    return i;
                }
            }
        }
        spin_unlock( & d->lock );
        break;

    case FLM_ATMEL:
        if( offset & ~(d->blksz-1) != offset ){
            fprintf(STDERR, "unaligned write to atmel device off=0x%x\n", offset);
            return -1;
        }
        if( len & ~(d->blksz-1) != len ){
            fprintf(STDERR, "partial block write to atmel device len=%d\n", len);
            return -1;
        }

        spin_lock( & d->lock );

        i = 0;
        while( i < len ){
            int n, l;

            /* only one pblk at a time */
            l = len - i;
            if( l > d->blksz ){
                l = d->blksz;
            }

            int plx = splhigh();	/* bytes must be written w/in 150us of each other */
            send_cmd(d, CMD_BYTEWRITE);
            for(n=0; n<l; n++){
                d->addr[ offset + i + n ] = buf[i + n];
            }
            splx(plx);

            while( d->addr[ offset + i ] & 0x80 != buf[i] & 0x80 ){
                if( d->addr[ offset + i ] & 0x20 &&
                    d->addr[ offset + i ] & 0x80 != buf[i] & 0x80 ){
                    spin_unlock( & d->lock );
                    return i;
                }
            }
            i += l;
        }
        spin_unlock( & d->lock );
        break;

    }

    return len;
}

int
flash_ioctl(FILE* f, int cmd, void* a){

    if( (cmd >> 8) & 0xF != 'm' )
        return -1;

    switch( cmd & 0xF ){

    case 'e':		/* erase */
        return erase(f->d, (int)a);
        break;

    default:
        return -1;
    }
}


static int
flash_learn(int i){
    int size, bsize;

    struct Flash_Disk *fdk = fldsk + i;

    if( fdk->flags & SSF_NOERASE || fdk->flags & SSF_READONLY ){
        /* ram or ROM */
        fdk->manuf = FLM_NONE;
        fdk->devid = 0;
        return 0;
    }

#ifdef PLATFORM_EMUL
    if( ! fdk->addr ){
        fdk->manuf = fdk->devid = 0;
        return 0;
    }
#endif

    spin_lock( & fdk->lock );
    send_cmd(fdk, CMD_READID);
    usleep( 10000 );		/* atmel specs say to wait 10ms */
    fdk->manuf = fdk->addr[0];
    fdk->devid = fdk->addr[1];
    send_cmd(fdk, CMD_READ);
    spin_unlock( & fdk->lock );

    switch( fdk->manuf ){
    case FLM_AMD:
        switch( fdk->devid ){
        case FLD_AMD29F010:	size =  128 * 1024;	break;
        case FLD_AMD29F040:	size =  512 * 1024;	break;
        case FLD_AMD29F080:	size = 1024 * 1024;	break;
        case FLD_AMD29F016:	size = 2048 * 1024;	break;
        default:		size = 0;		break;
        }
        if( ! fdk->size  ) fdk->size  = size;
        if( ! fdk->blksz ) fdk->blksz = 64*1024;

        if( !size || fdk->blksz != 64*1024 ){
            fprintf(STDERR, "unknown or misconfigured %s flash at %X (%s) type %d - not configuring\n",
                    "AMD", fdk->addr, flash_device[i].mntpt, fdk->devid);
            return -1;
        }
        break;

    case FLM_ATMEL:
        switch( fdk->devid ){
        case FLD_AT29C010:	size =  128 * 1024;	bsize = 128;	break;
        case FLD_AT29C020:	size =  256 * 1024;	bsize = 256;	break;
        case FLD_AT29C040:	size =  512 * 1024;	bsize = 256;	break;
        default:		size = 0;				break;
        }
        if( ! fdk->size  ) fdk->size  = size;
        if( ! fdk->blksz ) fdk->blksz = 64*1024;
        fdk->flags |= SSF_BLKWRITE;

        if( !size || fdk->blksz != bsize ){
            fprintf(STDERR, "unknown or misconfigured %s flash at %X (%s) type %d - not configuring\n",
                    "Atmel", fdk->addr, flash_device[i].mntpt, fdk->devid);
            return -1;
        }
        break;

    case FLM_SSTI:
        switch( fdk->devid ){
        case FLD_SSTI39F020:	size =  256 * 1024;	bsize = 4096;		break;
        case FLD_SSTI39F040:	size =  512 * 1024;	bsize = 4096;		break;
        case FLD_SSTI39F080:	size = 1024 * 1024;	bsize = 64 * 1024;	break;
        case FLD_SSTI39F016:	size = 2048 * 1024;	bsize = 4096;		break;
        default:		size = 0;					break;
        }
        if( ! fdk->size  ) fdk->size  = size;
        if( ! fdk->blksz ) fdk->blksz = bsize;
        if( !size || fdk->blksz != bsize ){
            fprintf(STDERR, "unknown or misconfigured %s flash at %X (%s) type %d - not configuring\n",
                    "SSTI", fdk->addr, flash_device[i].mntpt, fdk->devid);
            return -1;
        }
        break;

    default:
        fprintf(STDERR, "Flash device at 0x%x (%s) unknown manufacturer (%d) - not configuring\n",
                fdk->addr, flash_device[i].mntpt, fdk->manuf);
        return -1;
    }
    return 0;
}

static int
erase(struct Flash_Disk *fdk, int a){

    if( a & ~(fdk->blksz - 1) != a ){
        fprintf(STDERR, "unaligned erase a=0x%x\n", a);
        return -1;
    }

    switch( fdk->manuf ){
    case FLM_AMD:
    case FLM_SSTI:
        /* ~ 1 sec */
        spin_lock( & fdk->lock );
        send_cmd(fdk, CMD_SECTERASE);
        fdk->addr[ a ] = 0x30;

        while( !(fdk->addr[ a ] & 0x80) ){
            if( fdk->addr[ a ] & 0x20 && !(fdk->addr[ a ] & 0x80) ){
                /* timed out */
            }
            usleep(250000);
        }
        spin_lock( & fdk->lock );
        break;

    case FLM_ATMEL:
        break;

    default:
        break;
    }

    return 0;
}

int
flash_getchar(FILE *f){
    char c;

    if( f->flags & F_EOF )
        return -1;

    flash_read(f, &c, 1);
    return c;
}

int
flash_noop(FILE *f){
    return 1;
}

int
flash_putchar(FILE *f, char c){
    return flash_write(f, &c, 1);
}

/******************************************************************/

static void
send_cmd(struct Flash_Disk *fdk, struct Flash_Command c){
    volatile char *a;
    int i;

    a = fdk->addr;
    for(i=0; i<c.n; i++){
        a[c.c[i].addr] = c.c[i].data;
    }
}

