
/* $Id: locks.h,v 1.2 1999/05/09 21:52:59 jaw Exp $ */

#ifndef __locks_h__
#define __locks_h__

typedef int lock_t;

extern int spin_try_lock(lock_t *);
extern void spin_lock(lock_t *);
extern void spin_unlock(lock_t *);

#define spin_lockedp(l)		(*(l))

#endif /* __locks_h__ */

