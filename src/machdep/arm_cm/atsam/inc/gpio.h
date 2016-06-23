/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 12:53 (EDT)
  Function: gpio

*/


#ifndef __atsam_gpio_h__
#define __atsam_gpio_h__

#include <atsam.h>

#define __GPIO_PORT_PIN(PORT,PIN)	((PORT<<5) |PIN)

#define GPIO_A0         __GPIO_PORT_PIN(0,  0)
#define GPIO_A1         __GPIO_PORT_PIN(0,  1)
#define GPIO_A2         __GPIO_PORT_PIN(0,  2)
#define GPIO_A3         __GPIO_PORT_PIN(0,  3)
#define GPIO_A4         __GPIO_PORT_PIN(0,  4)
#define GPIO_A5         __GPIO_PORT_PIN(0,  5)
#define GPIO_A6         __GPIO_PORT_PIN(0,  6)
#define GPIO_A7         __GPIO_PORT_PIN(0,  7)
#define GPIO_A8         __GPIO_PORT_PIN(0,  8)
#define GPIO_A9         __GPIO_PORT_PIN(0,  9)
#define GPIO_A10        __GPIO_PORT_PIN(0,  10)
#define GPIO_A11        __GPIO_PORT_PIN(0,  11)
#define GPIO_A12        __GPIO_PORT_PIN(0,  12)
#define GPIO_A13        __GPIO_PORT_PIN(0,  13)
#define GPIO_A14        __GPIO_PORT_PIN(0,  14)
#define GPIO_A15        __GPIO_PORT_PIN(0,  15)
#define GPIO_A16        __GPIO_PORT_PIN(0,  16)
#define GPIO_A17        __GPIO_PORT_PIN(0,  17)
#define GPIO_A18        __GPIO_PORT_PIN(0,  18)
#define GPIO_A19        __GPIO_PORT_PIN(0,  19)
#define GPIO_A20        __GPIO_PORT_PIN(0,  20)
#define GPIO_A21        __GPIO_PORT_PIN(0,  21)
#define GPIO_A22        __GPIO_PORT_PIN(0,  22)
#define GPIO_A23        __GPIO_PORT_PIN(0,  23)
#define GPIO_A24        __GPIO_PORT_PIN(0,  24)
#define GPIO_A25        __GPIO_PORT_PIN(0,  25)
#define GPIO_A26        __GPIO_PORT_PIN(0,  26)
#define GPIO_A27        __GPIO_PORT_PIN(0,  27)
#define GPIO_A28        __GPIO_PORT_PIN(0,  28)
#define GPIO_A29        __GPIO_PORT_PIN(0,  29)
#define GPIO_A30        __GPIO_PORT_PIN(0,  30)
#define GPIO_A31        __GPIO_PORT_PIN(0,  31)

#define GPIO_B0         __GPIO_PORT_PIN(1,  0)
#define GPIO_B1         __GPIO_PORT_PIN(1,  1)
#define GPIO_B2         __GPIO_PORT_PIN(1,  2)
#define GPIO_B3         __GPIO_PORT_PIN(1,  3)
#define GPIO_B4         __GPIO_PORT_PIN(1,  4)
#define GPIO_B5         __GPIO_PORT_PIN(1,  5)
#define GPIO_B6         __GPIO_PORT_PIN(1,  6)
#define GPIO_B7         __GPIO_PORT_PIN(1,  7)
#define GPIO_B8         __GPIO_PORT_PIN(1,  8)
#define GPIO_B9         __GPIO_PORT_PIN(1,  9)
#define GPIO_B10        __GPIO_PORT_PIN(1,  10)
#define GPIO_B11        __GPIO_PORT_PIN(1,  11)
#define GPIO_B12        __GPIO_PORT_PIN(1,  12)
#define GPIO_B13        __GPIO_PORT_PIN(1,  13)
#define GPIO_B14        __GPIO_PORT_PIN(1,  14)
#define GPIO_B15        __GPIO_PORT_PIN(1,  15)
#define GPIO_B16        __GPIO_PORT_PIN(1,  16)
#define GPIO_B17        __GPIO_PORT_PIN(1,  17)
#define GPIO_B18        __GPIO_PORT_PIN(1,  18)
#define GPIO_B19        __GPIO_PORT_PIN(1,  19)
#define GPIO_B20        __GPIO_PORT_PIN(1,  20)
#define GPIO_B21        __GPIO_PORT_PIN(1,  21)
#define GPIO_B22        __GPIO_PORT_PIN(1,  22)
#define GPIO_B23        __GPIO_PORT_PIN(1,  23)
#define GPIO_B24        __GPIO_PORT_PIN(1,  24)
#define GPIO_B25        __GPIO_PORT_PIN(1,  25)
#define GPIO_B26        __GPIO_PORT_PIN(1,  26)
#define GPIO_B27        __GPIO_PORT_PIN(1,  27)
#define GPIO_B28        __GPIO_PORT_PIN(1,  28)
#define GPIO_B29        __GPIO_PORT_PIN(1,  29)
#define GPIO_B30        __GPIO_PORT_PIN(1,  30)
#define GPIO_B31        __GPIO_PORT_PIN(1,  31)

