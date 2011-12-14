/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function:

  $Id$

*/


#include <sys/types.h>
#include <sys/param.h>
#include <nstdio.h>
#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <conf.h>
#include <error.h>
#include <bootflags.h>
#include <misc.h>
#include <pio.h>
#include <cpufunc.h>
//#include <timer.h>
#include <asmdefs.h>

#define IO_ICU1	0x20
#define IO_ICU2	0xA0

#define ICU_OFFSET INT_OFFSET
#define IRQ_SLAVE 2


u_char cpl = 0xFF;		/* current priority level */
u_long ipend = 0;		/* pending interrupts - bit mask */
u_char yieldflag = 0;		/* a yield is required asap */

extern u_long k_paddr;

void intr_handler(struct intrframe);
void trap_handler(struct intrframe);

#define INT_OFFSET 32

#define INTR(n)                                 \
    asm(".globl _intr_" QUOTIFY(n));            \
    asm(".text");				\
    asm(".align 2");                            \
    asm("_intr_" QUOTIFY(n) ":");		\
    asm("pushl $0");	/* dummy */             \
    asm("pushl %eax");

#define INTRB(n)                                \
    asm("popl %eax");                           \
    asm("pushl $" QUOTIFY(n));                  \
    asm("jmp _intr_common");

#define INTRMASTER(n)                                                   \
    INTR(n)                                                             \
    asm("movb    $(0x60|(" QUOTIFY(n) "%8)),%al"); 	/* specific EOI */ \
    asm("outb    %al,$0x20");                                           \
    INTRB(n)
#define INTRSLAVE(n)                                                    \
    INTR(n)                                                             \
    asm("movb    $(0x60|(" QUOTIFY(n) "%8)),%al"); 	/* specific EOI */ \
    asm("outb    %al,$0xA0");            	/* do the second ICU first */ \
    asm("movb    $(0x60|2),%al");   	/* specific EOI for IRQ2 */     \
    asm("outb    %al,$0x20");                                           \
    INTRB(n)

#define TRAP(n)                                 \
    asm(".globl _trap_" QUOTIFY(n));            \
    asm(".text");				\
    asm(".align 2");                            \
    asm("_trap_" QUOTIFY(n) ":");		\
/*asm("cli");*/

#define TRAP1(n)                                \
    TRAP(n)					\
    asm("pushl $" QUOTIFY(n));                  \
    asm("jmp _trap_common");

#define TRAP2(n)                                \
    TRAP(n)					\
    asm("pushl $0");                            \
    asm("pushl $" QUOTIFY(n));                  \
    asm("jmp _trap_common");

asm(".text");
asm(".align 2");
asm("_intr_common:");
PUSHALOT();
asm("call " QC_LABEL(intr_handler));
asm("_intr_return:");
POPALOT();
asm("addl $8, %esp");
#ifdef USE_PROC
asm("cmpb $0, " QC_LABEL(yieldflag));
asm("je _xx_done_intr");
asm("cmpb $0, " QC_LABEL(cpl));
asm("jne _xx_done_intr");
asm("movb $0, " QC_LABEL(yieldflag));
asm("call " QC_LABEL(_yield));
#endif
asm("_xx_done_intr:");
asm("iret");


asm(".text");
asm(".align 2");
asm("_trap_common:");
PUSHALOT();
asm("call " QC_LABEL(trap_handler));
asm("jmp _intr_return");


TRAP2(0);
TRAP2(1);
TRAP2(2);
TRAP2(3);
TRAP2(4);
TRAP2(5);
TRAP2(6);
TRAP2(7);
TRAP1(8);
TRAP2(9);
TRAP1(10);
TRAP1(11);
TRAP1(12);
TRAP1(13);
TRAP1(14);
TRAP2(15);
TRAP2(16);
TRAP1(17);
TRAP2(18);
TRAP2(19);
TRAP2(20);
TRAP2(21);
TRAP2(22);
TRAP2(23);
TRAP2(24);
TRAP2(25);
TRAP2(26);
TRAP2(27);
TRAP2(28);
TRAP2(29);
TRAP2(30);
TRAP2(31);

INTRMASTER(32);
INTRMASTER(33);
INTRMASTER(34);
INTRMASTER(35);
INTRMASTER(36);
INTRMASTER(37);
INTRMASTER(38);
INTRMASTER(39);
INTRSLAVE(40);
INTRSLAVE(41);
INTRSLAVE(42);
INTRSLAVE(43);
INTRSLAVE(44);
INTRSLAVE(45);
INTRSLAVE(46);
INTRSLAVE(47);


