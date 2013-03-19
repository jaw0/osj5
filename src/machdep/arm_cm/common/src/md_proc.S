
/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-04 13:20 (EST)
  Function: machine dependent code - ARM Cortex-M3

  $Id$

*/

#include <asmdefs.h>
#include "assym.h"


ENTRY(PendSV_Handler)
        /* aka. _yield */
        /* hardware pushes r0-3,12,lr(r14),pc,xpsr */
        /* lr = exc_return */

        push {r4-r11}
        push {lr}
        bl _yield_next_proc     @ r0 = nextproc

        ldr r1, =currproc	@ r1 = &currproc
        ldr r2, [r1]		@ r2 = currproc

        str sp, [r2, #PROC_SP]  @ currproc->sp = SP
        ldr sp, [r0, #PROC_SP]  @ SP = nextproc->s
        str r0, [r1]		@ currproc = nextproc

        /* do we need to do a yield_bottom? */
        bl _need_yield_bottom
        cbz r0, _cont0$
        /* is it safe to insert the trampoline - check saved epsr */
        ldr r0, [sp, #16]
        ldr r1, =#0x600fc00
        and r0, r1
        cbnz r0, _cont0$        @ epsr not 0, not safe. skip

        /*
            insert a trampoline to call yield_bottom in user context
	    current:
	        lr,r4-11,r0-3,12,lr(r14),pc,xpsr
	    to:
	        lr,r4-11,r0-3,12,lr(r14), _tramp ,xpsr, pc
        */

          sub sp, #4
          mov r0, sp
          mov r1, #15           @ copy 15 words
_loop0$:
            ldr r2, [r0, #4]!   @ tmp = r0[4], r0 += 4
            str r2, [r0, #-4]   @ r0[-4] = tmp
            subs r1, #1
            bne _loop0$

          /* r0 points: [hole], pc, xpsr */
          ldr r2, =_yield_bottom_trampoline
          str r2, [r0], #4      @ insert _tramp, r0 += 4
          /* swap pc, xpsr */
          ldrd r1,r2, [r0]
          orr r1, #1            @ intr does not set bit on pc
          strd r2,r1, [r0]

_cont0$:

        pop {lr}
        pop {r4-r11}
        bx lr


/* NB: r13 = SP
   return PC is on the stack
*/
ENTRY(_yield_bottom_trampoline)
        push {r0-r12,lr}
        mrs r0, apsr
        push {r0}
        bl _yield_bottom
        pop {r0}
        msr apsr, r0
        pop {r0-r12,lr}
        pop {pc}



ENTRY(idle)
        wfi
        bx lr


ENTRY(HardFault_Handler)
        /* pass SP to handler */
        mov r0, sp
        b CHardFault_Handler

