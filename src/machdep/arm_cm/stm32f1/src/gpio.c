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

    int plx = splhigh();
    int io  = pin >> 4;

    GPIO_TypeDef *addr = _gpio_addr(pin);
    pin &= 0xF;
    int pos = (pin & 0x7) << 2;

    RCC->APB2ENR |= 1 << (io + 2);

    if( pin >= 8 ){
        addr->CRH &= ~(0xF << pos);
        addr->CRH |= mode << pos;
    }else{
        addr->CRL &= ~(0xF << pos);
        addr->CRL |= mode << pos;
    }

    addr->BSRR = 0x10000 << pin;	// off
    splx(plx);
}

