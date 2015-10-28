/**
  ******************************************************************************
  * @file    stm32l1xx.h
  * @author  MCD Application Team
  * @version V1.3.3
  * @date    20-April-2015
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Header File.
  *          This file contains all the peripheral register's definitions, bits
  *          definitions and memory mapping for STM32L1xx High-density, Medium-density,
  *          Medium-density and XL-density Plus devices.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e.
  *                code will be based on direct access to peripheral’s registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_STDPERIPH_DRIVER"
  *              - To change few application-specific parameters such as the HSE
  *                crystal frequency
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral’s registers hardware
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l1xx
  * @{
  */

#ifndef __STM32L1XX_H
#define __STM32L1XX_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Library_configuration_section
  * @{
  */

/* Uncomment the line below according to the target STM32L device used in your
   application
  */

#define STM32L1XX_MD
#define STM32L1XX_MDP
#define STM32L1XX_HD
#define STM32L1XX_XL

#if !defined (STM32L1XX_MD) && !defined (STM32L1XX_MDP) && !defined (STM32L1XX_HD) && !defined (STM32L1XX_XL)

/* #define STM32L1XX_MD  */   /*!< - Ultra Low Power Medium-density devices: STM32L151x6xx, STM32L151x8xx,
                                     STM32L151xBxx, STM32L152x6xx, STM32L152x8xx, STM32L152xBxx,
                                     STM32L151x6xxA, STM32L151x8xxA, STM32L151xBxxA, STM32L152x6xxA,
                                     STM32L152x8xxA and STM32L152xBxxA.
                                   - Ultra Low Power Medium-density Value Line devices: STM32L100x6xx,
                                     STM32L100x8xx and STM32L100xBxx.  */

/* #define STM32L1XX_MDP */   /*!< - Ultra Low Power Medium-density Plus devices: STM32L151xCxx, STM32L152xCxx and STM32L162xCxx
                                   - Ultra Low Power Medium-density Plus Value Line devices: STM32L100xCxx  */

/* #define STM32L1XX_HD */     /*!< Ultra Low Power High-density devices: STM32L151xDxx, STM32L152xDxx and STM32L162xDxx */

/* #define STM32L1XX_XL */     /*!< Ultra Low Power XL-density devices: STM32L151xExx, STM32L152xExx and STM32L162xExx */
#endif
/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */

#if !defined (STM32L1XX_MD) && !defined (STM32L1XX_MDP) && !defined (STM32L1XX_HD) && !defined (STM32L1XX_XL)
 #error "Please select first the target STM32L1xx device used in your application (in stm32l1xx.h file)"
#endif

/*
  The table below provides the list of available part numbers per category, and the corresponding preprocessor
  switch to be defined in the StdLib.
  ==============================================================================================================+
   Memory density level |           RPNs                | StdLib switch | Cat.1 | Cat.2 | Cat.3 | Cat.4 | Cat.5 |
  ==============================================================================================================+
                        | STM32L100x6xx, STM32L151x6xx, |               |       |       |       |       |       |
     32KB               | STM32L152x6xx, STM32L151x6xxA | STM32L1XX_MD  |   X   |   X   |       |       |       |
                        | and STM32L152x6xxA            |               |       |       |       |       |       |
  --------------------------------------------------------------------------------------------------------------+
                        | STM32L100x8xx, STM32L151x8xx, |               |       |       |       |       |       |
     64KB               | STM32L152x8xx, STM32L151x8xxA | STM32L1XX_MD  |   X   |   X   |       |       |       |
                        | and STM32L152x8xxA            |               |       |       |       |       |       |
  --------------------------------------------------------------------------------------------------------------+
                        | STM32L100xBxx, STM32L151xBxx, |               |       |       |       |       |       |
     128KB              | STM32L152xBxx, STM32L151xBxxA | STM32L1XX_MD  |   X   |   X   |       |       |       |
                        | and STM32L152xBxxA            |               |       |       |       |       |       |
  --------------------------------------------------------------------------------------------------------------+
                        | STM32L100xCxx, STM32L151xCxx, |               |       |       |       |       |       |
     256KB              | STM32L152xCxx and             | STM32L1XX_MDP |       |       |    X  |   X   |       |
                        | STM32L162xCxx                 |               |       |       |       |       |       |
  --------------------------------------------------------------------------------------------------------------+
                        | STM32L151xDxx, STM32L152xDxx  |               |       |       |       |       |       |
     384KB              | and STM32L162xDxx             | STM32L1XX_HD  |       |       |       |   X   |       |
  --------------------------------------------------------------------------------------------------------------+
                        | STM32L151xExx, STM32L152xExx  |               |       |       |       |       |       |
     512KB              | and STM32L162xExx             | STM32L1XX_XL  |       |       |       |       |   X   |
  ==============================================================================================================+
*/

/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
 * @brief STM32L1xx Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
#define __CM3_REV                 0x200 /*!< Cortex-M3 Revision r2p0                      */
#define __MPU_PRESENT             1     /*!< STM32L1 provides MPU                         */
#define __NVIC_PRIO_BITS          4     /*!< STM32L1 uses 4 Bits for the Priority Levels  */
#define __Vendor_SysTickConfig    0     /*!< Set to 1 if different SysTick Config is used */

/*!< Interrupt Number Definition */
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ******************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt                 */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                         */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                       */
  SVC_IRQn                    = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                          */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                    */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                          */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                      */

/******  STM32L specific Interrupt Numbers ***********************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                               */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt               */
  TAMPER_STAMP_IRQn           = 2,      /*!< Tamper and Time Stamp through EXTI Line Interrupts      */
  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup Timer through EXTI Line Interrupt            */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                  */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                    */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                    */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                    */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                    */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                    */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                    */
  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                         */
  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                         */
  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                         */
  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                         */
  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                         */
  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                         */
  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                         */
  ADC1_IRQn                   = 18,     /*!< ADC1 global Interrupt                                   */
  USB_HP_IRQn                 = 19,     /*!< USB High Priority Interrupt                             */
  USB_LP_IRQn                 = 20,     /*!< USB Low Priority Interrupt                              */
  DAC_IRQn                    = 21,     /*!< DAC Interrupt                                           */
  COMP_IRQn                   = 22,     /*!< Comparator through EXTI Line Interrupt                  */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                           */
  LCD_IRQn                    = 24,     /*!< LCD Interrupt                                           */
  TIM9_IRQn                   = 25,     /*!< TIM9 global Interrupt                                   */
  TIM10_IRQn                  = 26,     /*!< TIM10 global Interrupt                                  */
  TIM11_IRQn                  = 27,     /*!< TIM11 global Interrupt                                  */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                   */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                   */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                   */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                    */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                    */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                    */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                    */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                   */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                   */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                 */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                 */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                 */
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                         */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm through EXTI Line Interrupt                   */
  USB_FS_WKUP_IRQn            = 42,     /*!< USB FS WakeUp from suspend through EXTI Line Interrupt  */
  TIM6_IRQn                   = 43,     /*!< TIM6 global Interrupt                                   */

  TIM7_IRQn                   = 44,     /*!< TIM7 global Interrupt                                   */
  SDIO_IRQn                   = 45,     /*!< SDIO global Interrupt                                   */
  TIM5_IRQn                   = 46,     /*!< TIM5 global Interrupt                                   */
  SPI3_IRQn                   = 47,     /*!< SPI3 global Interrupt                                   */
  UART4_IRQn                  = 48,     /*!< UART4 global Interrupt                                  */
  UART5_IRQn                  = 49,     /*!< UART5 global Interrupt                                  */
  DMA2_Channel1_IRQn          = 50,     /*!< DMA2 Channel 1 global Interrupt                         */
  DMA2_Channel2_IRQn          = 51,     /*!< DMA2 Channel 2 global Interrupt                         */
  DMA2_Channel3_IRQn          = 52,     /*!< DMA2 Channel 3 global Interrupt                         */
  DMA2_Channel4_IRQn          = 53,     /*!< DMA2 Channel 4 global Interrupt                         */
  DMA2_Channel5_IRQn          = 54,     /*!< DMA2 Channel 5 global Interrupt                         */
  AES_IRQn                    = 55,     /*!< AES global Interrupt                                    */
  COMP_ACQ_IRQn               = 56      /*!< Comparator Channel Acquisition global Interrupt         */

} IRQn_Type;

