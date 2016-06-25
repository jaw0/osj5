
/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-04 13:20 (EST)
  Function: machine dependent code - ARM Cortex-M

*/

#include <asmdefs.h>
#include "assym.h"
#include <conf.h>


ENTRY(PendSV_Handler)
        /* aka. _yield */
        /* hardware pushes r0-3,12,lr(r14),pc,xpsr */
        /* lr = exc_return */

        /* push r4-r11, lr */
#ifdef __thumb2__
# ifdef KSTACK_SIZE
        /* current stack is MSP, put registers on PSP */
        mrs r0, psp
        stmdb r0!, {r4-r11}
        stmdb r0!, {lr}
        msr psp, r0
# else
        push {r4-r11}
        push {lr}
# endif

#else /* thumb */
# ifdef KSTACK_SIZE
        mov r1, sp	@ save sp
        mrs r0, psp
        mov sp, r0	@ sp = psp
        push {r4-r7}
        mov r2, r8
        mov r3, r9
        mov r4, r10
        mov r5, r11
        push {r2-r5}
        push {lr}
        mov r0, sp
        msr psp, r0
        mov sp, r1	@ restore sp
# else
        push {r4-r7}
        mov r1, r8
        mov r2, r9
        mov r3, r10
        mov r4, r11
        push {r1-r4}
        push {lr}
# endif
#endif

        /* get next proc */
        bl _yield_next_proc     @ r0 = nextproc
        ldr r1, =currproc	@ r1 = &currproc
        ldr r2, [r1]		@ r2 = currproc

#ifdef KSTACK_SIZE
        mrs r3, psp
        str r3, [r2, #PROC_SP]  @ currproc->sp = SP
        ldr r3, [r0, #PROC_SP]  @ SP = nextproc->sp
        msr psp, r3
#else
#  ifdef __thumb2__
        str sp, [r2, #PROC_SP]  @ currproc->sp = SP
        ldr sp, [r0, #PROC_SP]  @ SP = nextproc->sp
#  else
        mov r3, sp
        str r3, [r2, #PROC_SP]  @ currproc->sp = SP
        ldr r3, [r0, #PROC_SP]  @ SP = nextproc->sp
        mov sp, r3
#  endif
#endif

        isb
        str r0, [r1]		@ currproc = nextproc

        /* do we need to do a yield_bottom? */
        bl _need_yield_bottom
        cmp r0, #0
        beq _cont0$
        /* is it safe to insert the trampoline - check saved epsr */
        mrs r0, psp
        ldr r0, [r0, #64]
        ldr r1, =#0x600fc00
        ands r0, r1
        cmp r0, #0	        @ epsr is 0, ok
        beq _cont1$

        /* epsr not 0, skip */
        bl _yield_bottom_cancel
        b _cont0$
_cont1$:

        /*
            insert a trampoline to call yield_bottom in user context
	    current:
	        lr,r4-11,r0-3,12,lr(r14),pc,xpsr
	    to:
	        lr,r4-11,r0-3,12,lr(r14), _tramp ,xpsr, pc
        */
#ifdef KSTACK_SIZE
          mrs r0, psp
          subs r0, #4
          msr psp, r0
#else
          sub sp, #4
          mov r0, sp
#endif
          movs r1, #15           @ copy 15 words
_loop0$:
            ldr r2, [r0, #4]	 @ tmp = r0[4]
            str r2, [r0]	 @ r0[0] = tmp
            adds r0, #4
            subs r1, #1
            bne _loop0$

          /* r0 points: [hole], pc, xpsr */
          ldr r2, =_yield_bottom_trampoline

#ifdef __thumb2__
          str r2, [r0], #4      @ insert _tramp, r0 += 4
          /* swap pc, xpsr */
          ldrd r1,r2, [r0]
          orr  r1, #1           @ intr does not set bit on pc
          strd r2,r1, [r0]
#else
          str r2, [r0]      	@ insert _tramp, r0 += 4
          adds r0, #4

          /* swap pc, xpsr */
          ldr r1, [r0]
          ldr r2, [r0, #4]
          movs r4, #1
          orrs r1, r4           @ intr does not set bit on pc
          str r2, [r0]
          str r1, [r0, #4]
#endif

_cont0$:
#ifdef __thumb2__
# ifdef KSTACK_SIZE
        mrs r0, psp
        ldmfd r0!, {lr}
        ldmfd r0!, {r4-r11}
        msr psp, r0
# else
        pop {lr}
        pop {r4-r11}
# endif

#else /* thumb */
# ifdef KSTACK_SIZE
        mrs r0, psp
        ldmfd r0!, {r1}
        mov lr, r1
        ldmfd r0!, {r1-r4}
        mov r8,  r1
        mov r9,  r2
        mov r10, r3
        mov r11, r4
        ldmfd r0!, {r4-r7}
        msr psp, r0
# else
        pop {r1}
        mov lr, r1
        pop {r1-r4}
        mov r8,  r1
        mov r9,  r2
        mov r10, r3
        mov r11, r4
        pop {r4-r7}
# endif

#endif

        bx lr


/* NB: r13 = SP
   return PC is on the stack
*/
ENTRY(_yield_bottom_trampoline)
#ifdef __thumb2__
        push {r0-r12,lr}
        mrs r0, apsr
        push {r0}
        bl _yield_bottom
        pop {r0}
        msr apsr, r0
        pop {r0-r12,lr}
        pop {pc}
#else
        push {r0-r7}
        mov r0, r8
        mov r1, r9
        mov r2, r10
        mov r3, r11
        mov r4, r12
        mov r5, lr
        push {r0-r5}
        mrs r0, apsr
        push {r0}
        bl _yield_bottom
        pop {r0}
        msr apsr, r0
        pop {r0-r5}
        mov lr, r5
        mov r12, r4
        mov r11, r3
        mov r10, r2
        mov r9, r1
        mov r8, r0
        pop {r0-r7}
        pop {pc}
#endif


ENTRY(HardFault_Handler)
        /* pass SP to handler */
#ifdef KSTACK_SIZE
        mov  r0, lr
        movs r1, #4
        ands r0, r1
        bne hfh0$
        mrs r0, msp
        b hfh1$
hfh0$:
        mrs r0, psp
hfh1$:
#else
        mov r0, sp
#endif
        b CHardFault_Handler

/* switch to PSP. use MSP for irqs */
ENTRY(_switch_kstack)
#ifdef KSTACK_SIZE
        push {r1}
        mov r1, sp
        msr psp, r1     	/* PSP = SP */
        ldr r1, =#0xFFFFFFF0
        ands r0, r1       	/* 16 byte align */
        msr msp, r0     	/* MSP = arg */
        mrs r0, control
        movs r1, #2
        orrs r0, r1		/* psp is current sp */
        msr control, r0
        isb
        pop {r1}
#endif
        bx lr

