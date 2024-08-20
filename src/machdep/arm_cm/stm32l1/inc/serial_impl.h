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


static inline void
_serial_set_config(USART_TypeDef *addr, int brr, int datab, int stopb, int parity){

    addr->CR1 &= ~(1 << 13);
    addr->BRR = brr;

    uint32_t cr1 = addr->CR1;
    uint32_t cr2 = addr->CR2;
    cr1 &= ~( USART_CR1_M | USART_CR1_PCE | USART_CR1_PS );
    cr2 &= ~( USART_CR2_STOP_Msk );

    switch( datab ){
    case 9:   	cr1 |= USART_CR1_M; break;
    }

    switch( parity ){
    case 1:	cr1 |= USART_CR1_PCE | USART_CR1_PS; break;
    case 2:	cr1 |= USART_CR1_PCE; 		     break;
    }

    switch( stopb ){
    case 1:	cr2 |= 1 << USART_CR2_STOP_Pos;	     break;
    case 3:	cr2 |= 3 << USART_CR2_STOP_Pos;	     break;
    case 4:	cr2 |= 2 << USART_CR2_STOP_Pos;	     break;
    }

    addr->CR1 = cr1;
    addr->CR2 = cr2;
    addr->CR1 |= (1 << 13);
}

static inline void
_serial_send_brk(USART_TypeDef *addr){
    addr->CR1 |= USART_CR1_SBK;
}

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


static inline int
serial_baudclock(int i){

    switch(i){
    case 0:
        return apb2_clock_freq();
    case 1:
        return apb1_clock_freq();
    case 2:
        return apb1_clock_freq();
    case 3:
        return apb1_clock_freq();
    case 4:
        return apb1_clock_freq();
    case 5:
        return apb2_clock_freq();
    case 6:
        return apb1_clock_freq();
    case 7:
        return apb1_clock_freq();
    case 8:
        return apb1_clock_freq();

    default:
        PANIC("invalid serial");
        break;
    }
}



#endif /* __stm32l1_serial_impl_h__ */

