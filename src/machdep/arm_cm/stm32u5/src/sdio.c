/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Dec-13 18:27 (EST)
  Function: sdio using u5 iDMA

*/

#include <conf.h>
#include <clock.h>
#include <proc.h>
#include <dev.h>
#include <error.h>
#include <gpio.h>
#include <stm32.h>
#include <nvic.h>
#include <userint.h>

#if defined(SDIO_TRACE)
#  define TRACE
#endif
#include <trace.h>

#define IDBGRESP(x) 	trace_crumb5("sdio", "resp", x, SDIO->RESPCMD, r, SDIO->STA, SDIO->RESP1)


#define SDIO      	SDMMC1
#define SDIO_IRQn 	SDMMC1_IRQn


#define MAXTRY 		5
#define RTIMEOUT	4800000		// 100 ms
#define WTIMEOUT	24000000	// 500 ms

// slightly different than other stm32:
#define CMD_CPSMEN	(1<<12)
#define CMD_TRANS	(1<<6)
#define CMD_STOP	(1<<7)
#define CMD_WAIT_NONE	(0)
#define CMD_WAIT_SHORT	(1<<8)
#define CMD_WAIT_LONG	(3<<8)

#define SR_DATAEND	(1<<8)
#define SR_CMDSENT	(1<<7)
#define SR_CMDREND	(1<<6)
#define SR_DTIMEOUT	(1<<3)
#define SR_CTIMEOUT	(1<<2)
#define SR_DCRCFAIL	(1<<1)
#define SR_CCRCFAIL	(1<<0)

#define spldma()	splraise(IPL_XHIGH)

int sdio_ioctl(FILE*, int, void*);
int sdio_bread(FILE*, char*, int, offset_t);
int sdio_bwrite(FILE*, const char*, int, offset_t);
int sdio_stat(FILE *, struct stat*);

const struct io_fs sdio_fs = {
    0, /* putc */
    0, /* getc */
    0, /* close */
    0, /* flush */
    0, /* status */
    0, /* read */
    0, /* write */
    sdio_bread,  /* bread */
    sdio_bwrite, /* bwrite */
    0, /* seek */
    0, /* tell */
    sdio_stat,
    sdio_ioctl
};


struct SDIOinfo {
    lock_t		lock;
    FILE file;
    const char		*name;
    u_char		sdcid[16];
    u_char		sdcsd[16];	// a meshigas of unaligned jibber-jabber
    char		info[32];
    int			sectors;
    int			rca;
    u_char		ishc;

} sdcinfo[ N_SDIO ];

static int got_dataend;


static int initialize_card(struct SDIOinfo *);

int
sdio_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct SDIOinfo *ii = sdcinfo + unit;
    int i;

    bzero(ii, sizeof(struct SDIOinfo));

    finit( & ii->file );
    ii->file.d  = (void*)ii;
    ii->file.fs = & sdio_fs;
    ii->name = dev->name;
    ii->lock = 0;

    gpio_init( GPIO_D2,  GPIO_AF(12) | GPIO_PUSH_PULL  | GPIO_SPEED_100MHZ | GPIO_PULL_UP );	// cmd
    gpio_init( GPIO_C12, GPIO_AF(12) | GPIO_PUSH_PULL  | GPIO_SPEED_100MHZ );	// clk
    gpio_init( GPIO_C8,  GPIO_AF(12) | GPIO_PUSH_PULL  | GPIO_SPEED_100MHZ | GPIO_PULL_UP );	// data
    gpio_init( GPIO_C9,  GPIO_AF(12) | GPIO_PUSH_PULL  | GPIO_SPEED_100MHZ | GPIO_PULL_UP );	// data
    gpio_init( GPIO_C10, GPIO_AF(12) | GPIO_PUSH_PULL  | GPIO_SPEED_100MHZ | GPIO_PULL_UP );	// data
    gpio_init( GPIO_C11, GPIO_AF(12) | GPIO_PUSH_PULL  | GPIO_SPEED_100MHZ | GPIO_PULL_UP );	// data


    RCC->AHB2ENR1 |= 1<< 27;

    SDIO->POWER = 3;	// enable
    SDIO->CLKCR = 60;	// 400kHz at start

    trace_init();
    trace_crumb1("sdio", "init", ii);

    nvic_enable( SDIO_IRQn, IPL_DISK );

    int r = initialize_card(ii);
    trace_crumb1("sdio", "initr", r);

    // if( !r ) return 0;	/* no card installed */

    hexdump(ii->sdcid, 16);
    hexdump(ii->sdcsd, 16);



    // do we need partitions?
