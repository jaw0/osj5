

#include <conf.h>
#include <proc.h>
#include "usbd_cdc_if.h"

extern uint8_t  APP_Rx_Buffer []; /* Write CDC received data in this buffer.
                                     These data will be sent over USB IN endpoint
                                     in the CDC core functions. */
extern uint32_t APP_Rx_ptr_in;    /* Increment this pointer or roll it back to
                                     start address when writing received data
                                     in the buffer APP_Rx_Buffer. */
extern uint32_t APP_Rx_ptr_out;
extern uint32_t APP_Rx_length;


/* Private function prototypes -----------------------------------------------*/
static uint16_t VCP_Init     (void);
static uint16_t VCP_DeInit   (void);
static uint16_t VCP_Ctrl     (uint32_t Cmd, uint8_t* Buf, uint32_t Len);

uint16_t VCP_DataTx   (uint8_t* Buf, uint32_t Len);
//static uint16_t VCP_DataRx   (uint8_t* Buf, uint32_t Len);
extern int vcp_recvchars(char *, int);

const CDC_IF_Prop_TypeDef VCP_fops =
{
  VCP_Init,
  VCP_DeInit,
  VCP_Ctrl,
  VCP_DataTx,
  // VCP_DataRx
  vcp_recvchars,
};

static uint16_t
VCP_Init(void){
    return USBD_OK;
}

static uint16_t
VCP_DeInit(void){
    return USBD_OK;
}

static uint16_t
VCP_Ctrl (uint32_t Cmd, uint8_t* Buf, uint32_t Len){

    // XXX - some commands have data in wValue, which is not passed in

  switch (Cmd)
  {
  case SEND_ENCAPSULATED_COMMAND:
    /* Add your code here */
    break;

  case GET_ENCAPSULATED_RESPONSE:
    /* Add your code here */
    break;

  case SET_COMM_FEATURE:
    /* Add your code here */
    break;

  case GET_COMM_FEATURE:
    /* Add your code here */
    break;

  case CLEAR_COMM_FEATURE:
    /* Add your code here */
    break;

  case SET_LINE_CODING:
    /* Add your code here */
    break;

  case GET_LINE_CODING:
    /* Add your code here */
    break;

  case SET_CONTROL_LINE_STATE:
    /* Add your code here */
    break;

  case SEND_BREAK:
     /* Add your code here */
    break;

  default:
    break;
  }

  return USBD_OK;
}

/**
  * @brief  VCP_DataTx
  *         CDC received data to be send over USB IN endpoint are managed in
  *         this function.
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the opeartion: USBD_OK if all operations are OK else USBD_FAIL
  */
uint16_t
VCP_DataTx(uint8_t* Buf, uint32_t Len){
    int i;

    /* Get the data to be sent */
    for (i = 0; i < Len; i++){
        // buffer full?
        if( APP_Rx_ptr_in == APP_RX_DATA_SIZE - 1 && APP_Rx_ptr_out == 0 ) return Len - i;
        if( APP_Rx_ptr_in + 1 == APP_Rx_ptr_out ) return Len - i;

        APP_Rx_Buffer[APP_Rx_ptr_in++] = Buf[i];

        if( APP_Rx_ptr_in >= APP_RX_DATA_SIZE )
            APP_Rx_ptr_in = 0;
    }

    return USBD_OK;
}

/**
  * @brief  VCP_DataRx
  *         Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will block any OUT packet reception on USB endpoint
  *         untill exiting this function. If you exit this function before transfer
  *         is complete on CDC interface (ie. using DMA controller) it will result
  *         in receiving more data while previous ones are still not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the opeartion: USBD_OK if all operations are OK else USBD_FAIL
  */
static uint16_t
VCP_DataRx (uint8_t* Buf, uint32_t Len){
  uint32_t i;

  /* Send the received buffer */
  for (i = 0; i < Len; i++){
      kprintf("%c", Buf[i]);
  }

  return USBD_OK;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