#define GPIO_C0         __GPIO_PORT_PIN(2,  0)
#define GPIO_C1         __GPIO_PORT_PIN(2,  1)
#define GPIO_C2         __GPIO_PORT_PIN(2,  2)
#define GPIO_C3         __GPIO_PORT_PIN(2,  3)
#define GPIO_C4         __GPIO_PORT_PIN(2,  4)
#define GPIO_C5         __GPIO_PORT_PIN(2,  5)
#define GPIO_C6         __GPIO_PORT_PIN(2,  6)
#define GPIO_C7         __GPIO_PORT_PIN(2,  7)
#define GPIO_C8         __GPIO_PORT_PIN(2,  8)
#define GPIO_C9         __GPIO_PORT_PIN(2,  9)
#define GPIO_C10        __GPIO_PORT_PIN(2,  10)
#define GPIO_C11        __GPIO_PORT_PIN(2,  11)
#define GPIO_C12        __GPIO_PORT_PIN(2,  12)
#define GPIO_C13        __GPIO_PORT_PIN(2,  13)
#define GPIO_C14        __GPIO_PORT_PIN(2,  14)
#define GPIO_C15        __GPIO_PORT_PIN(2,  15)
#define GPIO_C16        __GPIO_PORT_PIN(2,  16)
#define GPIO_C17        __GPIO_PORT_PIN(2,  17)
#define GPIO_C18        __GPIO_PORT_PIN(2,  18)
#define GPIO_C19        __GPIO_PORT_PIN(2,  19)
#define GPIO_C20        __GPIO_PORT_PIN(2,  20)
#define GPIO_C21        __GPIO_PORT_PIN(2,  21)
#define GPIO_C22        __GPIO_PORT_PIN(2,  22)
#define GPIO_C23        __GPIO_PORT_PIN(2,  23)
#define GPIO_C24        __GPIO_PORT_PIN(2,  24)
#define GPIO_C25        __GPIO_PORT_PIN(2,  25)
#define GPIO_C26        __GPIO_PORT_PIN(2,  26)
#define GPIO_C27        __GPIO_PORT_PIN(2,  27)
#define GPIO_C28        __GPIO_PORT_PIN(2,  28)
#define GPIO_C29        __GPIO_PORT_PIN(2,  29)
#define GPIO_C30        __GPIO_PORT_PIN(2,  30)
#define GPIO_C31        __GPIO_PORT_PIN(2,  31)

#define GPIO_D0         __GPIO_PORT_PIN(3,  0)
#define GPIO_D1         __GPIO_PORT_PIN(3,  1)
#define GPIO_D2         __GPIO_PORT_PIN(3,  2)
#define GPIO_D3         __GPIO_PORT_PIN(3,  3)
#define GPIO_D4         __GPIO_PORT_PIN(3,  4)
#define GPIO_D5         __GPIO_PORT_PIN(3,  5)
#define GPIO_D6         __GPIO_PORT_PIN(3,  6)
#define GPIO_D7         __GPIO_PORT_PIN(3,  7)
#define GPIO_D8         __GPIO_PORT_PIN(3,  8)
#define GPIO_D9         __GPIO_PORT_PIN(3,  9)
#define GPIO_D10        __GPIO_PORT_PIN(3,  10)
#define GPIO_D11        __GPIO_PORT_PIN(3,  11)
#define GPIO_D12        __GPIO_PORT_PIN(3,  12)
#define GPIO_D13        __GPIO_PORT_PIN(3,  13)
#define GPIO_D14        __GPIO_PORT_PIN(3,  14)
#define GPIO_D15        __GPIO_PORT_PIN(3,  15)
#define GPIO_D16        __GPIO_PORT_PIN(3,  16)
#define GPIO_D17        __GPIO_PORT_PIN(3,  17)
#define GPIO_D18        __GPIO_PORT_PIN(3,  18)
#define GPIO_D19        __GPIO_PORT_PIN(3,  19)
#define GPIO_D20        __GPIO_PORT_PIN(3,  20)
#define GPIO_D21        __GPIO_PORT_PIN(3,  21)
#define GPIO_D22        __GPIO_PORT_PIN(3,  22)
#define GPIO_D23        __GPIO_PORT_PIN(3,  23)
#define GPIO_D24        __GPIO_PORT_PIN(3,  24)
#define GPIO_D25        __GPIO_PORT_PIN(3,  25)
#define GPIO_D26        __GPIO_PORT_PIN(3,  26)
#define GPIO_D27        __GPIO_PORT_PIN(3,  27)
#define GPIO_D28        __GPIO_PORT_PIN(3,  28)
#define GPIO_D29        __GPIO_PORT_PIN(3,  29)
#define GPIO_D30        __GPIO_PORT_PIN(3,  30)
#define GPIO_D31        __GPIO_PORT_PIN(3,  31)

