/*
  Copyright (c) 2016
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2016-Jun-25 19:04 (EDT)
  Function: sdio

*/


#include <conf.h>
#include <proc.h>
#include <dev.h>
#include <error.h>
#include <atsam.h>
#include <gpio.h>
#include <pmc.h>
#include <nvic.h>
#include <xdma.h>
#include <userint.h>


//#define HSMCIVERBOSE
//#define HSMCI_INIT_VERBOSE
#define CRUMBS	"hsmci"
#include <crumbs.h>


#define MAXTRY 		5
#define HSMCI_DMA_ID	0
#define WTIMEOUT	250000	// from spec

#define HSMCI_ERROR	(HSMCI_SR_RINDE  | HSMCI_SR_RDIRE | HSMCI_SR_RCRCE | HSMCI_SR_RENDE \
                         | HSMCI_SR_RTOE | HSMCI_SR_DCRCE | HSMCI_SR_DTOE  | HSMCI_SR_CSTOE)


int hsmci_ioctl(FILE*, int, void*);
int hsmci_bread(FILE*, char*, int, offset_t);
int hsmci_bwrite(FILE*, const char*, int, offset_t);
int hsmci_stat(FILE *, struct stat*);

const struct io_fs hsmci_fs = {
    0, /* putc */
    0, /* getc */
    0, /* close */
    0, /* flush */
    0, /* status */
    0, /* read */
    0, /* write */
    hsmci_bread,  /* bread */
    hsmci_bwrite, /* bwrite */
    0, /* seek */
    0, /* tell */
    hsmci_stat,
    hsmci_ioctl
};


struct HSMCIinfo {
    lock_t		lock;
    FILE 		file;
    const char		*name;
    u_char		sdcid[16];
    u_char		sdcsd[16];	// a meshigas of unaligned jibber-jabber
    int			sectors;
    int			rca;
    u_char		ishc;
    char		dmac;

} sdcinfo[ N_HSMCI ];


static int  initialize_card(struct HSMCIinfo *);
static void hsmci_dma_handler(void *);

int
hsmci_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct HSMCIinfo *ii = sdcinfo + unit;
    char info[32];
    int i;

    finit( & ii->file );
    ii->file.d  = (void*)ii;
    ii->file.fs = & hsmci_fs;
    ii->name = dev->name;
    ii->lock = 0;

    gpio_init( GPIO_A25,  GPIO_AF_D | GPIO_PUSH_PULL  		    );	// clk
    gpio_init( GPIO_A28,  GPIO_AF_C | GPIO_PUSH_PULL | GPIO_PULL_UP );	// cmd
    gpio_init( GPIO_A30,  GPIO_AF_C | GPIO_PUSH_PULL | GPIO_PULL_UP );	// data
    gpio_init( GPIO_A31,  GPIO_AF_C | GPIO_PUSH_PULL | GPIO_PULL_UP );	// data
    gpio_init( GPIO_A26,  GPIO_AF_C | GPIO_PUSH_PULL | GPIO_PULL_UP );	// data
    gpio_init( GPIO_A27,  GPIO_AF_C | GPIO_PUSH_PULL | GPIO_PULL_UP );	// data

    pmc_enable( ID_HSMCI );

    ii->dmac = dma_alloc( hsmci_dma_handler, unit );
    if( ii->dmac == -1 ){
        bootmsg("hsmci: cannot allocate dma channel\n");
        return 0;
    }

    HSMCI->HSMCI_CR    = HSMCI_CR_SWRST;

    HSMCI->HSMCI_DTOR  = HSMCI_DTOR_DTOMUL_1048576   | HSMCI_DTOR_DTOCYC(2);
    HSMCI->HSMCI_CSTOR = HSMCI_CSTOR_CSTOMUL_1048576 | HSMCI_CSTOR_CSTOCYC(2);
    HSMCI->HSMCI_CFG   = HSMCI_CFG_FERRCTRL;
    // Set power saving to maximum value
    HSMCI->HSMCI_MR    = HSMCI_MR_PWSDIV_Msk | HSMCI_MR_RDPROOF | HSMCI_MR_WRPROOF;
    // Enable the HSMCI and the Power Saving
    HSMCI->HSMCI_CR    = HSMCI_CR_MCIEN | HSMCI_CR_PWSEN;

    nvic_enable( HSMCI_IRQn, IPL_DISK );

    // RSN - card detect

    int r = initialize_card(ii);

    if( !r ) return 0;	/* no card installed */

    //hexdump(ii->sdcid, 16);
    //hexdump(ii->sdcsd, 16);


    info[0] = ii->sdcid[1];
    info[1] = ii->sdcid[2];
    info[2] = '/';
    for(i=0;i<5;i++)
        info[3+i] = ii->sdcid[3+i];
    info[8] = 0;

    const char *sdtype;
    int nsect;
    if( (ii->sdcsd[0] & 0xC0) == 0 ){
        // standard SD version 1.0
        int rblen = ii->sdcsd[5] & 0xF;
        int csize = (ii->sdcsd[8]>>6) + (ii->sdcsd[7]<<2) + ((ii->sdcsd[6] & 3)<<10);
        int cmult = (ii->sdcsd[10]>>7) + ((ii->sdcsd[9] & 3)<<1);
        nsect = (csize + 1) * (1<<(cmult + 2)) * (1<<(rblen - 9));
        sdtype = "SD/1.0";
        ii->ishc = 0;
    }else{
        // SDHC version 2.0
        nsect = (ii->sdcsd[9] + (ii->sdcsd[8]<<8) + ((ii->sdcsd[7]&0x3F)<<16) + 1) * 1024;
        sdtype = "SD/HC";
        ii->ishc = 1;
    }

    ii->sectors = nsect;

    bootmsg("%s at hsmci%d %s sdcard %s %d sect, %d MB\n",
            dev->name, unit,
            sdtype, info,
            nsect, nsect>>11
        );

    // set flags=1 to not automount
    if( ! dev->flags ){
        snprintf(info, sizeof(info), "%s:", ii->name);
        fmount( & ii->file, info, "fatfs" );

        bootmsg( "sdcard %s mounted on %s type %s\n",
                 ii->name, info, "fatfs" );
    }

    return (int)& ii->file;
}


