
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
        /* hardware pushes r0-3,12,lr(r14),pc,xpsr (and maybe float regs) */
        /* lr = exc_return */

        push {r4-r11}
        push {lr}
        bl _yield_next_proc     @ r0 = nextproc

        ldr r1, =currproc	@ r1 = &currproc
        ldr r2, [r1]		@ r2 = currproc

        @ currproc->sp = SP
        str sp, [r2, #PROC_SP]
        @ SP = nextproc->sp
        ldr sp, [r0, #PROC_SP]
        str r0, [r1]		@ currproc = nextproc

        /* RSN: insert yield_bottom trampoline into stack */
        bl _yield_bottom

        pop {lr}
        pop {r4-r11}
        bx lr

ENTRY(idle)
        /* XXX - because serial irq does not yet work */
        /* wfi */
        bx lr


ENTRY(HardFault_Handler)
        @ pass SP to handler
        mov r0, sp
        bl CHardFault_Handler