#define GPIO_E0         __GPIO_PORT_PIN(4,  0)
#define GPIO_E1         __GPIO_PORT_PIN(4,  1)
#define GPIO_E2         __GPIO_PORT_PIN(4,  2)
#define GPIO_E3         __GPIO_PORT_PIN(4,  3)
#define GPIO_E4         __GPIO_PORT_PIN(4,  4)
#define GPIO_E5         __GPIO_PORT_PIN(4,  5)
#define GPIO_E6         __GPIO_PORT_PIN(4,  6)
#define GPIO_E7         __GPIO_PORT_PIN(4,  7)
#define GPIO_E8         __GPIO_PORT_PIN(4,  8)
#define GPIO_E9         __GPIO_PORT_PIN(4,  9)
#define GPIO_E10        __GPIO_PORT_PIN(4,  10)
#define GPIO_E11        __GPIO_PORT_PIN(4,  11)
#define GPIO_E12        __GPIO_PORT_PIN(4,  12)
#define GPIO_E13        __GPIO_PORT_PIN(4,  13)
#define GPIO_E14        __GPIO_PORT_PIN(4,  14)
#define GPIO_E15        __GPIO_PORT_PIN(4,  15)
#define GPIO_E16        __GPIO_PORT_PIN(4,  16)
#define GPIO_E17        __GPIO_PORT_PIN(4,  17)
#define GPIO_E18        __GPIO_PORT_PIN(4,  18)
#define GPIO_E19        __GPIO_PORT_PIN(4,  19)
#define GPIO_E20        __GPIO_PORT_PIN(4,  20)
#define GPIO_E21        __GPIO_PORT_PIN(4,  21)
#define GPIO_E22        __GPIO_PORT_PIN(4,  22)
#define GPIO_E23        __GPIO_PORT_PIN(4,  23)
#define GPIO_E24        __GPIO_PORT_PIN(4,  24)
#define GPIO_E25        __GPIO_PORT_PIN(4,  25)
#define GPIO_E26        __GPIO_PORT_PIN(4,  26)
#define GPIO_E27        __GPIO_PORT_PIN(4,  27)
#define GPIO_E28        __GPIO_PORT_PIN(4,  28)
#define GPIO_E29        __GPIO_PORT_PIN(4,  29)
#define GPIO_E30        __GPIO_PORT_PIN(4,  30)
#define GPIO_E31        __GPIO_PORT_PIN(4,  31)


// (1:input schmitt) (1:input deglitch) (2:pull up/dn) (1:push/pull,open-drain) (2:AF) (2:mode)

#define GPIO_INPUT		0
#define GPIO_OUTPUT		1
#define GPIO_ANALOG		2
#define GPIO_AF_A		(3 | ((0)<<2))
#define GPIO_AF_B		(3 | ((1)<<2))
#define GPIO_AF_C		(3 | ((2)<<2))
#define GPIO_AF_D		(3 | ((3)<<2))


#define GPIO_PUSH_PULL		0
#define GPIO_OPEN_DRAIN		(1<<4)
#define GPIO_PULL_UP		(1<<5)
#define GPIO_PULL_DN		(2<<5)

#define GPIO_DEGLITCH		(1<<7)
#define GPIO_SCHMITT		(1<<8)


extern void gpio_init(uint32_t, uint32_t);


static inline Pio *
_gpio_addr(uint32_t pin){
    switch(pin>>5){
    case 0:	return PIOA;
    case 1:	return PIOB;
    case 2:	return PIOC;
    case 3:	return PIOD;
    case 4:	return PIOE;
    default:
        return 0;
    }
}

static inline void
gpio_set(uint32_t pin){
    _gpio_addr(pin)->PIO_SODR = 1 << (pin&0x1F);
}

static inline void
gpio_clear(uint32_t pin){
    _gpio_addr(pin)->PIO_CODR = 1 << (pin&0x1F);
}

static inline int
gpio_get(uint32_t pin){
    return (_gpio_addr(pin)->PIO_PDSR & (1 << (pin&0x1F))) ? 1 : 0;
}


#endif /* __atsam_gpio_h__ */
