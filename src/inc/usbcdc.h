/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-21 22:52 (EDT)
  Function: 

*/

#ifndef __usbcdc_h__
#define __usbcdc_h__

#define USB_CLASS_CDC                   0x02    /* Communicational Device class */
#define USB_CLASS_CDC_DATA              0x0A    /* Data Interface class */
#define USB_CDC_PROTO_V25TER            0x01    /* AT Commands: V.250 etc.*/


#define UDESCSUB_CDC_HEADER     0
#define UDESCSUB_CDC_CM         1 /* Call Management */
#define UDESCSUB_CDC_ACM        2 /* Abstract Control Model */
#define UDESCSUB_CDC_DLM        3 /* Direct Line Management */
#define UDESCSUB_CDC_TRF        4 /* Telephone Ringer */
#define UDESCSUB_CDC_TCLSR      5 /* Telephone Call ... */
#define UDESCSUB_CDC_UNION      6
#define UDESCSUB_CDC_CS         7 /* Country Selection */
#define UDESCSUB_CDC_TOM        8 /* Telephone Operational Modes */
#define UDESCSUB_CDC_USBT       9 /* USB Terminal */
#define UDESCSUB_CDC_NCT        10
#define UDESCSUB_CDC_PUF        11
#define UDESCSUB_CDC_EUF        12
#define UDESCSUB_CDC_MCMF       13
#define UDESCSUB_CDC_CCMF       14
#define UDESCSUB_CDC_ENF        15
#define UDESCSUB_CDC_ANF        16

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint8_t           bDescriptorSubtype;
        uint16_t          bcdCDC;
} PACKED usb_cdc_header_descriptor_t;

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint8_t           bDescriptorSubtype;
        uint8_t           bmCapabilities;
#define USB_CDC_CM_DOES_CM              0x01
#define USB_CDC_CM_OVER_DATA            0x02
        uint8_t           bDataInterface;
} PACKED usb_cdc_cm_descriptor_t;

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint8_t           bDescriptorSubtype;
        uint8_t           bmCapabilities;
#define USB_CDC_ACM_HAS_FEATURE         0x01
#define USB_CDC_ACM_HAS_LINE            0x02
#define USB_CDC_ACM_HAS_BREAK           0x04
#define USB_CDC_ACM_HAS_NETWORK_CONN    0x08
} PACKED usb_cdc_acm_descriptor_t;

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint8_t           bDescriptorSubtype;
        uint8_t           bMasterInterface;
        uint8_t           bSlaveInterface[1];
} PACKED usb_cdc_union_descriptor_t;

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint8_t           bDescriptorSubtype;
        uint8_t           iMacAddress;
        uint32_t          bmEthernetStatistics;
        uint16_t          wMaxSegmentSize;
        uint16_t          wNumberMCFikters;
        uint8_t           bNumberPowerFilters;
} PACKED usb_cdc_ethernet_descriptor_t;


#define UCDC_SEND_ENCAPSULATED_COMMAND  0x00
#define UCDC_GET_ENCAPSULATED_RESPONSE  0x01
#define UCDC_SET_COMM_FEATURE           0x02
#define UCDC_GET_COMM_FEATURE           0x03
#define  UCDC_ABSTRACT_STATE            0x01
#define  UCDC_COUNTRY_SETTING           0x02
#define UCDC_CLEAR_COMM_FEATURE         0x04
#define UCDC_SET_LINE_CODING            0x20
#define UCDC_GET_LINE_CODING            0x21
#define UCDC_SET_CONTROL_LINE_STATE     0x22
#define  UCDC_LINE_DTR                  0x0001
#define  UCDC_LINE_RTS                  0x0002
#define UCDC_SEND_BREAK                 0x23
#define  UCDC_BREAK_ON                  0xffff
#define  UCDC_BREAK_OFF                 0x0000


typedef struct {
        uint16_t   wState;
#define UCDC_IDLE_SETTING               0x0001
#define UCDC_DATA_MULTIPLEXED           0x0002
} PACKED usb_cdc_abstract_state_t;
#define UCDC_ABSTRACT_STATE_LENGTH 2

typedef struct {
        uint32_t  dwDTERate;
        uint8_t   bCharFormat;
#define UCDC_STOP_BIT_1                 0
#define UCDC_STOP_BIT_1_5               1
#define UCDC_STOP_BIT_2                 2
        uint8_t   bParityType;
#define UCDC_PARITY_NONE                0
#define UCDC_PARITY_ODD                 1
#define UCDC_PARITY_EVEN                2
#define UCDC_PARITY_MARK                3
#define UCDC_PARITY_SPACE               4
        uint8_t   bDataBits;
} PACKED usb_cdc_line_state_t;
#define UCDC_LINE_STATE_LENGTH 7

typedef struct {
        uint8_t   bmRequestType;
#define UCDC_NOTIFICATION               0xa1
        uint8_t   bNotification;
#define UCDC_N_NETWORK_CONNECTION       0x00
#define UCDC_N_RESPONSE_AVAILABLE       0x01
#define UCDC_N_AUX_JACK_HOOK_STATE      0x08
#define UCDC_N_RING_DETECT              0x09
#define UCDC_N_SERIAL_STATE             0x20
#define UCDC_N_CALL_STATE_CHANGED       0x28
#define UCDC_N_LINE_STATE_CHANGED       0x29
#define UCDC_N_CONNECTION_SPEED_CHANGE  0x2a
        uint16_t   wValue;
        uint16_t   wIndex;
        uint16_t   wLength;
        uint8_t   data[16];
} PACKED usb_cdc_notification_t;
#define UCDC_NOTIFICATION_LENGTH 8

/*
 * Bits set in the SERIAL STATE notifcation (first byte of data)
 */

#define UCDC_N_SERIAL_OVERRUN           0x40
#define UCDC_N_SERIAL_PARITY            0x20
#define UCDC_N_SERIAL_FRAMING           0x10
#define UCDC_N_SERIAL_RI                0x08
#define UCDC_N_SERIAL_BREAK             0x04
#define UCDC_N_SERIAL_DSR               0x02
#define UCDC_N_SERIAL_DCD               0x01

#endif /* __usbcdc_h__ */