#if 0
    dkpart_learn( dev, "sd", unit, & ii->file, nsect );
#else
    // or:

    // set flags=1 to not automount
    if( ! dev->flags ){
        snprintf(ii->info, sizeof(ii->info), "%s:", ii->name);

        bootmsg( "sdcard %s mounted on %s type %s\n",
                 ii->name, ii->info, "fatfs" );

        fmount( & ii->file, ii->info, "fatfs" );
    }
#endif

    return (int)& ii->file;
}

static void
spin_wait(int cnt){
    while(cnt-->0){
        __asm("nop");
    }
}

static inline void
sdio_reset(void){
    uint32_t ck = SDIO->CLKCR;

    RCC->AHB2RSTR1 |= 1<< 27;
    spin_wait(10);
    RCC->AHB2RSTR1 = 0;

    RCC->AHB2ENR1 |= 1<< 27;
    SDIO->POWER = 3;	// enable
    SDIO->CLKCR = ck;
}

static inline void
sdio_clr_icr(void){
    SDIO->ICR = 0x1FE00FFF;
}

static int
sdio_cmd_none(u_long cmd, u_long arg){
    int timeout = 0xFFFF;

    sdio_clr_icr();
    cmd |= (SDIO->CMD & ~0x1FFFF) | CMD_CPSMEN | CMD_WAIT_NONE;
    SDIO->ARG = arg;
    SDIO->CMD = cmd;

    // wait
    while( !(SDIO->STA & SR_CMDSENT) ) {
        if( !--timeout ) return SR_CTIMEOUT;
        __asm__ volatile ("nop");
    }

    return 0;
}

static int
__attribute__ ((optimize("-O0")))
_sdio_cmd(u_long cmd){

    sdio_clr_icr();

    trace_crumb2("sdio", "cmd", cmd, SDIO->STA);
    cmd |= (SDIO->CMD & ~0x1FFFF ) | CMD_CPSMEN;
    cmd |= (1<<11) | (1<<7); // QQQ waitpend, stop
    SDIO->CMD = cmd;

    uint32_t sr, pr=0;
    int count = 2000000;
    do {
        sr = SDIO->STA;
        if( count -- <= 0 ){
            trace_crumb1("sdio", "/cmd.c", sr);
            return SR_CTIMEOUT;
        }
        if( sr != pr ){
            trace_crumb2("sdio", "cmd+", sr, count);
        }
        pr = sr;
    } while (((sr & (SDMMC_STA_CCRCFAIL | SDMMC_STA_CMDREND // | SDMMC_STA_CTIMEOUT
                     /*| SDMMC_STA_BUSYD0END*/ )) == 0) && ((sr & SDMMC_STA_CPSMACT) != 0));

    trace_crumb4("sdio", "/cmd", cmd, SDIO->STA, count, SDIO->RESP1);

    return SDIO->STA & (SR_CCRCFAIL | SR_CTIMEOUT);
}
//#pragma GCC optimize ("-O3")

static int
sdio_cmd_short(u_long cmd, u_long arg){

    SDIO->ARG = arg;
    int r = _sdio_cmd( cmd | CMD_WAIT_SHORT );
    return r;
}

static int
sdio_cmd_r1(u_long cmd, u_long arg){

    SDIO->ARG = arg;
    int r = _sdio_cmd( cmd | CMD_WAIT_SHORT );

    if( SDIO->RESP1 & 0xFFFFE008 ) return -1;
    return r;
}

static int
sdio_cmd_r3(u_long cmd, u_long arg){

    SDIO->ARG = arg;
    int r = _sdio_cmd( cmd | CMD_WAIT_SHORT );
    // cmd does not return a CRC. ignore CRC error
    return r & SR_CTIMEOUT;
}

static int
sdio_cmd_long(u_long cmd, u_long arg, u_long *dst){

    SDIO->ARG = arg;
    int r = _sdio_cmd( cmd | CMD_WAIT_LONG );

    dst[0] = __REV(SDIO->RESP1);
    dst[1] = __REV(SDIO->RESP2);
    dst[2] = __REV(SDIO->RESP3);
    dst[3] = __REV(SDIO->RESP4);

    return r;
}


