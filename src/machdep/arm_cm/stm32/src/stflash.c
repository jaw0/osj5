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
#include <stflash.h>
#include <userint.h>

#include <stm32.h>

#ifdef PLATFORM_STM32U5
#  define CR	NSCR
#  define SR	NSSR
#  define KEYR	NSKEYR
#endif

#ifdef PLATFORM_STM32U5
#  define WRITE_BYTES	16	// 128 bits + ecc
#elif defined(PLATFORM_STM32L4)
#  define WRITE_BYTES	8	// 64 bits + ecc
#endif

extern struct Flash_Conf flash_device[];
extern FILE *flfs_open(MountEntry *, const char *, const char *);
extern int n_flashdev;
extern const u_char* _etext;

static struct Flash_Disk {
    FILE    file;
    lock_t  lock;
    int     blocksize;
    int     totalsize;
    int     blockno;
    int     nblocks;
    u_char* addr;
    const struct Flash_Info *info;
    const struct Flash_Conf *conf;
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
    short i, n, nfi=0;
    int bksz;
    const char *nm;
    const char *type;
    char mntpt[16];

    /*
       determine size of flash
       determine end of code
       determine what we can use
    */
    const struct Flash_Info *fi = stflash_flashinfo();

    for(n=0; fi[n].addr; n++){
        nfi ++;
        bksz = fi[n].block_size * 1024;
    }

    if( !nfi ){
        // no flash avail
        return 0;
    }

    /*
      addr + size => find + use. exactly or error.
      addr only   => use addr exactly or error. sized until end of bank.
      size only   => pick addr MAX(_etext, endbank-size) push to start of block. size to end of bank.
                  => _etext to start of block. to end of bank
    */

    for (i=0; i<n_flashdev; i++ ){
        struct Flash_Disk *f = fldsk + i;
        f->conf = flash_device + i;

        u_int addr = flash_device[i].addr;
        int size   = flash_device[i].size;
        struct Flash_Info *bank = 0;

        if( !addr ){
            bank = fi + nfi - 1; // default - use last bank
            if( size ){
                addr = bank->addr + bank->nblocks * bksz - size;
                size = 0;
            }else{
                addr = ((u_int)&_etext + bksz - 1) & ~(bksz - 1);
                if( addr < bank->addr ) addr = bank->addr;
            }
        }

        if( !bank ){
            for(n=0; n<nfi; n++){
                int b = fi[n].block_size * 1024;
                if( addr < fi[n].addr ) continue;
                if( addr > fi[n].addr + fi[n].nblocks * b ) continue;
                bank = fi + n;
                bksz = b;
                break;
            }

            if( !bank ){
                bootmsg("mem%d cannot configure flash. no matching bank for addr %x\n", i, addr);
                return 0;
            }
        }

        if( !size ){
            size = bank->nblocks * bksz;
        }

        int bkoff = (addr - bank->addr) / bksz;
        f->blocksize = bksz;
        f->addr = addr;
        f->blockno = bank->blockno + bkoff;
        f->nblocks = size / bksz;
        if( f->nblocks + bkoff > bank->nblocks ) f->nblocks = bank->nblocks - bkoff;
        f->totalsize = f->nblocks * bksz;
        f->info = fi;


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
                    i, fldsk[i].totalsize, fldsk[i].addr, nm, type);
        }
    }

    return 0;
}

int stflash_stat(FILE *f, struct stat *s){
    struct Flash_Disk *d;

    d = f->d;

    s->dev     = 0;
    s->size    = d->totalsize;
    s->blksize = d->blocksize;
    s->flags   = SSF_BIGERASE;
    s->mode    = 0;
    return 0;
}