extern u_long itable[];
asm(".globl " QC_LABEL(itable) "\n.data\n.align 4\n" QC_LABEL(itable) ":");
asm(".long 0, _trap_0,  0, _trap_1,  0, _trap_2,  0, _trap_3,  0, _trap_4,  0, _trap_5,  0, _trap_6,  0, _trap_7" );
asm(".long 0, _trap_8,  0, _trap_9,  0, _trap_10, 0, _trap_11, 0, _trap_12, 0, _trap_13, 0, _trap_14, 0, _trap_15");
asm(".long 0, _trap_16, 0, _trap_17, 0, _trap_18, 0, _trap_19, 0, _trap_20, 0, _trap_21, 0, _trap_22, 0, _trap_23");
asm(".long 0, _trap_24, 0, _trap_25, 0, _trap_26, 0, _trap_27, 0, _trap_28, 0, _trap_29, 0, _trap_30, 0, _trap_31");
asm(".long 0, _intr_32, 0, _intr_33, 0, _intr_34, 0, _intr_35, 0, _intr_36, 0, _intr_37, 0, _intr_38, 0, _intr_39");
asm(".long 0, _intr_40, 0, _intr_41, 0, _intr_42, 0, _intr_43, 0, _intr_44, 0, _intr_45, 0, _intr_46, 0, _intr_47");
asm(".text");

extern char idtdesc[];
asm(".globl " QC_LABEL(idtdesc) "\n.data\n.align 2\n" QC_LABEL(idtdesc) ": .word 2047\n.long 0");
asm(".text");


#ifdef USE_GDB
/* stub for gdb */
void
exceptionHandler(int i, u_long offset){
    u_short cs;
    u_short *its;

    asm("pushl %%cs;"
        "popl %0;" : "=r" (cs));

    its = (u_short*)itable;

    its[ 4 * i ] = offset;
    its[ 4 * i + 1 ] = cs;

    /* intr gate */
    its[ 4 * i + 2 ] = 0x8E00;

    its[ 4 * i + 3 ] = offset >> 16;
}
#endif

int
init_ints(void){
    u_short *its;
    u_short cs;
    u_long offset;
    int i;

    asm("pushl %%cs;"
        "popl %0;" : "=r" (cs));

    its = (u_short*)itable;

    for(i=0; i<48; i++){
        offset = itable[ 2 * i + 1 ];

        its[ 4 * i ] = offset;
        its[ 4 * i + 1 ] = cs;

        /* trap gate or intr gate ? */
        /* if( i < 32 ){ */
        if( 0 ){
            its[ 4 * i + 2 ] = 0x8F00;
        }else{
            its[ 4 * i + 2 ] = 0x8E00;
        }

        its[ 4 * i + 3 ] = offset >> 16;

    }
#ifndef PLATFORM_EMUL
    /* init 8259 PIC */

    outb(IO_ICU1, 0x11);            /* reset; program device, four bytes */
    outb(IO_ICU1+1, ICU_OFFSET);    /* starting at this vector index */
    outb(IO_ICU1+1, 1 << IRQ_SLAVE); /* slave on line 2 */
    outb(IO_ICU1+1, 1);             /* 8086 mode */
    outb(IO_ICU1+1, 0x00);          /* leave interrupts un-masked */
    outb(IO_ICU1, 0x68);            /* special mask mode (if available) */
    outb(IO_ICU1, 0x0a);            /* Read IRR by default. */

    outb(IO_ICU2, 0x11);            /* reset; program device, four bytes */
    outb(IO_ICU2+1, ICU_OFFSET+8);  /* starting at this vector index */
    outb(IO_ICU2+1, IRQ_SLAVE);
    outb(IO_ICU2+1, 1);             /* 8086 mode */
    outb(IO_ICU2+1, 0x00);          /* leave interrupts un-masked */
    outb(IO_ICU2, 0x68);            /* special mask mode (if available) */
    outb(IO_ICU2, 0x0a);            /* Read IRR by default. */


    /* need to convert vaddr->paddr */
    *(u_long*)(idtdesc + 2) = k_paddr + (u_long)itable;

    asm volatile ("lidt " QC_LABEL(idtdesc));
    irq_enable();
#endif
#ifdef USE_GDB
    if( bootflags & BOOT_USEGDB ){
        screen_puts("gdb: set traps\n");
        set_debug_traps();
    }
#endif

}

const char *const trapnames[] = {
    "divide error",
    "debugging",
    "NMI",
    "breakpoint",
    "overflow",
    "bound range exceeded",
    "invalid opcode",
    "no FPU",
    "double fault",
    "FPU segment overrun",
    "invalid TSS",
    "segment not available",
    "stack segment fault",
    "general protection fault",
    "page fault",
    "reverved",
    "FPU error",
    "alignment check",
    "machine check",
    "unknown",
};

