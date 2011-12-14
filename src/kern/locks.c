/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: spin locks

  $Id$

*/

#include <conf.h>
#include <proc.h>
#include <locks.h>

extern void yield(void);

/*
  obtain a lock
  NB: locks are not safe for bottom-half use
*/
void
spin_lock(lock_t* p){

    while( spin_lockedp(p) || !spin_try_lock(p) )
        tsleep( (void*)p, 0, "lock", 0 );
}

/* use gcc builtins */
/* return 1 for success, 0 for fail */
int
spin_try_lock(lock_t *p){
    return !__sync_lock_test_and_set(p, 1);
}

void
spin_unlock(lock_t *p){
    __sync_lock_release(p);
    wakeup( (void*)p );
}

