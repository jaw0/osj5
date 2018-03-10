/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-10 11:04 (EST)
  Function: 

*/
#ifndef __stm32l1_spi_impl_h__
#define __stm32l1_spi_impl_h__

#define DMA_TYPE_1

#include <spi_info.h>

#define SPIGPIO_CONF 	(GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_25MHZ)

#define PUT_DR(dev, c) (dev->DR = c)
#define GET_DR(dev)    (dev->DR)


static inline void
_spi_dev_init(int unit, struct SPIInfo *ii) {
    SPI_TypeDef *addr;
    int dmairqrx, dmairqtx;

    switch(unit){
    case 0:
        // on ahb2, dma1 chan2+3
        // CLK = A5, MISO = A6, MOSI = A7
        ii->addr      = addr = SPI1;
        ii->irq       = IRQ_SPI1;
        ii->rxdma     = DMA1_Channel2;
        ii->txdma     = DMA1_Channel3;
        ii->dma       = DMA1;
        ii->clock     = APB2CLOCK;
        dmairqrx      = IRQ_DMA1_CHANNEL2;
        dmairqtx      = IRQ_DMA1_CHANNEL3;
        ii->dmanrx    = 2;
        ii->dmantx    = 3;
        RCC->APB2ENR |= 1<<12;	// spi
        RCC->AHBENR  |= 1<<24;	// DMA1
        gpio_init( GPIO_A5, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        gpio_init( GPIO_A6, GPIO_AF(5) | GPIO_PULL_UP );
        gpio_init( GPIO_A7, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        break;
    case 1:
        // on ahb1, dma1 chan 3+4
        // CLK = B13, MISO = B14, MOSI = B15
        ii->addr      = addr = SPI2;
        ii->irq       = IRQ_SPI2;
        ii->rxdma     = DMA1_Channel4;
        ii->txdma     = DMA1_Channel5;
        ii->dma       = DMA1;
        ii->clock     = APB1CLOCK;
        dmairqrx      = IRQ_DMA1_CHANNEL4;
        dmairqtx      = IRQ_DMA1_CHANNEL5;
        ii->dmanrx    = 4;
        ii->dmantx    = 5;
        RCC->APB1ENR |= 1<<14;	// spi
        RCC->AHBENR  |= 1<<24;	// DMA1
        gpio_init( GPIO_B13, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        gpio_init( GPIO_B14, GPIO_AF(5) | GPIO_PULL_UP );
        gpio_init( GPIO_B15, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        break;
    case 2:
        // on ahb1, dma2 chan 1+2
        // CLK = B3, MISO = B4, MOSI = B5
        ii->addr      = addr = SPI3;
        ii->irq       = IRQ_SPI3;
        ii->rxdma     = DMA2_Channel1;
        ii->txdma     = DMA2_Channel2;
        ii->dma       = DMA2;
        ii->clock     = APB1CLOCK;
        dmairqrx      = IRQ_DMA2_CHANNEL1;
        dmairqtx      = IRQ_DMA2_CHANNEL2;
        ii->dmanrx    = 1;
        ii->dmantx    = 2;
        RCC->APB1ENR |= 1<<15;	// spi
        RCC->AHBENR  |= 1<<25;	// DMA2
        gpio_init( GPIO_B3, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        gpio_init( GPIO_B4, GPIO_AF(6) | GPIO_PULL_UP );
        gpio_init( GPIO_B5, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        break;
    default:
        // ...
        PANIC("invalid spi device");
    }

    nvic_enable( dmairqrx, IPL_DISK );
    nvic_enable( dmairqtx, IPL_DISK );
}


#endif /* __stm32l1_spi_impl_h__ */
