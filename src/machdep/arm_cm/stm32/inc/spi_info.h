/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-10 12:27 (EST)
  Function: 

*/
#ifndef __spi_info_h__
#define __spi_info_h__


#ifdef DMA_TYPE_1
typedef DMA_Channel_TypeDef DMAC_T;
#elif defined(DMA_TYPE_2)
typedef DMA_Stream_TypeDef DMAC_T;
#endif


struct SPIInfo {
    const char		*name;
    SPI_TypeDef 	*addr;
    DMAC_T 		*rxdma, *txdma;

    DMA_TypeDef		*dma;
    u_char		dmachan;

    u_char		dmanrx, dmantx;
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


#endif /* __spi_info_h__ */
