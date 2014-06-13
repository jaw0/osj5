
/* $Id: crt.S,v 1.6 2001/11/15 22:56:38 jaw Exp $ */

#include <asmdefs.h>
#include "assym.h"


#define _LONG0(x)	\
.globl x;		\
x:	.long 0

#define LONG0(x)	_LONG0(_C_LABEL(x))

.data
LONG0(bootseg)
LONG0(bootprog)
LONG0(bootexit)
LONG0(ourseg)

/*
LONG0(k_paddr)
LONG0(bootflags)
LONG0(bootmem0)
LONG0(bootmem1)
*/

/*
	XXX return to boot causes a reboot
*/

.text
/* entry from boot code */
ASMENTRY(crt_init)
        mov $0x2A, %al
        outb %al, $0xe9
	/* set some globals from bootflags (which are on stack) */
	movl 4(%esp), %eax
	movl %eax, _C_LABEL(bootflags)
	movl 8(%esp), %eax
	movl %eax, _C_LABEL(bootseg)
	movl 12(%esp), %eax
	movl %eax, _C_LABEL(bootprog)
	movl 16(%esp), %eax
	movl %eax, _C_LABEL(bootexit)
	# movl 20(%esp),
	# movl 24(%esp),
	movl 28(%esp), %eax
	movl %eax, _C_LABEL(bootmem0)
	movl 32(%esp), %eax
	movl %eax, _C_LABEL(bootmem1)

	movl _C_LABEL(bootseg), %eax
	shll $4, %eax
	addl _C_LABEL(bootprog), %eax
	movl %eax, _C_LABEL(k_paddr)
	shrl $4, %eax
	movl %eax, _C_LABEL(ourseg)

	/* set up new stack at top of mem */
	movl _C_LABEL(bootmem0), %eax
	addl _C_LABEL(bootmem1), %eax
	shll $10, %eax
	subl _C_LABEL(k_paddr), %eax
	subl $4, %eax
	movl %eax, %esp
	movl $0, %ebp

        mov $0x4e, %al
        outb %al, $0xe9
	call _C_LABEL(start)

	/* exit back to boot */
.globl _C_LABEL(kexit)
_C_LABEL(kexit):
	pushl $L2
	pushl $__LINE__
	pushl $L1
/*	call _C_LABEL(panic) */
	cli
	pushl %cs
	popl %eax
	subl $24, %eax	/* this is bootcodeseg */
	pushl %eax
	pushl _C_LABEL(bootexit)
	lret

L1: .asciz "kexit reached"
L2: .asciz __FILE__

