/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 12:53 (EDT)
  Function: gpio

*/


#ifndef __gpio_h__
#define __gpio_h__

#include <stm32.h>

#define GPIO_A0         0x00
#define GPIO_A1         0x01
#define GPIO_A2         0x02
#define GPIO_A3         0x03
#define GPIO_A4         0x04
#define GPIO_A5         0x05
#define GPIO_A6         0x06
#define GPIO_A7         0x07
#define GPIO_A8         0x08
#define GPIO_A9         0x09
#define GPIO_A10        0x0a
#define GPIO_A11        0x0b
#define GPIO_A12        0x0c
#define GPIO_A13        0x0d
#define GPIO_A14        0x0e
#define GPIO_A15        0x0f

#define GPIO_B0         0x10
#define GPIO_B1         0x11
#define GPIO_B2         0x12
#define GPIO_B3         0x13
#define GPIO_B4         0x14
#define GPIO_B5         0x15
#define GPIO_B6         0x16
#define GPIO_B7         0x17
#define GPIO_B8         0x18
#define GPIO_B9         0x19
#define GPIO_B10        0x1a
#define GPIO_B11        0x1b
#define GPIO_B12        0x1c
#define GPIO_B13        0x1d
#define GPIO_B14        0x1e
#define GPIO_B15        0x1f

#define GPIO_C0         0x20
#define GPIO_C1         0x21
#define GPIO_C2         0x22
#define GPIO_C3         0x23
#define GPIO_C4         0x24
#define GPIO_C5         0x25
#define GPIO_C6         0x26
#define GPIO_C7         0x27
#define GPIO_C8         0x28
#define GPIO_C9         0x29
#define GPIO_C10        0x2a
#define GPIO_C11        0x2b
#define GPIO_C12        0x2c
#define GPIO_C13        0x2d
#define GPIO_C14        0x2e
#define GPIO_C15        0x2f

#define GPIO_D0         0x30
#define GPIO_D1         0x31
#define GPIO_D2         0x32
#define GPIO_D3         0x33
#define GPIO_D4         0x34
#define GPIO_D5         0x35
#define GPIO_D6         0x36
#define GPIO_D7         0x37
#define GPIO_D8         0x38
#define GPIO_D9         0x39
#define GPIO_D10        0x3a
#define GPIO_D11        0x3b
#define GPIO_D12        0x3c
#define GPIO_D13        0x3d
#define GPIO_D14        0x3e
#define GPIO_D15        0x3f

#define GPIO_E0         0x40
#define GPIO_E1         0x41
#define GPIO_E2         0x42
#define GPIO_E3         0x43
#define GPIO_E4         0x44
#define GPIO_E5         0x45
#define GPIO_E6         0x46
#define GPIO_E7         0x47
#define GPIO_E8         0x48
#define GPIO_E9         0x49
#define GPIO_E10        0x4a
#define GPIO_E11        0x4b
#define GPIO_E12        0x4c
#define GPIO_E13        0x4d
#define GPIO_E14        0x4e
#define GPIO_E15        0x4f


#if defined(PLATFORM_STM32F1)
#  define GPIO_INPUT_ANALOG       (0x0 << 2)
#  define GPIO_INPUT_FLOATING     (0x1 << 2)
#  define GPIO_INPUT_PU_PD        (0x2 << 2)
#  define GPIO_OUTPUT_PP          (0x0 << 2)
#  define GPIO_OUTPUT_OD          (0x1 << 2)
#  define GPIO_AF_OUTPUT_PP       (0x2 << 2)
#  define GPIO_AF_OUTPUT_OD       (0x3 << 2)
#  define GPIO_INPUT              0x0
#  define GPIO_OUTPUT_10MHZ       0x1
#  define GPIO_OUTPUT_2MHZ        0x2
#  define GPIO_OUTPUT_50MHZ       0x3

#elif defined(PLATFORM_STM32F4)
//  (4:af) (1:x) (2:pull up/down) (2:ospeed) (1:push-pull,open-drain) (2:mode)
#  define GPIO_INPUT		0
#  define GPIO_OUTPUT		1
#  define GPIO_AF(n)		(2 | ((n)<<8))
#  define GPIO_ANALOG		3

#  define GPIO_PUSH_PULL	0
#  define GPIO_OPEN_DRAIN	(1<<2)

#  define GPIO_SPEED_2MHZ	0
#  define GPIO_SPEED_25MHZ	(1<<3)
#  define GPIO_SPEED_50MHZ	(2<<3)
#  define GPIO_SPEED_10MHZ	(3<<3)

#  define GPIO_PULL_UP		(1<<5)
#  define GPIO_PULL_DN		(2<<5)

#endif


extern void gpio_init(int, int);


static inline GPIO_TypeDef *
_gpio_addr(int pin){
    switch(pin>>4){
    case 0:	return GPIOA;
    case 1:	return GPIOB;
    case 2:	return GPIOC;
    case 3:	return GPIOD;
    case 4:	return GPIOE;
    default:
        return 0;
    }
}

static inline void
gpio_set(int pin){
    _gpio_addr(pin)->BSRR = 1 << (pin&0xF);
}

static inline void
gpio_clear(int pin){
    _gpio_addr(pin)->BSRR = 0x10000 << (pin&0xF);
}

static inline int
gpio_get(int pin){
    return (_gpio_addr(pin)->IDR & (1 << (pin&0xF))) ? 1 : 0;
}


#endif /* __gpio_h__ */
