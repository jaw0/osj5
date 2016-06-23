/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Nov-25 15:01 (EST)
  Function: interrupt vector table

*/

  .syntax unified
  .thumb
  .global  Default_Handler
  .section  .text.Default_Handler,"ax",%progbits
irqmsg:
        .asciz "irq default handler\n"
Default_Handler:
        ldr r0, =irqmsg
        bl kprintf
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler


/******************************************************************************
*
* The minimal vector table for a Cortex M3. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
*******************************************************************************/

  .global  Default_Handler

  .global  g_pfnVectors
  .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  MemManage_Handler
  .word  BusFault_Handler
  .word  UsageFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  DebugMon_Handler
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler

  /* External Interrupts */
  .word    SUPC_Handler   /*  0 Supply Controller */
  .word    RSTC_Handler   /*  1 Reset Controller */
  .word    RTC_Handler    /*  2 Real Time Clock */
  .word    RTT_Handler    /*  3 Real Time Timer */
  .word    WDT_Handler    /*  4 Watchdog Timer */
  .word    PMC_Handler    /*  5 Power Management Controller */
  .word    EFC_Handler    /*  6 Enhanced Embedded Flash Controller */
  .word    UART0_Handler  /*  7 UART 0 */
  .word    UART1_Handler  /*  8 UART 1 */
  .word    0
  .word    PIOA_Handler   /* 10 Parallel I/O Controller A */
  .word    PIOB_Handler   /* 11 Parallel I/O Controller B */
  .word    PIOC_Handler   /* 12 Parallel I/O Controller C */
  .word    USART0_Handler /* 13 USART 0 */
  .word    USART1_Handler /* 14 USART 1 */
  .word    USART2_Handler /* 15 USART 2 */
  .word    PIOD_Handler   /* 16 Parallel I/O Controller D */
  .word    PIOE_Handler   /* 17 Parallel I/O Controller E */
  .word    HSMCI_Handler  /* 18 Multimedia Card Interface */
  .word    TWIHS0_Handler /* 19 Two Wire Interface 0 HS */
  .word    TWIHS1_Handler /* 20 Two Wire Interface 1 HS */
  .word    SPI0_Handler   /* 21 Serial Peripheral Interface 0 */
  .word    SSC_Handler    /* 22 Synchronous Serial Controller */
  .word    TC0_Handler    /* 23 Timer/Counter 0 */
  .word    TC1_Handler    /* 24 Timer/Counter 1 */
  .word    TC2_Handler    /* 25 Timer/Counter 2 */
  .word    TC3_Handler    /* 26 Timer/Counter 3 */
  .word    TC4_Handler    /* 27 Timer/Counter 4 */
  .word    TC5_Handler    /* 28 Timer/Counter 5 */
  .word    AFEC0_Handler  /* 29 Analog Front End 0 */
  .word    DACC_Handler   /* 30 Digital To Analog Converter */
  .word    PWM0_Handler   /* 31 Pulse Width Modulation 0 */
  .word    ICM_Handler    /* 32 Integrity Check Monitor */
  .word    ACC_Handler    /* 33 Analog Comparator */
  .word    USBHS_Handler  /* 34 USB Host / Device Controller */
  .word    MCAN0_Handler  /* 35 MCAN Controller 0 */
  .word    MCAN0_Line1_Handler  /* 36 MCAN Controller 0 */
  .word    MCAN1_Handler  /* 37 MCAN Controller 1 */
  .word    MCAN1_Line1_Handler  /* 38 MCAN Controller 1 */
  .word    GMAC_Handler   /* 39 Ethernet MAC */
  .word    AFEC1_Handler  /* 40 Analog Front End 1 */
  .word    TWIHS2_Handler /* 41 Two Wire Interface 2 HS */
  .word    SPI1_Handler   /* 42 Serial Peripheral Interface 1 */
  .word    QSPI_Handler   /* 43 Quad I/O Serial Peripheral Interface */
  .word    UART2_Handler  /* 44 UART 2 */
  .word    UART3_Handler  /* 45 UART 3 */
  .word    UART4_Handler  /* 46 UART 4 */
  .word    TC6_Handler    /* 47 Timer/Counter 6 */
  .word    TC7_Handler    /* 48 Timer/Counter 7 */
  .word    TC8_Handler    /* 49 Timer/Counter 8 */
  .word    TC9_Handler    /* 50 Timer/Counter 9 */
  .word    TC10_Handler   /* 51 Timer/Counter 10 */
  .word    TC11_Handler   /* 52 Timer/Counter 11 */
  .word    MLB_Handler    /* 53 MediaLB */
  .word    0
  .word    0
  .word    AES_Handler    /* 56 AES */
  .word    TRNG_Handler   /* 57 True Random Generator */
  .word    XDMAC_Handler  /* 58 DMA */
  .word    ISI_Handler    /* 59 Camera Interface */
  .word    PWM1_Handler   /* 60 Pulse Width Modulation 1 */
  .word    0
  .word    SDRAMC_Handler /* 62 SDRAM Controller */
  .word    RSWDT_Handler  /* 63 Reinforced Secure Watchdog Timer */


  .size  g_pfnVectors, .-g_pfnVectors