static inline void
hsmci_clear_state(void){

}

static inline void
_hsmci_copy_resp(uint32_t *resp){
    resp[0] = HSMCI->HSMCI_RSPR[0];
    resp[1] = HSMCI->HSMCI_RSPR[1];
    resp[2] = HSMCI->HSMCI_RSPR[2];
    resp[3] = HSMCI->HSMCI_RSPR[3];
}

static void
hsmci_send_clock(void){
    int timeout = 0xFFFF;

    hsmci_clear_state();
    HSMCI->HSMCI_CMDR = HSMCI_CMDR_RSPTYP_NORESP
        | HSMCI_CMDR_SPCMD_INIT
        | HSMCI_CMDR_OPDCMD_OPENDRAIN;

    // Wait end of initialization command
    while (!(HSMCI->HSMCI_SR & HSMCI_SR_CMDRDY)){
        if( !--timeout ) return ;
    }
}

static int
hsmci_cmd_none(u_long cmd, u_long arg){
    int timeout = 0xFFFF;

    hsmci_clear_state();
    cmd |= HSMCI_CMDR_RSPTYP_NORESP | HSMCI_CMDR_MAXLAT_64;
    HSMCI->HSMCI_ARGR = arg;
    HSMCI->HSMCI_CMDR = cmd;

    while (!(HSMCI->HSMCI_SR & HSMCI_SR_CMDRDY)){
        if( !--timeout ) return -1;
    }

    return 0;
}

static inline int
_hsmci_cmd(u_long cmd, uint32_t *resp){

    hsmci_clear_state();
    cmd |= HSMCI_CMDR_MAXLAT_64;
    HSMCI->HSMCI_CMDR = cmd;

    while (!(HSMCI->HSMCI_SR & HSMCI_SR_CMDRDY)){}

    _hsmci_copy_resp(resp);

    return HSMCI->HSMCI_SR & HSMCI_ERROR;
}

static int
hsmci_cmd_short(u_long cmd, u_long arg, uint32_t *resp){

    HSMCI->HSMCI_ARGR = arg;
    return _hsmci_cmd( cmd | HSMCI_CMDR_RSPTYP_48_BIT, resp );
}

