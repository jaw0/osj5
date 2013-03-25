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

extern void pwm_init(int, int, int);
extern void pwm_set(int, int);
extern void tone_set(int, int);


#endif /* __pwm_h__ */
