/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-05 19:40 (EST)
  Function: 
 
  $Id$

*/

#include <asmdefs.h>

@ int _setjmp( r0 = jmpbuf )

ENTRY(_setjmp)
        add r0, #16	@ skip space for r0-3, but don't bother saving them
        stmia r0!, { r4-r7 }
        mov r1, r8
        mov r2, r9
        mov r3, r10
        stmia r0!, { r1-r3 }

        mov r1, r11
        mov r2, r12
        mov r3, r13
        stmia r0!, { r1-r3 }

        mov r1, r14
        stmia r0!, { r1 }

        @ QQQ - floats?

        @ return 0
        mov r0, #0
        bx lr

@ int _longjmp( r0 = jmpbuf, r1 = retval )
ENTRY(_longjmp)
        mov r2, r0
        add r2, #32
        ldmia r2!, { r3-r7 }
        mov r8,  r3
        mov r9,  r4
        mov r10, r5
        mov r11, r6
        mov r12, r7

        ldmia r2!, { r3,r4 }
        mov r13, r3
        mov r14, r4

        add r0, #16
        ldmia r0!, { r4-r7 }

        mov r0, r1
        bx lr
