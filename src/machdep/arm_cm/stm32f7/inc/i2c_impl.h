/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-27 20:00 (EDT)
  Function: stm32F7 i2c pin config

*/

#ifndef __stm32f7_i2c_impl_h__
#define __stm32f7_i2c_impl_h__

static inline void i2c_pins_init(int i, int altpins){

    int mode = GPIO_AF(4) | GPIO_OPEN_DRAIN | GPIO_SPEED_25MHZ ;
#ifdef I2C_PULLUPS
    mode |= GPIO_PULL_UP;
#endif

    switch(i){
    case 0:
        RCC->APB1ENR   |= 1<<21;
        if( altpins ){
            gpio_init( GPIO_B8, mode );	// cl
            gpio_init( GPIO_B9, mode ); // da
        }else{
            gpio_init( GPIO_B6, mode ); // cl
            gpio_init( GPIO_B7, mode ); // da
        }
        break;
    case 1:
        RCC->APB1ENR   |= 1<<22;
        if( altpins == 2 ){
            gpio_init( GPIO_H4, mode ); // cl
            gpio_init( GPIO_H5, mode ); // da
        }else if( altpins == 1 ){
            gpio_init( GPIO_F1, mode ); // cl
            gpio_init( GPIO_F0, mode ); // da
        }else{
            gpio_init( GPIO_B10, mode ); // cl
            gpio_init( GPIO_B11, mode ); // da
        }
        break;
#ifdef I2C3
    case 2:
        RCC->APB1ENR   |= 1<<23;
        if( altpins ){
            gpio_init( GPIO_H7, mode ); // cl
            gpio_init( GPIO_H8, mode ); // da
        }else{
            gpio_init( GPIO_A8, mode ); // cl
            gpio_init( GPIO_C9, mode ); // da
        }
        break;
#endif
#ifdef I2C4
    case 3:
        RCC->APB1ENR   |= 1<<24;
        switch(altpins){
        case 0:
            gpio_init( GPIO_D12, mode ); // cl
            gpio_init( GPIO_D13, mode ); // da
            break;
        case 1:
            gpio_init( GPIO_F14, mode ); // cl
            gpio_init( GPIO_F15, mode ); // da
            break;
        case 2:
            gpio_init( GPIO_H11, mode ); // cl
            gpio_init( GPIO_H12, mode ); // da
            break;
        }

        break;
#endif
    }
}

#endif /* __stm32f7_i2c_impl_h__ */
