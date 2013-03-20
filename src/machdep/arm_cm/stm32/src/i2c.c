/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-19 16:48 (EDT)
  Function: 
 
  $Id$

*/
#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <dev.h>
#include <error.h>
#include <clock.h>

/* NB: stm32f1 + f4 are compat, but at different addrs */
#include <stm32.h>

#define APB1CLOCK	36000000

#define CR1_START	0x10
#define CR1_STOP	0x20
#define CR1_ACK		0x40

#define SR1_SB		1
#define SR1_ADDR	2
#define SR1_BTF		4
#define SR1_RXNE	0x40
#define SR1_TXE		0x80


struct I2CInfo {
    I2C_TypeDef * addr;
    int 	  irq;
} i2cinfo[ N_I2C ];


int
i2c_init(struct Device_Conf *dev){
    int i    = dev->unit;
    I2C_TypeDef *addr;

    switch(i){
    case 0:
        // CL=B6, DA=B7
        i2cinfo[i].addr = addr = I2C1;
        i2cinfo[i].irq  = IRQ_I2C1_EV;

        RCC->APB2ENR |= 9;		// gpioB + AFI
        RCC->APB1ENR |= 0x200000;	// i2c1
        GPIOB->CRL   |= 0xFF000000;	// open-drain, AFI, 50MHz

        break;
    case 1:
        // CL=B10, DA=B11
        i2cinfo[i].addr = addr = I2C2;
        i2cinfo[i].irq  = IRQ_I2C2_EV;

        RCC->APB2ENR |= 9;		// gpioB + AFI
        RCC->APB1ENR |= 0x400000;	// i2c2
        GPIOB->CRH   |= 0xFF00;		// open-drain, AFI, 50MHz

        break;
    case 2:
        // 3rd on F4
    default:
        PANIC("invalid i2c device");
    }

    int speed = dev->baud;
    if( !speed ) speed = 100000;

    addr->CR2  |= APB1CLOCK/1000000;		// apb1 clock freq?
    addr->TRISE = APB1CLOCK/1000000 + 1;	// 1usec rise
    addr->CCR   = APB1CLOCK/speed/2;		// std mode

    addr->CR1 |= 1;	// enable

    bootmsg("%s at io 0x%x irq %d speed %dkHz\n", dev->name, i2cinfo[i].addr, i2cinfo[i].irq, speed);
    return 0;
}


int
_i2c_start(I2C_TypeDef *dev, int slave){

    // is it ready?

    dev->CR1 |= CR1_START;
    while(1){
        if( dev->SR1 & SR1_SB ) break;
    }
    dev->DR = slave;
    return 1;
}

inline int
_i2c_addr_wait(I2C_TypeDef *dev){

    while(1){
        if( dev->SR1 & SR1_ADDR ) break;
    }
    int tmp = dev->SR2;
    return 1;
}

inline int
_i2c_tx_wait(I2C_TypeDef *dev){

    while(1){
        if( dev->SR1 & SR1_TXE ) break;
    }
    return 1;
}

inline int
_i2c_rx_wait(I2C_TypeDef *dev){

    while(1){
        if( dev->SR1 & SR1_RXNE ) break;
    }
    return 1;
}

int
_i2c_stop(I2C_TypeDef *dev){

    while(1){
        if( dev->SR1 & SR1_BTF ) break;
    }
    dev->CR1 |= CR1_STOP;
}

int
_i2c_put(I2C_TypeDef *dev, int data){
    dev->DR = data;
    return 1;
}

int
_i2c_get(I2C_TypeDef *dev){
    return dev->DR;
}

/****************************************************************/

int
i2c_write(int unit, int addr, int len, char *data){
    I2C_TypeDef *dev = i2cinfo[unit].addr;
    int i = 0;

    _i2c_start(dev, addr);

    while(len --){
        if( i ) _i2c_tx_wait(dev);
        else{
            _i2c_addr_wait(dev);
            i = 1;
        }
        _i2c_put(dev, *data ++);
    }
    _i2c_stop(dev);

    return 1;
}

int
i2c_write2(int unit, int addr, int data){
    I2C_TypeDef *dev = i2cinfo[unit].addr;

    _i2c_start(dev, addr);
    _i2c_addr_wait(dev);
    _i2c_put(dev, addr);
    _i2c_tx_wait(dev);
    _i2c_put(dev, data);
    _i2c_stop(dev);

    return 1;
}

#if 0
i2c_read(dev, dev, data*, len){
}

i2c_read2(dev, dev, reg, *data){
}


#endif
