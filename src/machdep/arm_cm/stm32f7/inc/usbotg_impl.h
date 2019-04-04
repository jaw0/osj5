/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-22 17:55 (EDT)
  Function: stm32f7 usb impl

*/

#ifndef __stm32f7_usbfs_impl_h__
#define __stm32f7_usbfs_impl_h__

extern uint32_t *r_unique;
#define R_UNIQUE	r_unique

#define USB_FS_IRQN	OTG_FS_IRQn
#define USB_HS_IRQN	OTG_HS_IRQn

#define USB_FS_FIFOSIZE	1280
#define USB_HS_FIFOSIZE	4096


#define USB_FS_IRQ_HANDLER OTG_FS_IRQHandler
#define USB_HS_IRQ_HANDLER OTG_HS_IRQHandler

#ifndef APB1PERIPH_BASE
# define APB1PERIPH_BASE PERIPH_BASE
#endif


#define USB_OTG_HS_PERIPH_BASE               0x40040000U
#define USB_OTG_FS_PERIPH_BASE               0x50000000U


static inline void
_usb_otg_fs_init(void){

    RCC->AHB2ENR |= 1<<7;

    gpio_init( GPIO_A11, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
    gpio_init( GPIO_A12, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
}

static inline void
_usb_otg_hs_init(void){

    RCC->AHB1ENR |= 1 << 29;
    RCC->APB2ENR |= 1 << 31; // HS PHY

    // XXX - various options. B14,15 = builtin PHY
    gpio_init( GPIO_B14, GPIO_AF(12) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
    gpio_init( GPIO_B15, GPIO_AF(12) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );

}




#endif /* __stm32f7_usbfs_impl_h__ */
