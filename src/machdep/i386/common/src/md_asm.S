
/* $Id: asm.S,v 1.4 2002/07/12 22:41:26 jaw Exp $ */

#include <asmdefs.h>


/* rep_outsb(port, char*, count) */
ENTRY(rep_outsb)
	push %ebp
	movl %esp, %ebp
	pushl %ecx
	pushl %edx
	pushl %esi

	movl 16(%ebp), %ecx
	movl 12(%ebp), %esi
	movl  8(%ebp), %edx

	cld
	rep
	outsb

	popl %esi
	popl %edx
	popl %ecx
	popl %ebp
	ret
	
/* rep_outsw(port, char*, count) */
ENTRY(rep_outsw)
	push %ebp
	movl %esp, %ebp
	pushl %ecx
	pushl %edx
	pushl %esi

	movl 16(%ebp), %ecx
	movl 12(%ebp), %esi
	movl  8(%ebp), %edx

	cld
	rep
	outsw

	popl %esi
	popl %edx
	popl %ecx
	popl %ebp
	ret

/* rep_insb(port, char*, count) */
ENTRY(rep_insb)
	push %ebp
	movl %esp, %ebp
	pushl %ecx
	pushl %edx
	pushl %edi

	movl 16(%ebp), %ecx
	movl 12(%ebp), %edi
	movl  8(%ebp), %edx

	cld
	rep
	insb

	popl %edi
	popl %edx
	popl %ecx
	popl %ebp
	ret

/* rep_insw(port, char*, count) */
ENTRY(rep_insw)
	push %ebp
	movl %esp, %ebp
	pushl %ecx
	pushl %edx
	pushl %edi

	movl 16(%ebp), %ecx
	movl 12(%ebp), %edi
	movl  8(%ebp), %edx

	cld
	rep
	insw

	popl %edi
	popl %edx
	popl %ecx
	popl %ebp
	ret





