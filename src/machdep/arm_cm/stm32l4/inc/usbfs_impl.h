/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-22 17:55 (EDT)
  Function: stm32l4 usb impl

*/

#ifndef __stm32l4_usbfs_impl_h__
#define __stm32l4_usbfs_impl_h__

#define R_UNIQUE	((unsigned long*)(0x1FFF7590))


static inline void
_usb_fs_init(void){
    RCC->APB1ENR1  |= 1<<26;	// usb
    RCC->APB1ENR1  |= 1<<28;	// pwr
    PWR->CR2 |= 1<<10;

    gpio_init( GPIO_A11, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
    gpio_init( GPIO_A12, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
}

static inline void
_usb_fs_pullup_enable(void){
    USB->BCDR = USB_BCDR_DPPU;
}

static inline void
_usb_fs_pullup_disable(void){
    USB->BCDR = 0;
}



#endif /* __stm32l4_usbfs_impl_h__ */
