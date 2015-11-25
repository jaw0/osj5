/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-27 20:00 (EDT)
  Function: stm32L1 i2c pin config

*/

#ifndef __stm32l1_i2c_impl_h__
#define __stm32l1_i2c_impl_h__

static inline void i2c_pins_init(int i, int altpins){

    int mode = GPIO_AF(4) | GPIO_OPEN_DRAIN | GPIO_SPEED_HIGH ;
#ifdef I2C_PULLUPS
    mode |= GPIO_PULL_UP;
#endif

    switch(i){
    case 0:
        RCC->APB1ENR   |= 1<<21;
        if( altpins ){
            gpio_init( GPIO_B8, mode );	// cl
            gpio_init( GPIO_B9, mode );	// da
        }else{
            gpio_init( GPIO_B6, mode ); // cl
            gpio_init( GPIO_B7, mode ); // da
        }
        break;
    case 1:
        RCC->APB1ENR   |= 1<<22;
        gpio_init( GPIO_B10, mode );	// cl
        gpio_init( GPIO_B11, mode );	// da
        break;
    }
}

#endif /* __stm32l1_i2c_impl_h__ */
