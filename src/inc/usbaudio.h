/*
  Copyright (c) 2019
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2019-Mar-03 10:15 (EST)
  Function: usb class audio

*/

#ifndef __usbaudio_h__
#define __usbaudio_h__

#define  USB_SUBCLASS_AUDIOCONTROL        1
#define  USB_SUBCLASS_AUDIOSTREAM         2
#define  USB_SUBCLASS_MIDISTREAM          3

#define UDESCSUB_AC_HEADER      1
#define UDESCSUB_AC_INPUT       2
#define UDESCSUB_AC_OUTPUT      3
#define UDESCSUB_AC_MIXER       4
#define UDESCSUB_AC_SELECTOR    5
#define UDESCSUB_AC_FEATURE     6
#define UDESCSUB_AC_PROCESSING  7
#define UDESCSUB_AC_EXTENSION   8
#define UDESCSUB_AC_CLOCKSRC    10

#define UDESCSUB_AS_GENERAL         1
#define UDESCSUB_AS_FORMAT          2
#define UDESCSUB_AS_FORMAT_SPECIFIC 3

#define UDESCSUB_MS_HEADER      1
#define UDESCSUB_MS_JACKIN      2
#define UDESCSUB_MS_JACKOUT     3
#define UDESCSUB_MS_ELEMENT     4


#define UA_CS_EP_GENERAL	1

#define UA_FORMAT_TYPE_I	1
#define UA_IP_VERSION_02_00	0x20
#define UA_ADC_VER_2		0x200

#define AUCTL_REQTYPE_CUR   1
#define AUCTL_REQTYPE_RANGE 2
#define AUCTL_REQTYPE_MEM   3

/* terminal types */
/* USB terminal types */
#define UAT_UNDEFINED           0x0100
#define UAT_STREAM              0x0101
#define UAT_VENDOR              0x01ff
/* input terminal types */
#define UATI_UNDEFINED          0x0200
#define UATI_MICROPHONE         0x0201
#define UATI_DESKMICROPHONE     0x0202
#define UATI_PERSONALMICROPHONE 0x0203
#define UATI_OMNIMICROPHONE     0x0204
#define UATI_MICROPHONEARRAY    0x0205
#define UATI_PROCMICROPHONEARR  0x0206
/* output terminal types */
#define UATO_UNDEFINED          0x0300
#define UATO_SPEAKER            0x0301
#define UATO_HEADPHONES         0x0302
#define UATO_DISPLAYAUDIO       0x0303
#define UATO_DESKTOPSPEAKER     0x0304
#define UATO_ROOMSPEAKER        0x0305
#define UATO_COMMSPEAKER        0x0306
#define UATO_SUBWOOFER          0x0307
/* bidir terminal types */
#define UATB_UNDEFINED          0x0400
#define UATB_HANDSET            0x0401
#define UATB_HEADSET            0x0402
#define UATB_SPEAKERPHONE       0x0403
#define UATB_SPEAKERPHONEESUP   0x0404
#define UATB_SPEAKERPHONEECANC  0x0405
/* telephony terminal types */
#define UATT_UNDEFINED          0x0500
#define UATT_PHONELINE          0x0501
#define UATT_TELEPHONE          0x0502
#define UATT_DOWNLINEPHONE      0x0503
/* external terminal types */
#define UATE_UNDEFINED          0x0600
#define UATE_ANALOGCONN         0x0601
#define UATE_DIGITALAUIFC       0x0602
#define UATE_LINECONN           0x0603
#define UATE_LEGACYCONN         0x0604
#define UATE_SPDIF              0x0605
#define UATE_1394DA             0x0606
#define UATE_1394DV             0x0607
/* embedded function terminal types */
#define UATF_UNDEFINED          0x0700
#define UATF_CALIBNOISE         0x0701
#define UATF_EQUNOISE           0x0702
#define UATF_CDPLAYER           0x0703
#define UATF_DAT                0x0704
#define UATF_DCC                0x0705
#define UATF_MINIDISK           0x0706
#define UATF_ANALOGTAPE         0x0707
#define UATF_PHONOGRAPH         0x0708
#define UATF_VCRAUDIO           0x0709
#define UATF_VIDEODISCAUDIO     0x070a
#define UATF_DVDAUDIO           0x070b
#define UATF_TVTUNERAUDIO       0x070c
#define UATF_SATELLITE          0x070d
#define UATF_CABLETUNER         0x070e
#define UATF_DSS                0x070f
#define UATF_RADIORECV          0x0710
#define UATF_RADIOXMIT          0x0711
#define UATF_MULTITRACK         0x0712
#define UATF_SYNTHESIZER        0x0713



#define UMIDI_MS_HEADER 0x01
#define UMIDI_IN_JACK   0x02
#define UMIDI_OUT_JACK  0x03

#define UMIDI_EMBEDDED  0x01
#define UMIDI_EXTERNAL  0x02

#define UAUDIO_CMD_SET_CUR 0x01
#define UAUDIO_CMD_GET_CUR 0x81
#define UAUDIO_CMD_SET_MIN 0x02
#define UAUDIO_CMD_GET_MIN 0x82
#define UAUDIO_CMD_SET_MAX 0x03
#define UAUDIO_CMD_GET_MAX 0x83
#define UAUDIO_CMD_SET_RES 0x04
#define UAUDIO_CMD_GET_RES 0x84
#define UAUDIO_CMD_SET_MEM 0x05
#define UAUDIO_CMD_GET_MEM 0x85
#define UAUDIO_CMD_GET_STAT 0xff

typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint16_t 	bcdADC;
    uint8_t 	bCategory;
#define  UA_HDR_FUNCTION_IOBOX 8
    uint16_t 	wTotalLength;
    uint8_t 	bmControls;
} PACKED uaudioctl_cs_iface_header_descriptor_t;

typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint8_t	bClockID;
    uint8_t	bmAttributes;
    uint8_t	bmControls;
    uint8_t	bAssocTerminal;
    uint8_t	iClockSource;
} PACKED uaudioctl_cs_iface_clksrc_descriptor_t;

typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint8_t     bTerminalID;
    uint16_t    wTerminalType;
    uint8_t     bAssocTerminal;
    uint8_t     bCSourceID;
    uint8_t     bNrChannels;
    uint32_t    bmChannelConfig;
    uint8_t     iChannelNames;
    uint16_t    bmControls;
    uint8_t     iTerminal;
} PACKED uaudioctl_cs_iface_iterminal_descriptor_t;

typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint8_t     bTerminalID;
    uint16_t    wTerminalType;
    uint8_t     bAssocTerminal;
    uint8_t     bSourceID;
    uint8_t     bCSourceID;
    uint16_t    bmControls;
    uint8_t     iTerminal;
} PACKED uaudioctl_cs_iface_oterminal_descriptor_t;

typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint8_t     bUnitID;
    uint8_t     bSourceID;
    uint32_t    bmaControls[2];	// number of channels + 1
    uint8_t     iFeature;
} PACKED uaudioctl_cs_iface_features_descriptor_1t;

typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint8_t     bUnitID;
    uint8_t     bSourceID;
    uint32_t    bmaControls[3];
    uint8_t     iFeature;
} PACKED uaudioctl_cs_iface_features_descriptor_2t;
typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint8_t     bUnitID;
    uint8_t     bSourceID;
    uint32_t    bmaControls[5];
    uint8_t     iFeature;
} PACKED uaudioctl_cs_iface_features_descriptor_4t;
typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint8_t     bUnitID;
    uint8_t     bSourceID;
    uint32_t    bmaControls[9];
    uint8_t     iFeature;
} PACKED uaudioctl_cs_iface_features_descriptor_8t;

typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint8_t     bTerminalLink;
    uint8_t     bmControls;
    uint8_t     bFormatType;
    uint32_t    bmFormats;
    uint8_t     bNrChannels;
    uint32_t    bmChannelConfig;
    uint8_t     iChannelNames;
} PACKED uaudiostr_cs_iface_general_descriptor_t;

typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint8_t     bFormatType;
    uint8_t     bSubslotSize;
    uint8_t     bBitResolution;
} PACKED uaudiostr_cs_iface_format1_descriptor_t;

typedef struct {
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bDescriptorSubtype;
    uint8_t     bmAttributes;
    uint8_t     bmControls;
    uint8_t     bLockDelayUnits;
    uint16_t    wLockDelay;
} PACKED uaudiostr_cs_endpoint_descriptor_t;

typedef struct {
    uint16_t wNumSubRanges;
    struct {
        uint8_t bMIN;
        uint8_t bMAX;
        uint8_t bRES;
    } range[];
} PACKED uaudio_cs_range1_t;

typedef struct {
    uint16_t wNumSubRanges;
    struct {
        uint16_t wMIN;
        uint16_t wMAX;
        uint16_t wRES;
    } range[];
} PACKED uaudio_cs_range2_t;

typedef struct {
    uint16_t wNumSubRanges;
    struct {
        uint32_t dMIN;
        uint32_t dMAX;
        uint32_t dRES;
    } range[];
} PACKED uaudio_cs_range4_t;


typedef struct {
    uint8_t           bLength;
    uint8_t           bDescriptorType;
    uint8_t           bDescriptorSubtype;
    uint16_t          bcdMSC;
#define UA_MSC_VER_1 0x100
    uint16_t          wTotalLength;
} PACKED umidi_cs_iface_descriptor_t;

typedef struct {
    uint8_t           bLength;
    uint8_t           bDescriptorType;
    uint8_t           bDescriptorSubtype;
    uint8_t           bJackType;
    uint8_t           bJackID;
    uint8_t	      iJack;
} PACKED umidi_jackin_descriptor_t;

#define UMIDI_JACKOUT(N) \
typedef struct { \
    uint8_t           bLength;\
    uint8_t           bDescriptorType;\
    uint8_t           bDescriptorSubtype;\
    uint8_t           bJackType;\
    uint8_t           bJackID;\
    uint8_t	      bNrInputPins;\
    struct {\
        uint8_t bSourceID;\
        uint8_t bSourcePin;\
    } source[ N ];\
    uint8_t	      iJack;\
} PACKED umidi_jackout_descriptor_ ## N ## t;
UMIDI_JACKOUT(1)

#define UMIDI_CSEP(N) \
typedef struct {\
    uint8_t           bLength;\
    uint8_t           bDescriptorType;\
    uint8_t           bDescriptorSubtype;\
    uint8_t           bNumEmbMIDIJack;\
    uint8_t	      baAssocJackID[ N ];\
} PACKED umidi_cs_endpoint_descriptor_ ## N ## t;
UMIDI_CSEP(1)


#endif /* __usbaudio_h__ */
