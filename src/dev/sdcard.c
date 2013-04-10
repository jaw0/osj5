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

int sdcard_ioctl(FILE*, int, void*);
int sdcard_bread(FILE*, char*, int, offset_t);
int sdcard_bwrite(FILE*, const char*, int, offset_t);

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
    0, /* stat */
    sdcard_ioctl
};


struct SDCinfo {
    FILE file;
    const char		*name;
    struct SPIConf	spicf;
    u_char		sdcid[16];
    u_char		sdcsd[16];	// a meshigas of unaligned jibber-jabber
    int			sectors;
    int			ishc;
} sdcinfo[ N_SDCARD ];


//extern int spi_sd_init(const struct SPIConf *cf, char *, char *);
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
    ii->spicf.unit  = dev->port;
    ii->spicf.speed = 400000;
    ii->spicf.nss   = 1;
    ii->spicf.ss[0] = dev->arg[0];

    gpio_init( dev->arg[0], GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
    gpio_set( dev->arg[0] );

    int r = initialize_card(ii);

    if( !r ) return 0;	/* no card installed */

    ii->spicf.speed = dev->baud ? dev->baud : 25000000;

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

    return & ii->file;
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


/****************************************************************/

#define SDCMD(m, cmd)	\
    m.mode = SPIMO_WRITE; \
    m.dlen = 6; \
    m.data = (char*)cmd;

#define SDRX1(m)	\
    m.mode  = SPIMO_UNTIL; \
    m.until = _wait_response; \
    m.dlen  = 4000;

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

    m[0].mode  = SPIMO_PINSOFF;
    m[0].dlen  = 12;		// clock it > 74 cycles
    spi_xfer(& ii->spicf, 1, m, 1000000);

    int r = _sd_cmd_r1(ii, m, cmd0);
    kprintf("cmd0 %x, %x\n", r, m[3].response);
    if( r != SPI_XFER_OK ) return 0;

    // cmd8 - required to enable v2/HC features (>2GB)
    int rcmd8;
    r = _sd_cmd_r3(ii, m, cmd8, &rcmd8);
    kprintf("cmd8 %x, %x, %x\n", r, m[1].response, rcmd8);
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
    kprintf("cmd58 %x %x %x\n", r, m[1].response, ocr);
    // OCR - permitted voltages + CCS
    int ishc = 0;
    if( isv2 && (ocr & 0x40) ) ishc = 1;	// HC yay!
    // card is ready


    // read CID, CSD
    r = _sd_cmd_r16(ii, m, cmd10, ii->sdcid);
    kprintf("cid %x %x\n", r, m[1].response);
    r = _sd_cmd_r16(ii, m, cmd9,  ii->sdcsd);
    kprintf("csd %x %x\n", r, m[1].response);

    hexdump(ii->sdcid, 16);
    hexdump(ii->sdcsd, 16);

    return 1;
}

/****************************************************************/

int
sdcard_ioctl(FILE*f, int s, void*d){}

static inline void
_sdcard_blk(struct SDCinfo *ii, int pos, u_char *cmd){

    if( ii->ishc ) pos /= 512;

    cmd[1] = pos >> 24;
    cmd[2] = pos >> 16;
    cmd[3] = pos >> 8;
    cmd[4] = pos;

}

int
sdcard_bread(FILE*f, char*d, int len, offset_t pos){
    struct SDCinfo *ii = f->d;
    u_char cmd[6];
    spi_msg m[6];
    int tot = 0;

    cmd[0] = 0x40 | 17;

    while(len){

        _sdcard_blk(ii, pos, cmd);
        SDCMD(m[0], cmd);
        SDRX1(m[1]);
        m[2].mode  = SPIMO_UNTIL;
        m[2].until = _wait_token;
        m[2].dlen  = 1000;
        m[3].mode  = SPIMO_READ;
        m[3].dlen  = 512;
        m[3].data  = d;
        m[4].mode  = SPIMO_DELAY;	// skip crc
        m[4].dlen  = 2;
        SDFIN(m[5]);
        m[5].dlen = 16;			// extra delay

        int r = spi_xfer(& ii->spicf, 6, m, 1000000);
        if( r != SPI_XFER_OK ) return -1;

        len -= 512;
        pos += 512;
        d   += 512;
        tot += 512;
    }

    return tot;
}

static const u_short token = 0xFEFF;

int
sdcard_bwrite(FILE*f, const char*d, int len, offset_t pos){
    struct SDCinfo *ii = f->d;
    u_char cmd[6];
    spi_msg m[6];
    int tot = 0;

    cmd[0] = 0x40 | 24;

    while(len){

        _sdcard_blk(ii, pos, cmd);

        SDCMD(m[0], cmd);
        SDRX1(m[1]);
        m[2].mode  = SPIMO_WRITE;
        m[2].data  = (char*)&token;	// delay + token
        m[2].dlen  = 2;
        m[3].mode  = SPIMO_WRITE;
        m[3].dlen  = 512;
        m[3].data  = (char*)d;
        m[4].mode  = SPIMO_DELAY;	// skip crc
        m[4].dlen  = 2;
        SDFIN(m[5]);
        m[5].dlen = 16;			// extra delay

        int r = spi_xfer(& ii->spicf, 6, m, 1000000);
        if( r != SPI_XFER_OK ) return -1;

        len -= 512;
        pos += 512;
        d   += 512;
        tot += 512;
    }

    return tot;
}



