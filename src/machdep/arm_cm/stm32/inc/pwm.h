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

extern void pwm_init(int, int, int);
extern void pwm_set(int, int);
extern void tone_set(int, int);


#endif /* __pwm_h__ */
