/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 16:58 (EDT)
  Function: pwm
*/

#ifndef __pwm_h__
#define __pwm_h__

#define TIMER_1_1	0x10
#define TIMER_1_2	0x11
#define TIMER_1_3	0x12
#define TIMER_1_4	0x13

#define TIMER_2_1	0x20
#define TIMER_2_2	0x21
#define TIMER_2_3	0x22
#define TIMER_2_4	0x23

#define TIMER_3_1	0x30
#define TIMER_3_2	0x31
#define TIMER_3_3	0x32
#define TIMER_3_4	0x33

#define TIMER_4_1	0x40
#define TIMER_4_2	0x41
#define TIMER_4_3	0x42
#define TIMER_4_4	0x43

#define TIMER_5_1	0x50
#define TIMER_5_2	0x51
#define TIMER_5_3	0x52
#define TIMER_5_4	0x53

#define TIMER_6_1	0x60
#define TIMER_6_2	0x61
#define TIMER_6_3	0x62
#define TIMER_6_4	0x63

#define TIMER_7_1	0x70
#define TIMER_7_2	0x71
#define TIMER_7_3	0x72
#define TIMER_7_4	0x73

#define TIMER_8_1	0x80
#define TIMER_8_2	0x81
#define TIMER_8_3	0x82
#define TIMER_8_4	0x83

#define TIMER_9_1       0x90
#define TIMER_9_2       0x91
#define TIMER_9_3       0x92
#define TIMER_9_4       0x93

#define TIMER_10_1      0xa0
#define TIMER_10_2      0xa1
#define TIMER_10_3      0xa2
#define TIMER_10_4      0xa3

#define TIMER_11_1      0xb0
#define TIMER_11_2      0xb1
#define TIMER_11_3      0xb2
#define TIMER_11_4      0xb3

#define TIMER_12_1      0xc0
#define TIMER_12_2      0xc1
#define TIMER_12_3      0xc2
#define TIMER_12_4      0xc3

#define TIMER_13_1      0xd0
#define TIMER_13_2      0xd1
#define TIMER_13_3      0xd2
#define TIMER_13_4      0xd3

#define TIMER_14_1      0xe0
#define TIMER_14_2      0xe1
#define TIMER_14_3      0xe2
#define TIMER_14_4      0xe3

#define TIMER_15_1      0xf0
#define TIMER_15_2      0xf1
#define TIMER_15_3      0xf2
#define TIMER_15_4      0xf3

#define TIMER_16_1      0x100
#define TIMER_16_2      0x101
#define TIMER_16_3      0x102
#define TIMER_16_4      0x103

#define TIMER_17_1      0x110
#define TIMER_17_2      0x111
#define TIMER_17_3      0x112
#define TIMER_17_4      0x113

#define TIMER_18_1      0x120
#define TIMER_18_2      0x121
#define TIMER_18_3      0x122
#define TIMER_18_4      0x123

#define TIMER_19_1      0x130
#define TIMER_19_2      0x131
#define TIMER_19_3      0x132
#define TIMER_19_4      0x133

#define TIMER_20_1      0x140
#define TIMER_20_2      0x141
#define TIMER_20_3      0x142
#define TIMER_20_4      0x143

extern void pwm_init(int, int, int);
extern void pwm_set(int, int);
extern void tone_set(int, int);


#endif /* __pwm_h__ */