/**
  * @}
  */

#include "core_cm3.h"
#include <stdint.h>

/** @addtogroup Exported_types
  * @{
  */

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/**
  * @brief  __RAM_FUNC definition
  */
#if defined ( __CC_ARM   )
/* ARM Compiler
   ------------
   RAM functions are defined using the toolchain options.
   Functions that are executed in RAM should reside in a separate source module.
   Using the 'Options for File' dialog you can simply change the 'Code / Const'
   area of a module to a memory space in physical RAM.
   Available memory areas are declared in the 'Target' tab of the 'Options for Target'
   dialog.
*/
 #define __RAM_FUNC FLASH_Status

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
   RAM functions are defined using a specific toolchain keyword "__ramfunc".
*/
 #define __RAM_FUNC __ramfunc FLASH_Status

#elif defined   (  __GNUC__  )
/* GNU Compiler
   ------------
   RAM functions are defined using a specific toolchain attribute
   "__attribute__((section(".RamFunc")))".
*/
 #define __RAM_FUNC FLASH_Status __attribute__((section(".RamFunc")))

#elif defined   (  __TASKING__  )
/* TASKING Compiler
   ----------------
   RAM functions are defined using a specific toolchain pragma. This pragma is
   defined in the stm32l1xx_flash_ramfunc.c
*/
 #define __RAM_FUNC  FLASH_Status

#endif

/**
  * @}
  */

/** @addtogroup Peripheral_registers_structures
  * @{
  */

/**
  * @brief Analog to Digital Converter
  */

typedef struct
{
  __IO uint32_t SR;           /*!< ADC status register,                         Address offset: 0x00 */
  __IO uint32_t CR1;          /*!< ADC control register 1,                      Address offset: 0x04 */
  __IO uint32_t CR2;          /*!< ADC control register 2,                      Address offset: 0x08 */
  __IO uint32_t SMPR1;        /*!< ADC sample time register 1,                  Address offset: 0x0C */
  __IO uint32_t SMPR2;        /*!< ADC sample time register 2,                  Address offset: 0x10 */
  __IO uint32_t SMPR3;        /*!< ADC sample time register 3,                  Address offset: 0x14 */
  __IO uint32_t JOFR1;        /*!< ADC injected channel data offset register 1, Address offset: 0x18 */
  __IO uint32_t JOFR2;        /*!< ADC injected channel data offset register 2, Address offset: 0x1C */
  __IO uint32_t JOFR3;        /*!< ADC injected channel data offset register 3, Address offset: 0x20 */
  __IO uint32_t JOFR4;        /*!< ADC injected channel data offset register 4, Address offset: 0x24 */
  __IO uint32_t HTR;          /*!< ADC watchdog higher threshold register,      Address offset: 0x28 */
  __IO uint32_t LTR;          /*!< ADC watchdog lower threshold register,       Address offset: 0x2C */
  __IO uint32_t SQR1;         /*!< ADC regular sequence register 1,             Address offset: 0x30 */
  __IO uint32_t SQR2;         /*!< ADC regular sequence register 2,             Address offset: 0x34 */
  __IO uint32_t SQR3;         /*!< ADC regular sequence register 3,             Address offset: 0x38 */
  __IO uint32_t SQR4;         /*!< ADC regular sequence register 4,             Address offset: 0x3C */
  __IO uint32_t SQR5;         /*!< ADC regular sequence register 5,             Address offset: 0x40 */
  __IO uint32_t JSQR;         /*!< ADC injected sequence register,              Address offset: 0x44 */
  __IO uint32_t JDR1;         /*!< ADC injected data register 1,                Address offset: 0x48 */
  __IO uint32_t JDR2;         /*!< ADC injected data register 2,                Address offset: 0x4C */
  __IO uint32_t JDR3;         /*!< ADC injected data register 3,                Address offset: 0x50 */
  __IO uint32_t JDR4;         /*!< ADC injected data register 4,                Address offset: 0x54 */
  __IO uint32_t DR;           /*!< ADC regular data register,                   Address offset: 0x58 */
  __IO uint32_t SMPR0;        /*!< ADC sample time register 0,                  Address offset: 0x5C */
} ADC_TypeDef;

typedef struct
{
  __IO uint32_t CSR;          /*!< ADC common status register,                  Address offset: ADC1 base address + 0x300 */
  __IO uint32_t CCR;          /*!< ADC common control register,                 Address offset: ADC1 base address + 0x304 */
} ADC_Common_TypeDef;


/**
  * @brief AES hardware accelerator
  */

typedef struct
{
  __IO uint32_t CR;           /*!< AES control register,                        Address offset: 0x00 */
  __IO uint32_t SR;           /*!< AES status register,                         Address offset: 0x04 */
  __IO uint32_t DINR;         /*!< AES data input register,                     Address offset: 0x08 */
  __IO uint32_t DOUTR;        /*!< AES data output register,                    Address offset: 0x0C */
  __IO uint32_t KEYR0;        /*!< AES key register 0,                          Address offset: 0x10 */
  __IO uint32_t KEYR1;        /*!< AES key register 1,                          Address offset: 0x14 */
  __IO uint32_t KEYR2;        /*!< AES key register 2,                          Address offset: 0x18 */
  __IO uint32_t KEYR3;        /*!< AES key register 3,                          Address offset: 0x1C */
  __IO uint32_t IVR0;         /*!< AES initialization vector register 0,        Address offset: 0x20 */
  __IO uint32_t IVR1;         /*!< AES initialization vector register 1,        Address offset: 0x24 */
  __IO uint32_t IVR2;         /*!< AES initialization vector register 2,        Address offset: 0x28 */
  __IO uint32_t IVR3;         /*!< AES initialization vector register 3,        Address offset: 0x2C */
} AES_TypeDef;

