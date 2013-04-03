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


extern int spi_sd_init(const struct SPIConf *cf, char *, char *);

struct SDCinfo {
    const char		*name;
    struct SPIConf	spicf;
    u_char		sdcid[16];
    u_char		sdcsd[16];	// a meshigas of unaligned jibber-jabber
    int			sectors;
} sdcinfo[ N_SDCARD ];



int
sdcard_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct SDCinfo *ii = sdcinfo + unit;
    char info[32];
    int i;

    ii->name = dev->name;
    ii->spicf.unit  = dev->port;
    ii->spicf.speed = 400000;
    ii->spicf.nss   = 1;
    ii->spicf.ss[0] = dev->arg[0];

    gpio_init( dev->arg[0], GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
    gpio_set( dev->arg[0] );

    int r = spi_sd_init( & ii->spicf, (char*)ii->sdcid, (char*)ii->sdcsd );

    if( r ) return 0;	/* no card installed */

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
    }else{
        // SDHC version 2.0
        nsect = (ii->sdcsd[9] + (ii->sdcsd[8]<<8) + ((ii->sdcsd[7]&0x3F)<<16) + 1) * 1024;
        sdtype = "SD/HC";
    }

    ii->sectors = nsect;

    bootmsg("%s %s sdcard at spi%d %s %d sect, %d MB\n",
            dev->name, sdtype, dev->port,
            info,
            nsect, nsect>>11
        );


    return 0;
}

