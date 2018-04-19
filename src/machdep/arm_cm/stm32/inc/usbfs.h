/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-16 00:48 (EDT)
  Function: usb full speed device

*/



#define N_ENDPOINT	8
#define USBPMASIZE	      1024


typedef struct
{
  __IO uint16_t EP0R;            /*!< USB Endpoint 0 register,                Address offset: 0x00 */
  __IO uint16_t RESERVED0;       /*!< Reserved */
  __IO uint16_t EP1R;            /*!< USB Endpoint 1 register,                Address offset: 0x04 */
  __IO uint16_t RESERVED1;       /*!< Reserved */
  __IO uint16_t EP2R;            /*!< USB Endpoint 2 register,                Address offset: 0x08 */
  __IO uint16_t RESERVED2;       /*!< Reserved */
  __IO uint16_t EP3R;            /*!< USB Endpoint 3 register,                Address offset: 0x0C */
  __IO uint16_t RESERVED3;       /*!< Reserved */
  __IO uint16_t EP4R;            /*!< USB Endpoint 4 register,                Address offset: 0x10 */
  __IO uint16_t RESERVED4;       /*!< Reserved */
  __IO uint16_t EP5R;            /*!< USB Endpoint 5 register,                Address offset: 0x14 */
  __IO uint16_t RESERVED5;       /*!< Reserved */
  __IO uint16_t EP6R;            /*!< USB Endpoint 6 register,                Address offset: 0x18 */
  __IO uint16_t RESERVED6;       /*!< Reserved */
  __IO uint16_t EP7R;            /*!< USB Endpoint 7 register,                Address offset: 0x1C */
  __IO uint16_t RESERVED7[17];   /*!< Reserved */
  __IO uint16_t CNTR;            /*!< Control register,                       Address offset: 0x40 */
  __IO uint16_t RESERVED8;       /*!< Reserved */
  __IO uint16_t ISTR;            /*!< Interrupt status register,              Address offset: 0x44 */
  __IO uint16_t RESERVED9;       /*!< Reserved */
  __IO uint16_t FNR;             /*!< Frame number register,                  Address offset: 0x48 */
  __IO uint16_t RESERVEDA;       /*!< Reserved */
  __IO uint16_t DADDR;           /*!< Device address register,                Address offset: 0x4C */
  __IO uint16_t RESERVEDB;       /*!< Reserved */
  __IO uint16_t BTABLE;          /*!< Buffer Table address register,          Address offset: 0x50 */
  __IO uint16_t RESERVEDC;       /*!< Reserved */
  __IO uint16_t LPMCSR;          /*!< LPM Control and Status register,        Address offset: 0x54 */
  __IO uint16_t RESERVEDD;       /*!< Reserved */
  __IO uint16_t BCDR;            /*!< Battery Charging detector register,     Address offset: 0x58 */
  __IO uint16_t RESERVEDE;       /*!< Reserved */
} USB_TypeDef;


struct bufdesc {
    uint16_t addr;
    uint16_t count;
};

typedef struct {
    struct {
        struct bufdesc tx;
        struct bufdesc rx;
    } desc[N_ENDPOINT];
} USB_BufferDescr;



#define USB_BASE              (APB1PERIPH_BASE + 0x6800U)  /*!< USB_IP Peripheral Registers base address */
#define USB_PMAADDR           (APB1PERIPH_BASE + 0x6C00U)  /*!< USB_IP Packet Memory Area base address */

#define USB                   ((USB_TypeDef *) USB_BASE)
#define USBPMA		      ((USB_BufferDescr *)USB_PMAADDR)

/****************************************************************/

