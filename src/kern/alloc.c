/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: malloc/free
*/

/* based on NetBSD sys/lib/libsa/alloc.c */

  /*
   * Copyright (c) 1997 Christopher G. Demetriou.  All rights reserved.
   * Copyright (c) 1996
   *      Matthias Drochner.  All rights reserved.
   * Copyright (c) 1993
   *      The Regents of the University of California.  All rights reserved.
   *
   * This code is derived from software contributed to Berkeley by
   * The Mach Operating System project at Carnegie-Mellon University.
   *
   * Redistribution and use in source and binary forms, with or without
   * modification, are permitted provided that the following conditions
   * are met:
   * 1. Redistributions of source code must retain the above copyright
   *    notice, this list of conditions and the following disclaimer.
   * 2. Redistributions in binary form must reproduce the above copyright
   *    notice, this list of conditions and the following disclaimer in the
   *    documentation and/or other materials provided with the distribution.
   * 3. All advertising materials mentioning features or use of this software
   *    must display the following acknowledgement:
   *      This product includes software developed by the University of
   *      California, Berkeley and its contributors.
   * 4. Neither the name of the University nor the names of its contributors
   *    may be used to endorse or promote products derived from this software
   *    without specific prior written permission.
   *
   * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
   * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
   * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
   * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
   * SUCH DAMAGE.
   *
   * Copyright (c) 1989, 1990, 1991 Carnegie Mellon University
   * All Rights Reserved.
   *
   * Author: Alessandro Forin
   *
   * Permission to use, copy, modify and distribute this software and its
   * documentation is hereby granted, provided that both the copyright
   * notice and this permission notice appear in all copies of the
   * software, derivative works or modified versions, and any portions
   * thereof, and that both notices appear in supporting documentation.
   *
   * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
   * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
   * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
   *
   * Carnegie Mellon requests users of this software to return to
   *
   *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
   *  School of Computer Science
   *  Carnegie Mellon University
   *  Pittsburgh PA 15213-3890
   *
   * any improvements or extensions that they make and grant Carnegie the
   * rights to redistribute these changes.
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
int alloc_trace = 0;
#define xprintf	if(alloc_trace) ktprintf
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
extern char _end[];
#define HEAP_START _end
#endif

static char *top = 0;


void *
alloc(size)
    unsigned size;
{
    register struct fl **f = &freelist, **bestf = NULL;
    unsigned bestsize = 0xffffffff; /* greater than any real size */
    char *help;
    int failed;
    int plx;

    if( !top ) top = HEAP_START;

#ifdef ALLOC_TRACE
    xprintf("alloc(%d) top %x, fl %x\n", size, top, freelist);
#endif

    size = ALIGNED(size);

    plx = splproc();
#ifdef ALLOC_FIRST_FIT
    while (*f != 0 && (*f)->size < size)
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
    xprintf("\talloc need more. top %x\n", top );
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
#if defined(USE_PROC) && !defined(PROC_SMALL)
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
#if defined(USE_PROC) && !defined(PROC_SMALL)
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
#if defined(USE_PROC) && !defined(PROC_SMALL)
    if( currproc )
        currproc->memused -= f->size + OVRHD;
#endif
    /* put into freelist */
    f->next = freelist;
    freelist = f;
    splx(plx);
}

void
zfree(void *p, unsigned sz){
    bzero(p, sz);
    free(p, sz);

}

void *
malloc(int size){ return alloc(size); }

void *
calloc(int size, int len){ return alloc(size * len); }
