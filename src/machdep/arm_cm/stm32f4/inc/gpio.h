/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 12:53 (EDT)
  Function: gpio

*/


#ifndef __stm32f4_gpio_h__
#define __stm32f4_gpio_h__

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


#define GPIO_F0         0x50
#define GPIO_F1         0x51
#define GPIO_F2         0x52
#define GPIO_F3         0x53
#define GPIO_F4         0x54
#define GPIO_F5         0x55
#define GPIO_F6         0x56
#define GPIO_F7         0x57
#define GPIO_F8         0x58
#define GPIO_F9         0x59
#define GPIO_F10        0x5a
#define GPIO_F11        0x5b
#define GPIO_F12        0x5c
#define GPIO_F13        0x5d
#define GPIO_F14        0x5e
#define GPIO_F15        0x5f

#define GPIO_G0         0x60
#define GPIO_G1         0x61
#define GPIO_G2         0x62
#define GPIO_G3         0x63
#define GPIO_G4         0x64
#define GPIO_G5         0x65
#define GPIO_G6         0x66
#define GPIO_G7         0x67
#define GPIO_G8         0x68
#define GPIO_G9         0x69
#define GPIO_G10        0x6a
#define GPIO_G11        0x6b
#define GPIO_G12        0x6c
#define GPIO_G13        0x6d
#define GPIO_G14        0x6e
#define GPIO_G15        0x6f

#define GPIO_H0         0x70
#define GPIO_H1         0x71
#define GPIO_H2         0x72
#define GPIO_H3         0x73
#define GPIO_H4         0x74
#define GPIO_H5         0x75
#define GPIO_H6         0x76
#define GPIO_H7         0x77
#define GPIO_H8         0x78
#define GPIO_H9         0x79
#define GPIO_H10        0x7a
#define GPIO_H11        0x7b
#define GPIO_H12        0x7c
#define GPIO_H13        0x7d
#define GPIO_H14        0x7e
#define GPIO_H15        0x7f

#define GPIO_I0         0x80
#define GPIO_I1         0x81
#define GPIO_I2         0x82
#define GPIO_I3         0x83
#define GPIO_I4         0x84
#define GPIO_I5         0x85
#define GPIO_I6         0x86
#define GPIO_I7         0x87
#define GPIO_I8         0x88
#define GPIO_I9         0x89
#define GPIO_I10        0x8a
#define GPIO_I11        0x8b
#define GPIO_I12        0x8c
#define GPIO_I13        0x8d
#define GPIO_I14        0x8e
#define GPIO_I15        0x8f

#define GPIO_J0         0x90
#define GPIO_J1         0x91
#define GPIO_J2         0x92
#define GPIO_J3         0x93
#define GPIO_J4         0x94
#define GPIO_J5         0x95
#define GPIO_J6         0x96
#define GPIO_J7         0x97
#define GPIO_J8         0x98
#define GPIO_J9         0x99
#define GPIO_J10        0x9a
#define GPIO_J11        0x9b
#define GPIO_J12        0x9c
#define GPIO_J13        0x9d
#define GPIO_J14        0x9e
#define GPIO_J15        0x9f


//  (4:af) (1:x) (2:pull up/down) (2:ospeed) (1:push-pull,open-drain) (2:mode)
#define GPIO_INPUT		0
#define GPIO_OUTPUT		1
#define GPIO_AF(n)		(2 | ((n)<<8))
#define GPIO_ANALOG		3

#define GPIO_PUSH_PULL	0
#define GPIO_OPEN_DRAIN	(1<<2)

#define GPIO_SPEED_2MHZ		0
#define GPIO_SPEED_25MHZ	(1<<3)
#define GPIO_SPEED_50MHZ	(2<<3)
#define GPIO_SPEED_100MHZ	(3<<3)

#define GPIO_PULL_UP		(1<<5)
#define GPIO_PULL_DN		(2<<5)


extern void gpio_init(int, int);


static inline GPIO_TypeDef *
_gpio_addr(int pin){
    switch(pin>>4){
    case 0:	return GPIOA;
    case 1:	return GPIOB;
    case 2:	return GPIOC;
    case 3:	return GPIOD;
    case 4:	return GPIOE;
    case 5:	return GPIOF;
#ifdef GPIOG
    case 6:	return GPIOG;
#endif
#ifdef GPIOH
    case 7:	return GPIOH;
#endif
#ifdef GPIOI
    case 8:	return GPIOI;
#endif
#ifdef GPIOJ
    case 9:	return GPIOJ;
#endif
    default:
        // kprintf("invalid gpio pin %X\n", pin);
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

static inline void
gpio_setv(int pin, int v){
    if(v)
        _gpio_addr(pin)->BSRR = 1 << (pin&0xF);
    else
        _gpio_addr(pin)->BSRR = 0x10000 << (pin&0xF);
}


static inline int
gpio_get(int pin){
    return (_gpio_addr(pin)->IDR & (1 << (pin&0xF))) ? 1 : 0;
}


#endif /* __stm32f4_gpio_h__ */
