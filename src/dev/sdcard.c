/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-01 22:35 (EDT)
  Function: sd card block i/o

*/

#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <alloc.h>
#include <nstdio.h>
#include <locks.h>
#include <dev.h>
#include <error.h>
#include <spi.h>
#include <gpio.h>
#include <sdcard.h>
#include <userint.h>

#define MAXTRY 3
#define MAXMULTI	16

int sdcard_ioctl(FILE*, int, void*);
int sdcard_bread(FILE*, char*, int, offset_t);
int sdcard_bwrite(FILE*, const char*, int, offset_t);
int sdcard_stat(FILE *, struct stat*);


const struct io_fs sdcard_fs = {
    0, /* putc */
    0, /* getc */
    0, /* close */
    0, /* flush */
    0, /* status */
    0, /* read */
    0, /* write */
    sdcard_bread,  /* bread */
    sdcard_bwrite, /* bwrite */
    0, /* seek */
    0, /* tell */
    sdcard_stat,
    sdcard_ioctl
};


struct SDCinfo {
    FILE file;
    const char		*name;
    struct SPIConf	spicf;
    u_char		sdcid[16];
    u_char		sdcsd[16];	// a meshigas of unaligned jibber-jabber
    int			sectors;
    u_char		ishc;
    int8_t		maxblock;
    lock_t		lock;
    u_char		cmd[6];
    spi_msg		m[72];
} sdcinfo[ N_SDCARD ];


static int initialize_card(struct SDCinfo *);


int
sdcard_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct SDCinfo *ii = sdcinfo + unit;
    char info[32];
    int i;

    finit( & ii->file );
    ii->file.d  = (void*)ii;
    ii->file.fs = & sdcard_fs;

    ii->name = dev->name;
    ii->lock = 0;
    ii->spicf.unit  = dev->port;
    ii->spicf.speed = 400000;
    ii->spicf.nss   = 1;
    ii->spicf.ss[0] = dev->arg[0];
    ii->maxblock    = MAXMULTI;

    // XXX - this doesn't really belong here
#if defined(PLATFORM_STM32F1)
    gpio_init( dev->arg[0], GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
    gpio_set( dev->arg[0] );
    if( dev->arg[1] ){
        // card present? arg[1] is card detect io
        gpio_init( dev->arg[1], GPIO_INPUT_FLOATING );
        if( !gpio_get( dev->arg[1] ) ) return 0;
    }
#elif defined(PLATFORM_STM32F4)
    gpio_init( dev->arg[0], GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_25MHZ );
    gpio_set( dev->arg[0] );
    if( dev->arg[1] ){
        // card present? arg[1] is card detect io
        gpio_init( dev->arg[1], GPIO_INPUT );
        if( !gpio_get( dev->arg[1] ) ) return 0;
    }
#else
#  error "unknown platform"
#endif


    int r = initialize_card(ii);

    if( !r ) return 0;	/* no card installed */

    //hexdump(ii->sdcid, 16);
    //hexdump(ii->sdcsd, 16);

    ii->spicf.speed = dev->baud ? dev->baud : 25000000;
    int actspeed = spi_set_speed( & ii->spicf, ii->spicf.speed );
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

    bootmsg("%s at spi%d %s sdcard %s %d sect, %d MB\n",
            dev->name, dev->port,
            sdtype, info,
            nsect, nsect>>11
        );

    // do we need partitions?

#if 0
    dkpart_learn( dev, "sd", unit, & ii->file, nsect );
#else
    // or:

    snprintf(info, sizeof(info), "%s:", ii->name);
    fmount( & ii->file, info, "fatfs" );

    bootmsg( "sdcard %s speed %dkHz mounted on %s type %s\n",
	     ii->name, actspeed/1000, info, "fatfs" );
#endif

    return (int)& ii->file;
}

/****************************************************************/

