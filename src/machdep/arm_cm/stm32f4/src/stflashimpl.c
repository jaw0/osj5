/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Dec-29 13:01 (EST)
  Function: use on chip flash for storage

*/

#include <conf.h>
#include <nstdio.h>
#include <arch.h>
#include <dev.h>
#include <fs.h>
#include <misc.h>
#include <stflash.h>
#include <stm32.h>

#define R_FLASHKB	((unsigned short *)(0x1FFF7A22))
#define FLASHSTART	0x08000000


static struct Flash_Info finfo[3];


const struct Flash_Info *
stflash_flashinfo(){

    int size = *R_FLASHKB; // in kB: 512, 1024, 2048

    finfo[0].addr = 0x08020000;
    finfo[0].blockno = 5;
    finfo[0].blocksize = 128;
    finfo[0].nblocks = (size == 512) ? 3 : 7;
    finfo[1].addr = 0;

    if( size == 2048 ){
        finfo[1].addr = 0x08120000;
        finfo[1].blockno = 17;
        finfo[1].blocksize = 128;
        finfo[1].nblocks = 7;

        finfo[2].addr = 0;
    }

    return finfo;
}