/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

    .weak Reset_Handler
    .thumb_set Reset_Handler,Default_Handler

    .weak NMI_Handler
    .thumb_set NMI_Handler,Default_Handler

    .weak HardFault_Handler
    .thumb_set HardFault_Handler,Default_Handler

    .weak MemManage_Handler
    .thumb_set MemManage_Handler,Default_Handler

    .weak BusFault_Handler
    .thumb_set BusFault_Handler,Default_Handler

    .weak UsageFault_Handler
    .thumb_set UsageFault_Handler,Default_Handler

    .weak SVC_Handler
    .thumb_set SVC_Handler,Default_Handler

    .weak DebugMon_Handler
    .thumb_set DebugMon_Handler,Default_Handler

    .weak PendSV_Handler
    .thumb_set PendSV_Handler,Default_Handler

    .weak SysTick_Handler
    .thumb_set SysTick_Handler,Default_Handler

     .weak SUPC_Handler
    .thumb_set SUPC_Handler,Default_Handler

    .weak RSTC_Handler
    .thumb_set RSTC_Handler,Default_Handler

    .weak RTC_Handler
    .thumb_set RTC_Handler,Default_Handler

    .weak RTT_Handler
    .thumb_set RTT_Handler,Default_Handler

    .weak WDT_Handler
    .thumb_set WDT_Handler,Default_Handler

    .weak PMC_Handler
    .thumb_set PMC_Handler,Default_Handler

    .weak EFC_Handler
    .thumb_set EFC_Handler,Default_Handler

    .weak UART0_Handler
    .thumb_set UART0_Handler,Default_Handler

    .weak UART1_Handler
    .thumb_set UART1_Handler,Default_Handler

    .weak PIOA_Handler
    .thumb_set PIOA_Handler,Default_Handler

    .weak PIOB_Handler
    .thumb_set PIOB_Handler,Default_Handler

    .weak PIOC_Handler
    .thumb_set PIOC_Handler,Default_Handler

    .weak USART0_Handler
    .thumb_set USART0_Handler,Default_Handler

    .weak USART1_Handler
    .thumb_set USART1_Handler,Default_Handler

    .weak USART2_Handler
    .thumb_set USART2_Handler,Default_Handler

    .weak PIOD_Handler
    .thumb_set PIOD_Handler,Default_Handler

    .weak PIOE_Handler
    .thumb_set PIOE_Handler,Default_Handler

    .weak HSMCI_Handler
    .thumb_set HSMCI_Handler,Default_Handler

    .weak TWIHS0_Handler
    .thumb_set TWIHS0_Handler,Default_Handler

    .weak TWIHS1_Handler
    .thumb_set TWIHS1_Handler,Default_Handler

    .weak SPI0_Handler
    .thumb_set SPI0_Handler,Default_Handler

    .weak SSC_Handler
    .thumb_set SSC_Handler,Default_Handler

    .weak TC0_Handler
    .thumb_set TC0_Handler,Default_Handler

    .weak TC1_Handler
    .thumb_set TC1_Handler,Default_Handler

    .weak TC2_Handler
    .thumb_set TC2_Handler,Default_Handler

    .weak TC3_Handler
    .thumb_set TC3_Handler,Default_Handler

    .weak TC4_Handler
    .thumb_set TC4_Handler,Default_Handler

    .weak TC5_Handler
    .thumb_set TC5_Handler,Default_Handler

    .weak AFEC0_Handler
    .thumb_set AFEC0_Handler,Default_Handler

    .weak DACC_Handler
    .thumb_set DACC_Handler,Default_Handler

    .weak PWM0_Handler
    .thumb_set PWM0_Handler,Default_Handler

    .weak ICM_Handler
    .thumb_set ICM_Handler,Default_Handler

    .weak ACC_Handler
    .thumb_set ACC_Handler,Default_Handler

    .weak USBHS_Handler
    .thumb_set USBHS_Handler,Default_Handler

    .weak MCAN0_Handler
    .thumb_set MCAN0_Handler,Default_Handler

    .weak MCAN0_Line1_Handler
    .thumb_set MCAN0_Line1_Handler,Default_Handler

    .weak MCAN1_Handler
    .thumb_set MCAN1_Handler,Default_Handler

    .weak MCAN1_Line1_Handler
    .thumb_set MCAN1_Line1_Handler,Default_Handler

    .weak GMAC_Handler
    .thumb_set GMAC_Handler,Default_Handler

    .weak AFEC1_Handler
    .thumb_set AFEC1_Handler,Default_Handler

    .weak TWIHS2_Handler
    .thumb_set TWIHS2_Handler,Default_Handler

    .weak SPI1_Handler
    .thumb_set SPI1_Handler,Default_Handler

    .weak QSPI_Handler
    .thumb_set QSPI_Handler,Default_Handler

    .weak UART2_Handler
    .thumb_set UART2_Handler,Default_Handler

    .weak UART3_Handler
    .thumb_set UART3_Handler,Default_Handler

    .weak UART4_Handler
    .thumb_set UART4_Handler,Default_Handler

    .weak TC6_Handler
    .thumb_set TC6_Handler,Default_Handler

    .weak TC7_Handler
    .thumb_set TC7_Handler,Default_Handler

    .weak TC8_Handler
    .thumb_set TC8_Handler,Default_Handler

    .weak TC9_Handler
    .thumb_set TC9_Handler,Default_Handler

    .weak TC10_Handler
    .thumb_set TC10_Handler,Default_Handler

    .weak TC11_Handler
    .thumb_set TC11_Handler,Default_Handler

    .weak MLB_Handler
    .thumb_set MLB_Handler,Default_Handler

    .weak AES_Handler
    .thumb_set AES_Handler,Default_Handler

    .weak TRNG_Handler
    .thumb_set TRNG_Handler,Default_Handler

    .weak XDMAC_Handler
    .thumb_set XDMAC_Handler,Default_Handler

    .weak ISI_Handler
    .thumb_set ISI_Handler,Default_Handler

    .weak PWM1_Handler
    .thumb_set PWM1_Handler,Default_Handler

    .weak SDRAMC_Handler
    .thumb_set SDRAMC_Handler,Default_Handler

    .weak RSWDT_Handler
    .thumb_set RSWDT_Handler,Default_Handler

