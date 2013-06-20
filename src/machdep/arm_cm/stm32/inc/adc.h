/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-05 19:59 (EDT)
*/

#ifndef __stm32_adc_h__
#define __stm32_adc_h__

#define ADC_1_0		0x00
#define ADC_1_1		0x01
#define ADC_1_2		0x02
#define ADC_1_3		0x03
#define ADC_1_4		0x04
#define ADC_1_5		0x05
#define ADC_1_6		0x06
#define ADC_1_7		0x07
#define ADC_1_8		0x08
#define ADC_1_9		0x09
#define ADC_1_10	0x0A
#define ADC_1_11	0x0B
#define ADC_1_12	0x0C
#define ADC_1_13	0x0D
#define ADC_1_14	0x0E
#define ADC_1_15	0x0F

#define ADC_2_0		0x10
#define ADC_2_1		0x11
#define ADC_2_2		0x12
#define ADC_2_3		0x13
#define ADC_2_4		0x14
#define ADC_2_5		0x15
#define ADC_2_6		0x16
#define ADC_2_7		0x17
#define ADC_2_8		0x18
#define ADC_2_9		0x19
#define ADC_2_10	0x1A
#define ADC_2_11	0x1B
#define ADC_2_12	0x1C
#define ADC_2_13	0x1D
#define ADC_2_14	0x1E
#define ADC_2_15	0x1F

#define ADC_3_0		0x20
#define ADC_3_1		0x21
#define ADC_3_2		0x22
#define ADC_3_3		0x23
#define ADC_3_4		0x24
#define ADC_3_5		0x25
#define ADC_3_6		0x26
#define ADC_3_7		0x27
#define ADC_3_8		0x28
#define ADC_3_9		0x29
#define ADC_3_10	0x2A
#define ADC_3_11	0x2B
#define ADC_3_12	0x2C
#define ADC_3_13	0x2D
#define ADC_3_14	0x2E
#define ADC_3_15	0x2F

void adc_init(int, int);
int adc_get(int);


#endif /*  __stm32_adc_h__ */