/**
  * @brief Comparator
  */

typedef struct
{
  __IO uint32_t CSR;          /*!< COMP comparator control and status register, Address offset: 0x00 */
} COMP_TypeDef;

/**
  * @brief CRC calculation unit
  */

typedef struct
{
  __IO uint32_t DR;           /*!< CRC Data register,                           Address offset: 0x00 */
  __IO uint8_t  IDR;          /*!< CRC Independent data register,               Address offset: 0x04 */
  uint8_t   RESERVED0;        /*!< Reserved,                                    0x05                 */
  uint16_t  RESERVED1;        /*!< Reserved,                                    0x06                 */
  __IO uint32_t CR;           /*!< CRC Control register,                        Address offset: 0x08 */
} CRC_TypeDef;

/**
  * @brief Digital to Analog Converter
  */

typedef struct
{
  __IO uint32_t CR;           /*!< DAC control register,                                     Address offset: 0x00 */
  __IO uint32_t SWTRIGR;      /*!< DAC software trigger register,                            Address offset: 0x04 */
  __IO uint32_t DHR12R1;      /*!< DAC channel1 12-bit right-aligned data holding register,  Address offset: 0x08 */
  __IO uint32_t DHR12L1;      /*!< DAC channel1 12-bit left aligned data holding register,   Address offset: 0x0C */
  __IO uint32_t DHR8R1;       /*!< DAC channel1 8-bit right aligned data holding register,   Address offset: 0x10 */
  __IO uint32_t DHR12R2;      /*!< DAC channel2 12-bit right aligned data holding register,  Address offset: 0x14 */
  __IO uint32_t DHR12L2;      /*!< DAC channel2 12-bit left aligned data holding register,   Address offset: 0x18 */
  __IO uint32_t DHR8R2;       /*!< DAC channel2 8-bit right-aligned data holding register,   Address offset: 0x1C */
  __IO uint32_t DHR12RD;      /*!< Dual DAC 12-bit right-aligned data holding register,      Address offset: 0x20 */
  __IO uint32_t DHR12LD;      /*!< DUAL DAC 12-bit left aligned data holding register,       Address offset: 0x24 */
  __IO uint32_t DHR8RD;       /*!< DUAL DAC 8-bit right aligned data holding register,       Address offset: 0x28 */
  __IO uint32_t DOR1;         /*!< DAC channel1 data output register,                        Address offset: 0x2C */
  __IO uint32_t DOR2;         /*!< DAC channel2 data output register,                        Address offset: 0x30 */
  __IO uint32_t SR;           /*!< DAC status register,                                      Address offset: 0x34 */
} DAC_TypeDef;

/**
  * @brief Debug MCU
  */

typedef struct
{
  __IO uint32_t IDCODE;       /*!< MCU device ID code,                          Address offset: 0x00 */
  __IO uint32_t CR;           /*!< Debug MCU configuration register,            Address offset: 0x04 */
  __IO uint32_t APB1FZ;       /*!< Debug MCU APB1 freeze register,              Address offset: 0x08 */
  __IO uint32_t APB2FZ;       /*!< Debug MCU APB2 freeze register,              Address offset: 0x0C */
}DBGMCU_TypeDef;

/**
  * @brief DMA Controller
  */

typedef struct
{
  __IO uint32_t CCR;          /*!< DMA channel x configuration register        */
  __IO uint32_t CNDTR;        /*!< DMA channel x number of data register       */
  __IO uint32_t CPAR;         /*!< DMA channel x peripheral address register   */
  __IO uint32_t CMAR;         /*!< DMA channel x memory address register       */
} DMA_Channel_TypeDef;

typedef struct
{
  __IO uint32_t ISR;          /*!< DMA interrupt status register,               Address offset: 0x00 */
  __IO uint32_t IFCR;         /*!< DMA interrupt flag clear register,           Address offset: 0x04 */
} DMA_TypeDef;

/**
  * @brief External Interrupt/Event Controller
  */

typedef struct
{
  __IO uint32_t IMR;          /*!< EXTI interrupt mask register,                 Address offset: 0x00 */
  __IO uint32_t EMR;          /*!< EXTI event mask register,                     Address offset: 0x04 */
  __IO uint32_t RTSR;         /*!< EXTI rising edge trigger selection register,  Address offset: 0x08 */
  __IO uint32_t FTSR;         /*!< EXTI Falling edge trigger selection register, Address offset: 0x0C */
  __IO uint32_t SWIER;        /*!< EXTI software interrupt event register,       Address offset: 0x10 */
  __IO uint32_t PR;           /*!< EXTI pending register,                        Address offset: 0x14 */
} EXTI_TypeDef;

/**
  * @brief FLASH Registers
  */

typedef struct
{
  __IO uint32_t ACR;          /*!< Access control register,                     Address offset: 0x00 */
  __IO uint32_t PECR;         /*!< Program/erase control register,              Address offset: 0x04 */
  __IO uint32_t PDKEYR;       /*!< Power down key register,                     Address offset: 0x08 */
  __IO uint32_t PEKEYR;       /*!< Program/erase key register,                  Address offset: 0x0c */
  __IO uint32_t PRGKEYR;      /*!< Program memory key register,                 Address offset: 0x10 */
  __IO uint32_t OPTKEYR;      /*!< Option byte key register,                    Address offset: 0x14 */
  __IO uint32_t SR;           /*!< Status register,                             Address offset: 0x18 */
  __IO uint32_t OBR;          /*!< Option byte register,                        Address offset: 0x1c */
  __IO uint32_t WRPR;         /*!< Write protection register,                   Address offset: 0x20 */
  uint32_t   RESERVED[23];    /*!< Reserved,                                    0x24-0x7C            */
  __IO uint32_t WRPR1;        /*!< Write protection register 1,                 Address offset: 0x80 */
  __IO uint32_t WRPR2;        /*!< Write protection register 2,                 Address offset: 0x84 */
  __IO uint32_t WRPR3;        /*!< Write protection register 3,                 Address offset: 0x88 */
} FLASH_TypeDef;
/* IMPORTANT NOTE
   ==============
    In the StdLib, the naming of WRP registers is shifted vs. the Reference Manual:
      - WRPR correspond to WRPR1
      - WRPR1 correspond to WRPR2
      - WRPR2 correspond to WRPR3
      - WRPR3 correspond to WRPR4
  */

