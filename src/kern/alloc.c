/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: malloc/free

  $Id$

*/

#include <sys/param.h>
#include <conf.h>
#include <arch.h>
#include <alloc.h>
#include <nstdio.h>
#include <proc.h>
#include <error.h>


#if 0
#define DEBUG
#define ALLOC_TRACE
#define xprintf	printf
#endif

#ifdef PLATFORM_X86
extern u_long k_paddr;

#  define ISA_HOLE_START	(0x0A0000 - k_paddr)
#  define ISA_HOLE_END		(0x100000 - k_paddr)
#endif

char *_heap_limit = 0;


/*
 *      ALLOC_FIRST_FIT use a first-fit allocation algorithm, rather than
 *                      the default best-fit algorithm.
 *
 *      HEAP_LIMIT      heap limit address (defaults to "no limit").
 *
 *      HEAP_START      start address of heap (defaults to '&end').
 *
 *      DEBUG           enable debugging sanity checks.
 */

/*
 * Each block actually has ALIGNED(unsigned) + ALIGNED(size) bytes allocated
 * to it, as follows:
 *
 * 0 ... (sizeof(unsigned) - 1)
 *      allocated or unallocated: holds size of user-data part of block.
 *
 * sizeof(unsigned) ... (ALIGNED(sizeof(unsigned)) - 1)
 *      allocated: unused
 *      unallocated: depends on packing of struct fl
 *
 * ALIGNED(sizeof(unsigned)) ... (ALIGNED(sizeof(unsigned)) + ALIGNED(data size) - 1)
 *      allocated: user data
 *      unallocated: depends on packing of struct fl
 *
 * 'next' is only used when the block is unallocated (i.e. on the free list).
 * However, note that ALIGNED(sizeof(unsigned)) + ALIGNED(data size) must
 * be at least 'sizeof(struct fl)', so that blocks can be used as structures
 * when on the free list.
 */

struct fl {
    unsigned        size;
    struct fl       *next;
} *freelist = (struct fl *)0;

#define MIN_SIZE	ALIGNED(sizeof(struct fl))
#define OVRHD		ALIGNED(sizeof(unsigned))

#ifndef HEAP_START
extern char end[];
#define HEAP_START end
#endif

static char *top = (char*)HEAP_START;


void *
alloc(size)
    unsigned size;
{
    register struct fl **f = &freelist, **bestf = NULL;
    unsigned bestsize = 0xffffffff; /* greater than any real size */
    char *help;
    int failed;
    int plx;

#ifdef ALLOC_TRACE
    xprintf("alloc(%d)", size);
#endif

    size = ALIGNED(size);

    plx = splproc();
#ifdef ALLOC_FIRST_FIT
    while (*f != (struct fl *)0 && (*f)->size < size)
        f = &((*f)->next);
    bestf = f;
    failed = (*bestf == (struct fl *)0);
#else
    /* scan freelist */
    while (*f) {
        if ((*f)->size >= size) {
            if ((*f)->size == size) /* exact match */
                goto found;

            if ((*f)->size < bestsize) {
                /* keep best fit */
                bestf = f;
                bestsize = (*f)->size;
            }
        }
        f = &((*f)->next);
    }

    /* no match in freelist if bestsize unchanged */
    failed = (bestsize == 0xffffffff);
#endif

#ifdef ALLOC_TRACE
    xprintf("\talloc need more\n" );
#endif

    if (failed) { /* nothing found */

#ifdef USE_DDB_SYMS
        if( top == HEAP_START ){
            extern void init_ddb_syms(void);
            init_ddb_syms();
        }
#endif
        /*
         * allocate from heap, keep chunk len in
         * first word
         */
        help = top;

        /* make _sure_ the region can hold a struct fl. */
        if (size < MIN_SIZE )
            size = MIN_SIZE;

        top += OVRHD + size;
#ifdef PLATFORM_EMUL
        brk(top);
#endif
#ifdef ISA_HOLE_START
        if( (int)help < ISA_HOLE_START && (int)top > ISA_HOLE_START ){
            int sz;

            /* cannot display message here - kprintf may need to alloc */
#ifdef ALLOC_TRACE
            xprintf("\thopping over ISA hole...\n");
#endif
            /* add to freelist */
            sz = ISA_HOLE_START - (int)help;
            if( sz > 2 * MIN_SIZE ){
                *(unsigned *)help = sz - OVRHD;
#ifdef USE_PROC
                if( currproc )
                    currproc->memused += sz;
#endif
                free( help + OVRHD, *(unsigned *)help);
            }

            help = (char*)ISA_HOLE_END;
            top = help + OVRHD + size;
#ifdef PLATFORM_EMUL
            brk(top);
#endif
        }
#endif	/* ISA_HOLE_START */

        if( (_heap_limit && top > _heap_limit)
#ifdef HEAP_LIMIT
            || (top > (char*)HEAP_LIMIT)
#endif
            ){
            PANIC("heap full");
        }

        *(unsigned *)help = size;
#ifdef ALLOC_TRACE
        xprintf("\t=%x (fresh)\n", (u_long)help + OVRHD);
#endif
#ifdef USE_PROC
        if( currproc )
            currproc->memused += size + OVRHD;
#endif

        splx(plx);
        return(help + OVRHD);
    }


    /* we take the best fit */
    f = bestf;

found:
    /* remove from freelist */
    help = (char*)*f;
    *f = (*f)->next;
#ifdef ALLOC_TRACE
    xprintf("\treusing %x (size %d)", (u_long)help + OVRHD,
            *(unsigned *)help);
#endif
#ifdef USE_PROC
    if( currproc )
        currproc->memused += *(unsigned *)help + OVRHD;
#endif

    /* re-size if too big */
    bestsize = *(unsigned *)help;
    if( bestsize > 2 * size + OVRHD
        && bestsize > 2 * MIN_SIZE + OVRHD ){
        char *extra;

        *(unsigned *)help = size;
        extra = help + OVRHD + size;
        *(unsigned *)extra = bestsize - (size + OVRHD);
#ifdef ALLOC_TRACE
        xprintf("\tsplitting %x (sz %d) + %x (sz %d)\n", help, size, extra, *(unsigned *)extra);
#endif

        free( extra + OVRHD, *(unsigned *)extra);
    }

    splx(plx);
    return(help + OVRHD);
}

void
free(ptr, size)
    void *ptr;
    unsigned size; /* only for consistency check */
{
    register struct fl *f =
        (struct fl *)((char*)ptr - OVRHD);
    int plx;

#ifdef ALLOC_TRACE
    xprintf("free(%x, %d) (origsize %d)\n", (u_long)ptr, size, f->size);
#ifdef DEBUG
    if (size > f->size)
        xprintf("free %d bytes @%x, should be <=%d\n",
                size, (u_long)ptr, f->size);

    if (ptr < (void *)HEAP_START)
        xprintf("free: %x before start of heap.\n", (u_long)ptr);
#endif

#ifdef HEAP_LIMIT
    if (ptr > (void *)HEAP_LIMIT)
        kprintf("free: %x beyond end of heap.\n", (u_long)ptr);
#endif
#endif /* DEBUG */

    plx = splproc();
#ifdef USE_PROC
    if( currproc )
        currproc->memused -= f->size + OVRHD;
#endif
    /* put into freelist */
    f->next = freelist;
    freelist = f;
    splx(plx);
}


