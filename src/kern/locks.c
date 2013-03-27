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
sync_lock(lock_t* p, const char *wname){
    if(!wname) wname = "lock";

    while( sync_lockedp(p) || !sync_try_lock(p) )
        tsleep( (void*)p, -1, wname, 0 );
}

/* use gcc builtins */
/* return 1 for success, 0 for fail */
int
sync_try_lock(lock_t *p){
    return !__sync_lock_test_and_set(p, 1);
}

void
sync_unlock(lock_t *p){
    __sync_lock_release(p);
    wakeup( (void*)p );
}