/**
  * @brief Option Bytes Registers
  */

typedef struct
{
  __IO uint32_t RDP;               /*!< Read protection register,               Address offset: 0x00 */
  __IO uint32_t USER;              /*!< user register,                          Address offset: 0x04 */
  __IO uint32_t WRP01;             /*!< write protection register 0 1,          Address offset: 0x08 */
  __IO uint32_t WRP23;             /*!< write protection register 2 3,          Address offset: 0x0C */
  __IO uint32_t WRP45;             /*!< write protection register 4 5,          Address offset: 0x10 */
  __IO uint32_t WRP67;             /*!< write protection register 6 7,          Address offset: 0x14 */
  __IO uint32_t WRP89;             /*!< write protection register 8 9,          Address offset: 0x18 */
  __IO uint32_t WRP1011;           /*!< write protection register 10 11,        Address offset: 0x1C */
  uint32_t   RESERVED[24];         /*!< Reserved,                               0x20-0x7C            */
  __IO uint32_t WRP1213;           /*!< write protection register 12 13,        Address offset: 0x80 */
  __IO uint32_t WRP1415;           /*!< write protection register 14 15,        Address offset: 0x84 */
} OB_TypeDef;

/**
  * @brief Operational Amplifier (OPAMP)
  */

typedef struct
{
  __IO uint32_t CSR;          /*!< OPAMP control/status register,                     Address offset: 0x00 */
  __IO uint32_t OTR;          /*!< OPAMP offset trimming register for normal mode,    Address offset: 0x04 */
  __IO uint32_t LPOTR;        /*!< OPAMP offset trimming register for low power mode, Address offset: 0x08 */
} OPAMP_TypeDef;

/**
  * @brief Flexible Static Memory Controller
  */

typedef struct
{
  __IO uint32_t BTCR[8];      /*!< NOR/PSRAM chip-select control register(BCR) and chip-select timing register(BTR), Address offset: 0x00-1C */
} FSMC_Bank1_TypeDef;

/**
  * @brief Flexible Static Memory Controller Bank1E
  */

typedef struct
{
  __IO uint32_t BWTR[7];      /*!< NOR/PSRAM write timing registers, Address offset: 0x104-0x11C */
} FSMC_Bank1E_TypeDef;

/**
  * @brief General Purpose IO
  */

typedef struct
{
  __IO uint32_t MODER;        /*!< GPIO port mode register,                     Address offset: 0x00      */
  __IO uint16_t OTYPER;       /*!< GPIO port output type register,              Address offset: 0x04      */
  uint16_t RESERVED0;         /*!< Reserved,                                    0x06                      */
  __IO uint32_t OSPEEDR;      /*!< GPIO port output speed register,             Address offset: 0x08      */
  __IO uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,        Address offset: 0x0C      */
  __IO uint16_t IDR;          /*!< GPIO port input data register,               Address offset: 0x10      */
  uint16_t RESERVED1;         /*!< Reserved,                                    0x12                      */
  __IO uint16_t ODR;          /*!< GPIO port output data register,              Address offset: 0x14      */
  uint16_t RESERVED2;         /*!< Reserved,                                    0x16                      */
  __IO uint32_t BSRR;         /*!< GPIO port bit set/reset low registerBSRR,    Address offset: 0x18      */
  __IO uint32_t LCKR;         /*!< GPIO port configuration lock register,       Address offset: 0x1C      */
  __IO uint32_t AFRL;         /*!< GPIO alternate function low register,        Address offset: 0x20-0x24 */
  __IO uint32_t AFRH;         /*!< GPIO alternate function low register,        Address offset: 0x20-0x24 */

  __IO uint16_t BRR;          /*!< GPIO bit reset register,                     Address offset: 0x28      */
  uint16_t RESERVED3;         /*!< Reserved,                                    0x2A                      */

} GPIO_TypeDef;

/**
  * @brief SysTem Configuration
  */

typedef struct
{
  __IO uint32_t MEMRMP;       /*!< SYSCFG memory remap register,                      Address offset: 0x00      */
  __IO uint32_t PMC;          /*!< SYSCFG peripheral mode configuration register,     Address offset: 0x04      */
  __IO uint32_t EXTICR[4];    /*!< SYSCFG external interrupt configuration registers, Address offset: 0x08-0x14 */
} SYSCFG_TypeDef;

/**
  * @brief Inter-integrated Circuit Interface
  */

typedef struct
{
  __IO uint16_t CR1;          /*!< I2C Control register 1,                      Address offset: 0x00 */
  uint16_t  RESERVED0;        /*!< Reserved,                                    0x02                 */
  __IO uint16_t CR2;          /*!< I2C Control register 2,                      Address offset: 0x04 */
  uint16_t  RESERVED1;        /*!< Reserved,                                    0x06                 */
  __IO uint16_t OAR1;         /*!< I2C Own address register 1,                  Address offset: 0x08 */
  uint16_t  RESERVED2;        /*!< Reserved,                                    0x0A                 */
  __IO uint16_t OAR2;         /*!< I2C Own address register 2,                  Address offset: 0x0C */
  uint16_t  RESERVED3;        /*!< Reserved,                                    0x0E                 */
  __IO uint16_t DR;           /*!< I2C Data register,                           Address offset: 0x10 */
  uint16_t  RESERVED4;        /*!< Reserved,                                    0x12                 */
  __IO uint16_t SR1;          /*!< I2C Status register 1,                       Address offset: 0x14 */
  uint16_t  RESERVED5;        /*!< Reserved,                                    0x16                 */
  __IO uint16_t SR2;          /*!< I2C Status register 2,                       Address offset: 0x18 */
  uint16_t  RESERVED6;        /*!< Reserved,                                    0x1A                 */
  __IO uint16_t CCR;          /*!< I2C Clock control register,                  Address offset: 0x1C */
  uint16_t  RESERVED7;        /*!< Reserved,                                    0x1E                 */
  __IO uint16_t TRISE;        /*!< I2C TRISE register,                          Address offset: 0x20 */
  uint16_t  RESERVED8;        /*!< Reserved,                                    0x22                 */
} I2C_TypeDef;

/**
  * @brief Independent WATCHDOG
  */

typedef struct
{
  __IO uint32_t KR;           /*!< Key register,                                Address offset: 0x00 */
  __IO uint32_t PR;           /*!< Prescaler register,                          Address offset: 0x04 */
  __IO uint32_t RLR;          /*!< Reload register,                             Address offset: 0x08 */
  __IO uint32_t SR;           /*!< Status register,                             Address offset: 0x0C */
} IWDG_TypeDef;


/**
  * @brief LCD
  */