static const u_char cmd0[]  = { 0x40,      0, 0, 0, 0, 0x95 };
static const u_char cmd8[]  = { 0x40 |  8, 0, 0, 1, 0xAA, 0x87 };
static const u_char cmd9[]  = { 0x40 |  9, 0, 0, 0, 0, 0x95 };
static const u_char cmd10[] = { 0x40 | 10, 0, 0, 0, 0, 0x95 };
static const u_char cmd55[] = { 0x40 | 55, 0, 0, 0, 0, 0x95 };
static const u_char cmd58[] = { 0x40 | 58, 0, 0, 0, 0, 0x95 };
static const u_char cmd41[] = { 0x40 | 41, 0, 0, 0, 0, 0x95 };
static const u_char cmd41v2[] = { 0x40 | 41, 0x40, 0, 0, 0, 0x95 };

static int
_wait_response(int c){
    if( c & 0x80 ) return 0;
    return 1; 	// got it
}

static int
_wait_token(int c){
    if( c == 0xFF ) return 0;
    return 1; 	// got it
}

static int
_wait_notnull(int c){
    if( c == 0 ) return 0;
    return 1; 	// got it
}

static int
_wait_datatoken(int c){
    return 1;
}

/****************************************************************/

#define SDCMD(m, cmd)	\
    m.mode = SPIMO_WRITE; \
    m.dlen = 6; \
    m.data = (char*)cmd;

#define SDRX1(m)	\
    m.mode  = SPIMO_UNTIL; \
    m.until = _wait_response; \
    m.dlen  = 50000;

#define SDRXD1(m)	\
    m.mode  = SPIMO_READ; \
    m.data  = & m.response; \
    m.dlen  = 1;

#define SDFIN(m)	\
    m.mode = SPIMO_PINSOFF; \
    m.dlen = 4;

static int
_sd_cmd_r1(struct SDCinfo *ii, spi_msg *m, const char *cmd){
    SDCMD(m[0], cmd);
    SDRX1(m[1]);
    SDFIN(m[2]);
    return spi_xfer(& ii->spicf, 3, m, 1000000);
}

static int
_sd_cmd_r3(struct SDCinfo *ii, spi_msg *m, const char *cmd, char *res){
    SDCMD(m[0], cmd);
    SDRX1(m[1]);
    m[2].mode  = SPIMO_READ;
    m[2].dlen  = 4;
    m[2].data  = res;
    SDFIN(m[3]);
    m[3].dlen = 16;	// extra delay
    return spi_xfer(& ii->spicf, 4, m, 1000000);
}

static int
_sd_cmd_r16(struct SDCinfo *ii, spi_msg *m, const char *cmd, char *res){

    SDCMD(m[0], cmd);
    SDRX1(m[1]);
    m[2].mode  = SPIMO_UNTIL;
    m[2].until = _wait_token;
    m[2].dlen  = 1000;
    m[3].mode  = SPIMO_READ;
    m[3].dlen  = 16;
    m[3].data  = res;
    m[4].mode  = SPIMO_DELAY;	// skip crc
    m[4].dlen  = 2;
    SDFIN(m[5]);
    m[5].dlen = 16;		// extra delay

    return spi_xfer(& ii->spicf, 6, m, 1000000);
}


static int
initialize_card(struct SDCinfo *ii){
    spi_msg m[6];
    int i, r;

    for(i=0; i<5; i++){
        m[0].mode  = SPIMO_PINSOFF;
        m[0].dlen  = 12 * (i+1);		// clock it > 74 cycles
        spi_xfer(& ii->spicf, 1, m, 1000000);

        r = _sd_cmd_r1(ii, m, cmd0);

        //kprintf("cmd0 %x, %x\n", r, m[3].response);
        if( r == SPI_XFER_OK ) break;
    }
    if( r != SPI_XFER_OK ) return 0;

    // cmd8 - required to enable v2/HC features (>2GB)
    int rcmd8;
    r = _sd_cmd_r3(ii, m, cmd8, (char*)&rcmd8);
    //kprintf("cmd8 %x, %x, %x\n", r, m[1].response, rcmd8);
    if( r != SPI_XFER_OK ) return 0;

    int isv2 = 0;
    if( (m[1].response & 0x7E) == 0 ) isv2 = 1;	// 2.0 yay!
    // RSN - check voltages


    // loop until ready
    //  cmd 55/41 => R1
    int max = 1000;
    while( max-- > 0 ){
        r = _sd_cmd_r1(ii, m, cmd55);
        r = _sd_cmd_r1(ii, m, isv2 ? cmd41v2 : cmd41);
        //kprintf("cmd41 %x %x\n", r, m[1].response);
        if( !(m[1].response & 1) ) break;	// ready
    }

    // cmd 58 => R3
    int ocr;
    r = _sd_cmd_r3(ii, m, cmd58, (char*)&ocr);
    // NB - ocr is byte swapped
    //kprintf("cmd58 %x %x %x\n", r, m[1].response, ocr);
    // OCR - permitted voltages + CCS
    int ishc = 0;
    if( isv2 && (ocr & 0x40) ) ishc = 1;	// HC yay!
    // card is ready


    // read CID, CSD
    r = _sd_cmd_r16(ii, m, cmd10, ii->sdcid);
    r = _sd_cmd_r16(ii, m, cmd9,  ii->sdcsd);

    return 1;
}

