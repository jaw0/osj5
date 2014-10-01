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

#define sync_lockedp(l)		(*(l))


/*
  obtain a lock
  NB: locks are not safe for bottom-half use
*/

int
sync_tlock(lock_t* p, const char *wname, int timeout){
    if(!wname) wname = "lock";

    while(1){
        asleep( (void*)p, wname );
        if( !sync_lockedp(p) && sync_try_lock(p) ){
            aunsleep();
            return 1;
        }
        int t = await( -1, timeout );
        if( t ) break; /* time out */
    }

    return 0;
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