static int
hsmci_cmd_r1(u_long cmd, u_long arg, uint32_t *resp){

    HSMCI->HSMCI_ARGR = arg;
    int r = _hsmci_cmd( cmd | HSMCI_CMDR_RSPTYP_48_BIT, resp );

    if( resp[0] & 0xFFFFE008 ) return -1;
    return r;
}

static int
hsmci_cmd_r1b(u_long cmd, u_long arg, uint32_t *resp){

    HSMCI->HSMCI_ARGR = arg;
    int r = _hsmci_cmd( cmd | HSMCI_CMDR_RSPTYP_R1B, resp );

    if( resp[0] & 0xFFFFE008 ) return -1;
    return r;
}

static int
hsmci_cmd_r3(u_long cmd, u_long arg, uint32_t *resp){

    HSMCI->HSMCI_ARGR = arg;
    int r = _hsmci_cmd( cmd | HSMCI_CMDR_RSPTYP_48_BIT, resp );

    // cmd does not return a CRC. ignore CRC error
    return HSMCI->HSMCI_SR & (HSMCI_ERROR & ~HSMCI_SR_RCRCE);
}

static int
hsmci_cmd_long(u_long cmd, u_long arg, u_long *dst, uint32_t *resp){

    HSMCI->HSMCI_ARGR = arg;
    int r = _hsmci_cmd( cmd | HSMCI_CMDR_RSPTYP_136_BIT, resp );

    dst[0] = __REV(resp[0]);
    dst[1] = __REV(resp[1]);
    dst[2] = __REV(resp[2]);
    dst[3] = __REV(resp[3]);

    return r;
}

static void
_set_speed(int speed){

    uint32_t r = HSMCI->HSMCI_MR;
    r &= ~0x100FF;

    int div = periph_clock_freq() / speed;
    div -= 2;

    if( div < 0 ) div = 0;
    if( div > 0x1FF ) div = 0x1FF;

    r |= (div & 1) << 16;
    r |= (div >> 1);

    HSMCI->HSMCI_MR = r;
}


#ifdef HSMCI_INIT_VERBOSE
#  define IDBGRESP(x)    kprintf("hsmci cmd %2d r %x sr %x res %08.8x %08.8x %08.8x %08.8x\n", x, \
                                 r, HSMCI->HSMCI_SR, HSMCI->HSMCI_RSPR[0], HSMCI->HSMCI_RSPR[1], \
                                 HSMCI->HSMCI_RSPR[2], HSMCI->HSMCI_RSPR[3])
#else
#  define IDBGRESP(x)
#endif

static int
initialize_card(struct HSMCIinfo *ii){

    int i, r;
    int isv2 = 0;
    int ishc = 0;
    uint32_t resp[4];

    // 400kHz, 1 bit mode
    HSMCI->HSMCI_SDCR = 0;	// 1bit mode
    _set_speed( 400000 );

    hsmci_send_clock();

    for(i=0; i<5; i++){
        r = hsmci_cmd_none(0, 0);
        // if( !r ) break;
    }
    if( r ) return 0;

    // cmd8 - required to enable v2/HC features (>2GB)
    r = hsmci_cmd_short( 8, 0x01AA, resp );
    IDBGRESP(8);
    if( r ) return 0;
    r = resp[0];
    if( (r & 0xFF) == 0xAA && (r & 0x7E00) == 0 ) isv2 = 1;	// 2.0 yay!

    // loop until ready
    //  cmd 55/41 => R1
    for(i=0; i<10000; i++){
        r = hsmci_cmd_short( 55, 0, resp );
        r = hsmci_cmd_r3( 41, 0x80100000 | (isv2 ? (1<<30) : 0), resp );
        if( !r && (resp[0] & (1<<31)) ) break;
    }

    IDBGRESP(41);

    if( isv2 && (resp[0] & 0x40000000) ) ishc = 1;	// HC yay!

    // read CID
    r = hsmci_cmd_long( 2, 0,  (u_long*)ii->sdcid, resp );
    IDBGRESP(2);
    if( r ) return 0;

    // set RCA
    r = hsmci_cmd_short( 3, 0, resp );
    IDBGRESP(3);
    if( r ) return 0;
    ii->rca = resp[0] >> 16;

    // read CSD
    r = hsmci_cmd_long( 9, ii->rca << 16,  (u_long*)ii->sdcsd, resp );
    IDBGRESP(9);
    if( r ) return 0;

    // select card
    r = hsmci_cmd_short( 7, ii->rca << 16, resp );
    IDBGRESP(7);
    if( r ) return 0;

    // 4 bit mode
    r = hsmci_cmd_short( 55, ii->rca << 16, resp );
    r = hsmci_cmd_short( 6, 2, resp );
    IDBGRESP(6);

    if( !r )
        HSMCI->HSMCI_SDCR = HSMCI_SDCR_SDCBUS_4;

    // increase speed
    if( isv2 && ishc ){
        _set_speed( 50000000 );	// 50MHz
    }else{
        _set_speed( 25000000 ); // 25MHz
    }

    return 1;

}