static int
initialize_card(struct SDIOinfo *ii){

    int i, r;
    int isv2 = 0;
    int ishc = 0;

    // 400kHz, 1 bit mode
    SDIO->CLKCR = 60;

    for(i=0; i<5; i++){
        r = sdio_cmd_none(0, 0);
        // if( !r ) break;
    }
    IDBGRESP(0);
    if( r ) return 0;

    // cmd8 - required to enable v2/HC features (>2GB)
    r = sdio_cmd_short( 8, 0x01AA );
    IDBGRESP(8);
    if( r ) return 0;
    r = SDIO->RESP1;
    if( (r & 0xFF) == 0xAA && (r & 0x7E00) == 0 ) isv2 = 1;	// 2.0 yay!

    // loop until ready
    //  cmd 55/41 => R1
    for(i=0; i<10000; i++){
        r = sdio_cmd_short( 55, 0 );
        r = sdio_cmd_r3( 41, 0x80100000 | (isv2 ? (1<<30) : 0) );
        if( !r && (SDIO->RESP1 & (1<<31)) ) break;
        spin_wait(50000);
    }

    IDBGRESP(41);

    if( isv2 && (SDIO->RESP1 & 0x40000000) ) ishc = 1;	// HC yay!

    // read CID
    r = sdio_cmd_long( 2, 0,  (u_long*)ii->sdcid );
    IDBGRESP(2);
    if( r ) return 0;

    // set RCA
    r = sdio_cmd_short( 3, 0 );
    IDBGRESP(3);
    if( r ) return 0;
    ii->rca = SDIO->RESP1 >> 16;
    trace_crumb1("sdio", "RCA", ii->rca);

    // read CSD
    r = sdio_cmd_long( 9, ii->rca << 16,  (u_long*)ii->sdcsd );
    IDBGRESP(9);
    if( r ) return 0;

    // select card
    r = sdio_cmd_short( 7, ii->rca << 16 );
    IDBGRESP(7);
    if( r ) return 0;

    trace_crumb1("sdio", "SWITCH", SDIO->STA);

#if 0
    // XXX ? U5 is broken ?
    //   gpioD[0..3] = ok
    //   nope, even at slow speed

    // 4 bit mode
    r = sdio_cmd_short( 55, ii->rca << 16 );
    IDBGRESP(55);
    r = sdio_cmd_short( 6, 2 );
    IDBGRESP(6);

    // if( !r )
        SDIO->CLKCR |= 1 << 14;	// 4 bit bus

    trace_crumb2("sdio", "CLKR", SDIO->CLKCR, r);

    // XXX
    r = sdio_cmd_short( 55, ii->rca << 16 );
    IDBGRESP(55);
    r = sdio_cmd_short( 6, 2 );
    IDBGRESP(6);

#endif

#if 1
    // increase speed
    SDIO->CLKCR &= ~0x3FF;
    if( isv2 && ishc ){
        SDIO->CLKCR |= 0;	// disable divider => 48MHz
    }else{
        // 48MHz / 2 => 24MHz
        SDIO->CLKCR |= 1;
    }
    trace_crumb1("sdio", "CLKR", SDIO->CLKCR);

#endif

    ii->info[0] = ii->sdcid[1];
    ii->info[1] = ii->sdcid[2];
    ii->info[2] = '/';
    for(i=0;i<5;i++)
        ii->info[3+i] = ii->sdcid[3+i];
    ii->info[8] = 0;

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
        // [3] == max tran_speed
    }

    ii->sectors = nsect;

    bootmsg("%s at sdio %s sdcard %s %d sect, %d MB\n",
            ii->name,
            sdtype, ii->info,
            nsect, nsect>>11
        );

    return 1;

}

static void
sdio_clear(struct SDIOinfo *ii){
    initialize_card(ii);
}

static void
sdio_stop(void){
    int r = sdio_cmd_short( 12 | CMD_STOP, 0 );
    IDBGRESP(12);
}


static void
dma_clr_irq(void){
    int plx = spldma();
#if 0
    DMA->LIFCR |= 0x3D << 22;
#endif
    splx(plx);
}