/* bit positions */
#define USB_EP_CTR_RX                            ((uint16_t)0x8000U)           /*!<  EndPoint Correct TRansfer RX */
#define USB_EP_DTOG_RX                           ((uint16_t)0x4000U)           /*!<  EndPoint Data TOGGLE RX */
#define USB_EPRX_STAT                            ((uint16_t)0x3000U)           /*!<  EndPoint RX STATus bit field */
#define USB_EP_SETUP                             ((uint16_t)0x0800U)           /*!<  EndPoint SETUP */
#define USB_EP_T_FIELD                           ((uint16_t)0x0600U)           /*!<  EndPoint TYPE */
#define USB_EP_KIND                              ((uint16_t)0x0100U)           /*!<  EndPoint KIND */
#define USB_EP_CTR_TX                            ((uint16_t)0x0080U)           /*!<  EndPoint Correct TRansfer TX */
#define USB_EP_DTOG_TX                           ((uint16_t)0x0040U)           /*!<  EndPoint Data TOGGLE TX */
#define USB_EPTX_STAT                            ((uint16_t)0x0030U)           /*!<  EndPoint TX STATus bit field */
#define USB_EPADDR_FIELD                         ((uint16_t)0x000FU)           /*!<  EndPoint ADDRess FIELD */

/* EndPoint REGister MASK (no toggle fields) */
#define USB_EPREG_MASK     (USB_EP_CTR_RX|USB_EP_SETUP|USB_EP_T_FIELD|USB_EP_KIND|USB_EP_CTR_TX|USB_EPADDR_FIELD)
                                                                         /*!< EP_TYPE[1:0] EndPoint TYPE */
#define USB_EP_TYPE_MASK                         ((uint16_t)0x0600U)           /*!< EndPoint TYPE Mask */
#define USB_EP_BULK                              ((uint16_t)0x0000U)           /*!< EndPoint BULK */
#define USB_EP_CONTROL                           ((uint16_t)0x0200U)           /*!< EndPoint CONTROL */
#define USB_EP_ISOCHRONOUS                       ((uint16_t)0x0400U)           /*!< EndPoint ISOCHRONOUS */
#define USB_EP_INTERRUPT                         ((uint16_t)0x0600U)           /*!< EndPoint INTERRUPT */
#define USB_EP_T_MASK                        ((uint16_t) ~USB_EP_T_FIELD & USB_EPREG_MASK)

#define USB_EPKIND_MASK                      ((uint16_t)~USB_EP_KIND & USB_EPREG_MASK) /*!< EP_KIND EndPoint KIND */
                                                                         /*!< STAT_TX[1:0] STATus for TX transfer */
#define USB_EP_TX_DIS                            ((uint16_t)0x0000U)           /*!< EndPoint TX DISabled */
#define USB_EP_TX_STALL                          ((uint16_t)0x0010U)           /*!< EndPoint TX STALLed */
#define USB_EP_TX_NAK                            ((uint16_t)0x0020U)           /*!< EndPoint TX NAKed */
#define USB_EP_TX_VALID                          ((uint16_t)0x0030U)           /*!< EndPoint TX VALID */
#define USB_EPTX_DTOG1                           ((uint16_t)0x0010U)           /*!< EndPoint TX Data TOGgle bit1 */
#define USB_EPTX_DTOG2                           ((uint16_t)0x0020U)           /*!< EndPoint TX Data TOGgle bit2 */
#define USB_EPTX_DTOGMASK  (USB_EPTX_STAT|USB_EPREG_MASK)
                                                                         /*!< STAT_RX[1:0] STATus for RX transfer */
#define USB_EP_RX_DIS                            ((uint16_t)0x0000U)           /*!< EndPoint RX DISabled */
#define USB_EP_RX_STALL                          ((uint16_t)0x1000U)           /*!< EndPoint RX STALLed */
#define USB_EP_RX_NAK                            ((uint16_t)0x2000U)           /*!< EndPoint RX NAKed */
#define USB_EP_RX_VALID                          ((uint16_t)0x3000U)           /*!< EndPoint RX VALID */
#define USB_EPRX_DTOG1                           ((uint16_t)0x1000U)           /*!< EndPoint RX Data TOGgle bit1 */
#define USB_EPRX_DTOG2                           ((uint16_t)0x2000U)           /*!< EndPoint RX Data TOGgle bit1 */
#define USB_EPRX_DTOGMASK  (USB_EPRX_STAT|USB_EPREG_MASK)

