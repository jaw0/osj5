
/*
  Copyright 1998 Jeff Weisberg <jaw@op.net>
  see the file LICENSE for details
*/

#ifdef RCSID
static const char *const rcsid
= "@(#)$Id: panic.c,v 1.6 2001/11/15 22:56:38 jaw Exp $";
#endif

#include <sys/types.h>
#include <sys/param.h>
#include <nstdio.h>
#include <proc.h>
#include <error.h>
#include <bootflags.h>
#include <asmdefs.h>

static int npanic = 0;
extern struct Proc *schedulerproc;
void stack_trace(void *);

void
panic(const char *m, int l, const char *f){

	if( ! npanic++ )
		kprintf("PANIC: %s at line %d of %s (currproc=%x)\nhalting\n", m, l, f, currproc);

#ifdef PLATFORM_EMUL
	system("stty -raw echo");
        kill(getpid(), 6);
        *(char*)1 = 1;
        _exit(1);
#else
#ifdef USE_GDB
	if( bootflags & BOOT_USEGDB )
		breakpoint();
#  ifdef USE_DDB
	else{
	    currproc = schedulerproc;
	    cli();
	}
#  endif
#else
#  ifdef USE_DDB
	if( schedulerproc ){
	    currproc = schedulerproc;
	    cli();
	}
#  endif
	stack_trace(0);
	
	asm("cli");
	asm("hlt");
#endif

#endif
}

/* create an invalid IDT and cause an interrrupt */
void
reboot(void){
	extern char idtdesc[];

#ifdef PLATFORM_EMUL
	abort();
#else
	idtdesc[0] = idtdesc[1] = 0;

	asm volatile ("lidt " QC_LABEL(idtdesc));
	asm volatile ("int $0xFF");
#endif
}

struct stackframe {
	struct stackframe *next;
	u_long ret;
	u_long arg[0];
};

void
stack_trace(void *ibp){
	struct stackframe *bp;
	
	if( !ibp ){
		asm volatile ("movl %%ebp, %0" : "=r" (ibp));
	}

	for(bp=ibp; bp; bp=bp->next){

		kprintf("ret=%x f(%x, %x, %x, %x, %x, %x)\n",
			bp->ret, bp->arg[0], bp->arg[1], bp->arg[2],
			bp->arg[3], bp->arg[4], bp->arg[5]);

	}
}

