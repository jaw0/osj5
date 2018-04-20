/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-10 21:17 (EDT)
  Function: common usb defs

*/

#define USB_LANG_EN_US		0x0409


#define USB_REQ_TYPE_WRITE                0x00
#define USB_REQ_TYPE_READ                 0x80
#define USB_REQ_TYPE_STANDARD             0x00
#define USB_REQ_TYPE_CLASS                0x20
#define USB_REQ_TYPE_VENDOR               0x40
#define USB_REQ_TYPE_DEVICE               0x00
#define USB_REQ_TYPE_INTERFACE            0x01
#define USB_REQ_TYPE_ENDPOINT             0x02
#define USB_REQ_TYPE_OTHER                0x03

/* Requests */
#define USB_REQ_GET_STATUS                  0x00
#define USB_REQ_CLEAR_FEATURE               0x01
#define USB_REQ_SET_FEATURE                 0x03
#define USB_REQ_SET_ADDRESS                 0x05
#define USB_REQ_GET_DESCRIPTOR              0x06
#define  USB_DESC_DEVICE                      0x01
#define  USB_DESC_CONFIG                      0x02
#define  USB_DESC_STRING                      0x03
#define  USB_DESC_INTERFACE                   0x04
#define  USB_DESC_ENDPOINT                    0x05
#define  USB_DESC_DEVICE_QUALIFIER            0x06
#define  USB_DESC_OTHER_SPEED_CONFIGURATION   0x07
#define  USB_DESC_INTERFACE_POWER             0x08
#define  USB_DESC_OTG                         0x09
#define  USB_DESC_CS_DEVICE                   0x21 /* class specific */
#define  USB_DESC_CS_CONFIG                   0x22
#define  USB_DESC_CS_STRING                   0x23
#define  USB_DESC_CS_INTERFACE                0x24
#define  USB_DESC_CS_ENDPOINT                 0x25
#define  USB_DESC_HUB                         0x29
#define USB_REQ_SET_DESCRIPTOR              0x07
#define USB_REQ_GET_CONFIG                  0x08
#define USB_REQ_SET_CONFIG                  0x09
#define USB_REQ_GET_INTERFACE               0x0A
#define USB_REQ_SET_INTERFACE               0x0B
#define USB_REQ_SYNCH_FRAME                 0x0C


#define USB_CLASS_PER_INTERFACE     0x00
#define USB_SUBCLASS_NONE           0x00
#define USB_PROTO_NONE              0x00
#define USB_CLASS_AUDIO             0x01
#define USB_CLASS_PHYSICAL          0x05
#define USB_CLASS_STILL_IMAGE       0x06
#define USB_CLASS_PRINTER           0x07
#define USB_CLASS_MASS_STORAGE      0x08
#define USB_CLASS_HUB               0x09
#define USB_CLASS_CSCID             0x0B
#define USB_CLASS_CONTENT_SEC       0x0D
#define USB_CLASS_VIDEO             0x0E
#define USB_CLASS_HEALTHCARE        0x0F
#define USB_CLASS_AV                0x10
#define USB_CLASS_BILLBOARD         0x11
#define USB_CLASS_CBRIDGE           0x12
#define USB_CLASS_DIAGNOSTIC        0xDC
#define USB_CLASS_WIRELESS          0xE0
#define USB_CLASS_MISC              0xEF
#define USB_CLASS_APP_SPEC          0xFE
#define USB_CLASS_VENDOR            0xFF
#define USB_SUBCLASS_VENDOR         0xFF
#define USB_PROTO_VENDOR            0xFF


#define USB_DTYPE_DEVICE            0x01
#define USB_DTYPE_CONFIGURATION     0x02
#define USB_DTYPE_STRING            0x03
#define USB_DTYPE_INTERFACE         0x04
#define USB_DTYPE_ENDPOINT          0x05
#define USB_DTYPE_QUALIFIER         0x06
#define USB_DTYPE_OTHER             0x07
#define USB_DTYPE_INTERFACEPOWER    0x08
#define USB_DTYPE_OTG               0x09
#define USB_DTYPE_DEBUG             0x0A
#define USB_DTYPE_INTERFASEASSOC    0x0B
#define USB_DTYPE_CS_INTERFACE      0x24
#define USB_DTYPE_CS_ENDPOINT       0x25

#define USB_NO_DESCRIPTOR	    0

typedef struct {
        uint8_t           bmRequestType;
        uint8_t           bRequest;
        uint16_t          wValue;
        uint16_t          wIndex;
        uint16_t          wLength;
} usb_device_request_t;

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
}  usb_descriptor_t;

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        char 		  bData[0];
}  usb_data_descriptor_t;

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint16_t	  wData[0];
}  usb_wdata_descriptor_t;


typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint16_t          bcdUSB;
#define UD_USB_2_0              0x0200
#define UD_IS_USB2(d) (UGETW((d)->bcdUSB) >= UD_USB_2_0)
        uint8_t           bDeviceClass;
        uint8_t           bDeviceSubClass;
        uint8_t           bDeviceProtocol;
        uint8_t           bMaxPacketSize;
        /* The fields below are not part of the initial descriptor. */
        uint16_t          idVendor;
        uint16_t          idProduct;
        uint16_t          bcdDevice;
        uint8_t           iManufacturer;
        uint8_t           iProduct;
        uint8_t           iSerialNumber;
        uint8_t           bNumConfigurations;
}  usb_device_descriptor_t;
#define USB_DEVICE_DESCRIPTOR_SIZE 18

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint16_t          wTotalLength;
        uint8_t           bNumInterface;
        uint8_t           bConfigurationValue;
        uint8_t           iConfiguration;
        uint8_t           bmAttributes;
#define UC_ATTR_MBO             0x80
#define UC_SELF_POWERED         0x40
#define UC_REMOTE_WAKEUP        0x20
        uint8_t           bMaxPower; /* max current in 2 mA units */
#define UC_POWER_FACTOR 2
}  usb_config_descriptor_t;
#define USB_CONFIG_DESCRIPTOR_SIZE 9

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint8_t           bInterfaceNumber;
        uint8_t           bAlternateSetting;
        uint8_t           bNumEndpoints;
        uint8_t           bInterfaceClass;
        uint8_t           bInterfaceSubClass;
        uint8_t           bInterfaceProtocol;
        uint8_t           iInterface;
}  usb_interface_descriptor_t;
#define USB_INTERFACE_DESCRIPTOR_SIZE 9

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint8_t           bEndpointAddress;
#define UE_GET_DIR(a)   ((a) & 0x80)
#define UE_SET_DIR(a,d) ((a) | (((d)&1) << 7))
#define UE_DIR_IN       0x80
#define UE_DIR_OUT      0x00
#define UE_ADDR         0x0f
#define UE_GET_ADDR(a)  ((a) & UE_ADDR)
        uint8_t           bmAttributes;
#define UE_XFERTYPE     0x03
#define  UE_CONTROL     0x00
#define  UE_ISOCHRONOUS 0x01
#define  UE_BULK        0x02
#define  UE_INTERRUPT   0x03
#define UE_GET_XFERTYPE(a)      ((a) & UE_XFERTYPE)
#define UE_ISO_TYPE     0x0c
#define  UE_ISO_ASYNC   0x04
#define  UE_ISO_ADAPT   0x08
#define  UE_ISO_SYNC    0x0c
#define UE_GET_ISO_TYPE(a)      ((a) & UE_ISO_TYPE)
        uint16_t           wMaxPacketSize;
#define UE_GET_TRANS(a)         (((a) >> 11) & 0x3)
#define UE_GET_SIZE(a)          ((a) & 0x7ff)
        uint8_t           bInterval;
}  usb_endpoint_descriptor_t;
#define USB_ENDPOINT_DESCRIPTOR_SIZE 7

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint16_t          bString[126];
}  usb_string_descriptor_t;
#define USB_MAX_STRING_LEN 128
#define USB_LANGUAGE_TABLE 0    /* # of the string language id table */
#define USB_MAX_ENCODED_STRING_LEN (USB_MAX_STRING_LEN * 3) /* UTF8 */



typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint16_t          bcdUSB;
        uint8_t           bDeviceClass;
        uint8_t           bDeviceSubClass;
        uint8_t           bDeviceProtocol;
        uint8_t           bMaxPacketSize0;
        uint8_t           bNumConfigurations;
        uint8_t           bReserved;
}  usb_device_qualifier_t;
#define USB_DEVICE_QUALIFIER_SIZE 10

typedef struct {
        uint8_t           bLength;
        uint8_t           bDescriptorType;
        uint8_t           bmAttributes;
#define UOTG_SRP        0x01
#define UOTG_HNP        0x02
}  usb_otg_descriptor_t;

/* OTG feature selectors */
#define UOTG_B_HNP_ENABLE       3
#define UOTG_A_HNP_SUPPORT      4
#define UOTG_A_ALT_HNP_SUPPORT  5

typedef struct {
        uint16_t           wStatus;
/* Device status flags */
#define UDS_SELF_POWERED                0x0001
#define UDS_REMOTE_WAKEUP               0x0002
/* Endpoint status flags */
#define UES_HALT                        0x0001
}  usb_status_t;


