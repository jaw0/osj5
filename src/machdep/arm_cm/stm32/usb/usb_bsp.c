
#include <conf.h>
#include <proc.h>
#include "usb_bsp.h"

void
USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE *pdev){

}

void
USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE *pdev){

}

/**
  * @brief  BSP_Drive_VBUS
  *         Drives the Vbus signal through IO
  * @param  speed : Full, Low
  * @param  state : VBUS states
  * @retval None
  */

void
USB_OTG_BSP_DriveVBUS(uint32_t speed, uint8_t state){

}

/**
  * @brief  USB_OTG_BSP_ConfigVBUS
  *         Configures the IO for the Vbus and OverCurrent
  * @param  Speed : Full, Low
  * @retval None
  */

void
USB_OTG_BSP_ConfigVBUS(uint32_t speed){

}

/**
  * @brief  USB_OTG_BSP_TimeInit
  *         Initialises delay unit Systick timer /Timer2
  * @param  None
  * @retval None
  */
void
USB_OTG_BSP_TimeInit(void){

}

/**
  * @brief  USB_OTG_BSP_uDelay
  *         This function provides delay time in micro sec
  * @param  usec : Value of delay required in micro sec
  * @retval None
  */
void
USB_OTG_BSP_uDelay(uint32_t usec){
    if( 0 && currproc ){
        usleep(usec);
        return;
    }

    usec = 12 * usec;
    while( usec-- > 0 ) { __asm("nop"); }
}


/**
  * @brief  USB_OTG_BSP_mDelay
  *          This function provides delay time in milli sec
  * @param  msec : Value of delay required in milli sec
  * @retval None
  */
void
USB_OTG_BSP_mDelay(uint32_t msec){
  USB_OTG_BSP_uDelay(msec * 1000);
}


/**
  * @brief  USB_OTG_BSP_TimerIRQ
  *         Time base IRQ
  * @param  None
  * @retval None
  */

void
USB_OTG_BSP_TimerIRQ(void){

}
