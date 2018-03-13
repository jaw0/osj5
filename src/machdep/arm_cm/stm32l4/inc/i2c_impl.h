/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-27 20:00 (EDT)
  Function: stm32L4 i2c pin config

*/

#ifndef __stm32l4_i2c_impl_h__
#define __stm32l4_i2c_impl_h__

static inline void i2c_pins_init(int i, int altpins){

    int mode = GPIO_AF(4) | GPIO_OPEN_DRAIN | GPIO_SPEED_HIGH ;
#ifdef I2C_PULLUPS
    mode |= GPIO_PULL_UP;
#endif

    switch(i){
    case 0:
        RCC->APB1ENR1   |= 1<<21;
        switch(altpins){
        case 0:
            gpio_init( GPIO_B6, mode ); // cl
            gpio_init( GPIO_B7, mode ); // da
            break;
        case 1:
            gpio_init( GPIO_B8, mode );	// cl
            gpio_init( GPIO_B9, mode );	// da
            break;
        case 2:
            gpio_init( GPIO_A9, mode ); // cl
            gpio_init( GPIO_A10, mode ); // da
            break;
        case 3:
            gpio_init( GPIO_G14, mode ); // cl
            gpio_init( GPIO_G13, mode ); // da
            break;
        }
        break;
    case 1:
        RCC->APB1ENR1   |= 1<<22;
        switch(altpins){
        case 0:
            gpio_init( GPIO_B10, mode ); // cl
            gpio_init( GPIO_B11, mode ); // da
            break;
        case 1:
            gpio_init( GPIO_B13, mode ); // cl
            gpio_init( GPIO_B14, mode ); // da
            break;
        case 2:
            gpio_init( GPIO_F1, mode ); // cl
            gpio_init( GPIO_F0, mode ); // da
            break;
        case 3:
            gpio_init( GPIO_H4, mode ); // cl
            gpio_init( GPIO_H3, mode ); // da
            break;
        }
        break;

    case 2:
        RCC->APB1ENR1   |= 1<<23;
        switch(altpins){
        case 0:
            gpio_init( GPIO_A7, mode ); // cl
            gpio_init( GPIO_B4, mode ); // da
            break;
        case 1:
            gpio_init( GPIO_C0, mode ); // cl
            gpio_init( GPIO_C1, mode ); // da
            break;
        case 2:
            gpio_init( GPIO_G7, mode ); // cl
            gpio_init( GPIO_G8, mode ); // da
            break;
        case 3:
            gpio_init( GPIO_H7, mode ); // cl
            gpio_init( GPIO_H8, mode ); // da
            break;
        }

    case 3:
        RCC->APB1ENR2   |= 1<<1;
        switch(altpins){
        case 0:
            gpio_init( GPIO_D12, mode ); // cl
            gpio_init( GPIO_D13, mode ); // da
            break;
        case 1:
            gpio_init( GPIO_F14, mode ); // cl
            gpio_init( GPIO_F15, mode ); // da
            break;
        }
    }
}

#endif /* __stm32l4_i2c_impl_h__ */
