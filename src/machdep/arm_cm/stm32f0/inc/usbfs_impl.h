/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-22 17:55 (EDT)
  Function: stm32f0 usb impl

*/

#ifndef __stm32f0_usbfs_impl_h__
#define __stm32f0_usbfs_impl_h__

#define R_UNIQUE	((unsigned long*)(0x1FFFF7AC))
#define USBPMASIZE	1024
#define PMASHIFT	0
#define USB_IRQN	31
#define USB_IRQ_HANDLER USB_IRQHandler

#ifndef APB1PERIPH_BASE
# define APB1PERIPH_BASE PERIPH_BASE
#endif

#define USB_BASE              (APB1PERIPH_BASE + 0x5C00U)  /*!< USB_IP Peripheral Registers base address */
#define USB_PMAADDR           (APB1PERIPH_BASE + 0x6000U)  /*!< USB_IP Packet Memory Area base address */


static inline void
_usb_fs_init(void){
    RCC->APB1ENR  |= 1<<23;	// usb

    //gpio_init( GPIO_A11, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
    //gpio_init( GPIO_A12, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
}

#define _usb_fs_pullup_enable()	 (USB->BCDR = USB_BCDR_DPPU)
#define _usb_fs_pullup_disable() (USB->BCDR = 0)



#endif /* __stm32f0_usbfs_impl_h__ */