typedef struct
{
  __IO uint32_t CR;        /*!< LCD control register,              Address offset: 0x00 */
  __IO uint32_t FCR;       /*!< LCD frame control register,        Address offset: 0x04 */
  __IO uint32_t SR;        /*!< LCD status register,               Address offset: 0x08 */
  __IO uint32_t CLR;       /*!< LCD clear register,                Address offset: 0x0C */
  uint32_t RESERVED;       /*!< Reserved,                          Address offset: 0x10 */
  __IO uint32_t RAM[16];   /*!< LCD display memory,           Address offset: 0x14-0x50 */
} LCD_TypeDef;

/**
  * @brief Power Control
  */

typedef struct
{
  __IO uint32_t CR;   /*!< PWR power control register,        Address offset: 0x00 */
  __IO uint32_t CSR;  /*!< PWR power control/status register, Address offset: 0x04 */
} PWR_TypeDef;

/**
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t CR;            /*!< RCC clock control register,                                   Address offset: 0x00 */
  __IO uint32_t ICSCR;         /*!< RCC Internal clock sources calibration register,              Address offset: 0x04 */
  __IO uint32_t CFGR;          /*!< RCC Clock configuration register,                             Address offset: 0x08 */
  __IO uint32_t CIR;           /*!< RCC Clock interrupt register,                                 Address offset: 0x0C */
  __IO uint32_t AHBRSTR;       /*!< RCC AHB peripheral reset register,                            Address offset: 0x10 */
  __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           Address offset: 0x14 */
  __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           Address offset: 0x18 */
  __IO uint32_t AHBENR;        /*!< RCC AHB peripheral clock enable register,                     Address offset: 0x1C */
  __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                    Address offset: 0x20 */
  __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                    Address offset: 0x24 */
  __IO uint32_t AHBLPENR;      /*!< RCC AHB peripheral clock enable in low power mode register,   Address offset: 0x28 */
  __IO uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register,  Address offset: 0x2C */
  __IO uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register,  Address offset: 0x30 */
  __IO uint32_t CSR;           /*!< RCC Control/status register,                                  Address offset: 0x34 */
} RCC_TypeDef;

/**
  * @brief Routing Interface
  */

typedef struct
{
  __IO uint32_t ICR;       /*!< RI input capture register,                           Address offset: 0x04 */
  __IO uint32_t ASCR1;     /*!< RI analog switches control register,                 Address offset: 0x08 */
  __IO uint32_t ASCR2;     /*!< RI analog switch control register 2,                 Address offset: 0x0C */
  __IO uint32_t HYSCR1;    /*!< RI hysteresis control register 1,                    Address offset: 0x10 */
  __IO uint32_t HYSCR2;    /*!< RI Hysteresis control register 2,                    Address offset: 0x14 */
  __IO uint32_t HYSCR3;    /*!< RI Hysteresis control register 3,                    Address offset: 0x18 */
  __IO uint32_t HYSCR4;    /*!< RI Hysteresis control register 4,                    Address offset: 0x1C */
  __IO uint32_t ASMR1;     /*!< RI Analog switch mode register 1,                    Address offset: 0x20 */
  __IO uint32_t CMR1;      /*!< RI Channel mask register 1,                          Address offset: 0x24 */
  __IO uint32_t CICR1;     /*!< RI Channel identification for capture register 1,    Address offset: 0x28 */
  __IO uint32_t ASMR2;     /*!< RI Analog switch mode register 2,                    Address offset: 0x2C */
  __IO uint32_t CMR2;      /*!< RI Channel mask register 2,                          Address offset: 0x30 */
  __IO uint32_t CICR2;     /*!< RI Channel identification for capture register 2,    Address offset: 0x34 */
  __IO uint32_t ASMR3;     /*!< RI Analog switch mode register 3,                    Address offset: 0x38 */
  __IO uint32_t CMR3;      /*!< RI Channel mask register 3,                          Address offset: 0x3C */
  __IO uint32_t CICR3;     /*!< RI Channel identification for capture register3 ,    Address offset: 0x40 */
  __IO uint32_t ASMR4;     /*!< RI Analog switch mode register 4,                    Address offset: 0x44 */
  __IO uint32_t CMR4;      /*!< RI Channel mask register 4,                          Address offset: 0x48 */
  __IO uint32_t CICR4;     /*!< RI Channel identification for capture register 4,    Address offset: 0x4C */
  __IO uint32_t ASMR5;     /*!< RI Analog switch mode register 5,                    Address offset: 0x50 */
  __IO uint32_t CMR5;      /*!< RI Channel mask register 5,                          Address offset: 0x54 */
  __IO uint32_t CICR5;     /*!< RI Channel identification for capture register 5,    Address offset: 0x58 */
} RI_TypeDef;

/**
  * @brief Real-Time Clock
  */

