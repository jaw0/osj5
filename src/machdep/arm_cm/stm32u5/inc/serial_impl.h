/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-27 21:26 (EDT)
  Function: 

*/

#ifndef __stm32u5_serial_impl_h__
#define __stm32u5_serial_impl_h__

#define SERIAL_PUT(addr, ch)	(addr)->TDR = ch
#define SERIAL_GET(addr)	(addr)->RDR
#define SERIAL_STATUS(addr)	(addr)->ISR

#define SERIAL_CR1_EN 	(\
    0x0C 		/* enable rx/tx, no parity, 8 bit, ...*/        \
    | 0x20 	 	/* enable RX irq */ \
    | USART_CR1_FIFOEN \
    | 1)		/* enable */


static inline void
_serial_set_config(USART_TypeDef *addr, int brr, int datab, int stopb, int parity){

    addr->CR1 &= ~1;
    addr->BRR = brr;

    uint32_t cr1 = addr->CR1;
    uint32_t cr2 = addr->CR2;
    cr1 &= ~( USART_CR1_M0 | USART_CR1_M1 | USART_CR1_PCE | USART_CR1_PS );
    cr2 &= ~( USART_CR2_STOP_Msk );

    switch( datab ){
    case 7:   	cr1 |= USART_CR1_M1; break;
    case 9:   	cr1 |= USART_CR1_M0; break;
    case 8:     break;
    }

    switch( parity ){
    case 1:	cr1 |= USART_CR1_PCE | USART_CR1_PS; break;
    case 2:	cr1 |= USART_CR1_PCE; 		     break;
    case 0:     break;
    }

    switch( stopb ){
    case 1:	cr2 |= 1 << USART_CR2_STOP_Pos;	     break;
    case 3:	cr2 |= 3 << USART_CR2_STOP_Pos;	     break;
    case 4:	cr2 |= 2 << USART_CR2_STOP_Pos;	     break;
    case 2:     break;
    }

    addr->CR1 = cr1;
    addr->CR2 = cr2;
    addr->CR1 |= 1;
}

static inline void
_serial_send_brk(USART_TypeDef *addr){
    addr->RQR |= USART_RQR_SBKRQ;
}

static inline void
serial_pins_init(int i, int altpins){

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
        RCC->APB1ENR1 |= 1<<17;
        if( altpins ){
            gpio_init( GPIO_D5, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_D6, GPIO_AF(7) | GPIO_PUSH_PULL );
        }else{
            gpio_init( GPIO_A2, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_A3, GPIO_AF(7) | GPIO_PUSH_PULL );
        }
        break;
    case 2:
        RCC->APB1ENR1 |= 1<<18;
        switch( altpins ){
        case 0:
            gpio_init( GPIO_B10, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_B11, GPIO_AF(7) | GPIO_PUSH_PULL );
            break;
        case 1:
            gpio_init( GPIO_C10, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_C11, GPIO_AF(7) | GPIO_PUSH_PULL );
            break;
        case 2:
            gpio_init( GPIO_C4, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_C5, GPIO_AF(7) | GPIO_PUSH_PULL );
            break;
        case 3:
            gpio_init( GPIO_D8, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_D9, GPIO_AF(7) | GPIO_PUSH_PULL );
            break;
        }
        break;
    case 3:
        RCC->APB1ENR1 |= 1<<19;
        if( altpins ){
            gpio_init( GPIO_C10, GPIO_AF(8) | GPIO_PUSH_PULL );
            gpio_init( GPIO_C11, GPIO_AF(8) | GPIO_PUSH_PULL );
        }else{
            gpio_init( GPIO_A0, GPIO_AF(8) | GPIO_PUSH_PULL );
            gpio_init( GPIO_A1, GPIO_AF(8) | GPIO_PUSH_PULL );
        }
        break;
    case 4:
        RCC->APB1ENR1 |= 1<<20;
        if( altpins ){
            gpio_init( GPIO_C12, GPIO_AF(8) | GPIO_PUSH_PULL );
            gpio_init( GPIO_D2,  GPIO_AF(8) | GPIO_PUSH_PULL );
        }else{
            gpio_init( GPIO_C12, GPIO_AF(8) | GPIO_PUSH_PULL );
            gpio_init( GPIO_D2,  GPIO_AF(8) | GPIO_PUSH_PULL );
        }
        break;
    case 5:
        RCC->APB1ENR1 |= 1<<25;
        switch( altpins ){
        case 0:
            gpio_init( GPIO_C2, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_C3, GPIO_AF(7) | GPIO_PUSH_PULL );
            break;
        case 1:
            gpio_init( GPIO_C8, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_C9, GPIO_AF(7) | GPIO_PUSH_PULL );
            break;
        case 2:
            gpio_init( GPIO_E0, GPIO_AF(7) | GPIO_PUSH_PULL );
            gpio_init( GPIO_E1, GPIO_AF(7) | GPIO_PUSH_PULL );
            break;
        }
        break;

        // LPUART1:
        // A2,3; B10,11; C1,0; G7,8

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
    default:
        return apb1_clock_freq();
    }
}



#endif /* __stm32u5_serial_impl_h__ */