static void
hsmci_clear(struct HSMCIinfo *ii){
    initialize_card(ii);
}

static void
hsmci_stop(void){
    uint32_t resp[4];
    int r = hsmci_cmd_r1b( 12 | HSMCI_CMDR_TRCMD_STOP_DATA, 0, resp );
}


void
hsmci_dma_handler(void *w){
    DROP_CRUMB("dma-irq", w, 0);
    wakeup( HSMCI );
}

void
HSMCI_Handler(void){
    uint32_t sr = HSMCI->HSMCI_SR;

    DROP_CRUMB("hsmci-irq", sr, 0);

    if( (sr & HSMCI_SR_DTIP) == 0 ){
        HSMCI->HSMCI_IDR = HSMCI_IER_DTIP;
        wakeup( HSMCI );
    }
}
/*
Wait until the current command execution has successfully completed. a. Check that CMDRDY and NOTBUSY are asserted in HSMCI_SR.
Program the block length in the card. This value defines the value block_length.
Program the block length in the HSMCI Configuration Register with block_length value.
Set RDPROOF bit in HSMCI_MR to avoid overflow.
Configure the fields of the HSMCI_MR as follows:
a. Program FBYTE to one when the transfer is not multiple of 4, zero otherwise.
Issue a READ_SINGLE_BLOCK/WRITE_MULTIPLE_BLOCK command.
Program the DMA controller.
a. Read the Channel Status Register to choose an available (disabled) channel.
b. Clear any pending interrupts on the channel from the previous DMA transfer by reading the DMAC_CISx register.
c. Program the channel registers.
d. The DMAC_CSAx register for Channel x must be set with the starting address of the HSMCI_FIFO address.
e. The DMAC_CDAx register for Channel x must be word aligned.
f. Configure the fields of DMAC_CCx for Channel x as follows:
–DWIDTH is set to WORD when the length is a multiple of 4, otherwise it is set to BYTE. –CSIZE must be set according to the value of HSMCI_DMA.CHKSIZE.
g. Configure the fields of the DMAC_CUBCx register of Channel x as follows:
–UBLEN is programmed with block_length/4 when the transfer length is multiple of 4, block_length
otherwise.
h. Enable Channel x, writing one to DMAC_GE.EN[x]. The DMAC is ready and waiting for request.
Wait for XFRDONE in the HSMCI_SR.

*/

