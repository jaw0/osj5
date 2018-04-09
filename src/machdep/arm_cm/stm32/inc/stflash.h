

#ifndef __stm32_stflash_h__
#define __stm32_stflash_h__

struct Flash_Info {
    u_int addr;
    short blockno;
    int   block_size;	// in kB
    int	  write_size;
    int   erase_size;
    int   nblocks;
};


extern const struct Flash_Info * stflash_flashinfo();
extern u_int stflash_flashend();


#endif /* __stm32_stflash_h__ */