typedef struct
{
  __IO uint32_t TR;         /*!< RTC time register,                                         Address offset: 0x00 */
  __IO uint32_t DR;         /*!< RTC date register,                                         Address offset: 0x04 */
  __IO uint32_t CR;         /*!< RTC control register,                                      Address offset: 0x08 */
  __IO uint32_t ISR;        /*!< RTC initialization and status register,                    Address offset: 0x0C */
  __IO uint32_t PRER;       /*!< RTC prescaler register,                                    Address offset: 0x10 */
  __IO uint32_t WUTR;       /*!< RTC wakeup timer register,                                 Address offset: 0x14 */
  __IO uint32_t CALIBR;     /*!< RTC calibration register,                                  Address offset: 0x18 */
  __IO uint32_t ALRMAR;     /*!< RTC alarm A register,                                      Address offset: 0x1C */
  __IO uint32_t ALRMBR;     /*!< RTC alarm B register,                                      Address offset: 0x20 */
  __IO uint32_t WPR;        /*!< RTC write protection register,                             Address offset: 0x24 */
  __IO uint32_t SSR;        /*!< RTC sub second register,                                   Address offset: 0x28 */
  __IO uint32_t SHIFTR;     /*!< RTC shift control register,                                Address offset: 0x2C */
  __IO uint32_t TSTR;       /*!< RTC time stamp time register,                              Address offset: 0x30 */
  __IO uint32_t TSDR;       /*!< RTC time stamp date register,                              Address offset: 0x34 */
  __IO uint32_t TSSSR;      /*!< RTC time-stamp sub second register,                        Address offset: 0x38 */
  __IO uint32_t CALR;       /*!< RRTC calibration register,                                 Address offset: 0x3C */
  __IO uint32_t TAFCR;      /*!< RTC tamper and alternate function configuration register,  Address offset: 0x40 */
  __IO uint32_t ALRMASSR;   /*!< RTC alarm A sub second register,                           Address offset: 0x44 */
  __IO uint32_t ALRMBSSR;   /*!< RTC alarm B sub second register,                           Address offset: 0x48 */
  uint32_t RESERVED7;       /*!< Reserved, 0x4C                                                                  */
  __IO uint32_t BKP0R;      /*!< RTC backup register 0,                                     Address offset: 0x50 */
  __IO uint32_t BKP1R;      /*!< RTC backup register 1,                                     Address offset: 0x54 */
  __IO uint32_t BKP2R;      /*!< RTC backup register 2,                                     Address offset: 0x58 */
  __IO uint32_t BKP3R;      /*!< RTC backup register 3,                                     Address offset: 0x5C */
  __IO uint32_t BKP4R;      /*!< RTC backup register 4,                                     Address offset: 0x60 */
  __IO uint32_t BKP5R;      /*!< RTC backup register 5,                                     Address offset: 0x64 */
  __IO uint32_t BKP6R;      /*!< RTC backup register 6,                                     Address offset: 0x68 */
  __IO uint32_t BKP7R;      /*!< RTC backup register 7,                                     Address offset: 0x6C */
  __IO uint32_t BKP8R;      /*!< RTC backup register 8,                                     Address offset: 0x70 */
  __IO uint32_t BKP9R;      /*!< RTC backup register 9,                                     Address offset: 0x74 */
  __IO uint32_t BKP10R;     /*!< RTC backup register 10,                                    Address offset: 0x78 */
  __IO uint32_t BKP11R;     /*!< RTC backup register 11,                                    Address offset: 0x7C */
  __IO uint32_t BKP12R;     /*!< RTC backup register 12,                                    Address offset: 0x80 */
  __IO uint32_t BKP13R;     /*!< RTC backup register 13,                                    Address offset: 0x84 */
  __IO uint32_t BKP14R;     /*!< RTC backup register 14,                                    Address offset: 0x88 */
  __IO uint32_t BKP15R;     /*!< RTC backup register 15,                                    Address offset: 0x8C */
  __IO uint32_t BKP16R;     /*!< RTC backup register 16,                                    Address offset: 0x90 */
  __IO uint32_t BKP17R;     /*!< RTC backup register 17,                                    Address offset: 0x94 */
  __IO uint32_t BKP18R;     /*!< RTC backup register 18,                                    Address offset: 0x98 */
  __IO uint32_t BKP19R;     /*!< RTC backup register 19,                                    Address offset: 0x9C */
  __IO uint32_t BKP20R;     /*!< RTC backup register 20,                                    Address offset: 0xA0 */
  __IO uint32_t BKP21R;     /*!< RTC backup register 21,                                    Address offset: 0xA4 */
  __IO uint32_t BKP22R;     /*!< RTC backup register 22,                                    Address offset: 0xA8 */
  __IO uint32_t BKP23R;     /*!< RTC backup register 23,                                    Address offset: 0xAC */
  __IO uint32_t BKP24R;     /*!< RTC backup register 24,                                    Address offset: 0xB0 */
  __IO uint32_t BKP25R;     /*!< RTC backup register 25,                                    Address offset: 0xB4 */
  __IO uint32_t BKP26R;     /*!< RTC backup register 26,                                    Address offset: 0xB8 */
  __IO uint32_t BKP27R;     /*!< RTC backup register 27,                                    Address offset: 0xBC */
  __IO uint32_t BKP28R;     /*!< RTC backup register 28,                                    Address offset: 0xC0 */
  __IO uint32_t BKP29R;     /*!< RTC backup register 29,                                    Address offset: 0xC4 */
  __IO uint32_t BKP30R;     /*!< RTC backup register 30,                                    Address offset: 0xC8 */
  __IO uint32_t BKP31R;     /*!< RTC backup register 31,                                    Address offset: 0xCC */
} RTC_TypeDef;

/**
  * @brief SD host Interface
  */

typedef struct
{
  __IO uint32_t POWER;          /*!< SDIO power control register,    Address offset: 0x00 */
  __IO uint32_t CLKCR;          /*!< SDI clock control register,     Address offset: 0x04 */
  __IO uint32_t ARG;            /*!< SDIO argument register,         Address offset: 0x08 */
  __IO uint32_t CMD;            /*!< SDIO command register,          Address offset: 0x0C */
  __I uint32_t  RESPCMD;        /*!< SDIO command response register, Address offset: 0x10 */
  __I uint32_t  RESP1;          /*!< SDIO response 1 register,       Address offset: 0x14 */
  __I uint32_t  RESP2;          /*!< SDIO response 2 register,       Address offset: 0x18 */
  __I uint32_t  RESP3;          /*!< SDIO response 3 register,       Address offset: 0x1C */
  __I uint32_t  RESP4;          /*!< SDIO response 4 register,       Address offset: 0x20 */
  __IO uint32_t DTIMER;         /*!< SDIO data timer register,       Address offset: 0x24 */
  __IO uint32_t DLEN;           /*!< SDIO data length register,      Address offset: 0x28 */
  __IO uint32_t DCTRL;          /*!< SDIO data control register,     Address offset: 0x2C */
  __I uint32_t  DCOUNT;         /*!< SDIO data counter register,     Address offset: 0x30 */
  __I uint32_t  STA;            /*!< SDIO status register,           Address offset: 0x34 */
  __IO uint32_t ICR;            /*!< SDIO interrupt clear register,  Address offset: 0x38 */
  __IO uint32_t MASK;           /*!< SDIO mask register,             Address offset: 0x3C */
  uint32_t      RESERVED0[2];   /*!< Reserved, 0x40-0x44                                  */
  __I uint32_t  FIFOCNT;        /*!< SDIO FIFO counter register,     Address offset: 0x48 */
  uint32_t      RESERVED1[13];  /*!< Reserved, 0x4C-0x7C                                  */
  __IO uint32_t FIFO;           /*!< SDIO data FIFO register,        Address offset: 0x80 */
} SDIO_TypeDef;

/**
  * @brief Serial Peripheral Interface
  */

typedef struct
{
  __IO uint16_t CR1;        /*!< SPI control register 1 (not used in I2S mode),      Address offset: 0x00 */
  uint16_t      RESERVED0;  /*!< Reserved, 0x02                                                           */
  __IO uint16_t CR2;        /*!< SPI control register 2,                             Address offset: 0x04 */
  uint16_t      RESERVED1;  /*!< Reserved, 0x06                                                           */
  __IO uint16_t SR;         /*!< SPI status register,                                Address offset: 0x08 */
  uint16_t      RESERVED2;  /*!< Reserved, 0x0A                                                           */
  __IO uint16_t DR;         /*!< SPI data register,                                  Address offset: 0x0C */
  uint16_t      RESERVED3;  /*!< Reserved, 0x0E                                                           */
  __IO uint16_t CRCPR;      /*!< SPI CRC polynomial register (not used in I2S mode), Address offset: 0x10 */
  uint16_t      RESERVED4;  /*!< Reserved, 0x12                                                           */
  __IO uint16_t RXCRCR;     /*!< SPI RX CRC register (not used in I2S mode),         Address offset: 0x14 */
  uint16_t      RESERVED5;  /*!< Reserved, 0x16                                                           */
  __IO uint16_t TXCRCR;     /*!< SPI TX CRC register (not used in I2S mode),         Address offset: 0x18 */
  uint16_t      RESERVED6;  /*!< Reserved, 0x1A                                                           */
  __IO uint16_t I2SCFGR;    /*!< SPI_I2S configuration register,                     Address offset: 0x1C */
  uint16_t      RESERVED7;  /*!< Reserved, 0x1E                                                           */
  __IO uint16_t I2SPR;      /*!< SPI_I2S prescaler register,                         Address offset: 0x20 */
  uint16_t      RESERVED8;  /*!< Reserved, 0x22                                                           */
} SPI_TypeDef;

