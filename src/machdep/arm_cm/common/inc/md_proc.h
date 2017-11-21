
/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-04 13:21 (EST)
  Function: proc machine dependent code - ARM Cortex-M4
 
  $Id$

*/

/* $Id: os.h,v 1.6 2001/10/31 18:09:12 jaw Exp $ */

#ifndef __os_machdep_arm_cm4_all_md_proc_h__
#define __os_machdep_arm_cm4_all_md_proc_h__

#include <sys/types.h>
#include <conf.h>

typedef uint32_t uregister_t;

#define IPL_ZERO	0x00	// basepri 0 enables all
#define IPL_PROC	0xF0
#define IPL_TTY		0xD0
#define IPL_DISK	0xC0
#define IPL_MOTOR	0xB0
#define IPL_CLOCK	0x80
#define IPL_I2C		0x20
#define IPL_HIGH	0x10

#define splproc()	splraise(IPL_PROC)
#define splalloc()	splproc()
#define spltty()	splraise(IPL_TTY)
#define splterm()	spltty()
#define spldisk()	splraise(IPL_DISK)
#define splmotor()	splraise(IPL_MOTOR)
#define splclock()	splraise(IPL_CLOCK)
#define splhigh()	splraise(IPL_HIGH)
#define spl0()		spllower(IPL_ZERO)
#define splx(x)		spllower(x)


#define SCB_ICSR	0xE000ED04
#define ICSR_PENDSVSET	0x10000000

#define irq_disable()        __asm__("cpsid i")
#define irq_enable()         __asm__("cpsie if")

static inline void
sched_yield(){
    /* cause a PendSV int to fire */
    *(volatile unsigned*)SCB_ICSR = ICSR_PENDSVSET;
}

static inline int
splraise(int ncpl) {
    int ocpl;

    /* ocpl = basepri */
    asm("mrs %0, basepri" : "=r" (ocpl));

    if( !ocpl || ncpl && (ncpl < ocpl) ){
        /* basepri = ncpl */
        asm("msr basepri, %0" : : "r" (ncpl));
    }

    return ocpl;
}

static inline int
spllower(int ncpl) {
    int ocpl;

    /* ocpl = basepri */
    asm("mrs %0, basepri" : "=r" (ocpl));

    /* basepri = ncpl */
    asm("msr basepri, %0" : : "r" (ncpl));

    return ocpl;
}

static inline void
md_yield(){
    sched_yield();
    spl0();
}


extern void _start_proc(void (*)(void));
extern void exit(int);

static inline u_long *
_setup_initial_stack(u_long *s, char *start /* NOT USED */, void *entry){

    if( (int)s % 8 ) s --;	// eabi requires 8 byte alignment

    // hardware interrupt frame
    *--s = 0x01000000;		// xpsr
    *--s = (u_long)_start_proc;	// pc
    *--s = (u_long)exit;	// lr
    *--s = 0;			// r12
    *--s = 0;			// r3
    *--s = 0;			// r2
    *--s = 0;			// r1
    *--s = (u_long)entry;	// r0

    // pendsv_handler pushes
    *--s = 0;			// r11
    *--s = 0;			// r10
    *--s = 0;			// r9
    *--s = 0;			// r8
    *--s = 0;			// r7
    *--s = 0;			// r6
    *--s = 0;			// r5
    *--s = 0;			// r4
#ifdef KSTACK_SIZE
    *--s = 0xFFFFFFFD;		// lr - EXC_RETURN(thread mode, MSP, no floats)
#else
    *--s = 0xFFFFFFF9;		// lr - EXC_RETURN(thread mode, PSP, no floats)
#endif
    return s;
}

#endif /* __os_machdep_arm_cm4_all_md_proc_h__ */

