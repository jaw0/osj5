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

#define R_FLASHKB	((unsigned short *)(0x0BFA07A0))

static struct Flash_Info finfo[2];

const struct Flash_Info *
stflash_flashinfo(){

    int size = *R_FLASHKB; // in kB: 512, 1024, 2048, 4096

    finfo[0].addr = 0x08000000;
    finfo[0].blockno = 0;
    finfo[0].block_size = 8;
    finfo[0].nblocks = size / 8;
    finfo[0].erase_size = 8192;
    finfo[0].write_size = 16;
    finfo[1].addr = 0;

    return finfo;
}
