

extern void nvic_enable(int irq, int prio);


#define EXCEPTION_NMI        2
#define EXCEPTION_HARDFAULT  3
#define EXCEPTION_MEMMANAGE  4
#define EXCEPTION_BUSFAULT   5
#define EXCEPTION_USAGEFAULT 6
#define EXCEPTION_SVCALL     11
#define EXCEPTION_PENDSV     14
#define EXCEPTION_SYSTICK    15

#define IRQ_WWDG                   0
#define IRQ_PVD_VDDIO2             1
#define IRQ_RTC                    2
#define IRQ_FLASH                  3
#define IRQ_RCC                    4
#define IRQ_EXTI0_1                5
#define IRQ_EXTI2_3                6
#define IRQ_EXTI4_15               7
#define IRQ_TS                     8
#define IRQ_DMA1_Ch1               9
#define IRQ_DMA1_Ch2_3_DMA2_Ch1_2  10
#define IRQ_DMA1_Ch4_7_DMA2_Ch3_5  11
#define IRQ_ADC1_COMP              12
#define IRQ_TIM1_BRK_UP_TRG_COM    13
#define IRQ_TIM1_CC                14
#define IRQ_TIM2                   15
#define IRQ_TIM3                   16
#define IRQ_TIM6_DAC               17
#define IRQ_TIM7                   18
#define IRQ_TIM14                  19
#define IRQ_TIM15                  20
#define IRQ_TIM16                  21
#define IRQ_TIM17                  22
#define IRQ_I2C1                   23
#define IRQ_I2C2                   24
#define IRQ_SPI1                   25
#define IRQ_SPI2                   26
#define IRQ_USART1                 27
#define IRQ_USART2                 28
#define IRQ_USART3_4               29
#define IRQ_CEC_CAN                30
#define IRQ_USB                    31