/**
  * @brief TIM
  */

typedef struct
{
  __IO uint16_t CR1;          /*!< TIM control register 1,              Address offset: 0x00 */
  uint16_t      RESERVED0;    /*!< Reserved, 0x02                                            */
  __IO uint16_t CR2;          /*!< TIM control register 2,              Address offset: 0x04 */
  uint16_t      RESERVED1;    /*!< Reserved, 0x06                                            */
  __IO uint16_t SMCR;         /*!< TIM slave mode control register,     Address offset: 0x08 */
  uint16_t      RESERVED2;    /*!< Reserved, 0x0A                                            */
  __IO uint16_t DIER;         /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
  uint16_t      RESERVED3;    /*!< Reserved, 0x0E                                            */
  __IO uint16_t SR;           /*!< TIM status register,                 Address offset: 0x10 */
  uint16_t      RESERVED4;    /*!< Reserved, 0x12                                            */
  __IO uint16_t EGR;          /*!< TIM event generation register,       Address offset: 0x14 */
  uint16_t      RESERVED5;    /*!< Reserved, 0x16                                            */
  __IO uint16_t CCMR1;        /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
  uint16_t      RESERVED6;    /*!< Reserved, 0x1A                                            */
  __IO uint16_t CCMR2;        /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
  uint16_t      RESERVED7;    /*!< Reserved, 0x1E                                            */
  __IO uint16_t CCER;         /*!< TIM capture/compare enable register, Address offset: 0x20 */
  uint16_t      RESERVED8;    /*!< Reserved, 0x22                                            */
  __IO uint32_t CNT;          /*!< TIM counter register,                Address offset: 0x24 */
  __IO uint16_t PSC;          /*!< TIM prescaler,                       Address offset: 0x28 */
  uint16_t      RESERVED10;   /*!< Reserved, 0x2A                                            */
  __IO uint32_t ARR;          /*!< TIM auto-reload register,            Address offset: 0x2C */
  uint32_t      RESERVED12;   /*!< Reserved, 0x30                                            */
  __IO uint32_t CCR1;         /*!< TIM capture/compare register 1,      Address offset: 0x34 */
  __IO uint32_t CCR2;         /*!< TIM capture/compare register 2,      Address offset: 0x38 */
  __IO uint32_t CCR3;         /*!< TIM capture/compare register 3,      Address offset: 0x3C */
  __IO uint32_t CCR4;         /*!< TIM capture/compare register 4,      Address offset: 0x40 */
  uint32_t      RESERVED17;   /*!< Reserved, 0x44                                            */
  __IO uint16_t DCR;          /*!< TIM DMA control register,            Address offset: 0x48 */
  uint16_t      RESERVED18;   /*!< Reserved, 0x4A                                            */
  __IO uint16_t DMAR;         /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
  uint16_t      RESERVED19;   /*!< Reserved, 0x4E                                            */
  __IO uint16_t OR;           /*!< TIM option register,                 Address offset: 0x50 */
  uint16_t      RESERVED20;   /*!< Reserved, 0x52                                            */
} TIM_TypeDef;

/**
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */

typedef struct
{
  __IO uint16_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
  uint16_t      RESERVED0;  /*!< Reserved, 0x02                                                */
  __IO uint16_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
  uint16_t      RESERVED1;  /*!< Reserved, 0x06                                                */
  __IO uint16_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  uint16_t      RESERVED2;  /*!< Reserved, 0x0A                                                */
  __IO uint16_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  uint16_t      RESERVED3;  /*!< Reserved, 0x0E                                                */
  __IO uint16_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  uint16_t      RESERVED4;  /*!< Reserved, 0x12                                                */
  __IO uint16_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  uint16_t      RESERVED5;  /*!< Reserved, 0x16                                                */
  __IO uint16_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
  uint16_t      RESERVED6;  /*!< Reserved, 0x1A                                                */
} USART_TypeDef;

/**
  * @brief Window WATCHDOG
  */

typedef struct
{
  __IO uint32_t CR;   /*!< WWDG Control register,       Address offset: 0x00 */
  __IO uint32_t CFR;  /*!< WWDG Configuration register, Address offset: 0x04 */
  __IO uint32_t SR;   /*!< WWDG Status register,        Address offset: 0x08 */
} WWDG_TypeDef;

/**
  * @}
  */

/** @addtogroup Peripheral_memory_map
  * @{
  */

#define FLASH_BASE            ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE             ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE          ((uint32_t)0x22000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE        ((uint32_t)0x42000000) /*!< Peripheral base address in the bit-band region */

#define FSMC_R_BASE           ((uint32_t)0xA0000000) /*!< FSMC registers base address */

/*!< Peripheral memory map */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800)
#define TIM5_BASE             (APB1PERIPH_BASE + 0x0C00)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x1000)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x1400)
#define LCD_BASE              (APB1PERIPH_BASE + 0x2400)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE            (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE            (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000)
#define DAC_BASE              (APB1PERIPH_BASE + 0x7400)
#define COMP_BASE             (APB1PERIPH_BASE + 0x7C00)
#define RI_BASE               (APB1PERIPH_BASE + 0x7C04)
#define OPAMP_BASE            (APB1PERIPH_BASE + 0x7C5C)

#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400)
#define TIM9_BASE             (APB2PERIPH_BASE + 0x0800)
#define TIM10_BASE            (APB2PERIPH_BASE + 0x0C00)
#define TIM11_BASE            (APB2PERIPH_BASE + 0x1000)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2400)
#define ADC_BASE              (APB2PERIPH_BASE + 0x2700)
#define SDIO_BASE             (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)

