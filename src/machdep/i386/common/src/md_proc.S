/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-06 16:44 (EST)
  Function: 
 
  $Id$

*/

/* NB: gas uses "op src, dst */

#include <asmdefs.h>
#include "assym.h"

#define addr32  .byte 0x67
#define data32  .byte 0x66

CR0_PE          =       0x1

/* these must match the definitions in os.h */
#define PUSHALOT()                      \
        pushl %ebp; /*movl %esp, %ebp;*/\
        pushfl;                         \
        pushl %eax;                     \
        pushl %ebx;                     \
        pushl %ecx;                     \
        pushl %edx;                     \
        pushl %esi;                     \
        pushl %edi;                     \
        pushl %ds;                      \
        pushl %es;

#define POPALOT()               \
        popl %es;               \
        popl %ds;               \
        popl %edi;              \
        popl %esi;              \
        popl %edx;              \
        popl %ecx;              \
        popl %ebx;              \
        popl %eax;              \
        popfl;                  \
        popl %ebp;

#define IPL_PROC                1

#ifdef PLATFORM_EMUL
#       define CLI
#       define STI
#else
#       define CLI      cli
#       define STI      sti
#endif

/* Xspllower
       create a (fake) intrframe
       and call intr_handler (int# = 0xFFFF)
*/
ENTRY(Xspllower)
        CLI
        pushl %eax              /* error code */
        pushl $0xFFFF           /* int number */
        PUSHALOT()
        call _C_LABEL(intr_handler)
        POPALOT()
        addl $8, %esp
        STI
        ret

/*
extern  u_long * _setup_initial_stack(u_long *s, char *start, void *entry);
        start (bp+12) - not used
*/

ENTRY(_setup_initial_stack)
        push %ebp
        movl %esp, %ebp
        pushl %esi
        pushl %edi
        pushl %ebx
        movl %esp, %edi          /* save sp */
        movl 8(%ebp), %eax       /* = s */
        movl 16(%ebp), %ebx      /* = entry */
        /* switch to new stack */
        movl %eax, %esp
        pushl %ebx
        pushl $0		/* fake return addr */
        pushl $_start_proc
        PUSHALOT()
        /* return new sp */
        movl %esp, %eax
        /* restore stack */
        movl %edi, %esp
        popl %ebx
        popl %edi
        popl %esi
        popl %ebp
        ret

ENTRY(_yield)

        movb $IPL_PROC, _C_LABEL(cpl)                   /* splproc */

        STI
        PUSHALOT()

        call _yield_next_proc
        /* ax = nextproc */
        movl %eax, %edi
        movl _C_LABEL(currproc), %esi

        /* switch sp's */
        movl %esp, PROC_SP(%esi)
        movl PROC_SP(%edi), %esp

        /* switch proc */
        movl %edi, _C_LABEL(currproc)
        movb $0, _C_LABEL(yieldflag)                    /* yieldflag = 0 */

        call _need_yield_bottom
        cmpl $0, %eax
        je A$
        call _yield_bottom

A$:
        POPALOT()
        movb $0, _C_LABEL(cpl)                          /* spl0 */
        ret

