/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-22 17:55 (EDT)
  Function: stm32l4(+) usb/otg/hs+fs impl

*/

#ifndef __stm32u5_usbotgfs_impl_h__
#define __stm32u5_usbotgfs_impl_h__

#define R_UNIQUE	((unsigned long*)(0x0BFA0700))

#define USB_FS_IRQN	OTG_HS_IRQn
#define USB_HS_IRQN	OTG_HS_IRQn

// host+dev devices: 6/1280
// otg/fs devices: 6/1280
// otg/hs devices: 9/4096

#define USB_FS_ENDPOINTS 9
#define USB_FS_FIFOSIZE	 1280
#define USB_HS_FIFOSIZE	 4096


//#define USB_FS_IRQ_HANDLER OTG_FS_IRQHandler
#define USB_HS_IRQ_HANDLER OTG_HS_IRQHandler

#define USB_OTG_HS_PERIPH_BASE               USB_OTG_HS_BASE
#define USB_OTG_FS_PERIPH_BASE               USB_OTG_HS_BASE


#define USB_HSPHY_INTERNAL


static inline void
_usb_otg_fs_init(void){

    RCC->AHB2ENR1 |= 1<<14;	 // usb otg
    RCC->APB2ENR  |= 1<<24;	 // usb clk enable, only on FS devs

    PWR->SVMCR |= PWR_SVMCR_USV; // enable usb power

    gpio_init( GPIO_A11, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
    gpio_init( GPIO_A12, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
}

static inline void
_usb_otg_hs_init(void){

    RCC->AHB2ENR1 |= RCC_AHB2ENR1_OTGEN;
    RCC->AHB2ENR1 |= RCC_AHB2ENR1_USBPHYCEN;

    PWR->SVMCR |= PWR_SVMCR_USV; 	// enable usb power

    // enable usb HS epod power
    PWR->VOSR |= PWR_VOSR_USBBOOSTEN | PWR_VOSR_USBPWREN;
    while( (PWR->VOSR & PWR_VOSR_USBBOOSTRDY) == 0 ){}

    SYSCFG->OTGHSPHYTUNER2 = (SYSCFG->OTGHSPHYTUNER2 & ~0x7F) | 2;
    SYSCFG->OTGHSPHYCR |= 1;	 // enable hs phy

    // NB - there is no AF. magic happens.
    //gpio_init( GPIO_A11, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
    //gpio_init( GPIO_A12, GPIO_AF(10) | GPIO_PUSH_PULL | GPIO_SPEED_100MHZ );
}


#define _usb_fs_pullup_enable()	 (USB->BCDR = USB_BCDR_DPPU)
#define _usb_fs_pullup_disable() (USB->BCDR = 0)


#endif /* __stm32u5_usbotgfs_impl_h__ */
