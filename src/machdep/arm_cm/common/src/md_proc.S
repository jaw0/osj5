
/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-04 13:20 (EST)
  Function: machine dependent code - ARM Cortex-M4

  $Id$

*/

#include <asmdefs.h>
#include "assym.h"


ENTRY(PendSV_Handler)
        /* aka. _yield */
        /* hardware pushes r0-3,12,lr(r14),pc,xpsr (and maybe float regs) */
        /* lr = exc_return */

        push {r4-r7,lr}
        mov r0, r8
        mov r1, r9
        mov r2, r10
        mov r3, r11
        push {r0-r3}

        bl _yield_next_proc
        @ r0 = nextproc
        ldr r1, =currproc	@ r1 = &currproc
        ldr r2, [r1]		@ r2 = currproc

        @ currproc->sp = SP
        mov r3, sp
        str r3, [r2, #PROC_SP]
        @ SP = nextproc->sp
        ldr r3, [r0, #PROC_SP]
        mov sp, r3
        str r0, [r1]		@ currproc = nextproc

        bl _yield_bottom

        pop {r0-r3}
        mov r8, r0
        mov r9, r1
        mov r10, r2
        mov r11, r3
        pop {r0-r7,pc}


ENTRY(idle)
        wfi
        bx lr


