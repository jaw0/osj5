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
        .align 2
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


.macro IRQ name
    .word \name
    .weak \name
    .thumb_set \name, Default_Handler
.endm


g_pfnVectors:
  .word _estack
  .word Reset_Handler
  IRQ  NMI_Handler
  IRQ  HardFault_Handler
  IRQ  MemManage_Handler
  IRQ  BusFault_Handler
  IRQ  UsageFault_Handler
  IRQ  SecureFault_Handler
  .word  0
  .word  0
  .word  0
  IRQ  SVC_Handler
  IRQ  DebugMon_Handler
  .word  0
  IRQ  PendSV_Handler
  IRQ  SysTick_Handler

  /* External Interrupts */
    IRQ  WWDG_IRQHandler
    IRQ  PVD_PVM_IRQHandler
    IRQ  RTC_IRQHandler
    IRQ  RTC_S_IRQHandler
    IRQ  TAMP_IRQHandler
    IRQ  RAMCFG_IRQHandler
    IRQ  FLASH_IRQHandler
    IRQ  FLASH_S_IRQHandler
    IRQ  GTZC_IRQHandler
    IRQ  RCC_IRQHandler
    IRQ  RCC_S_IRQHandler
    IRQ  EXTI0_IRQHandler
    IRQ  EXTI1_IRQHandler
    IRQ  EXTI2_IRQHandler
    IRQ  EXTI3_IRQHandler
    IRQ  EXTI4_IRQHandler
    IRQ  EXTI5_IRQHandler
    IRQ  EXTI6_IRQHandler
    IRQ  EXTI7_IRQHandler
    IRQ  EXTI8_IRQHandler
    IRQ  EXTI9_IRQHandler
    IRQ  EXTI10_IRQHandler
    IRQ  EXTI11_IRQHandler
    IRQ  EXTI12_IRQHandler
    IRQ  EXTI13_IRQHandler
    IRQ  EXTI14_IRQHandler
    IRQ  EXTI15_IRQHandler
    IRQ  IWDG_IRQHandler
    IRQ  SAES_IRQHandler
    IRQ  GPDMA1_Channel0_IRQHandler
    IRQ  GPDMA1_Channel1_IRQHandler
    IRQ  GPDMA1_Channel2_IRQHandler
    IRQ  GPDMA1_Channel3_IRQHandler
    IRQ  GPDMA1_Channel4_IRQHandler
    IRQ  GPDMA1_Channel5_IRQHandler
    IRQ  GPDMA1_Channel6_IRQHandler
    IRQ  GPDMA1_Channel7_IRQHandler
    IRQ  ADC1_2_IRQHandler
    IRQ  DAC1_IRQHandler
    IRQ  FDCAN1_IT0_IRQHandler
    IRQ  FDCAN1_IT1_IRQHandler
    IRQ  TIM1_BRK_IRQHandler
    IRQ  TIM1_UP_IRQHandler
    IRQ  TIM1_TRG_COM_IRQHandler
    IRQ  TIM1_CC_IRQHandler
    IRQ  TIM2_IRQHandler
    IRQ  TIM3_IRQHandler
    IRQ  TIM4_IRQHandler
    IRQ  TIM5_IRQHandler
    IRQ  TIM6_IRQHandler
    IRQ  TIM7_IRQHandler
    IRQ  TIM8_BRK_IRQHandler
    IRQ  TIM8_UP_IRQHandler
    IRQ  TIM8_TRG_COM_IRQHandler
    IRQ  TIM8_CC_IRQHandler
    IRQ  I2C1_EV_IRQHandler
    IRQ  I2C1_ER_IRQHandler
    IRQ  I2C2_EV_IRQHandler
    IRQ  I2C2_ER_IRQHandler
    IRQ  SPI1_IRQHandler
    IRQ  SPI2_IRQHandler
    IRQ  USART1_IRQHandler
    IRQ  USART2_IRQHandler
    IRQ  USART3_IRQHandler
    IRQ  UART4_IRQHandler
    IRQ  UART5_IRQHandler
    IRQ  LPUART1_IRQHandler
    IRQ  LPTIM1_IRQHandler
    IRQ  LPTIM2_IRQHandler
    IRQ  TIM15_IRQHandler
    IRQ  TIM16_IRQHandler
    IRQ  TIM17_IRQHandler
    IRQ  COMP_IRQHandler
    IRQ  OTG_HS_IRQHandler
    IRQ  CRS_IRQHandler
    IRQ  FMC_IRQHandler
    IRQ  OCTOSPI1_IRQHandler
    IRQ  PWR_S3WU_IRQHandler
    IRQ  SDMMC1_IRQHandler
    IRQ  SDMMC2_IRQHandler
    IRQ  GPDMA1_Channel8_IRQHandler
    IRQ  GPDMA1_Channel9_IRQHandler
    IRQ  GPDMA1_Channel10_IRQHandler
    IRQ  GPDMA1_Channel11_IRQHandler
    IRQ  GPDMA1_Channel12_IRQHandler
    IRQ  GPDMA1_Channel13_IRQHandler
    IRQ  GPDMA1_Channel14_IRQHandler
    IRQ  GPDMA1_Channel15_IRQHandler
    IRQ  I2C3_EV_IRQHandler
    IRQ  I2C3_ER_IRQHandler
    IRQ  SAI1_IRQHandler
    IRQ  SAI2_IRQHandler
    IRQ  TSC_IRQHandler
    IRQ  AES_IRQHandler
    IRQ  RNG_IRQHandler
    IRQ  FPU_IRQHandler
    IRQ  HASH_IRQHandler
    IRQ  PKA_IRQHandler
    IRQ  LPTIM3_IRQHandler
    IRQ  SPI3_IRQHandler
    IRQ  I2C4_ER_IRQHandler
    IRQ  I2C4_EV_IRQHandler
    IRQ  MDF1_FLT0_IRQHandler
    IRQ  MDF1_FLT1_IRQHandler
    IRQ  MDF1_FLT2_IRQHandler
    IRQ  MDF1_FLT3_IRQHandler
    IRQ  UCPD1_IRQHandler
    IRQ  ICACHE_IRQHandler
    IRQ  OTFDEC1_IRQHandler
    IRQ  OTFDEC2_IRQHandler
    IRQ  LPTIM4_IRQHandler
    IRQ  DCACHE1_IRQHandler
    IRQ  ADF1_IRQHandler
    IRQ  ADC4_IRQHandler
    IRQ  LPDMA1_Channel0_IRQHandler
    IRQ  LPDMA1_Channel1_IRQHandler
    IRQ  LPDMA1_Channel2_IRQHandler
    IRQ  LPDMA1_Channel3_IRQHandler
    IRQ  DMA2D_IRQHandler
    IRQ  DCMI_PSSI_IRQHandler
    IRQ  OCTOSPI2_IRQHandler
    IRQ  MDF1_FLT4_IRQHandler
    IRQ  MDF1_FLT5_IRQHandler
    IRQ  CORDIC_IRQHandler
    IRQ  FMAC_IRQHandler
    IRQ  LSECSSD_IRQHandler
    IRQ  USART6_IRQHandler
    IRQ  I2C5_ER_IRQHandler
    IRQ  I2C5_EV_IRQHandler
    IRQ  I2C6_ER_IRQHandler
    IRQ  I2C6_EV_IRQHandler
    IRQ  HSPI1_IRQHandler
    IRQ  GPU2D_IRQHandler
    IRQ  GPU2D_ER_IRQHandler
    IRQ  GFXMMU_IRQHandler
    IRQ  LTDC_IRQHandler
    IRQ  LTDC_ER_IRQHandler
    IRQ  DSI_IRQHandler
    IRQ  DCACHE2_IRQHandler
    IRQ  GFXTIM_IRQHandler
    IRQ  JPEG_IRQHandler

  .size  g_pfnVectors, .-g_pfnVectors