static void
dma_start(u_long flags, char *dst, int len){
#if 0
    dcache_flush(dst, len);

    DMASTR->CR   &= ~1;	// clear EN first
    while( DMASTR->CR & 1 ) {} // wait for it

    DMASTR->PAR   = (u_long) & SDIO->FIFO;
    DMASTR->M0AR  = (u_long) dst;
    DMASTR->NDTR  = len >> 2;

    DMASTR->CR   &= (0xF<<28) | (1<<20);
    DMASTR->CR   |= flags | DMASCR_MINC | (DMACHAN << 25)
        | DMASCR_PFCTRL
        | (1 << 23) | (1 << 21)	// burst
        | (2 << 16)		// high prio
        | (2 << 13) | (2 << 11)	// 32bit
        // RSN - IE
        ;

    DMASTR->FCR  &= ~0x7;
    DMASTR->FCR  |= (1<<2) // use fifo
        | 3;		   // thresh=full

    DMASTR->CR   |= DMASCR_EN;
#endif
}

static void
dma_stop(char *dst, int len){
#if 0
    dcache_invalidate(dst, len);

    DMASTR->CR &= ~(DMASCR_EN | DMASCR_TEIE | DMASCR_TCIE);
    dma_clr_irq();
#endif
}

static int
dma_wait_complete(void){
    utime_t t1 = get_hrtime() + 1000000;

    SDIO->MASK |= SDMMC_STA_DATAEND;

#define WAIT_DONE (SDMMC_STA_DATAEND \
                   | SDMMC_STA_CTIMEOUT | SDMMC_STA_DTIMEOUT \
                   | SDMMC_STA_CCRCFAIL | SDMMC_STA_DCRCFAIL)

    while( 1 ){
        asleep( SDIO, "sdio" );
        if( got_dataend ) break;
        if( SDIO->STA & WAIT_DONE ) break;

        await( 0x81, 1000000 );
        if( got_dataend ) break;
        if( SDIO->STA & WAIT_DONE ) break;
        if( get_hrtime() > t1 ) break;
    }

    aunsleep();
    SDIO->MASK &= ~SDMMC_STA_DATAEND;

    if( SDIO->STA & SDMMC_STA_DATAEND ){
        got_dataend = 1;
        SDIO->ICR |= SDMMC_STA_DATAEND;
    }

    trace_crumb1("sdio", "woke", SDIO->STA);

    return ! got_dataend;

}

int
sdio_bread(FILE*f, char*d, int len, offset_t pos){
    struct SDIOinfo *ii = f->d;
    int tries, ret=-1, r;

    trace_crumb3("sdio", "READ", pos, len, SDIO->STA);

#ifdef DMAALIGN
    if( (int)d & 0x1F ) kprintf("sdio buf align %x %d\n", d, len);
#endif

    if( ii->ishc ) pos /= 512;

    sync_lock(& ii->lock, "sdcard");

    for(tries=0; tries<MAXTRY; tries++){

        SDIO->DCTRL   = 0;
        SDIO->DTIMER  = RTIMEOUT << 3; // XXX
        SDIO->DLEN    = len;
        SDIO->DCTRL  |= 0
            | (1 << 13) // rst fifo
            | (9<<4)	// 512B block
            | (3<<2)	// xfer until STOP
            | (1<<1)	// read
            ;

        SDIO->ICR       = 0xFFFFFFFF;
        SDIO->IDMABASER = d;
        SDIO->IDMACTRL  = 1;
        got_dataend     = 0;

        trace_crumb2("sdio", "read", tries, SDIO->STA);

        r = sdio_cmd_r1( 18 | CMD_TRANS, pos );
        IDBGRESP(18);

        // kprintf("sdio cmd %d r %x sr %x res %x\n", SDIO->RESPCMD, r, SDIO->STA, SDIO->RESP1);


        if( !r ){
            trace_crumb1("sdio", "wait", SDIO->STA);
            r = dma_wait_complete();
            trace_crumb2("sdio", "/wait", r, SDIO->STA);

            if( SDIO->STA & SR_DTIMEOUT ) r = -1;

            if( r )
                kprintf("dma err %x, %x\n", r, SDIO->STA );
        }else{
            trace_crumb1("sdio", "err", r);
        }

        //kprintf("dma %x %x\n", DMASTR->NDTR, DMA->LISR >> 22);
        //kprintf("sr %x dl %x ct %x fc %x\n", SDIO->STA, SDIO->DLEN, SDIO->DCOUNT, SDIO->FIFOCNT);
        sdio_stop();
        // dma_stop(d, len);

        if( !r ){
            // all done!
            ret = len;
            break;
        }

        kcprintf("sd read error %qx, %d => %x, %x\n", pos, len, r, SDIO->RESP1);
        usleep(10000);

        if( tries > 2 ) sdio_clear( ii );
    }

    trace_crumb1("sdio", "/read", ret);
    
    sync_unlock(& ii->lock );
    // kprintf("sdrd => %d\n", ret);
    //if( ret > 0 ){
        hexdump( d, 16 );
    //    hexdump( d+512-16, 16 );
    //}
    return ret;
}

