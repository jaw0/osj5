/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-22 17:55 (EDT)
  Function: stm32l4(+) usb/otg/fs impl

*/

#ifndef __stm32l4_usbotgfs_impl_h__
#define __stm32l4_usbotgfs_impl_h__

#define R_UNIQUE	((unsigned long*)(0x1FFF7590))

#define USB_FS_IRQN	OTG_FS_IRQn

#define USB_FS_ENDPOINTS 6
#define USB_FS_FIFOSIZE	 1280


#define USB_FS_IRQ_HANDLER OTG_FS_IRQHandler


static inline void
_usb_otg_fs_init(void){

    RCC->AHB2ENR  |= 1<<12;	// usb otg
    RCC->APB1ENR1 |= 1<<28;	// pwr
    PWR->CR2 |= 1<<10;

    gpio_init( GPIO_A11, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
    gpio_init( GPIO_A12, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
}

#define _usb_fs_pullup_enable()	 (USB->BCDR = USB_BCDR_DPPU)
#define _usb_fs_pullup_disable() (USB->BCDR = 0)


#endif /* __stm32l4_usbotgfs_impl_h__ */
