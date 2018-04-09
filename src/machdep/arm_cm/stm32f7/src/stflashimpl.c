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

#define R_FLASHKB	((unsigned short *)(0x1FF0F442))

#define FLASHSTART	0x08000000


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




static struct Flash_Info finfo[3];


static int
dualboot_enabled(){
    return 0;
}

const struct Flash_Info *
stflash_flashinfo(){

    int size = *R_FLASHKB; // in kB

    if( dualboot_enabled() ){
        finfo[0].addr = 0x08020000;
        finfo[0].blockno = 5;
        finfo[0].block_size = 128;
        finfo[0].erase_size = 128 * 1024;
        finfo[0].write_size = 4;
        finfo[0].nblocks = (size == 2048) ? 7 : 3;

        finfo[1].addr = 0x08120000;
        finfo[1].blockno = 5 | (1<<4);
        finfo[1].block_size = 128;
        finfo[1].erase_size = 128 * 1024;
        finfo[1].write_size = 4;
        finfo[1].nblocks = (size == 2048) ? 7 : 3;

        finfo[2].addr = 0;
    }else{
        finfo[0].addr = 0x08040000;
        finfo[0].blockno = 5;
        finfo[0].block_size = 256;
        finfo[0].erase_size = 256 * 1024;
        finfo[0].write_size = 4;
        finfo[0].nblocks = (size == 2048) ? 7 : 3;

        finfo[1].addr = 0;
    }

    return finfo;
}