static void
sdio_wait_tx_complete(void){
    utime_t t1 = get_hrtime() + 100000;

    while(1){
//        if( !(SDIO->STA & (1<<12)) ) return;	// rxact
        if( !(SDIO->STA & SR_DATAEND) ) return;	// dataend
        if( get_hrtime() > t1 )      return;
    }
}

// wait for write to complete
static int
sdio_write_wait(int rca){
    int r;

    utime_t t1 = get_hrtime() + 250000;

    while(1){
        r = sdio_cmd_short( 13, rca << 16 );
        //kprintf("sdio13 cmd %d r %x sr %x res %x\n", SDIO->RESPCMD, r, SDIO->STA, SDIO->RESP1);
        r = SDIO->RESP1;
        if( ((r >> 9) & 7) < 5 ) return 0;
        if( get_hrtime() > t1 )  return -1;
        yield();
    }
}
int
sdio_bwrite(FILE*f, const char*d, int len, offset_t pos){
    struct SDIOinfo *ii = f->d;

    int tries, ret=-1, r;

    trace_crumb3("sdio", "WRITE", pos, len, SDIO->STA);


#ifdef DMAALIGN
    if( (int)d & 0x1F ) kprintf("sdio buf align %x %d\n", d, len);
#endif

    if( ii->ishc ) pos /= 512;

    sync_lock(& ii->lock, "sdcard");

    for(tries=0; tries<MAXTRY; tries++){

        if( len > 512 ){
            sdio_cmd_short( 55, ii->rca << 16 );
            sdio_cmd_short( 23, len >> 9 );	// pre-erase (slight speed improvement)
            IDBGRESP(23);
        }

        SDIO->DCTRL   = 0;
        SDIO->DTIMER  = WTIMEOUT << 3; // XXX
        SDIO->DLEN    = len;
        SDIO->DCTRL  |= 0
            | (1 << 13) // rst fifo
            | (9<<4)	// 512B block
            | (3<<2)	// xfer until STOP
            | (0<<1)	// write
            ;

        SDIO->ICR       = 0xFFFFFFFF;
        SDIO->IDMABASER = d;
        SDIO->IDMACTRL  = 1;
        got_dataend     = 0;

        trace_crumb2("sdio", "write", tries, SDIO->STA);

        if( len == 512 ){
            r = sdio_cmd_r1( 24 | CMD_TRANS, pos );		// single block
            IDBGRESP(24);
        }else{
            r = sdio_cmd_r1( 25 | CMD_TRANS, pos );		// multi block
            IDBGRESP(25);
        }

        if( !r ){
            // wait for dma complete, and xfer complete
            trace_crumb1("sdio", "wait", SDIO->STA);
            r = dma_wait_complete();
            trace_crumb2("sdio", "/wait", r, SDIO->STA);

            if( r )
                kprintf("dma err %x, %x\n", r, 0);

        }else{
            trace_crumb1("sdio", "err", r);
        }


        if( len != 512 ) sdio_stop();
        r |= sdio_write_wait(ii->rca);

        if( !r ){
            // all done!
            ret = len;
            break;
        }

        kcprintf("sd write error %qx, %d => %x, %x\n", pos, len, r, SDIO->RESP1);
        usleep(10000);
        if( tries > 2 ) sdio_clear( ii );

    }

    trace_crumb1("sdio", "/write", ret);
    sync_unlock(& ii->lock );
    //kprintf("sdwr => %d; %x %x %x\n", ret);

    return ret;

}


int
sdio_ioctl(FILE*f, int s, void*d){}