int
hsmci_bread(FILE*f, char*d, int len, offset_t pos){
    struct HSMCIinfo *ii = f->d;
    uint32_t resp[4];
    int tries, ret=-1, r;

#ifdef HSMCIVERBOSE
    kprintf("sdrd %qx %d\n", pos, len);
#endif

    if( ii->ishc ) pos /= 512;
    int nblk = len >> 9;

    sync_lock(& ii->lock, "sdcard");

    for(tries=0; tries<MAXTRY; tries++){

        RESET_CRUMBS();
        DROP_CRUMB("read try", tries, 0);

        HSMCI->HSMCI_BLKR = (512 << 16) | (nblk);
        HSMCI->HSMCI_DMA  = HSMCI_DMA_DMAEN | HSMCI_DMA_CHKSIZE_4;

        int cmd = 18 | HSMCI_CMDR_TRTYP_MULTIPLE | HSMCI_CMDR_TRDIR_READ | HSMCI_CMDR_TRCMD_START_DATA;

        dma_config(ii->dmac, XDMAF_P2M | XDMAF_MINC | XDMAF_32BIT | XDMAF_CHK_4, HSMCI_DMA_ID, & HSMCI->HSMCI_FIFO, d, 512/4 );
        dma_start(ii->dmac);

        r = hsmci_cmd_r1( cmd , pos, resp );

        DROP_CRUMB("read r,sr", r, HSMCI->HSMCI_SR);

        if( !r ){
            r = dma_wait_complete(ii->dmac, (void*)HSMCI, -1, 100000);
            DROP_CRUMB("read dma/r, sr", r, HSMCI->HSMCI_SR);

            // RSN - wait for XFERDONE
            if( HSMCI->HSMCI_SR & HSMCI_ERROR ) r = -1;
            if( (HSMCI->HSMCI_SR & HSMCI_SR_CMDRDY) == 0 ) r = -1;

            if( r )
                kprintf("err hsmci sr=%x\n", r, HSMCI->HSMCI_SR );
        }

        HSMCI->HSMCI_DMA = 0;
        dma_stop(ii->dmac);
        hsmci_stop();

        DROP_CRUMB("read end r,len", r, len);
#ifdef HSMCIVERBOSE
        DUMP_CRUMBS();
        RESET_CRUMBS();
#endif
        if( !r ){
            // all done!
            ret = len;
            break;
        }

        kcprintf("sd read error %qx, %d => %x, %x\n", pos, len, r, resp[0]);
        DUMP_CRUMBS();
        usleep(10000);
        if( tries > 2 ) hsmci_clear( ii );
    }

    sync_unlock(& ii->lock );

#ifdef HSMCIVERBOSE
    kprintf("sdrd => %d\n", ret);
    if( ret > 0 ){
        hexdump( d, 16 );
        hexdump( d+512-16, 16 );
    }
#endif

    return ret;
}


// wait for write to complete
static int
hsmci_write_wait(int rca, uint32_t *resp){
    int r;

    utime_t t1 = get_time() + WTIMEOUT;

    while(1){
        r = hsmci_cmd_short( 13, rca << 16, resp );
        // DROP_CRUMB("cmd13 r,sr", resp[0], HSMCI->HSMCI_SR);

        r = resp[0];
        if( ((r >> 9) & 7) < 5 ) return 0;
        if( get_time() > t1 )    return -1;
        yield();
    }
}

int
hsmci_bwrite(FILE*f, const char*d, int len, offset_t pos){
    struct HSMCIinfo *ii = f->d;
    uint32_t resp[4];
    int tries, ret=-1, r, cmd;

#ifdef HSMCIVERBOSE
    kprintf("sdwr %qx %d\n", pos, len);
#endif

    if( ii->ishc ) pos /= 512;
    int nblk = len >> 9;

    sync_lock(& ii->lock, "sdcard");

    for(tries=0; tries<MAXTRY; tries++){

        RESET_CRUMBS();
        DROP_CRUMB("write try", tries, 0);

        HSMCI->HSMCI_BLKR = (512 << 16) | (nblk);
        r = HSMCI->HSMCI_MR;
        r |= HSMCI_MR_WRPROOF;
        HSMCI->HSMCI_MR = r;

        if( len == 512 ){
            cmd = 24 | HSMCI_CMDR_TRTYP_SINGLE;		// single block
        }else{
            hsmci_cmd_short( 55, ii->rca << 16, resp );
            hsmci_cmd_short( 23, nblk, resp );		// ACMD23, pre-erase (slight speed improvement)
            cmd = 25 | HSMCI_CMDR_TRTYP_MULTIPLE;	// multi block
        }

        HSMCI->HSMCI_BLKR = (512 << 16) | (nblk);
        HSMCI->HSMCI_DMA  = HSMCI_DMA_DMAEN | HSMCI_DMA_CHKSIZE_4;

        cmd |= HSMCI_CMDR_TRDIR_WRITE | HSMCI_CMDR_TRCMD_START_DATA;

        dma_config(ii->dmac, XDMAF_M2P | XDMAF_MINC | XDMAF_32BIT | XDMAF_CHK_4, HSMCI_DMA_ID, & HSMCI->HSMCI_FIFO, d, 512/4 );
        dma_start(ii->dmac);

        r = hsmci_cmd_r1( cmd , pos, resp );

        DROP_CRUMB("write r,sr", r, HSMCI->HSMCI_SR);

        if( !r ){
            r = dma_wait_complete(ii->dmac, (void*)HSMCI, -1, 100000);
            DROP_CRUMB("write dma/r, sr", r, HSMCI->HSMCI_SR);

            // RSN - wait for XFERDONE
            if( HSMCI->HSMCI_SR & HSMCI_ERROR ) r = -1;
            if( (HSMCI->HSMCI_SR & HSMCI_SR_CMDRDY) == 0 ) r = -1;
            if( r )
                kprintf("err hsmci r %x, sr %x\n", r, HSMCI->HSMCI_SR );
        }

        HSMCI->HSMCI_DMA = 0;
        dma_stop(ii->dmac);

        if( len != 512 ) hsmci_stop();
        r |= hsmci_write_wait(ii->rca, resp);

        DROP_CRUMB("write end r,len", r, len);
#ifdef HSMCIVERBOSE
        DUMP_CRUMBS();
        RESET_CRUMBS();
#endif
        if( !r ){
            // all done!
            ret = len;
            break;
        }

        kcprintf("sd write error %qx, %d => %x, %x\n", pos, len, r, resp[0]);
        DUMP_CRUMBS();
        usleep(10000);
        if( tries > 2 ) hsmci_clear( ii );

    }

    sync_unlock(& ii->lock );

#ifdef HSMCIVERBOSE
    kprintf("sdwr => %d\n", ret);
#endif

    return ret;

}

