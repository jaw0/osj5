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


static inline GPIO_TypeDef *
_gpio_addr(int pin){
    switch(pin>>4){
    case 0:	return GPIOA;
    case 1:	return GPIOB;
    case 2:	return GPIOC;
    case 3:	return GPIOD;
    case 4:	return GPIOE;
    default:
        PANIC("invalid gpio");
    }
}


void
gpio_init(int pin, int mode){

    int plx = splhigh();
    int io  = pin >> 4;
    RCC->APB2ENR |= 1 << (io + 2);

    GPIO_TypeDef *addr = _gpio_addr(pin);
    pin &= 0xF;
    int pos = (pin & 0x7) << 2;

    if( pin >= 8 ){
        addr->CRH &= ~(0xF << pos);
        addr->CRH |= mode << pos;
    }else{
        addr->CRL &= ~(0xF << pos);
        addr->CRL |= mode << pos;
    }
    splx(plx);
}

void
gpio_set(int pin){
    _gpio_addr(pin)->BSRR = 1 << (pin&0xF);
}

void
gpio_clear(int pin){
    _gpio_addr(pin)->BSRR = 0x10000 << (pin&0xF);
}

int
gpio_get(int pin){
    return (_gpio_addr(pin)->IDR & (1 << (pin&0xF))) ? 1 : 0;
}



