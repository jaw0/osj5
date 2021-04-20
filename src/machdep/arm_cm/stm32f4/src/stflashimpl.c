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

extern uint16_t stm32f4_cpuid;

static struct Flash_Info finfo[8];

const struct Flash_Info finfo_40X[] = { // 40x, 41x
    { .addr = 0x08000000, .blockno = 0, .block_size = 16, .erase_size = 16*1024, .write_size = 4, .nblocks = 4 },
    { .addr = 0x08010000, .blockno = 4, .block_size = 64, .erase_size = 64*1024, .write_size = 4, .nblocks = 1 },
    { .addr = 0x08020000, .blockno = 5, .block_size =128, .erase_size =128*1024, .write_size = 4, .nblocks = 7 },
    {0},
};

const struct Flash_Info finfo_42X[] = { // 42x, 43x
    { .addr = 0x08000000, .blockno = 0, .block_size = 16, .erase_size = 16*1024, .write_size = 4, .nblocks = 4 },
    { .addr = 0x08010000, .blockno = 4, .block_size = 64, .erase_size = 64*1024, .write_size = 4, .nblocks = 1 },
    { .addr = 0x08020000, .blockno = 5, .block_size =128, .erase_size =128*1024, .write_size = 4, .nblocks = 7 },
    { .addr = 0x08100000, .blockno =12, .block_size = 16, .erase_size = 16*1024, .write_size = 4, .nblocks = 4 },
    { .addr = 0x08110000, .blockno =16, .block_size = 64, .erase_size = 64*1024, .write_size = 4, .nblocks = 1 },
    { .addr = 0x08120000, .blockno =17, .block_size =128, .erase_size =128*1024, .write_size = 4, .nblocks = 7 },
    {0},
};


const struct Flash_Info *
stflash_flashinfo(){

    int size = *R_FLASHKB; // in kB: 512, 1024, 2048
#if 0
    if( stm32f4_cpuid == CPUID_STM32F40X ){
        bcopy(finfo_40X, finfo, sizeof(finfo_40X));

        finfo[2].nblocks = (size == 512) ? 3 : 7;
        return finfo;
    }

    if( stm32f4_cpuid == CPUID_STM32F42X ){
        bcopy(finfo_42X, finfo, sizeof(finfo_42X));
        return finfo;
    }

#endif
    finfo[0].addr = 0x08020000;
    finfo[0].blockno = 5;
    finfo[0].block_size = 128;
    finfo[0].erase_size = 128 * 1024;
    finfo[0].write_size = 4;
    finfo[0].nblocks = (size == 512) ? 3 : 7;
    finfo[1].addr = 0;

    if( size == 2048 ){
        finfo[1].addr = 0x08120000;
        finfo[1].blockno = 17;
        finfo[1].block_size = 128;
        finfo[1].erase_size = 128 * 1024;
        finfo[1].write_size = 4;
        finfo[1].nblocks = 7;

        finfo[2].addr = 0;
    }

    return finfo;
}
