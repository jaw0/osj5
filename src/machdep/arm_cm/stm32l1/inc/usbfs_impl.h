/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-22 17:55 (EDT)
  Function: stm32l1 usb impl

*/

#ifndef __stm32l1_usbfs_impl_h__
#define __stm32l1_usbfs_impl_h__

extern uint32_t r_unique;
#define R_UNIQUE	r_unique
#define USBPMASIZE	512
#define PMASHIFT	1
#define USB_IRQN	20
#define USB_IRQ_HANDLER USB_LP_IRQHandler

#ifndef APB1PERIPH_BASE
# define APB1PERIPH_BASE PERIPH_BASE
#endif

#define USB_BASE              (APB1PERIPH_BASE + 0x5C00U)  /*!< USB_IP Peripheral Registers base address */
#define USB_PMAADDR           (APB1PERIPH_BASE + 0x6000U)  /*!< USB_IP Packet Memory Area base address */

static inline void
_usb_fs_init(void){
    RCC->APB2ENR  |= 1;		// syscfg
    RCC->APB1ENR  |= 1<<23;	// usb
}

#define _usb_fs_pullup_enable()	 (SYSCFG->PMC |= 1)
#define _usb_fs_pullup_disable() (SYSCFG->PMC &= ~1)



#endif /* __stm32l1_usbfs_impl_h__ */
