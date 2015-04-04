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
#include <misc.h>

#include <stm32.h>

#define R_FLASHKB	((unsigned short *)(0x1FFF7A22))

#define FLASHSTART	0x08000000
#define BLOCKSIZE       (128*1024)
#define BLOCKSHIFT	17

const struct Flash_Info {
    int     block;
    u_int   addr;
} flashinfo[] = {
    {  5, 0x08020000 },
    {  6, 0x08040000 },
    {  7, 0x08060000 },
    {  8, 0x08080000 },
    {  9, 0x080A0000 },
    { 10, 0x080C0000 },
    { 11, 0x080E0000 },
        // 12-16: a bunch of small blocks
    { 17, 0x08120000 },
    { 18, 0x08140000 },
    { 19, 0x08160000 },
    { 20, 0x08180000 },
    { 21, 0x081A0000 },
    { 22, 0x081C0000 },
    { 23, 0x081E0000 },
};

extern struct Flash_Conf flash_device[];
extern FILE *flfs_open(MountEntry *, const char *, const char *);
extern int n_flashdev;
extern const u_char* _etext;

static struct Flash_Disk {
    FILE               file;
    lock_t             lock;
    int                blocks;
    const struct Flash_Conf *conf;
    const struct Flash_Info *info;

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
    short i, n, ba=-1, bz=-1;
    const char *nm;
    const char *type;
    char mntpt[16];

    /*
       determine size of flash
       determine end of code
       determine what we can use
    */
    u_int fend = FLASHSTART + ((*R_FLASHKB) << 10);

    for(n=0; n<ELEMENTSIN(flashinfo); n++){
        if( flashinfo[n].addr < (u_int)&_etext ) continue;
        if( flashinfo[n].addr + BLOCKSIZE > fend ) break;
        bz = n;
        if( ba == -1 ) ba = n;
    }

    for (i=0; i<n_flashdev; i++ ){
        fldsk[i].conf = flash_device + i;
        fldsk[i].info = 0;

        if( flash_device[i].addr ){
            // use specified region of flash

            // find conf for specified addr
            for(n=0; n<ELEMENTSIN(flashinfo); n++){
                if( flashinfo[n].addr == (u_int)flash_device[i].addr ){
                    fldsk[i].info = flashinfo + n;
                    break;
                }
            }

            if( ! fldsk[i].info ){
                bootmsg("mem%d cannot configure flash @ 0x%x\n", i, flashinfo[n].addr);
                return 0;
            }
            if( flash_device[i].size ){
                fldsk[i].blocks = flash_device[i].size / BLOCKSIZE;
            }else{
                fldsk[i].blocks = 1;
            }

        }else{
            // auto configure all available flash

            if( ba == -1 ){
                bootmsg("mem%d cannot configure flash. no free space\n");
                return 0;
            }
            fldsk[i].info   = flashinfo + ba;
            fldsk[i].blocks = bz - ba + 1;
        }

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

        if( fldsk[i].info ){
            bootmsg("mem%d %d bytes @ 0x%X mounted on %s type %s\n",
                    i, fldsk[i].blocks<<BLOCKSHIFT, fldsk[i].info->addr, nm, type);
        }
    }

    return 0;
}

int stflash_stat(FILE *f, struct stat *s){
    struct Flash_Disk *d;

    d = f->d;

    s->dev     = 0;
    s->size    = d->blocks << BLOCKSHIFT;
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

    if( offset >= d->blocks<<BLOCKSHIFT )
        return 0;

    int blk = offset >> BLOCKSHIFT;
    int off = offset & (BLOCKSIZE - 1);

    memcpy(buf, (char*)d->info[blk].addr + off, len);
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
    int i;

    d = f->d;

    if( offset >= d->blocks<<BLOCKSHIFT )
        return 0;

    int blk = offset >> BLOCKSHIFT;
    int off = offset & (BLOCKSIZE - 1);

    // kprintf("stf write %d @ %x => %x\n", len, b, d->addr + offset);
    ststart(d);

    if( len & 3 ){
        // not a multiple of 32bits, go byte-by-byte
        const unsigned char *src = (unsigned char*)b;
        unsigned char *dst = (unsigned char*)(d->info[blk].addr + off);
        FLASH->CR |= (0<<8) | 1;	// 8 bits, enable program

        for(i=0; i<len; i++){
            wait_not_busy();
            dst[i] = src[i];
        }

    }else{
        const unsigned long *src = (unsigned long*)b;
        unsigned long *dst = (unsigned long*)(d->info[blk].addr + off);
        FLASH->CR |= (2<<8) | 1;	// 32 bits, enable program

        len /= 4;
        for(i=0; i<len; i++){
            wait_not_busy();
            dst[i] = src[i];
        }
    }

    wait_not_busy();
    FLASH->CR &= ~1;		// disable program
    FLASH->CR &= ~(3<<8);	// clear size
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
    int blk  = a >> BLOCKSHIFT;
    int sect = fdk->info[blk].block;

    ststart(fdk);
    wait_not_busy();
    FLASH->CR |= (sect<<3) | 2;	// sector erase
    FLASH->CR |= 1<<16;			// start
    wait_not_busy();
    FLASH->CR &= ~( (sect<<3) | 2 | (1<<16) );
    stfinish(fdk);
    return 0;
}

int
stflash_noop(FILE *f){
    return 1;
}

