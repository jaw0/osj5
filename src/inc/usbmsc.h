/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Aug-28 20:07 (EDT)
  Function: usb mass storage

*/

#ifndef __usbmsc_h__
#define __usbmsc_h__

struct Sense {
    uint8_t key, asc, ascq;
};

typedef struct {
    int8_t  readonly;
    struct Sense sense;
    FILE   *fio;
    int (*ready)(void);
    void (*activity)(void);
    char *prod;
} usb_msc_iocf_t;


#define USB_CLASS_MSC                   0x08
#define  USB_SUBCLASS_RBC         1
#define  USB_SUBCLASS_SFF8020I    2
#define  USB_SUBCLASS_QIC157      3
#define  USB_SUBCLASS_UFI         4
#define  USB_SUBCLASS_SFF8070I    5
#define  USB_SUBCLASS_SCSI        6

#define  USB_PROTO_MASS_CBI_I     0
#define  USB_PROTO_MASS_CBI       1
#define  USB_PROTO_MASS_BBB       0x50
#define  USB_PROTO_MASS_UAS       0x62

#define UR_BBB_RESET    	0xff            /* Bulk-Only reset */
#define UR_BBB_GET_MAX_LUN      0xfe

/* Command Block Wrapper */
typedef struct {
        uint32_t          dCBWSignature;
#define CBWSIGNATURE    0x43425355
        uint32_t          dCBWTag;
        uint32_t          dCBWDataTransferLength;
        uint8_t           bCBWFlags;
#define CBWFLAGS_OUT    0x00
#define CBWFLAGS_IN     0x80
        uint8_t           bCBWLUN;
        uint8_t           bCDBLength;
#define CBWCDBLENGTH    16
        uint8_t           CBWCDB[CBWCDBLENGTH];
} PACKED umass_bbb_cbw_t;

/* Command Status Wrapper */
typedef struct {
        uint32_t          dCSWSignature;
#define CSWSIGNATURE            0x53425355
        uint32_t          dCSWTag;
        uint32_t          dCSWDataResidue;
        uint8_t           bCSWStatus;
#define CSWSTATUS_GOOD  0x0
#define CSWSTATUS_FAILED 0x1
#define CSWSTATUS_PHASE 0x2
} PACKED umass_bbb_csw_t;

typedef struct {
    uint8_t d[8];
    char    manuf[8];
    char    prod[16];
    char    rev[4];
} PACKED umass_bbb_inquiry_t;

typedef struct {
    uint8_t  cmd;
    uint8_t  _resv1;
    uint32_t lba;
    uint8_t  _resv2;
    uint16_t len;
} PACKED umass_bbb_rw10_t;

typedef struct {


} PACKED umass_bbb_write10_t;


#define SCSI_TEST_UNIT_READY			    0x00
#define SCSI_FORMAT_UNIT                            0x04
#define SCSI_INQUIRY                                0x12
#define SCSI_MODE_SELECT6                           0x15
#define SCSI_MODE_SELECT10                          0x55
#define SCSI_MODE_SENSE6                            0x1A
#define SCSI_MODE_SENSE10                           0x5A
#define SCSI_ALLOW_MEDIUM_REMOVAL                   0x1E
#define SCSI_READ6                                  0x08
#define SCSI_READ10                                 0x28
#define SCSI_READ12                                 0xA8
#define SCSI_READ16                                 0x88

#define SCSI_READ_CAPACITY10                        0x25
#define SCSI_READ_CAPACITY16                        0x9E

#define SCSI_REQUEST_SENSE                          0x03
#define SCSI_START_STOP_UNIT                        0x1B
#define SCSI_TEST_UNIT_READY                        0x00
#define SCSI_WRITE6                                 0x0A
#define SCSI_WRITE10                                0x2A
#define SCSI_WRITE12                                0xAA
#define SCSI_WRITE16                                0x8A

#define SCSI_VERIFY10                               0x2F
#define SCSI_VERIFY12                               0xAF
#define SCSI_VERIFY16                               0x8F

#define SCSI_SEND_DIAGNOSTIC                        0x1D
#define SCSI_READ_FORMAT_CAPACITIES                 0x23


#define SKEY_NO_SENSE                                    0
#define SKEY_RECOVERED_ERROR                             1
#define SKEY_NOT_READY                                   2
#define SKEY_MEDIUM_ERROR                                3
#define SKEY_HARDWARE_ERROR                              4
#define SKEY_ILLEGAL_REQUEST                             5
#define SKEY_UNIT_ATTENTION                              6
#define SKEY_DATA_PROTECT                                7
#define SKEY_BLANK_CHECK                                 8
#define SKEY_VENDOR_SPECIFIC                             9
#define SKEY_COPY_ABORTED                               10
#define SKEY_ABORTED_COMMAND                            11
#define SKEY_VOLUME_OVERFLOW                            13
#define SKEY_MISCOMPARE                                 14

#define SASC_INVALID_CDB                                 0x20
#define SASC_INVALID_FIELD_IN_COMMAND                    0x24
#define SASC_PARAMETER_LIST_LENGTH_ERROR                 0x1A
#define SASC_INVALID_FIELD_IN_PARAMETER_LIST             0x26
#define SASC_ADDRESS_OUT_OF_RANGE                        0x21
#define SASC_MEDIUM_NOT_PRESENT                          0x3A
#define SASC_MEDIUM_HAVE_CHANGED                         0x28
#define SASC_WRITE_PROTECTED                             0x27
#define SASC_UNRECOVERED_READ_ERROR                      0x11
#define SASC_WRITE_FAULT                                 0x03

#endif /* __usbmsc_h__ */
