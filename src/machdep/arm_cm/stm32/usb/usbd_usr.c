

#include "usbd_usr.h"
#include "usbd_ioreq.h"
#include "usbd_cdc_core.h"
#include "usbd_desc.h"

//################################################################

__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END;

void *
usb_start(void){

    USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc,
            &USBD_CDC_cb,
            &USR_cb);

    return & USB_OTG_dev;
}

void
OTG_FS_IRQHandler(void){
    USBD_OTG_ISR_Handler(&USB_OTG_dev);
}


//################################################################

static void
USBD_USR_Init(void){
    //kprintf("usbd init\n");
}

static void
USBD_USR_DeviceReset(uint8_t speed){
    //kprintf("usbd reset\n");
}

static void
USBD_USR_DeviceConfigured(void){
    //kprintf("usbd conf\n");
}

static void
USBD_USR_DeviceSuspended(void){
  /* Users can do their application actions here for the USB-Reset */
    //kprintf("usbd suspend\n");
}

static void
USBD_USR_DeviceResumed(void){
  /* Users can do their application actions here for the USB-Reset */
    //kprintf("usbd resume\n");
}

static void
USBD_USR_DeviceConnected(void){
    //kprintf("usbd connect\n");
}

static void
USBD_USR_DeviceDisconnected(void){
    //kprintf("usbd disconnect\n");
}

//################################################################

USBD_Usr_cb_TypeDef USR_cb = {
  USBD_USR_Init,
  USBD_USR_DeviceReset,
  USBD_USR_DeviceConfigured,
  USBD_USR_DeviceSuspended,
  USBD_USR_DeviceResumed,
  USBD_USR_DeviceConnected,
  USBD_USR_DeviceDisconnected,
};
