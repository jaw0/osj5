/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-27 21:26 (EDT)
  Function: 

*/

#ifndef __stm32f4_serial_impl_h__
#define __stm32f4_serial_impl_h__

static inline void serial_pins_init(int i, int altpins){

    switch(i){
    case 0:
        RCC->APB2ENR |= 1<<4;
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
        if( altpins == 2 ){
            gpio_init( GPIO_D8, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_D9, GPIO_AF(7) | GPIO_PUSH_PULL );
        } else if( altpins == 1 ){
            gpio_init( GPIO_C10, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_C11, GPIO_AF(7) | GPIO_PUSH_PULL );
        }else{
            gpio_init( GPIO_B10, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_B11, GPIO_AF(7) | GPIO_PUSH_PULL );
        }
        break;
    case 3:
        RCC->APB1ENR |= 1<<19;
        if( altpins ){
            gpio_init( GPIO_A0, GPIO_AF(8) | GPIO_PUSH_PULL );
            gpio_init( GPIO_A1, GPIO_AF(8) | GPIO_PUSH_PULL );
        }else{
            gpio_init( GPIO_C10, GPIO_AF(8) | GPIO_PUSH_PULL );
            gpio_init( GPIO_C11, GPIO_AF(8) | GPIO_PUSH_PULL );
        }
        break;

    case 4:
        RCC->APB1ENR |= 1<<20;
        gpio_init( GPIO_C12, GPIO_AF(8) | GPIO_PUSH_PULL );
        gpio_init( GPIO_D2,  GPIO_AF(8) | GPIO_PUSH_PULL );
        break;
    case 5:
        RCC->APB2ENR |= 1<<5;
        if( altpins ){
            gpio_init( GPIO_C6, GPIO_AF(8) | GPIO_PUSH_PULL );
            gpio_init( GPIO_C7, GPIO_AF(8) | GPIO_PUSH_PULL );
        }else{
            gpio_init( GPIO_G9,  GPIO_AF(8) | GPIO_PUSH_PULL );
            gpio_init( GPIO_G14, GPIO_AF(8) | GPIO_PUSH_PULL );
        }
        break;

        // on the F4[23]X
    case 6:
        RCC->APB1ENR |= 1<<30;
        if( altpins ){
            gpio_init( GPIO_F6, GPIO_AF(8) | GPIO_PUSH_PULL );
            gpio_init( GPIO_F7, GPIO_AF(8) | GPIO_PUSH_PULL );
        }else{
            gpio_init( GPIO_E7, GPIO_AF(8) | GPIO_PUSH_PULL );
            gpio_init( GPIO_E8, GPIO_AF(8) | GPIO_PUSH_PULL );
        }
        break;

    case 7:
        RCC->APB1ENR |= 1<<31;
        gpio_init( GPIO_E0, GPIO_AF(8) | GPIO_PUSH_PULL );
        gpio_init( GPIO_E1, GPIO_AF(8) | GPIO_PUSH_PULL );
        break;

    default:
        PANIC("invalid serial");
        break;
    }
}

#endif /* __stm32f4_serial_impl_h__ */