/****************************************************************/

int
sdcard_ioctl(FILE*f, int s, void*d){}

static inline void
_sdcard_blk(struct SDCinfo *ii, offset_t pos, u_char *cmd){

    if( ii->ishc ) pos /= 512;

    cmd[1] = pos >> 24;
    cmd[2] = pos >> 16;
    cmd[3] = pos >> 8;
    cmd[4] = pos;

    cmd[5] = 0;		// no crc
}

static void
sdcard_clear(struct SDCinfo *ii){
    spi_clear(& ii->spicf );
    initialize_card(ii);
}

static const char _cmd_stop[] = { 0x40 | 12, 0,0,0,0,0 };

int
sdcard_bread(FILE*f, char*d, int len, offset_t pos){
    struct SDCinfo *ii = f->d;
    u_char *cmd = ii->cmd;
    spi_msg *m  = ii->m;
    int tot = 0, tries, r, nummsg;

    sync_lock(& ii->lock, "sdcard");
    bzero(m, sizeof(m));
    cmd[0] = 0x40 | 18;

    //kprintf("sdrd %qx %d\n", pos, len);

    while(len){
        int nblk = len >> 9;
        if( nblk > MAXMULTI ) nblk = MAXMULTI;

        for(tries=0; tries<MAXTRY; tries++){

            _sdcard_blk(ii, pos, cmd);
            SDCMD(m[0], cmd);			// command
            SDRX1(m[1]);			// response
            nummsg = 2;

            // add more blocks
            for(r=0; r<nblk; r++){
                m[nummsg].mode  = SPIMO_UNTIL;
                m[nummsg].until = _wait_token;
                m[nummsg].dlen  = 100000;
                nummsg++;

                m[nummsg].mode  = SPIMO_READ;
                m[nummsg].dlen  = 512;
                m[nummsg].data = (char*)d + (r<<9);
                nummsg++;

                m[nummsg].mode  = SPIMO_DELAY;	// skip crc
                m[nummsg].dlen  = 2;
                nummsg++;
            }

            // stop!
            m[nummsg].mode = SPIMO_WRITE;
            m[nummsg].dlen = 6;
            m[nummsg].data = _cmd_stop;
            nummsg++;
            SDRX1(m[nummsg]);			// response
            nummsg ++;

            SDFIN(m[nummsg]);
            m[nummsg].dlen = 16;		// extra delay
            nummsg++;

            r = spi_xfer(& ii->spicf, nummsg, m, 1000000);

            // QQQ - which response?
            if( m[1].response != 0 ) r = m[1].response;
            if( r == SPI_XFER_OK ) break;

            kcprintf("sd read error %qx, %d => %x, %x\n", pos, len, r, m[5].response);
            //hexdump(m, sizeof(ii->m));
            usleep(10000);
            sdcard_clear( ii );
        }

        if( r != SPI_XFER_OK ){
            sync_unlock(& ii->lock );
            return -1;
        }
        len -= nblk * 512;
        pos += nblk * 512;
        d   += nblk * 512;
        tot += nblk * 512;
    }

    sync_unlock(& ii->lock );
    return tot;
}

