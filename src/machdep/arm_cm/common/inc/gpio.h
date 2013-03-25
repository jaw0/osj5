/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 12:53 (EDT)
  Function: gpio

*/


#ifndef __gpio_h__
#define __gpio_h__

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

#define GPIO_INPUT_ANALOG        (0x0 << 2)
#define GPIO_INPUT_FLOATING      (0x1 << 2)
#define GPIO_INPUT_PU_PD         (0x2 << 2)
#define GPIO_OUTPUT_PP           (0x0 << 2)
#define GPIO_OUTPUT_OD           (0x1 << 2)
#define GPIO_AF_OUTPUT_PP        (0x2 << 2)
#define GPIO_AF_OUTPUT_OD        (0x3 << 2)

#define GPIO_INPUT              0x0
#define GPIO_OUTPUT_10MHZ       0x1
#define GPIO_OUTPUT_2MHZ        0x2
#define GPIO_OUTPUT_50MHZ       0x3



extern void gpio_init(int, int);
extern void gpio_set(int);
extern void gpio_clear(int);
extern int gpio_get(int);

#endif /* __gpio_h__ */