#define GPIOA_BASE            (AHBPERIPH_BASE + 0x0000)
#define GPIOB_BASE            (AHBPERIPH_BASE + 0x0400)
#define GPIOC_BASE            (AHBPERIPH_BASE + 0x0800)
#define GPIOD_BASE            (AHBPERIPH_BASE + 0x0C00)
#define GPIOE_BASE            (AHBPERIPH_BASE + 0x1000)
#define GPIOH_BASE            (AHBPERIPH_BASE + 0x1400)
#define GPIOF_BASE            (AHBPERIPH_BASE + 0x1800)
#define GPIOG_BASE            (AHBPERIPH_BASE + 0x1C00)
#define CRC_BASE              (AHBPERIPH_BASE + 0x3000)
#define RCC_BASE              (AHBPERIPH_BASE + 0x3800)


#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x3C00) /*!< FLASH registers base address */
#define OB_BASE               ((uint32_t)0x1FF80000)    /*!< FLASH Option Bytes base address */

#define DMA1_BASE             (AHBPERIPH_BASE + 0x6000)
#define DMA1_Channel1_BASE    (DMA1_BASE + 0x0008)
#define DMA1_Channel2_BASE    (DMA1_BASE + 0x001C)
#define DMA1_Channel3_BASE    (DMA1_BASE + 0x0030)
#define DMA1_Channel4_BASE    (DMA1_BASE + 0x0044)
#define DMA1_Channel5_BASE    (DMA1_BASE + 0x0058)
#define DMA1_Channel6_BASE    (DMA1_BASE + 0x006C)
#define DMA1_Channel7_BASE    (DMA1_BASE + 0x0080)

#define DMA2_BASE             (AHBPERIPH_BASE + 0x6400)
#define DMA2_Channel1_BASE    (DMA2_BASE + 0x0008)
#define DMA2_Channel2_BASE    (DMA2_BASE + 0x001C)
#define DMA2_Channel3_BASE    (DMA2_BASE + 0x0030)
#define DMA2_Channel4_BASE    (DMA2_BASE + 0x0044)
#define DMA2_Channel5_BASE    (DMA2_BASE + 0x0058)

#define AES_BASE              ((uint32_t)0x50060000)

#define FSMC_Bank1_R_BASE     (FSMC_R_BASE + 0x0000) /*!< FSMC Bank1 registers base address */
#define FSMC_Bank1E_R_BASE    (FSMC_R_BASE + 0x0104) /*!< FSMC Bank1E registers base address */

#define DBGMCU_BASE           ((uint32_t)0xE0042000) /*!< Debug MCU registers base address */

/*!< Unique device ID registers */
#if defined (STM32L1XX_MD)
 #define         UID1          ((uint32_t)0x1FF80050)
 #define         UID2          ((uint32_t)0x1FF80054)
 #define         UID3          ((uint32_t)0x1FF80064)
#elif defined (STM32L1XX_MDP) || defined (STM32L1XX_HD) || defined (STM32L1XX_XL)
 #define         UID1          ((uint32_t)0x1FF800D0)
 #define         UID2          ((uint32_t)0x1FF800D4)
 #define         UID3          ((uint32_t)0x1FF800E4)
#endif

/**
  * @}
  */

/** @addtogroup Peripheral_declaration
  * @{
  */

#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                ((TIM_TypeDef *) TIM4_BASE)
#define TIM5                ((TIM_TypeDef *) TIM5_BASE)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                ((TIM_TypeDef *) TIM7_BASE)
#define LCD                 ((LCD_TypeDef *) LCD_BASE)
#define RTC                 ((RTC_TypeDef *) RTC_BASE)
#define WWDG                ((WWDG_TypeDef *) WWDG_BASE)
#define IWDG                ((IWDG_TypeDef *) IWDG_BASE)
#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define SPI3                ((SPI_TypeDef *) SPI3_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define USART3              ((USART_TypeDef *) USART3_BASE)
#define UART4               ((USART_TypeDef *) UART4_BASE)
#define UART5               ((USART_TypeDef *) UART5_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                ((I2C_TypeDef *) I2C2_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)
#define DAC                 ((DAC_TypeDef *) DAC_BASE)
#define COMP                ((COMP_TypeDef *) COMP_BASE)
#define RI                  ((RI_TypeDef *) RI_BASE)
#define OPAMP               ((OPAMP_TypeDef *) OPAMP_BASE)
#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)

#define ADC1                ((ADC_TypeDef *) ADC1_BASE)
#define ADC                 ((ADC_Common_TypeDef *) ADC_BASE)
#define SDIO                ((SDIO_TypeDef *) SDIO_BASE)
#define TIM9                ((TIM_TypeDef *) TIM9_BASE)
#define TIM10               ((TIM_TypeDef *) TIM10_BASE)
#define TIM11               ((TIM_TypeDef *) TIM11_BASE)
#define SPI1                ((SPI_TypeDef *) SPI1_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define DMA1                ((DMA_TypeDef *) DMA1_BASE)
#define DMA1_Channel1       ((DMA_Channel_TypeDef *) DMA1_Channel1_BASE)
#define DMA1_Channel2       ((DMA_Channel_TypeDef *) DMA1_Channel2_BASE)
#define DMA1_Channel3       ((DMA_Channel_TypeDef *) DMA1_Channel3_BASE)
#define DMA1_Channel4       ((DMA_Channel_TypeDef *) DMA1_Channel4_BASE)
#define DMA1_Channel5       ((DMA_Channel_TypeDef *) DMA1_Channel5_BASE)
#define DMA1_Channel6       ((DMA_Channel_TypeDef *) DMA1_Channel6_BASE)
#define DMA1_Channel7       ((DMA_Channel_TypeDef *) DMA1_Channel7_BASE)

#define DMA2                ((DMA_TypeDef *) DMA2_BASE)
#define DMA2_Channel1       ((DMA_Channel_TypeDef *) DMA2_Channel1_BASE)
#define DMA2_Channel2       ((DMA_Channel_TypeDef *) DMA2_Channel2_BASE)
#define DMA2_Channel3       ((DMA_Channel_TypeDef *) DMA2_Channel3_BASE)
#define DMA2_Channel4       ((DMA_Channel_TypeDef *) DMA2_Channel4_BASE)
#define DMA2_Channel5       ((DMA_Channel_TypeDef *) DMA2_Channel5_BASE)

#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define CRC                 ((CRC_TypeDef *) CRC_BASE)

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOH               ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)

#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)
#define OB                  ((OB_TypeDef *) OB_BASE)

#define AES                 ((AES_TypeDef *) AES_BASE)

#define FSMC_Bank1          ((FSMC_Bank1_TypeDef *) FSMC_Bank1_R_BASE)
#define FSMC_Bank1E         ((FSMC_Bank1E_TypeDef *) FSMC_Bank1E_R_BASE)

#define DBGMCU              ((DBGMCU_TypeDef *) DBGMCU_BASE)

/**
  * @}
  */

/** @addtogroup Exported_constants
  * @{
  */

 /**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L1XX_H */

/**
  * @}
  */

  /**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
