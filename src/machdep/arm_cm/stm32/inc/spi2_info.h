/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-10 12:27 (EST)
  Function: spi2 info

*/
#ifndef __stm32_spi2_info_h__
#define __stm32_spi2_info_h__


struct SPIInfo {
    const char		*name;
    SPI_TypeDef 	*addr;
    int			maxtsize;

    dma_req_t		dmareq;

    u_char 	  	irq;
    int			clock;

    lock_t		lock;
    int			state;
    u_long		errorflags;

    // currently doing:
    spi_msg		*msg;
    int			num_msg;
    const struct SPIConf	*cf;
    utime_t		timeout;
};


#endif /* __stm32_spi2_info_h__ */
