
/* $Id: locks.h,v 1.2 1999/05/09 21:52:59 jaw Exp $ */

#ifndef __locks_h__
#define __locks_h__

typedef int lock_t;

extern int sync_try_lock(lock_t *);
extern void sync_lock(lock_t *, const char *);
extern void sync_unlock(lock_t *);

#endif /* __locks_h__ */