/******************  Bits definition for USB_CNTR register  *******************/
#define USB_CNTR_CTRM                            ((uint16_t)0x8000U)           /*!< Correct TRansfer Mask */
#define USB_CNTR_PMAOVRM                         ((uint16_t)0x4000U)           /*!< DMA OVeR/underrun Mask */
#define USB_CNTR_ERRM                            ((uint16_t)0x2000U)           /*!< ERRor Mask */
#define USB_CNTR_WKUPM                           ((uint16_t)0x1000U)           /*!< WaKe UP Mask */
#define USB_CNTR_SUSPM                           ((uint16_t)0x0800U)           /*!< SUSPend Mask */
#define USB_CNTR_RESETM                          ((uint16_t)0x0400U)           /*!< RESET Mask   */
#define USB_CNTR_SOFM                            ((uint16_t)0x0200U)           /*!< Start Of Frame Mask */
#define USB_CNTR_ESOFM                           ((uint16_t)0x0100U)           /*!< Expected Start Of Frame Mask */
#define USB_CNTR_L1REQM                          ((uint16_t)0x0080U)           /*!< LPM L1 state request interrupt mask */
#define USB_CNTR_L1RESUME                        ((uint16_t)0x0020U)           /*!< LPM L1 Resume request */
#define USB_CNTR_RESUME                          ((uint16_t)0x0010U)           /*!< RESUME request */
#define USB_CNTR_FSUSP                           ((uint16_t)0x0008U)           /*!< Force SUSPend */
#define USB_CNTR_LPMODE                          ((uint16_t)0x0004U)           /*!< Low-power MODE */
#define USB_CNTR_PDWN                            ((uint16_t)0x0002U)           /*!< Power DoWN */
#define USB_CNTR_FRES                            ((uint16_t)0x0001U)           /*!< Force USB RESet */

/******************  Bits definition for USB_ISTR register  *******************/
#define USB_ISTR_EP_ID                           ((uint16_t)0x000FU)           /*!< EndPoint IDentifier (read-only bit)  */
#define USB_ISTR_DIR                             ((uint16_t)0x0010U)           /*!< DIRection of transaction (read-only bit)  */
#define USB_ISTR_L1REQ                           ((uint16_t)0x0080U)           /*!< LPM L1 state request  */
#define USB_ISTR_ESOF                            ((uint16_t)0x0100U)           /*!< Expected Start Of Frame (clear-only bit) */
#define USB_ISTR_SOF                             ((uint16_t)0x0200U)           /*!< Start Of Frame (clear-only bit) */
#define USB_ISTR_RESET                           ((uint16_t)0x0400U)           /*!< RESET (clear-only bit) */
#define USB_ISTR_SUSP                            ((uint16_t)0x0800U)           /*!< SUSPend (clear-only bit) */
#define USB_ISTR_WKUP                            ((uint16_t)0x1000U)           /*!< WaKe UP (clear-only bit) */
#define USB_ISTR_ERR                             ((uint16_t)0x2000U)           /*!< ERRor (clear-only bit) */
#define USB_ISTR_PMAOVR                          ((uint16_t)0x4000U)           /*!< DMA OVeR/underrun (clear-only bit) */
#define USB_ISTR_CTR                             ((uint16_t)0x8000U)           /*!< Correct TRansfer (clear-only bit) */

#define USB_CLR_L1REQ                        (~USB_ISTR_L1REQ)           /*!< clear LPM L1  bit */
#define USB_CLR_ESOF                         (~USB_ISTR_ESOF)            /*!< clear Expected Start Of Frame bit */
#define USB_CLR_SOF                          (~USB_ISTR_SOF)             /*!< clear Start Of Frame bit */
#define USB_CLR_RESET                        (~USB_ISTR_RESET)           /*!< clear RESET bit */
#define USB_CLR_SUSP                         (~USB_ISTR_SUSP)            /*!< clear SUSPend bit */
#define USB_CLR_WKUP                         (~USB_ISTR_WKUP)            /*!< clear WaKe UP bit */
#define USB_CLR_ERR                          (~USB_ISTR_ERR)             /*!< clear ERRor bit */
#define USB_CLR_PMAOVR                       (~USB_ISTR_PMAOVR)          /*!< clear DMA OVeR/underrun bit*/
#define USB_CLR_CTR                          (~USB_ISTR_CTR)             /*!< clear Correct TRansfer bit */