int
sdio_stat(FILE *f, struct stat *s){
    struct SDIOinfo *ii = f->d;

    s->dev     = 0;
    s->size    = (long long)ii->sectors * 512;
    s->ctime   = 0;
    s->blksize = 512;
    s->mode    = 0;
    s->flags   = SSF_BLKWRITE | SSF_NOERASE;

    return 0;
}

void
SDMMC1_IRQHandler(void){

    trace_crumb1("sdio", "irq!", SDIO->STA);

    if( SDIO->STA & SDMMC_STA_DATAEND ){
        SDIO->ICR |= SDMMC_STA_DATAEND;
        got_dataend = 1;
        wakeup( SDIO );
    }

}

#ifdef KTESTING

DEFUN(sdrdtest, "sd card test")
{
    char *buf = alloc(1024);
    struct SDIOinfo *s = sdcinfo + 0;

    int r = initialize_card(s);
    printf("init => %x\n", r);

    trace_reset();
    r = sdio_bread(&s->file, buf, 1024, 0);
    printf("read => %x\n", r);
    hexdump(buf, 256);

    return 0;
}

DEFUN(sdwrtest, "sd card test")
{
    char *buf = alloc(1024);
    struct SDIOinfo *s = sdcinfo + 0;

    int r;
    //int r = initialize_card(s);
    //printf("init => %x\n", r);
    //trace_reset();

    r = sdio_bread(&s->file, buf, 1024, 0);
    printf("read => %x\n", r);
    hexdump(buf, 256);

    trace_reset();
    r = sdio_bwrite(&s->file, buf, 1024, 0);
    printf("write => %x\n", r);

    return 0;
}


DEFUN(sdtest, "sd card test")
{
    char *buf = alloc(1024);
    FILE *f   = fopen("dev:sd0", "w");

    printf("reading...\n");
    sdio_bread( f, buf, 512, 0);	// read first sector
    printf("%16,.4H\n", buf);
    printf("%16,.4H\n", buf+512-16);

    memset(buf, random() & 0xFF, 512);
    printf("%16,.4H\n", buf);

    printf("writing...\n");
    sdio_bwrite(f, buf, 512, 0xF0000 ); // write

    printf("reading...\n");
    bzero(buf, 512);
    sdio_bread( f, buf, 512, 0xF0000 ); // read back
    printf("%16,.4H\n", buf);
    printf("%16,.4H\n", buf+512-16);

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
            fwrite(f, (char*)0x20000000, wl );
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
    int i, len;
    FILE *f;

    if( argc != 2 ){
        f_error("rdfile name");
        return -1;
    }

    len = atoi(argv[2]);
    char *buf = alloc( 8192 );

    int t0 = get_hrtime();
    f = fopen( argv[1], "r" );
    if( f ){
        while(1){
            int rl = fread(f, buf, 8192);
            if( rl != 8192 ) break;
        }
        fclose(f);

        int t1 = get_hrtime();
        printf("time: %d\n", t1 - t0);
    }

    free(buf, 8192);
    return 0;
}

DEFUN(sdgpio, "")
{

    gpio_init( GPIO_C8,  GPIO_OUTPUT | GPIO_PUSH_PULL  | GPIO_SPEED_100MHZ | GPIO_PULL_UP );	// data
    gpio_init( GPIO_C9,  GPIO_OUTPUT | GPIO_PUSH_PULL  | GPIO_SPEED_100MHZ | GPIO_PULL_UP );	// data
    gpio_init( GPIO_C10, GPIO_OUTPUT | GPIO_PUSH_PULL  | GPIO_SPEED_100MHZ | GPIO_PULL_UP );	// data
    gpio_init( GPIO_C11, GPIO_OUTPUT | GPIO_PUSH_PULL  | GPIO_SPEED_100MHZ | GPIO_PULL_UP );	// data

    while(1){
        gpio_set(GPIO_C8);  usleep(125000);
        gpio_set(GPIO_C9);  usleep(125000);
        gpio_set(GPIO_C10); usleep(125000);
        gpio_set(GPIO_C11); usleep(125000);

        gpio_clear(GPIO_C8);  usleep(125000);
        gpio_clear(GPIO_C9);  usleep(125000);
        gpio_clear(GPIO_C10); usleep(125000);
        gpio_clear(GPIO_C11); usleep(125000);

    }

    return 0;
}
#endif
