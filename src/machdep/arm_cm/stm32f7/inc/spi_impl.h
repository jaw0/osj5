/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-10 11:04 (EST)
  Function: 

*/
#ifndef __stm32f7_spi_impl_h__
#define __stm32f7_spi_impl_h__

#define DMA_TYPE_2

#include <spi_info.h>

#define SPIGPIO_CONF 	(GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_25MHZ)
#define CR2_FRXTH_8BIT	(1<<12)
#define CR2_DS_8BIT	(7<<8)

#define PUT_DR(dev, c) (*(char*)&(dev->DR) = c)
#define GET_DR(dev)    (*(char*)&(dev->DR))


static inline void
_spi_dev_init(int unit, struct SPIInfo *ii){
    SPI_TypeDef *addr;
    int dmairqrx, dmairqtx;

    switch(unit){
    case 0:
        // on ahb2, dma2 chan2+3
        // CLK = A5, MISO = A6, MOSI = A7
        ii->addr      = addr = SPI1;
        ii->irq       = IRQ_SPI1;
        ii->rxdma     = DMA2_Stream2;
        ii->txdma     = DMA2_Stream3;
        ii->dma	      = DMA2;
        ii->clock     = APB2CLOCK;
        dmairqrx      = IRQ_DMA2_STREAM2;
        dmairqtx      = IRQ_DMA2_STREAM3;
        ii->dmanrx    = 2;
        ii->dmantx    = 3;
        ii->dmachan   = 3;
        RCC->APB2ENR |= 1<<12;	// spi
        RCC->AHB1ENR |= 1<<22;	// DMA2
        gpio_init( GPIO_A5, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        gpio_init( GPIO_A6, GPIO_AF(5) | GPIO_PULL_UP );
        gpio_init( GPIO_A7, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        break;
    case 1:
        // on ahb1, dma1 chan 3+4
        // CLK = B13, MISO = B14, MOSI = B15
        ii->addr      = addr = SPI2;
        ii->irq       = IRQ_SPI2;
        ii->rxdma     = DMA1_Stream3;
        ii->txdma     = DMA1_Stream4;
        ii->dma	      = DMA1;
        ii->clock     = APB1CLOCK;
        dmairqrx      = IRQ_DMA1_STREAM3;
        dmairqtx      = IRQ_DMA1_STREAM4;
        ii->dmanrx    = 3;
        ii->dmantx    = 4;
        ii->dmachan   = 0;
        RCC->APB1ENR |= 1<<14;	// spi
        RCC->AHB1ENR |= 1<<21;	// DMA1
        gpio_init( GPIO_B13, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        gpio_init( GPIO_B14, GPIO_AF(5) | GPIO_PULL_UP );
        gpio_init( GPIO_B15, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        break;
    case 2:
        // on ahb1, dma1 chan 2+5
        // CLK = B3, MISO = B4, MOSI = B5
        ii->addr      = addr = SPI3;
        ii->irq       = IRQ_SPI3;
        ii->rxdma     = DMA1_Stream2;
        ii->txdma     = DMA1_Stream5;
        ii->dma	      = DMA1;
        ii->clock     = APB2CLOCK;
        dmairqrx      = IRQ_DMA1_STREAM2;
        dmairqtx      = IRQ_DMA1_STREAM5;
        ii->dmanrx    = 2;
        ii->dmantx    = 5;
        ii->dmachan   = 0;
        RCC->APB1ENR |= 1<<15;	// spi
        RCC->AHB1ENR |= 1<<21;	// DMA1
        gpio_init( GPIO_B3, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        gpio_init( GPIO_B4, GPIO_AF(6) | GPIO_PULL_UP );
        gpio_init( GPIO_B5, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        break;

    case 3:
        // on ahb2, dma2 chan2+3
        // CLK = E12, MISO = E13, MOSI = E14
        ii->addr      = addr = SPI4;
        ii->irq       = SPI4_IRQn;
        ii->rxdma     = DMA2_Stream0;
        ii->txdma     = DMA2_Stream1;
        ii->dma	      = DMA2;
        ii->clock     = APB2CLOCK;
        dmairqrx      = IRQ_DMA2_STREAM0;
        dmairqtx      = IRQ_DMA2_STREAM1;
        ii->dmanrx    = 0;
        ii->dmantx    = 1;
        ii->dmachan   = 4;
        RCC->APB2ENR |= 1<<13;	// spi
        RCC->AHB1ENR |= 1<<22;	// DMA2
        gpio_init( GPIO_E12, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        gpio_init( GPIO_E13, GPIO_AF(5) | GPIO_PULL_UP );
        gpio_init( GPIO_E14, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        break;
 
    default:
        bootmsg("invalid spi%d\n", unit);
        PANIC("invalid spi");
    }

    addr->CR2 &= ~0xE7;
    addr->CR2 |= CR2_FRXTH_8BIT | CR2_DS_8BIT;

    nvic_enable( dmairqrx, IPL_DISK );
    nvic_enable( dmairqtx, IPL_DISK );

}


#endif /* __stm32f7_spi_impl_h__ */