int
stflash_bread(FILE *f, char *buf, int len, offset_t offset){
    struct Flash_Disk *d;
    int fd, i;

    d = f->d;

    if( offset >= d->totalsize )
        return 0;

    // kprintf("stf read %d @ %x => %x + %x\n", len, buf, d->addr, offset);
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

void
wait_not_busy(void){
    int i;

    while(1){
        int b = FLASH->SR & (1<<16);
        if( !b ){
            FLASH->SR = 0xF3;
            for(i=0; i<1000; i++) __asm("nop");
            return;
        }
    }
}

int
stflash_bwrite(FILE *f, const char *b, int len, offset_t offset){
    struct Flash_Disk *d;
    int i;

    d = f->d;

    if( offset >= d->totalsize )
        return 0;

    kprintf("stf write %d @ %x => %x + %x\n", len, b, d->addr, offset);
    //hexdump(b, len);
    ststart(d);
    FLASH->SR = 0xFFFFFFFF;	// clear errors

#ifdef WRITE_BYTES
    // wide writes + ecc
    if( len & (WRITE_BYTES - 1) ){
        // not a multiple of N-bits, read-modify-write
        unsigned long buf[4];
        unsigned long *dst = (unsigned long*)(d->addr + (offset & ~(WRITE_BYTES - 1)));

        kprintf("rmw: len %d, dst %x+%x\n", len, dst, offset & (WRITE_BYTES - 1));

        // read
        memcpy((char*)buf, (char*)dst, WRITE_BYTES);
        // modify
        for(i=0; i<len&(WRITE_BYTES - 1); i++){
            ((char*)buf)[i + (offset & (WRITE_BYTES - 1))] = b[i];
        }
        // hexdump(buf, 8);
        // write
        FLASH->CR |= 1;	// enable program

        for(i=0; i<(WRITE_BYTES>>2); i++){
            wait_not_busy();
            dst[i] = buf[i];

            if( FLASH->SR & 0xF2 ) kprintf("err: len %d %x; @ %x, cr %x\n", len, FLASH->SR, dst + i, FLASH->CR);
            //if( dst[i] != buf[i] ) kprintf("err @%x: %x != %x\n", dst + i, dst[i], buf[i]);
        }

#else
    if( len & 3 ){
        // not a multiple of 32bits, go byte-by-byte
        const unsigned char *src = (unsigned char*)b;
        unsigned char *dst = (unsigned char*)(d->addr + offset);
        FLASH->CR |= (0<<8) | 1;	// 8 bits, enable program

        for(i=0; i<len; i++){
            wait_not_busy();
            dst[i] = src[i];
            //if( FLASH->SR & 0xF2 ) kprintf("err: %x; @ %x, cr %x\n", FLASH->SR, dst + i, FLASH->CR);
            //if( dst[i] != src[i] ) kprintf("err @%x: %x != %x\n", dst + i, dst[i], src[i]);
        }
#endif
    }else{
        const unsigned long *src = (unsigned long*)b;
        unsigned long *dst = (unsigned long*)(d->addr + offset);
        FLASH->CR |= (2<<8) | 1;	// 32 bits, enable program

        int wlen = len / 4;
        kprintf("wr: len %d, dst %x\n", len, dst);

        for(i=0; i<wlen; i++){
#ifdef WRITE_BYTES
#  if WRITE_BYTES == 8
            // has ECC, can only overwrite with all 0s
            if( !(i&1) && (src[i]==0xFFFFFFFF) && (src[i+1]==0xFFFFFFFF) ){
                i ++;
                continue;
            }
            // write same data? skip
            if( !(i&1) && (src[i] == dst[i]) && (src[i+1] == dst[i+1]) ){
                i ++;
                continue;
            }
#  endif
#  if WRITE_BYTES == 16
            // write all ones? skip ahead
            if( !(i&3) && (src[i]==0xFFFFFFFF) && (src[i+1]==0xFFFFFFFF)
                && (src[i+2]==0xFFFFFFFF) && (src[i+3]==0xFFFFFFFF) ){
                i += 3;
                continue;
            }
            // write same data? skip
            if( !(i&3) && (src[i] == dst[i]) && (src[i+1] == dst[i+1])
                && (src[i+2] == dst[i+2]) && (src[i+3] == dst[i+3]) ){
                i += 3;
                continue;
            }
#  endif
#endif

            wait_not_busy();
            dst[i] = src[i];
            if( FLASH->SR & 0xF2 ) kprintf("err: len %d, %x; @ %x, cr %x [src %x dst %x] \n", len, FLASH->SR, dst + i, FLASH->CR, src+i, dst+i);
            //if( dst[i] != src[i] ) kprintf("err @%x: %x != %x\n", dst + i, dst[i], src[i]);
        }
    }

    wait_not_busy();
    FLASH->CR &= ~1;		// disable program
    FLASH->CR &= ~(3<<8);	// clear size
    stfinish(d);

    //hexdump(d->addr + offset, len);
    return len;
}

int
stflash_ioctl(FILE* f, int cmd, void* a){
    struct Flash_Disk *fdk = f->d;
    offset_t *o = a;

    if( ((cmd >> 8) & 0xFF) != 'm' )
        return -1;

    switch( cmd & 0xFF ){
    case 'e':		/* erase */
        return erase(f->d, (int)a);
        break;
    case 'i':		/* flash info */
        o[0] = fdk->info->write_size;
        o[1] = fdk->info->erase_size;
        return 0;

    default:
        return -1;
    }
}


static int
erase(struct Flash_Disk *fdk, int a){

    int blk  = a / fdk->blocksize;
    int sect = fdk->blockno + blk;

#ifdef PLATFORM_STM32U5
    int nb = fdk->info->nblocks;
    int bank = (sect >= (nb >> 1)) ? 1 : 0;
    kprintf(">> fl a %x, off %x, nb %d, sect %d, bk %d\n", a, fdk->blockno, nb, sect, bank);
    if( bank ){
        sect -= (nb >> 1);
        sect |= (1 << 11);
    }
#endif

    kprintf("stm32 flash erase a %x b %x (sect %x)\n", a, blk, sect);

    ststart(fdk);
    FLASH->SR = 0xFFFFFFFF;	// clear errors
    wait_not_busy();
    FLASH->CR |= (sect<<3) | 2;	// sector erase
    FLASH->CR |= 1<<16;		// start
    wait_not_busy();
    FLASH->CR &= ~( (sect<<3) | 2 | (1<<16) );
    kprintf(">> SR %x\n", FLASH->SR);
    stfinish(fdk);

    return 0;
}

int
stflash_noop(FILE *f){
    return 1;
}

/****************************************************************/

#ifdef KTESTING

DEFUN(stflash_wr, "test write")
{
    if( argc < 3 )
        return -1;

    int off = atoi_base(16, argv[1]);
    int len = atoi_base(16, argv[2]);

    printf("addr: %x\n", fldsk[0].addr + off);
    stflash_bwrite(&fldsk[0].file, &off, len, off);

    return 0;
}

DEFUN(stflash_er, "test erase")
{
    if( argc < 2 )
        return -1;

    int off = atoi_base(16, argv[1]);

    printf("addr: %x\n", fldsk[0].addr + off);
    erase( fldsk, off );

    return 0;
}




#endif
