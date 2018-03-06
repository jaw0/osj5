
/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-04 13:21 (EST)
  Function: proc machine dependent code - ARM Cortex-M4
 
  $Id$

*/

/* $Id: os.h,v 1.6 2001/10/31 18:09:12 jaw Exp $ */

#ifndef __os_machdep_i386_common_md_proc_h__
#define __os_machdep_i386_common_md_proc_h__

#include <sys/types.h>
#include <conf.h>

typedef uint32_t uregister_t;

struct intrframe {
        int es;
        int ds;
        int di;
        int si;
        int dx;
        int cx;
        int bx;
        int ax;
        int cc;
        int bp;
        int number;
        int code;       /* or ax or 0 */
        int ip;
        int cs;
        int flags;
};
/* NB: flags needed so yield works right */
#define PUSHALOT()                                              \
        __asm__("pushl %ebp; movl %esp, %ebp");                 \
        __asm__("pushfl");                                      \
        __asm__("pushl %eax");                                  \
        __asm__("pushl %ebx");                                  \
        __asm__("pushl %ecx");                                  \
        __asm__("pushl %edx");                                  \
        __asm__("pushl %esi");                                  \
        __asm__("pushl %edi");                                  \
        __asm__("pushl %ds");                                   \
        __asm__("pushl %es");

#define POPALOT()                                               \
        __asm__("popl %es");                                    \
        __asm__("popl %ds");                                    \
        __asm__("popl %edi");                                   \
        __asm__("popl %esi");                                   \
        __asm__("popl %edx");                                   \
        __asm__("popl %ecx");                                   \
        __asm__("popl %ebx");                                   \
        __asm__("popl %eax");                                   \
        __asm__("popfl");                                       \
        __asm__("popl %ebp");


#define IPL_ZERO	0
#define IPL_PROC	1
#define IPL_TTY		2
#define IPL_DISK	3
#define IPL_MOTOR	4
#define IPL_CLOCK	5
#define IPL_HIGH	6

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


extern u_char cpl;
extern u_long ipend;
extern u_char yieldflag;

#define sched_yield()    (yieldflag = 1)
#define md_yield()	_yield()

extern void yield(void);
static __inline int splraise(int);
static __inline int spllower(int);
extern void Xspllower();
extern int install_interrupt(int, int, void (*)(struct intrframe*), const char *);

static __inline int
splraise(int ncpl) {
        int ocpl = cpl;

        if( ncpl > cpl )
                cpl = ncpl;
        return (ocpl);
}

static __inline int
spllower(int ncpl) {
        int ocpl = cpl;

        cpl = ncpl;
        if( ipend && ncpl < ocpl ){
                Xspllower();
        }
#ifdef USE_PROC
        if( yieldflag && !ncpl ){
                yield();
        }
#endif
        return (ocpl);
}

#ifdef PLATFORM_EMUL
#       define irq_enable()
#       define irq_disable()
#else
#       define irq_disable()        __asm__("cli")
#       define irq_enable()         __asm__("sti")
#endif

extern void _start_proc(void (*)(void));

extern  u_long * _setup_initial_stack(u_long *s, char *, void *entry);


#endif /*  __os_machdep_i386_common_md_proc_h__ */


