/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-27 21:26 (EDT)
  Function: 

*/

#ifndef __stm32l1_serial_impl_h__
#define __stm32l1_serial_impl_h__

static inline void serial_pins_init(int i, int altpins){

    switch(i){
    case 0:
        RCC->APB2ENR |= 1<<14;
        if( altpins ){
            gpio_init( GPIO_B6, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_B7, GPIO_AF(7) | GPIO_PUSH_PULL );
        }else{
            gpio_init( GPIO_A9,  GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_A10, GPIO_AF(7) | GPIO_PUSH_PULL );
        }
        break;
    case 1:
        RCC->APB1ENR |= 1<<17;
        if( altpins ){
            gpio_init( GPIO_D5, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_D6, GPIO_AF(7) | GPIO_PUSH_PULL );
        }else{
            gpio_init( GPIO_A2, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_A3, GPIO_AF(7) | GPIO_PUSH_PULL );
        }
        break;
    case 2:
        RCC->APB1ENR |= 1<<18;
        if( altpins ){
            gpio_init( GPIO_C10, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_C11, GPIO_AF(7) | GPIO_PUSH_PULL );
        }else{
            gpio_init( GPIO_B10, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_B11, GPIO_AF(7) | GPIO_PUSH_PULL );
        }
        // alt: d8, d9
        break;
#if 0
    case 3:
        RCC->APB1ENR |= 1<<19;
        break;
    case 4:
        RCC->APB1ENR |= 1<<20;
        break;
#endif
    default:
        PANIC("invalid serial");
        break;
    }
}

#endif /* __stm32l1_serial_impl_h__ */

