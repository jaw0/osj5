/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-13 16:35 (EST)
  Function: 
 
  $Id$

*/

#include <conf.h>
#include <proc.h>
#include <time.h>
#include <msgs.h>


utime_t systime = 0;

void
systime_tick(void){

    /* keep track of real time */
    systime += PROC_TIME;

#ifdef USE_PROC
    struct Proc *p;

    wakeup( &systime );

    for(p=(struct Proc*)proclist; p; p=p->next){
        /* check timeouts */
        if( p->state & PRS_BLOCKED ){
            if( p->timeout && p->timeout <= systime ){
                p->timeout = 0;
                sigunblock(p);
                if( p->wchan != WCHAN_NEVER )
                    ksendmsg(p, MSG_TIMEOUT);
            }
        }

        /* handle alarm clocks */
        if( p->alarm && p->alarm <= get_time() ){
            p->alarm = 0;
            if( p->state & PRS_BLOCKED )
                sigunblock(p);
            ksendmsg(p, MSG_ALARM);
        }
    }

    if( currproc && (--timeremain <= 0) ){
        sched_yield();
    }
#endif

}

