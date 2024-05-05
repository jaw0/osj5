/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-10 11:04 (EST)
  Function: 

*/
#ifndef __stm32u5_spi_impl_h__
#define __stm32u5_spi_impl_h__

#include <spi2_info.h>

#define SPIGPIO_CONF 	(GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_25MHZ)


static inline void
_spi_dev_init(struct Device_Conf *dev, struct SPIInfo *ii){
    SPI_TypeDef *addr;
    int dmairqrx, dmairqtx;

    switch(dev->unit){

    case 0:
        // on apb2, dma2 chan2+3
        // CLK = A5, MISO = A6, MOSI = A7
        ii->addr      = addr = SPI1;
        ii->irq       = SPI1_IRQn;
        ii->clock     = APB2CLOCK;
        ii->maxtsize  = 65535;
        RCC->APB2ENR |= 1<<12;	// spi

        ii->dmareq.req_rx = 6;
        ii->dmareq.req_tx = 7;


        switch( dev->port ){
        case 0x01:
            gpio_init( GPIO_A1,  GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            gpio_init( GPIO_A11, GPIO_AF(5) | GPIO_PULL_UP );
            gpio_init( GPIO_A12, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            break;
        case 0x13:
            gpio_init( GPIO_B3, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            gpio_init( GPIO_B4, GPIO_AF(5) | GPIO_PULL_UP ); // MISO
            gpio_init( GPIO_B5, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            break;
        case 0x4D:
            // NB - different than the F7 E(12..14)
            gpio_init( GPIO_E13, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            gpio_init( GPIO_E14, GPIO_AF(5) | GPIO_PULL_UP ); // MISO
            gpio_init( GPIO_E15, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            break;
        case 0x05:
        default:
            gpio_init( GPIO_A5, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            gpio_init( GPIO_A6, GPIO_AF(5) | GPIO_PULL_UP ); //MISO
            gpio_init( GPIO_A7, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        }
        break;

    case 1:
        // on ahb1, dma1 chan 3+4
        // CLK = B13, MISO = B14, MOSI = B15
        ii->addr      = addr = SPI2;
        ii->irq       = IRQ_SPI2;
        ii->clock     = APB1CLOCK;
        ii->maxtsize  = 65535;
        RCC->APB1ENR1 |= 1<<14;	// spi

        ii->dmareq.req_rx = 8;
        ii->dmareq.req_tx = 9;

        switch( dev->port ){
        case 0x31:
            gpio_init( GPIO_D1, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            gpio_init( GPIO_D3, GPIO_AF(5) | GPIO_PULL_UP ); // MISO
            gpio_init( GPIO_D4, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            break;
        case 0x81:
            gpio_init( GPIO_I1, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            gpio_init( GPIO_I2, GPIO_AF(5) | GPIO_PULL_UP ); // MISO
            gpio_init( GPIO_I3, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            break;
        case 0x1D:
        default:
            gpio_init( GPIO_B13, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
            gpio_init( GPIO_B14, GPIO_AF(5) | GPIO_PULL_UP ); // MISO
            gpio_init( GPIO_B15, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        }

        break;

    case 2:
        ii->addr      = addr = SPI3;
        ii->irq       = IRQ_SPI3;
        ii->clock     = APB1CLOCK;
        ii->maxtsize  = 1023;
        RCC->APB3ENR |= 1<<5;	// spi

        ii->dmareq.req_rx = 10;
        ii->dmareq.req_tx = 11;


        gpio_init( GPIO_G9,  GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        gpio_init( GPIO_G10, GPIO_AF(6) | GPIO_PULL_UP ); // MISO
        gpio_init( GPIO_G11, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        break;


    }

}


#endif /* __stm32u5_spi_impl_h__ */
