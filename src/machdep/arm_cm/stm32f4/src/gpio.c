/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 12:10 (EDT)
  Function: gpio pins

*/

#include <conf.h>
#include <arch.h>
#include <error.h>
#include <clock.h>
#include <proc.h>
#include <gpio.h>
#include <stm32.h>


void
gpio_init(int pin, int mode){

    GPIO_TypeDef *addr = _gpio_addr(pin);
    if( !addr ) return;

    int plx = splhigh();
    int io  = pin >> 4;

    pin &= 0xF;
    int pos = (pin & 0x7) << 2;

#if defined(PLATFORM_STM32F4) || defined(PLATFORM_STM32F7)
    RCC->AHB1ENR |= 1 << io;
#elif defined(PLATFORM_STM32F0)
    RCC->AHBENR |= 1 << (io + 17);
#elif defined(PLATFORM_STM32L4) || defined(PLATFORM_STM32L4PLUS)
    RCC->AHB2ENR |= 1 << io;
#elif defined(PLATFORM_STM32U5)
    RCC->AHB2ENR1 |= 1 << io;

#elif defined(PLATFORM_STM32L1)

    // F,G,H are mixed-up on the L1
    switch( io ){
    case 5:	RCC->AHBENR  |= 1 << 6;	break;
    case 6:	RCC->AHBENR  |= 1 << 7;	break;
    case 7:	RCC->AHBENR  |= 1 << 5;	break;
    default:
        RCC->AHBENR  |= 1 << io;
        break;
    }
#else
#  error "unknown platform"
#endif

    addr->MODER   &= ~( 3 << (pin*2) );
    addr->PUPDR   &= ~( 3 << (pin*2) );
    addr->OSPEEDR &= ~( 3 << (pin*2) );

    addr->MODER   |= (mode&3) << (pin*2);
    addr->PUPDR   |= ((mode>>5) & 3) << (pin*2);
    addr->OSPEEDR |= ((mode>>3) & 3) << (pin*2);

    addr->OTYPER  &= ~( 1<<pin );
    addr->OTYPER  |= ((mode>>2) & 1) << pin;

    if( pin >= 8 ){
        addr->AFRH &= ~(0xF << pos);
        addr->AFRH |= ((mode>>8) & 0xF) << pos;
    }else{
        addr->AFRL &= ~(0xF << pos);
        addr->AFRL |= ((mode>>8) & 0xF) << pos;
    }

    addr->BSRR = 0x10000 << pin;	// off
    splx(plx);
}

