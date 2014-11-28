/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Dec-29 13:01 (EST)
  Function: use on chip flash for storage

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

#include <stm32.h>

// currently, we only support sector 11 (the last sector)
#define FLASHSECT	11
#define BLOCKSIZE	(128*1024)

extern struct Flash_Conf flash_device[];
extern FILE *flfs_open(MountEntry *, const char *, const char *);
extern int n_flashdev;


static struct Flash_Disk {
    FILE 	file;
    struct Flash_Conf	*conf;
    lock_t 	lock;

    u_char 	*addr;
    int 	size;

} fldsk[ N_FLASHDEV ];


int stflash_bread(FILE*,char*,int,offset_t);
int stflash_bwrite(FILE*,const char*,int,offset_t);
int stflash_stat(FILE*, struct stat*);
int stflash_ioctl(FILE*, int, void*);
static int erase(struct Flash_Disk *, int);
static void send_cmd(struct Flash_Disk *, struct Flash_Command);

static const struct io_fs stflash_port_fs = {
    0, 0,	/* putchar, getchar */
    0, 0, 	/* close, flush */
    0, 		/* status */
    0, 0,	/* read, write */
    stflash_bread,
    stflash_bwrite,
    0, 0, 	/* seek, tell */
    stflash_stat,
    stflash_ioctl
};

int
stflash_init(struct Device_Conf *dev){
    int i;
    const char *nm;
    const char *type;
    char mntpt[16];

    for (i=0; i<n_flashdev; i++ ){
        fldsk[i].conf   = flash_device + i;
        fldsk[i].size   = flash_device[i].size;
        fldsk[i].addr   = flash_device[i].addr;

        finit( & fldsk[i].file );
        fldsk[i].file.d = (void*)& fldsk[i];
        fldsk[i].file.fs = & stflash_port_fs;

        if( flash_device[i].fstype )
            type = flash_device[i].fstype;
        else
            type = "flfs";

        /* mount filesystem */
        if( flash_device[i].mntpt ){
            fmount( & fldsk[i].file, nm=flash_device[i].mntpt, type );
        }else{
            /* mount point not specified, use mem# */
            snprintf(mntpt, 16, "mem%d:", i);
            fmount( & fldsk[i].file, nm=mntpt, type );
        }

        /* also create special device file */
        snprintf(mntpt, 16, "mem%d", i);
        fmount( & fldsk[i].file, mntpt, 0 );

        if( fldsk[i].addr ){
            bootmsg("mem%d %d bytes @ 0x%X mounted on %s type %s\n",
                    i, fldsk[i].size, fldsk[i].addr, nm, type);
        }
    }

    return 0;
}

int stflash_stat(FILE *f, struct stat *s){
    struct Flash_Disk *d;

    d = f->d;

    s->dev     = 0;
    s->size    = d->size;
    s->blksize = BLOCKSIZE;
    s->flags   = SSF_BIGERASE;
    s->mode    = 0;
    return 0;
}

int
stflash_bread(FILE *f, char *buf, int len, offset_t offset){
    struct Flash_Disk *d;
    int fd, i;

    d = f->d;

    if( offset >= d->size )
        return 0;

    memcpy(buf, (char*)d->addr + offset, len);
    return len;
}

static void
ststart(struct Flash_Disk *d){
    sync_lock( & d->lock, "flash" );
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
}

static void
stfinish(struct Flash_Disk *d){
    FLASH->CR |= 1<<31;
    sync_unlock( & d->lock );
}

static void
wait_not_busy(void){
    while(1){
        int b = FLASH->SR & (1<<16);
        if( !b ) return;
    }
}

int
stflash_bwrite(FILE *f, const char *b, int len, offset_t offset){
    struct Flash_Disk *d;
    const unsigned long *src = (unsigned long*)b;
    int i;

    d = f->d;
    unsigned long *dst = (unsigned long*)(d->addr + offset);

    if( offset >= d->size )
        return 0;

    // kprintf("stf write %d @ %x => %x\n", len, b, dst);
    ststart(d);
    FLASH->CR |= (2<<8) | 1;	// 32 bits, enable program

    len /= 4;
    for(i=0; i<len; i++){
        wait_not_busy();
        dst[i] = src[i];
    }

    wait_not_busy();
    FLASH->CR &= ~1;		// disable program
    stfinish(d);

    return len;
}

int
stflash_ioctl(FILE* f, int cmd, void* a){

    if( ((cmd >> 8) & 0xFF) != 'm' )
        return -1;

    switch( cmd & 0xFF ){
    case 'e':		/* erase */
        return erase(f->d, (int)a);
        break;

    default:
        return -1;
    }
}


static int
erase(struct Flash_Disk *fdk, int a){

    kprintf("stm32 flash erase\n");
    ststart(fdk);
    wait_not_busy();
    FLASH->CR |= (FLASHSECT<<3) | 2;	// sector erase
    FLASH->CR |= 1<<16;			// start
    wait_not_busy();
    FLASH->CR &= ~( (FLASHSECT<<3) | 2 | (1<<16) );
    stfinish(fdk);
    return 0;
}

int
stflash_noop(FILE *f){
    return 1;
}