void
dump_intrframe(struct intrframe *fr){

    kprintf("\tat cs:ip=%0.8x:%0.8x flags=%0.8x/%0.8x\n", fr->cs, fr->ip, fr->flags, fr->cc);
    kprintf("\tax=%0.8x bx=%0.8x cx=%0.8x dx=%0.8x ds=%0.8x\n", fr->ax, fr->bx, fr->cx, fr->dx, fr->ds);
    kprintf("\tsp=%0.8x bp=%0.8x si=%0.8x di=%0.8x es=%0.8x\n", &fr, fr->bp, fr->si, fr->di, fr->es);
}

void
trap_handler(struct intrframe fr){
    const char *msg;

    if( fr.number >= sizeof(trapnames)/sizeof(trapnames[0])){
        msg = "unknown";
    }else{
        msg = trapnames[ fr.number ];
    }

    kprintf("* * * * * TRAP %d(%x) - %s * * * * *\n", fr.number, fr.code, msg);
#ifdef USE_PROC
    kprintf("in process %0.8x (%s)\n", currproc, (currproc && currproc->name)
            ? currproc->name : "unknown");
#endif
    dump_intrframe( & fr );
    stack_trace();


#ifdef USE_PROC
    if( currproc->flags & PRF_IMPORTANT ){
        PANIC( msg );
    }else{
        kprintf("killing process\n");
        sigkill( (proc_t)currproc );
        sched_yield();
    }
#else
    PANIC( msg );
#endif

}

void unusedirq(struct intrframe*);
void hardclock(struct intrframe*);
void serialirq(struct intrframe*);

struct {
    void (*f)(struct intrframe*);
    u_char pl;
    const char *name;
} inthnd[] = {
    /* master */
    { hardclock, IPL_CLOCK, "timer0" },
    { unusedirq, IPL_HIGH,  "int0-kbd" },
    { unusedirq, IPL_HIGH,  "slave" },
    { unusedirq, IPL_HIGH,  "asio1/int8" },
    { unusedirq, IPL_HIGH,  "asio0/int9" },
    { unusedirq, IPL_HIGH,  "int1-lpt" },
    { unusedirq, IPL_HIGH,  "int2-fdc" },
    { unusedirq, IPL_HIGH,  "int3-lpt" },

    /* slave */
    { unusedirq, IPL_HIGH,  "int4-rtc" },
    { unusedirq, IPL_HIGH,  "ssio/int5" },
    { unusedirq, IPL_HIGH,  "timer1" },
    { unusedirq, IPL_HIGH,  "timer2" },
    { unusedirq, IPL_HIGH,  "dma/int6" },
    { unusedirq, IPL_HIGH,  "int6/dma" },
    { unusedirq, IPL_HIGH,  "int7" },
    { unusedirq, IPL_HIGH,  "watchdog" },

};

int
install_interrupt(int irq, int prio, void (*f)(struct intrframe*), const char *name){

    XE9('I');
    if( irq >= sizeof(inthnd)/sizeof(inthnd[0]) || irq < 0 )
        return -1;
    XE9('a');
    if( inthnd[irq].f != unusedirq )
        return -1;

    XE9('b');
    irq_disable();
    XE9('c');
    inthnd[irq].f    = f;
    inthnd[irq].pl   = prio;
    inthnd[irq].name = name;
    XE9('d');
    irq_enable();
    XE9('I');

    return 0;
}



void
intr_handler(struct intrframe fr){
    int i, iin;
    int plx, pl;

    iin = fr.number - INT_OFFSET;

    /* screen_printf("IRQ %d - %s\n", fr.number, inthnd[iin].name); */
/*	if( iin==3 || iin==4 )
        kprintf("IRQ %d - %s\n", fr.number, iin < 16 ? inthnd[iin].name : "fake");
*/
    /* NB: Xspllower fakes an interrupt with an invalid number */
    if( iin < sizeof(inthnd)/sizeof(inthnd[0]) ){
        /* can we handle this now ? */
        if( cpl < (pl=inthnd[iin].pl) ){
            plx = cpl;
            cpl = pl;	/* we know that cpl < pl */
            irq_enable();
            inthnd[iin].f( &fr );
            irq_disable();
            cpl = plx;
        }else{
            ipend |= 1<<iin;
            return;
            /* anything pending must have a lower prio than we do
               so don't bother checking them */
        }
    }

    /* handle any other pending ints */

    for(i=0; i<32; i++){
        if( ! (ipend & (1<<i)) )
            continue;

        if( cpl < (pl=inthnd[i].pl) ){
            plx = cpl;
            cpl = pl;
            ipend &= ~ (1<<i);
            fr.number = i + INT_OFFSET;
            irq_enable();
            inthnd[i].f( &fr );
            irq_disable();
            cpl = plx;
        }
    }
}

void
unusedirq(struct intrframe* fr){

    kprintf("stray irq: %d - %s\n", fr->number,
	    inthnd[fr->number - INT_OFFSET].name);
}

void
hardclock(struct intrframe* fr){

    systime_tick();
}


