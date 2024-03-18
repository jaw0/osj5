/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-10 11:04 (EST)
  Function: 

*/
#ifndef __stm32f0_spi_impl_h__
#define __stm32f0_spi_impl_h__

#define DMA_TYPE_1

#include <spi_info.h>

#define SPIGPIO_CONF   (GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ)
#define PUT_DR(dev, c) (dev->DR = c)
#define GET_DR(dev)    (dev->DR)


static inline void
_spi_dev_init(struct Device_Conf *dev, struct SPIInfo *ii){
    SPI_TypeDef *addr;
    int dmairqrx, dmairqtx;

    switch(dev->unit){



    }

    nvic_enable( dmairqrx, IPL_DISK );
    nvic_enable( dmairqtx, IPL_DISK );
}


#endif /* __stm32f0_spi_impl_h__ */
