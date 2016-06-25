/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 16:58 (EDT)
  Function: pwm
*/

#ifndef __atsam_pwm_h__
#define __atsam_pwm_h__

// timer counter
//                        <00><TC><CHAN><OUT>
#define TIMER_TC_0_A	0x00000
#define TIMER_TC_0_B	0x00001
#define TIMER_TC_1_A	0x00010
#define TIMER_TC_1_B	0x00011
#define TIMER_TC_2_A	0x00020
#define TIMER_TC_2_B	0x00021

#define TIMER_TC_3_A	0x00100
#define TIMER_TC_3_B	0x00101
#define TIMER_TC_4_A	0x00110
#define TIMER_TC_4_B	0x00111
#define TIMER_TC_5_A	0x00120
#define TIMER_TC_5_B	0x00121

#define TIMER_TC_6_A	0x00200
#define TIMER_TC_6_B	0x00201
#define TIMER_TC_7_A	0x00210
#define TIMER_TC_7_B	0x00211
#define TIMER_TC_8_A	0x00220
#define TIMER_TC_8_B	0x00221

#define TIMER_TC_9_A	0x00300
#define TIMER_TC_9_B	0x00301
#define TIMER_TC_10_A	0x00310
#define TIMER_TC_10_B	0x00311
#define TIMER_TC_11_A	0x00320
#define TIMER_TC_11_B	0x00321
// ...

// pwm
#define TIMER_PWM_0_0	0x10000
#define TIMER_PWM_0_1	0x10001
#define TIMER_PWM_0_2	0x10002
#define TIMER_PWM_0_3	0x10003
#define TIMER_PWM_0_0L	0x10008
#define TIMER_PWM_0_1L	0x10009
#define TIMER_PWM_0_2L	0x1000A
#define TIMER_PWM_0_3L	0x1000B

#define TIMER_PWM_1_0	0x10010
#define TIMER_PWM_1_1	0x10011
#define TIMER_PWM_1_2	0x10012
#define TIMER_PWM_1_3	0x10013
#define TIMER_PWM_1_0L	0x10018
#define TIMER_PWM_1_1L	0x10019
#define TIMER_PWM_1_2L	0x1001A
#define TIMER_PWM_1_3L	0x1001B

#define TIMER_PWM_2_0	0x10020
#define TIMER_PWM_2_1	0x10021
#define TIMER_PWM_2_2	0x10022
#define TIMER_PWM_2_3	0x10023
#define TIMER_PWM_2_0L	0x10028
#define TIMER_PWM_2_1L	0x10029
#define TIMER_PWM_2_2L	0x1002A
#define TIMER_PWM_2_3L	0x1002B

extern void pwm_init(int, int, int);
extern void pwm_set(int, int);
extern void freq_set(int, int);


#endif /* __atsam_pwm_h__ */