/******************  Bits definition for USB_FNR register  ********************/
#define USB_FNR_FN                               ((uint16_t)0x07FFU)           /*!< Frame Number */
#define USB_FNR_LSOF                             ((uint16_t)0x1800U)           /*!< Lost SOF */
#define USB_FNR_LCK                              ((uint16_t)0x2000U)           /*!< LoCKed */
#define USB_FNR_RXDM                             ((uint16_t)0x4000U)           /*!< status of D- data line */
#define USB_FNR_RXDP                             ((uint16_t)0x8000U)           /*!< status of D+ data line */

/******************  Bits definition for USB_DADDR register    ****************/
#define USB_DADDR_ADD                            ((uint8_t)0x7FU)              /*!< ADD[6:0] bits (Device Address) */
#define USB_DADDR_ADD0                           ((uint8_t)0x01U)              /*!< Bit 0 */
#define USB_DADDR_ADD1                           ((uint8_t)0x02U)              /*!< Bit 1 */
#define USB_DADDR_ADD2                           ((uint8_t)0x04U)              /*!< Bit 2 */
#define USB_DADDR_ADD3                           ((uint8_t)0x08U)              /*!< Bit 3 */
#define USB_DADDR_ADD4                           ((uint8_t)0x10U)              /*!< Bit 4 */
#define USB_DADDR_ADD5                           ((uint8_t)0x20U)              /*!< Bit 5 */
#define USB_DADDR_ADD6                           ((uint8_t)0x40U)              /*!< Bit 6 */

#define USB_DADDR_EF                             ((uint8_t)0x80U)              /*!< Enable Function */

/******************  Bit definition for USB_BTABLE register  ******************/
#define USB_BTABLE_BTABLE                        ((uint16_t)0xFFF8U)           /*!< Buffer Table */

/******************  Bits definition for USB_BCDR register  *******************/
#define USB_BCDR_BCDEN                           ((uint16_t)0x0001U)           /*!< Battery charging detector (BCD) enable */
#define USB_BCDR_DCDEN                           ((uint16_t)0x0002U)           /*!< Data contact detection (DCD) mode enable */
#define USB_BCDR_PDEN                            ((uint16_t)0x0004U)           /*!< Primary detection (PD) mode enable */
#define USB_BCDR_SDEN                            ((uint16_t)0x0008U)           /*!< Secondary detection (SD) mode enable */
#define USB_BCDR_DCDET                           ((uint16_t)0x0010U)           /*!< Data contact detection (DCD) status */
#define USB_BCDR_PDET                            ((uint16_t)0x0020U)           /*!< Primary detection (PD) status */
#define USB_BCDR_SDET                            ((uint16_t)0x0040U)           /*!< Secondary detection (SD) status */
#define USB_BCDR_PS2DET                          ((uint16_t)0x0080U)           /*!< PS2 port or proprietary charger detected */
#define USB_BCDR_DPPU                            ((uint16_t)0x8000U)           /*!< DP Pull-up Enable */

/*******************  Bit definition for LPMCSR register  *********************/
#define USB_LPMCSR_LMPEN                         ((uint16_t)0x0001U)           /*!< LPM support enable  */
#define USB_LPMCSR_LPMACK                        ((uint16_t)0x0002U)           /*!< LPM Token acknowledge enable*/
#define USB_LPMCSR_REMWAKE                       ((uint16_t)0x0008U)           /*!< bRemoteWake value received with last ACKed LPM Token */
#define USB_LPMCSR_BESL                          ((uint16_t)0x00F0U)           /*!< BESL value received with last ACKed LPM Token  */

