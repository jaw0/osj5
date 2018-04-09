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

#include <atsam.h>

#define FLASHSTART	0x400000
#define BLOCKSIZE       (128*1024)
#define BLOCKSHIFT	17


extern struct Flash_Conf flash_device[];
extern FILE *flfs_open(MountEntry *, const char *, const char *);
extern int n_flashdev;
extern const u_char _etext[];

int flash_total_size;
int flash_page_size;

static struct Flash_Disk {
    FILE               file;
    lock_t             lock;
    int                blocks;
    void	       *addr;
    const struct Flash_Conf *conf;
    uint32_t		buf[4];

} fldsk[ N_FLASHDEV ];


int atflash_bread(FILE*,char*,int,offset_t);
int atflash_bwrite(FILE*,const char*,int,offset_t);
int atflash_stat(FILE*, struct stat*);
int atflash_ioctl(FILE*, int, void*);
static int erase(struct Flash_Disk *, int);
static void send_cmd(struct Flash_Disk *, struct Flash_Command);
static int  getd(void);

static const struct io_fs atflash_port_fs = {
    0, 0,	/* putchar, getchar */
    0, 0, 	/* close, flush */
    0, 		/* status */
    0, 0,	/* read, write */
    atflash_bread,
    atflash_bwrite,
    0, 0, 	/* seek, tell */
    atflash_stat,
    atflash_ioctl
};

int
atflash_init(struct Device_Conf *dev){
    short i, n, ba=-1, bz=-1;
    const char *nm;
    const char *type;
    char mntpt[16];


    getd();

    for (i=0; i<n_flashdev; i++ ){
        fldsk[i].conf = flash_device + i;

        if( flash_device[i].addr ){
            // use specified region of flash
            fldsk[i].addr = flash_device[i].addr;

            if( flash_device[i].size ){
                fldsk[i].blocks = flash_device[i].size / BLOCKSIZE;
            }else{
                fldsk[i].blocks = 1;
            }

        }else{
            // auto configure all available flash
            fldsk[i].addr = ((int)_etext + BLOCKSIZE - 1) & ~BLOCKSIZE;
            int sz = (FLASHSTART + flash_total_size) - (int)fldsk[i].addr;
            fldsk[i].blocks = sz / BLOCKSIZE;

            if( !sz ){
                bootmsg("mem%d cannot configure flash. no free space\n");
                return 0;
            }
        }

        finit( & fldsk[i].file );
        fldsk[i].file.d = (void*)& fldsk[i];
        fldsk[i].file.fs = & atflash_port_fs;

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
                    i, fldsk[i].blocks<<BLOCKSHIFT, fldsk[i].addr, nm, type);
        }
    }

    return 0;
}


static int getd(void){

    EFC->EEFC_FCR = EEFC_FCR_FKEY_PASSWD | 0;	// GETD
    int x = EFC->EEFC_FRR;
    flash_total_size = EFC->EEFC_FRR;
    flash_page_size  = EFC->EEFC_FRR;

    bootmsg("eefc: tot %d, pg %d\n", flash_total_size, flash_page_size);

}

int atflash_stat(FILE *f, struct stat *s){
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
atflash_bread(FILE *f, char *buf, int len, offset_t offset){
    struct Flash_Disk *d;
    int fd, i;

    d = f->d;

    if( offset >= d->blocks<<BLOCKSHIFT )
        return 0;

    memcpy(buf, (char*)d->addr + offset, len);
    return len;
}

static void
ststart(struct Flash_Disk *d){
    sync_lock( & d->lock, "flash" );
}

static void
stfinish(struct Flash_Disk *d){
    sync_unlock( & d->lock );
}


static void __attribute__ ((section(".ramfunc")))
_write_page(const unsigned long *src, unsigned long *dst, int page, int plen){
    int i;

    for(i=0; i<plen; i++)
        dst[i] = src[i];

    EFC->EEFC_FCR = EEFC_FCR_FKEY_PASSWD | (page << 8) | 1; // write page

    while(1){
        int b = EFC->EEFC_FSR & EEFC_FSR_FRDY;
        if( b ) break;
    }
}

int
atflash_bwrite(FILE *f, const char *b, int len, offset_t offset){
    struct Flash_Disk *d;
    int i, olen=len;

    d = f->d;

    if( offset >= d->blocks<<BLOCKSHIFT )
        return 0;

    // kprintf("atf write %d @ %x => %x\n", len, b, d->addr + offset);

    const unsigned long *src = (unsigned long*)b;
    unsigned long *dst = (unsigned long*)(d->addr + offset);

    if( len < 16 ){
        // cannot write < 128bits
        unsigned long *dx = (unsigned long*)(d->addr + (offset & ~0xF));
        for(i=0; i<4; i++)
            d->buf[i] = dx[i];

        for(i=0; i<len; i+=4){
            d->buf[ ((offset + i) & 0xF)/4 ] = *src;
            src ++;
        }

        dst = dx;
        src = d->buf;
        len = 16;
    }

    ststart(d);

    while(len){
        // page by page
        int plen = len;
        uint32_t page = ((int)dst - FLASHSTART) / flash_page_size;
        if( plen > flash_page_size ) plen = flash_page_size;

        irq_disable();
        _write_page(src, dst, page, plen/4);
        irq_enable();
        len -= plen;
    }

    stfinish(d);

    return olen;
}

int
atflash_ioctl(FILE* f, int cmd, void* a){
    struct Flash_Disk *fdk = f->d;
    offset_t *o = a;

    if( ((cmd >> 8) & 0xFF) != 'm' )
        return -1;

    switch( cmd & 0xFF ){
    case 'e':		/* erase */
        return erase(f->d, (int)a);
        break;

    case 'i':		/* flash info */
        o[0] = 4;
        o[1] = flash_page_size;
        return 0;

    default:
        return -1;
    }
}

static void __attribute__ ((section(".ramfunc")))
_erase_sector(int page){

    EFC->EEFC_FCR = EEFC_FCR_FKEY_PASSWD | (page << 8) | 0x11; // sector erase

    while(1){
        int b = EFC->EEFC_FSR & EEFC_FSR_FRDY;
        if( b ) break;
    }
}

static int
erase(struct Flash_Disk *fdk, int a){

    kprintf("eefc flash erase %x\n", a);

    int page = ((int)fdk->addr + a - FLASHSTART) / flash_page_size;

    ststart(fdk);
    irq_disable();

    _erase_sector( page );

    irq_enable();
    stfinish(fdk);
    return 0;
}

int
atflash_noop(FILE *f){
    return 1;
}

