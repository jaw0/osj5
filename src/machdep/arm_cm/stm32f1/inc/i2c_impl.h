/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-27 20:00 (EDT)
  Function: stm32F1 i2c pin config

*/

#ifndef __stm32f1_i2c_impl_h__
#define __stm32f1_i2c_impl_h__

static inline void i2c_pins_init(int i, int altpins){

    switch(i){
    case 0:
        RCC->APB2ENR |= 1;		// AFI
        RCC->APB1ENR |= 0x200000;	// i2c1
        gpio_init( GPIO_B6, GPIO_AF_OUTPUT_OD | GPIO_OUTPUT_10MHZ );	// cl
        gpio_init( GPIO_B7, GPIO_AF_OUTPUT_OD | GPIO_OUTPUT_10MHZ );	// da
        break;
    case 1:
        RCC->APB2ENR |= 1;		// AFI
        RCC->APB1ENR |= 0x400000;	// i2c2
        gpio_init( GPIO_B10, GPIO_AF_OUTPUT_OD | GPIO_OUTPUT_10MHZ );	// cl
        gpio_init( GPIO_B11, GPIO_AF_OUTPUT_OD | GPIO_OUTPUT_10MHZ );	// da

        break;
    }
}

#endif /* __stm32f1_i2c_impl_h__ */