int
hsmci_ioctl(FILE*f, int s, void*d){}

int
hsmci_stat(FILE *f, struct stat *s){
    struct HSMCIinfo *ii = f->d;

    s->dev     = 0;
    s->size    = (long long)ii->sectors * 512;
    s->ctime   = 0;
    s->blksize = 512;
    s->mode    = 0;
    s->flags   = SSF_BLKWRITE | SSF_NOERASE;

    return 0;
}


#ifdef KTESTING

DEFUN(blktest, "read block")
{
    if( argc < 2 ) return 0;

    int blk   = atoi(argv[1]);
    char *buf = alloc(512);
    FILE *f   = fopen("dev:sd0", "w");

    hsmci_bread( f, buf, 512, blk);
    hexdump( buf, 512 );

    free(buf);
    return 0;
}

DEFUN(sdtest, "sd card test")
{
    char *buf = alloc(1024);
    FILE *f   = fopen("dev:sd0", "w");

    printf(">> read 1st sector:\n");
    hsmci_bread( f, buf, 512, 0);	// read first sector
    hexdump( buf, 32 );
    hexdump( buf+512-32, 32 );

    printf(">> fill buf rand:\n");
    memset(buf, random() & 0xFF, 512);
    hexdump( buf, 16 );

    printf(">> write buf\n");
    hsmci_bwrite(f, buf, 512, 0xF0000 ); // write

    printf(">> read back:\n");
    bzero(buf, 512);
    hsmci_bread( f, buf, 512, 0xF0000 ); // read back
    hexdump( buf, 16 );
    hexdump( buf+512-16, 16 );


    free(buf, 1024);
    return 0;
}


DEFUN(wrfile, "test file write timing")
{
    int i, len;
    FILE *f;

    if( argc != 3 ){
        f_error("mkfile name len");
        return -1;
    }

    len = atoi(argv[2]);

    int t0 = get_hrtime();
    f = fopen( argv[1], "w!" );

    if( f ){
        // start of RAM
        while(len){
            int wl = (len > 65536) ? 65536 : len;
            fwrite(f, (char*)0x20400000, wl );
            len -= wl;
        }
        fclose(f);

        int t1 = get_hrtime();
        printf("time: %d\n", t1 - t0);
    }
    return 0;
}

DEFUN(rdfile, "test file read timing")
{
    int bksz=8192, i;
    FILE *f;

    if( argc < 2 ){
        f_error("rdfile name [bksz]");
        return -1;
    }

    if( argc > 2 )
        bksz = atoi(argv[2]);


    char *buf = alloc( bksz );

    int t0 = get_hrtime();
    f = fopen( argv[1], "r" );
    if( f ){
        while(1){
            int rl = fread(f, buf, bksz);
            if( rl != bksz ) break;
        }
        fclose(f);

        int t1 = get_hrtime();
        printf("time: %d\n", t1 - t0);
    }

    free(buf, bksz);
    return 0;
}


#endif
