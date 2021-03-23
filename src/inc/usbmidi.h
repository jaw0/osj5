/*
  Copyright (c) 2019
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2019-Mar-03 10:15 (EST)
  Function: usb midi

*/

#ifndef __usbmidi_h__
#define __usbmidi_h__

#define UMIDI_MS_HEADER 0x01
#define UMIDI_IN_JACK   0x02
#define UMIDI_OUT_JACK  0x03

#define UMIDI_EMBEDDED  0x01
#define UMIDI_EXTERNAL  0x02



typedef struct {
    uint8_t           bLength;
    uint8_t           bDescriptorType;
    uint8_t           bDescriptorSubtype;
    uint16_t          bcdMSC;
    uint16_t          wTotalLength;
} PACKED umidi_cs_interface_descriptor_t;

typedef struct {
    uint8_t           bLength;
    uint8_t           bDescriptorType;
    uint8_t           bDescriptorSubtype;
    uint8_t           bJackType;
    uint8_t           bJackID;
    uint8_t	      iJack;
} PACKED umidi_jackin_descriptor_t;

typedef struct {
    uint8_t           bLength;
    uint8_t           bDescriptorType;
    uint8_t           bDescriptorSubtype;
    uint8_t           bJackType;
    uint8_t           bJackID;
    uint8_t	      bNrInputPins;
        { 
            baSourceID
                BaSourcePin
           }
    
    uint8_t	      iJack;
} PACKED umidi_jackout_descriptor_t;

typedef struct {
    uint8_t           bLength;
    uint8_t           bDescriptorType;
    uint8_t           bDescriptorSubtype;
    uint8_t           bNumEmbMIDIJack;
} PACKED umidi_cs_endpoint_descriptor_t;


#endif /* __usbmidi_h__ */
