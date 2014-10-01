
/* $Id: locks.h,v 1.2 1999/05/09 21:52:59 jaw Exp $ */

#ifndef __locks_h__
#define __locks_h__

typedef int lock_t;

extern int sync_try_lock(lock_t *);
extern int sync_tlock(lock_t *, const char *, int);
extern void sync_unlock(lock_t *);

#define sync_lock(l, n)	sync_tlock(l,n,0)


#endif /* __locks_h__ */

