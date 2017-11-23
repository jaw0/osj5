/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-27 21:26 (EDT)
  Function: 

*/

#ifndef __stm32f1_serial_impl_h__
#define __stm32f1_serial_impl_h__


#define SERIAL_PUT(addr, ch)	(addr)->DR = ch
#define SERIAL_GET(addr)	(addr)->DR
#define SERIAL_STATUS(addr)	(addr)->SR

#define SERIAL_CR1_EN 	(\
    0x200C 		/* enable rx/tx, no parity, 8 bit, ... */ \
    | 0x20 )	 	/* enable RX irq */

  
static inline void
serial_pins_init(int i, int altpins){

    switch(i){
    case 0:
        RCC->APB2ENR |= 0x4005;		// usart1+gpioA+afi
        GPIOA->CRH   |= 0x4b0;
        break;
    case 1:
        RCC->APB2ENR |= 0x5;
        RCC->APB1ENR |= 0x20000;
        GPIOA->CRL    = 0x4b00;
        break;
    case 2:
        RCC->APB2ENR |= 0x9;
        RCC->APB1ENR |= 0x40000;
        GPIOB->CRH    = 0x4b00;
        break;

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
    default:
        PANIC("invalid serial");
        break;

    }
}


#endif /* __stm32f1_serial_impl_h__ */