static const u_char  token_multi[] = {0xFC};
static const u_char  token_stop[]  = {0xFD, 0xFF};	// plus delay

int
sdcard_bwrite(FILE*f, const char*d, int len, offset_t pos){
    struct SDCinfo *ii = f->d;
    u_char *cmd = ii->cmd;
    spi_msg *m  = ii->m;
    int tot = 0, r;
    int8_t tries, nummsg;

    sync_lock(& ii->lock, "sdcard");
    bzero(m, sizeof(m));
    cmd[0] = 0x40 | 25;

    //kprintf("sdwr %qx %d\n", pos, len);

    while(len){
        int nblk = len >> 9;
        if( nblk > ii->maxblock ) nblk = ii->maxblock;

        for(tries=0; tries<MAXTRY; tries++){

            _sdcard_blk(ii, pos, cmd);
            SDCMD(m[0], cmd);			// command
            SDRX1(m[1]);			// response
            nummsg = 2;

            // add more blocks
            for(r=0; r<nblk; r++){
                // start token
                m[nummsg].mode = SPIMO_WRITE;
                m[nummsg].data = (char*)token_multi;
                m[nummsg].dlen = 1;
                nummsg ++;

                // data + crc
                m[nummsg].mode = SPIMO_WRITE;
                m[nummsg].dlen = 512 + 2;
                m[nummsg].data = (char*)d + (r<<9);
                nummsg ++;

                // response
                SDRXD1(m[nummsg]);
                nummsg ++;

                m[nummsg].mode  = SPIMO_UNTIL_SLOW;		// this is usually quick
                m[nummsg].until = _wait_notnull;
                m[nummsg].dlen  = 1000000;
                nummsg++;
            }
            m[nummsg].mode = SPIMO_WRITE;
            m[nummsg].data = (char*)token_stop;
            m[nummsg].dlen = 2;
            nummsg ++;

            m[nummsg].mode  = SPIMO_UNTIL_SLOW;		// typically ~2ms
            m[nummsg].until = _wait_notnull;
            m[nummsg].dlen  = 2000000;
            nummsg++;


            SDFIN(m[nummsg]);
            m[nummsg].dlen = 16;				// extra delay
            nummsg ++;

            r = spi_xfer(& ii->spicf, nummsg, m, 1000000);

            // check responses
            int8_t i;
            for(i=0; i<nblk; i++){
                //kprintf("m%dr %x; ", 4*i + 4, m[4*i+4].response);
                if( (m[4*i+4].response & 0x1f) != 5 ){
                    r = SPI_XFER_ERROR;
                    kcprintf("sd bad-resp [%d/%d] => %x\n", i, 4*i+4, m[4*i+4].response);
                }
            }

            if(r){
                spi_dump_crumb();

                //r = SPI_XFER_ERROR;
                // try again with less
                if( nblk > 1 ) nblk >>= 1;
            }

            if( r == SPI_XFER_OK ) break;

            kcprintf("sd write error %qx, %d => %d, %x\n", pos, nblk, r, m[nummsg-5].response);
            //hexdump(m, sizeof(ii->m));
            usleep(10000);
            sdcard_clear( ii );
        }

        if( r != SPI_XFER_OK ){
            sync_unlock(& ii->lock );
            return -1;
        }
        len -= nblk * 512;
        pos += nblk * 512;
        d   += nblk * 512;
        tot += nblk * 512;
    }

    sync_unlock(& ii->lock );
    return tot;
}

int
sdcard_stat(FILE *f, struct stat *s){
    struct SDCinfo *ii = f->d;

    s->dev     = 0;
    s->size    = (long long)ii->sectors * 512;
    s->ctime   = 0;
    s->blksize = 512;
    s->mode    = 0;
    s->flags   = SSF_BLKWRITE | SSF_NOERASE;

    return 0;
}

/****************************************************************/

#ifdef KTESTING
DEFUN(set_sdcard_speed, "change sdcard speed")
{
    int n = 5000000;

    if( argc > 1 ) n = atoi(argv[1]);
    sdcinfo[0].spicf.speed = n;
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
#endif
