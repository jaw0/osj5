/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Dec-29 13:01 (EST)
  Function: use on chip flash for storage

*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <stflash.h>
#include <stm32.h>

extern uint16_t *r_flashkb;
extern uint16_t stm32f7_cpuid;

/*
- If nDBANK=1, Size of main memory block:
  4 sectors of 32 KBytes,
  1 sector of 128 KBytes,
  7 sectors of 256 KBytes (reference to memory organization)
- If nDBANK=0, Each 1MB banks is composed of:
  4 sectors of 16 KBytes,
  1 sector of 64 KBytes,
  7 sectors of 128 KBytes (reference to memory organization)
*/




static struct Flash_Info finfo[8];

const struct Flash_Info finfo_72X[] = {
    { .addr = 0x08000000, .blockno = 0, .block_size = 16, .erase_size = 16*1024, .write_size = 4, .nblocks = 4 },
    { .addr = 0x08010000, .blockno = 4, .block_size = 64, .erase_size = 64*1024, .write_size = 4, .nblocks = 1 },
    { .addr = 0x08020000, .blockno = 5, .block_size =128, .erase_size =128*1024, .write_size = 4, .nblocks = 3 },
    {0},
};
const struct Flash_Info finfo_74X[] = {
    { .addr = 0x08000000, .blockno = 0, .block_size = 32, .erase_size = 32*1024, .write_size = 4, .nblocks = 4 },
    { .addr = 0x08020000, .blockno = 4, .block_size =128, .erase_size =128*1024, .write_size = 4, .nblocks = 1 },
    { .addr = 0x08040000, .blockno = 5, .block_size =256, .erase_size =256*1024, .write_size = 4, .nblocks = 3 },
    {0},
};

const struct Flash_Info finfo_76X1[] = { // single bank
    { .addr = 0x08000000, .blockno = 0, .block_size = 32, .erase_size = 32*1024, .write_size = 4, .nblocks = 4 },
    { .addr = 0x08020000, .blockno = 4, .block_size =128, .erase_size =128*1024, .write_size = 4, .nblocks = 1 },
    { .addr = 0x08040000, .blockno = 5, .block_size =256, .erase_size =256*1024, .write_size = 4, .nblocks = 7 },
    {0},
};
const struct Flash_Info finfo_76X21[] = { // dual bannk, 1MB
    { .addr = 0x08000000, .blockno = 0, .block_size = 16, .erase_size = 16*1024, .write_size = 4, .nblocks = 4 },
    { .addr = 0x08010000, .blockno = 4, .block_size = 64, .erase_size = 64*1024, .write_size = 4, .nblocks = 1 },
    { .addr = 0x08020000, .blockno = 5, .block_size =128, .erase_size =128*1024, .write_size = 4, .nblocks = 3 },
    { .addr = 0x08080000, .blockno =12, .block_size = 16, .erase_size = 16*1024, .write_size = 4, .nblocks = 4 },
    { .addr = 0x08090000, .blockno =16, .block_size = 64, .erase_size = 64*1024, .write_size = 4, .nblocks = 1 },
    { .addr = 0x080A0000, .blockno =17, .block_size =128, .erase_size =128*1024, .write_size = 4, .nblocks = 3 },
    {0},
};
const struct Flash_Info finfo_76X22[] = { // dual bank, 2MB
    { .addr = 0x08000000, .blockno = 0, .block_size = 16, .erase_size = 16*1024, .write_size = 4, .nblocks = 4 },
    { .addr = 0x08010000, .blockno = 4, .block_size = 64, .erase_size = 64*1024, .write_size = 4, .nblocks = 1 },
    { .addr = 0x08020000, .blockno = 5, .block_size =128, .erase_size =128*1024, .write_size = 4, .nblocks = 7 },
    { .addr = 0x08100000, .blockno =12, .block_size = 16, .erase_size = 16*1024, .write_size = 4, .nblocks = 4 },
    { .addr = 0x08110000, .blockno =16, .block_size = 64, .erase_size = 64*1024, .write_size = 4, .nblocks = 1 },
    { .addr = 0x08120000, .blockno =17, .block_size =128, .erase_size =128*1024, .write_size = 4, .nblocks = 7 },
    {0},
};

static int
dualboot_enabled(){
    return 0;
}

const struct Flash_Info *
stflash_flashinfo(){

    int size = *r_flashkb; // in kB

    if( stm32f7_cpuid == CPUID_STM32F72X ){
        // 64k, 256k or 512k
        bcopy(finfo_72X, finfo, sizeof(finfo_72X));

        if( size == 64 ){
            finfo[1].addr = 0;
            finfo[2].addr = 0;
            return finfo;
        }

        finfo[2].nblocks = (size == 512) ? 3 : 1;
        return finfo;
    }

    if( stm32f7_cpuid == CPUID_STM32F74X ){
        // 64k, 512k, or 1M
        bcopy(finfo_74X, finfo, sizeof(finfo_74X));
        if( size == 64 ){
            finfo[0].nblocks = 2;
            finfo[1].addr = 0;
            finfo[2].addr = 0;
            return finfo;
        }

        finfo[2].nblocks = (size == 1024) ? 3 : 1;
        return finfo;
    }

    // CPUID_STM32F76X
    if( dualboot_enabled() ){
        // 1MB or 2MB
        if( size == 1024 ){
            bcopy(finfo_76X21, finfo, sizeof(finfo_76X21));
        }else{
            bcopy(finfo_76X22, finfo, sizeof(finfo_76X22));
        }
    }else{
        // 1MB or 2MB
        bcopy(finfo_76X1, finfo, sizeof(finfo_76X1));
        finfo[2].nblocks = (size == 2048) ? 7 : 3;
    }

    return finfo;
}
