/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-10 11:04 (EST)
  Function: 

*/
#ifndef __stm32f1_spi_impl_h__
#define __stm32f1_spi_impl_h__

#define DMA_TYPE_1

#include <spi_info.h>

#define SPIGPIO_CONF 	(GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ)

#define PUT_DR(dev, c) (dev->DR = c)
#define GET_DR(dev)    (dev->DR)


static inline void
_spi_dev_init(struct Device_Conf *dev, struct SPIInfo *ii){
    SPI_TypeDef *addr;
    int dmairqrx, dmairqtx;

    switch(dev->unit){
    case 0:
        // on ahb2, dma1 chan2+3
        // CLK = A5, MISO = A6, MOSI = A7
        ii->addr      = addr = SPI1;
        ii->irq       = IRQ_SPI1;
        ii->dma       = DMA;
        ii->rxdma     = DMA_Channel2;
        ii->txdma     = DMA_Channel3;
        ii->clock     = APB2CLOCK;
        dmairqrx      = IRQ_DMA1_CHANNEL2;
        dmairqtx      = IRQ_DMA1_CHANNEL3;
        ii->dmanrx    = 2;
        ii->dmantx    = 3;
        RCC->APB2ENR |= 1;	// AFI
        RCC->APB2ENR |= 1<<12;	// spi
        gpio_init( GPIO_A5, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
        gpio_init( GPIO_A6, GPIO_INPUT_FLOATING );
        gpio_init( GPIO_A7, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
        break;
    case 1:
        // on ahb1, dma1 chan 4+5
        // CLK = B13, MISO = B14, MOSI = B15
        ii->addr      = addr = SPI2;
        ii->irq       = IRQ_SPI2;
        ii->dma       = DMA;
        ii->rxdma     = DMA_Channel4;
        ii->txdma     = DMA_Channel5;
        ii->clock     = APB1CLOCK;
        dmairqrx      = IRQ_DMA1_CHANNEL4;
        dmairqtx      = IRQ_DMA1_CHANNEL5;
        ii->dmanrx    = 4;
        ii->dmantx    = 5;
        RCC->APB2ENR |= 1;	// AFI
        RCC->APB1ENR |= 1<<14;	// spi
        gpio_init( GPIO_B13, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
        gpio_init( GPIO_B14, GPIO_INPUT_FLOATING );
        gpio_init( GPIO_B15, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
        break;
    default:
        // ...
        PANIC("invalid spi device");

    }

    RCC->AHBENR |= 1;	// DMA1
    nvic_enable( dmairqrx, IPL_DISK );
    nvic_enable( dmairqtx, IPL_DISK );
}


#endif /* __stm32f1_spi_impl_h__ */
