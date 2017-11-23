/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-27 21:26 (EDT)
  Function: 

*/

#ifndef __stm32l1_serial_impl_h__
#define __stm32l1_serial_impl_h__

#define SERIAL_PUT(addr, ch)	(addr)->DR = ch
#define SERIAL_GET(addr)	(addr)->DR
#define SERIAL_STATUS(addr)	(addr)->SR

#define SERIAL_CR1_EN 	(\
    0x200C 		/* enable rx/tx, no parity, 8 bit, ... */ \
    | 0x20 )	 	/* enable RX irq */


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

static inline void
serial_params(int i, USART_TypeDef**addr, int *irq, int *clock){

    switch(i){
    case 0:
        *addr  = USART1;
        *clock = apb2_clock_freq();
        *irq   = (int) IRQ_USART1;
        break;
    case 1:
        *addr  = USART2;
        *clock = apb1_clock_freq();
        *irq   = (int) IRQ_USART2;
        break;
    case 2:
        *addr  = USART3;
        *clock = apb1_clock_freq();
        *irq   = (int) IRQ_USART3;
        break;
#ifdef UART4
    case 3:
        *addr  = UART4;
        *irq   = (int) IRQ_UART4;
        *clock = apb1_clock_freq();
        break;
#endif
#ifdef UART5
    case 4:
        *addr  = UART5;
        *irq   = (int) IRQ_UART5;
        *clock = apb1_clock_freq();
        break;
#endif
#ifdef USART6
    case 5:
        *addr  = USART6;
        *irq   = (int) IRQ_USART6;
        *clock = apb2_clock_freq();
        break;
#endif
#ifdef UART7
    case 6:
        *addr  = UART7;
        *irq   = (int) IRQ_UART7;
        *clock = apb1_clock_freq();
        break;
#endif
#ifdef UART8
    case 7:
        *addr  = UART8;
        *irq   = (int) IRQ_UART8;
        *clock = apb1_clock_freq();
        break;
#endif

    default:
        PANIC("invalid serial");
        break;

    }
}

#endif /* __stm32l1_serial_impl_h__ */

