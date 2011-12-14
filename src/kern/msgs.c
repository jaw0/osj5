/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: signals, messages, exceptions

  $Id$

*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <arch.h>
#include <alloc.h>
#include <proc.h>
#include <error.h>
#include <msgs.h>

/* message handling */
void ksendmsg();

int
sendmsg(proc_t proc, u_long msgval, u_long ret){
    struct Msg *msg;

    PROCOK(proc);

    if( msgval < 32 ){
        ksendmsg(proc, msgval);
        return 0;
    }

    if( currproc->flags & PRF_NONBLOCK )
        return 1;

    msg = (struct Msg*)alloc(sizeof(struct Msg));
    msg->next = 0;
    msg->msgval = msgval;
    msg->retval = ret;

    int plx = splproc();

    if( proc->msgtail ){
        proc->msgtail->next = msg;
    }else{
        proc->msghead = msg;
    }
    proc->msgtail = msg;

    proc->flags |= PRF_MSGPEND;
    splx(plx);

    return 0;
}

/* bottom half safe sendmsg */
void
ksendmsg(proc_t proc, u_long msg){

    PROCOK(proc);

    if( msg > 31 )
        return;

    proc->sigmsgs |= 1<<msg;
    proc->flags   |= PRF_MSGPEND;
}

void
throw(u_long msg, u_long ret){
    struct Catch *c;

    for(c=currproc->clist; c; c=c->next){

        /* match ? */
        if( msg != c->msgval )
            continue;

        c->retval = ret;

        if( c->func ){
            (c->func)(msg, ret);
            break;
        }
        _longjmp(c->jb, 1);
    }
}

/* get saved msg and throw it */
void
_xthrow(void){
    struct Msg *msg;
    int m, v;

    /* deliver any signals */
    if( currproc->sigmsgs ){
        for(m=0; m<32; m++){
            if( currproc->sigmsgs & (1<<m) ){
                currproc->sigmsgs &= ~(1<<m);
                if( !currproc->sigmsgs && !currproc->msghead )
                    currproc->flags &= ~PRF_MSGPEND;
                throw(m, 1);
            }
        }
    }

    /* deliver any msgs */
    while( currproc->msghead ){

        int plx = splproc();

        msg = currproc->msghead;
        currproc->msghead = msg->next;
        if( ! msg->next ){
            currproc->msgtail = 0;
            currproc->flags &= ~PRF_MSGPEND;
        }

        splx(plx);

        m = msg->msgval;
        v = msg->retval;

        free( msg, sizeof(struct Msg) );

        throw(m, v);
    }
}

