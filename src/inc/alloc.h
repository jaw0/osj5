
/* $Id: alloc.h,v 1.2 1999/07/02 22:03:41 jaw Exp $ */

#ifndef __alloc_h__
#define __alloc_h__

#include <conf.h>
#include <arch.h>

#ifdef USE_EMUL
#  define free	mfree
#endif

extern void * alloc(unsigned size);
extern void free(void *ptr, unsigned size);

extern char *_heap_limit;

#define ALIGNED(x)	(((x)+(ALIGNMENT-1)) & ~(ALIGNMENT-1))

#define ATTR_ALIGNED	__attribute__ ((aligned(ALIGNMENT)))

#endif /* __alloc_h__ */

