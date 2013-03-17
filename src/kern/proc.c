/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: processes

  $Id$

*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#ifdef USE_NSTDIO
#include <nstdio.h>
#endif
#include <proc.h>
#include <alloc.h>
#include <arch.h>
#include <error.h>
#include <msgs.h>
#include <fs.h>
#include <bootflags.h>

#define STACK_MIN	2048
#define INIT_STACK	4096

volatile struct Proc *proclist = 0;

volatile long timeremain = 0;
volatile struct Proc *currproc = 0, *readylist = 0, *realtimelist = 0, *realtimetail = 0;
struct Proc *schedulerproc = 0;

static struct Proc *waittable[WAITTABLESIZE];

static void scheduler(void), prioritizer(void);
static int dispose_of_cadaver(proc_t);
void realtimelist_add(proc_t);
void realtimelist_remove(void);
void idle(void);


/* trampoline to start proc */
void
_start_proc( void (*entry)(void) ){
    entry();
    exit(-1);
}

void
kdump( u_long *start, u_long *end ){

    while( start < end ){
        kprintf(" %08.8X", *start);
        start ++;
    }
    kprintf("\n");
}

proc_t
start_proc(int ssize, void *entry, const char *name){
    struct Proc *proc;
    char *stack;
    int asize;

    if( ssize < STACK_MIN )
        ssize = STACK_MIN;

    /* put Proc at top of stack */
    ssize = ALIGNED(ssize);
    asize = ssize + ALIGNED(sizeof(struct Proc));
    stack = alloc( asize );
    bzero(stack, asize);

    proc = (struct Proc*) (stack + ssize);

    /* set up new proc's stack */
    proc->sp = (u_long)_setup_initial_stack((u_long*)proc, stack, entry);

    // kprintf("proc %X sp %X\n", proc, proc->sp);
    /* change a few entries in proc */
    proc->name        = name;
    proc->alloc_size  = asize;
    proc->stack_start = stack;
    proc->memused     = asize;
    proc->timeslice   = 5;	/* QQQ */

#ifdef CHECKPROC
    proc->magic = PROCMAGIC;
    proc->lowsp = proc->sp;
#endif
#ifdef USE_NSTDIO
    /* copy from parent */
    proc->stdin  = STDIN;
    proc->stdout = STDOUT;
    proc->stderr = STDERR;
#endif
    proc->cwd    = currproc->cwd;

    /* keep track of family tree */
    /* are you my mommy? */
    proc->mommy = (proc_t)currproc;

    /* siblings */
    if( currproc )
        proc->brother = currproc->booboo;

    /* it is safe to be preempted until something points to the new proc */
    /* QQQ - what happens if we get killed before we finish */
    int plx = splproc();

    if( proc->brother )
        proc->brother->sister = proc;
    /* parent's child */
    if( currproc )
        currproc->booboo = proc;

    /* add to proclist */
    proc->next = (proc_t)proclist;
    if( proclist )
        proclist->prev = proc;
    proclist = proc;

    splx(plx);

    return proc;

}

/*
  init_proc
  initialize multi-process stuff
*/

void
init_proc(proc_t p){

    /* set up initial proc */
    bzero(p, sizeof(struct Proc));
    bzero(waittable, WAITTABLESIZE * sizeof(struct Proc *));

    p->timeslice = 5;

    p->timeallotted = p->timeslice;
    p->flags  = PRF_NONBLOCK | PRF_AUTOREAP;
#ifdef USE_NSTDIO
    p->stdin  = kconsole_port;
    p->stdout = kconsole_port;
    p->stderr = kconsole_port;
#endif
    p->cwd    = 0;
    /* estimated size of needed stack, for run-time error checking */
    p->stack_start = _heap_limit = (char*)p - INIT_STACK;
    p->name = "init";
#ifdef CHECKPROC
    p->magic = PROCMAGIC;
    p->lowsp = (u_long)&p;
#endif
    currproc = p;
    proclist = currproc;
    timeremain = p->timeslice;

#ifdef MOUNT_ROOT
    if( !chdir( MOUNT_ROOT ) ){
        bootmsg("root on %s\n", MOUNT_ROOT);
    }
#endif

#ifdef USE_CONSOLE
    if( (bootflags & BOOT_SINGLE) && kconsole_port ){
        bootmsg("proc starting single user\nexit to continue with multi user startup\n");
        splx(IPL_PROC);
        shell();
    }
#endif
    bootmsg("proc starting: init");

    /* start scheduler in a child process */
    schedulerproc = start_proc(2048, scheduler, "scheduler");
    bootmsg(" scheduler");

    /* start prioritizer */
    start_proc(2048, prioritizer, "prioritizer");
    bootmsg(" prioritizer");

    bootmsg("\nproc starting multiuser\n");

    /* this starts up multiuser mode */
    spl0();
    irq_enable();

    currproc->flags &= ~PRF_NONBLOCK;
#ifdef USE_NSTDIO
    p->stdin  = console_port;
    p->stdout = console_port;
    p->stderr = console_port;
#endif
}


/*
  wait
  wait for a child process to finish
*/

int
wait(proc_t pid){
    int rv;

    PROCOK(currproc);
    PROCOK(pid);

    if( currproc->flags & PRF_NONBLOCK )
        return -1;

    if( pid->mommy && pid->mommy != currproc )
        /* pedeophilia not permitted */
        /* can only wait for your own children */
        return -1;

    while( !( pid->state & PRS_DEAD )){
        tsleep(pid, currproc->prio, "proc", 0);
    }

    /* pid is now dead, dispose of cadaver */
    rv = pid->exitval;
    dispose_of_cadaver(pid);

    return rv;
}

/*
  check all of our kids, if any are dead, dispose of the body
*/

int
reapkids(void){
    struct Proc *p;

    for(p=currproc->booboo; p; ){
        proc_t n = p->brother;
        if( p->state & PRS_DEAD )
            dispose_of_cadaver(p);
        p = n;
    }

    currproc->flags &= ~PRF_DEADKID;
    return 0;
}

/*
  do the work of cleaning up a dead process
*/

static int
dispose_of_cadaver(proc_t pid){
    struct Proc *p;
    int plx;

    PROCOK(pid);

    if( currproc->flags & PRF_REALTIME ){
        /* we cannot allow realtime processes to change the proclist
           because if we preempt the scheduler, this will cause confusion */

        /* yield'ing will force the process to be run via the normal
           runlist, ergo not pre-empting scheduler */
        yield();
    }

    if( ! (pid->state & PRS_DEAD) )
        /* attempt to dispose of the living */
        return -1;

    sigunblock(pid);
    plx = splproc();

    /* remove from proclist ... */
    if( pid->prev )
        pid->prev->next = pid->next;
    if( pid->next )
        pid->next->prev = pid->prev;
    if( proclist == pid )
        proclist = pid->next;

    /* need to orphan any children it had */
    for(p=pid->booboo; p; p=p->brother){
        p->mommy = 0;
    }

    /* remove from sibling list */
    if( pid->brother )
        pid->brother->sister = pid->sister;
    if( pid->sister )
        pid->sister->brother = pid->brother;

    if( pid->mommy && pid->mommy->booboo == pid ){
        if( pid->sister )
            pid->mommy->booboo = pid->sister;
        else
            pid->mommy->booboo = pid->brother;
    }

    /* remove from ready and realtime lists */
    if( pid->rnext )
        pid->rnext->rprev = pid->rprev;
    if( pid->rprev )
        pid->rprev->rnext = pid->rnext;

    if( pid->rtnext )
        pid->rtnext->rtprev = pid->rtprev;
    if( pid->rtprev )
        pid->rtprev->rtnext = pid->rtnext;

    if( readylist == pid )
        readylist = pid->rnext;
    if( realtimelist == pid )
        realtimelist = pid->rtnext;


    splx(plx);
    bzero(pid, sizeof(struct Proc));

    if( pid->alloc_size )
        /* initial process was not alloc()ed */
        free(pid->stack_start, pid->alloc_size);

    return 0;
}

/*
  prioritizer runs as a seperate process
  which sets the priority of processes
  based on cpu use, ...
*/

static void
prioritizer(void){
    struct Proc *p;
    int plx;
    utime_t lastt;
    int dt;

    currproc->timeslice = 255;
    currproc->flags = PRF_AUTOREAP | PRF_IMPORTANT;

    while(1){

        /* kprintf("*P*"); */

        lastt = get_time();
        usleep(PRIO_TIME);

        /* calculate estimated cpu use params */
        dt = get_time() - lastt;
        dt = (dt + PRIO_TIME/2) / PRIO_TIME;
        if( dt > 31 )
            dt = 31;
        dt = 1 << dt;

        for(p=(proc_t)proclist; p; p=p->next){
            /* recalc estimated cpu */
            p->estcpu /= dt;
            /* QQQ base prio on estcpu? or yielded/allotted? or both? */
            if( p->timeallotted ){
                if( p->timeallotted != p->p_allotted ){
                    p->timeused +=
                        (p->timeallotted - p->p_allotted
                         - p->timeyielded + p->p_yielded) * 16 /
                        (p->timeallotted - p->p_allotted);
                    p->timeused /=2;

                    p->p_allotted = p->timeallotted;
                    p->p_yielded  = p->timeyielded;
                }

                p->prio = (p->timeused
                           * (p->estcpu * 16 * PROC_TIME) / (PRIO_TIME * 2)) / 8
                    + p->nice;

            }else{
                p->prio = p->nice;
            }
            if( p->prio < 0 ) p->prio = 0;
            if( p->prio > 64) p->prio = 64;


            if( p->state & PRS_DEAD && (!p->mommy || p->mommy==currproc
                                        || p->mommy->flags & PRF_AUTOREAP) ){
                /* dead orphan, do something with the body before it smells */
                struct Proc *prev;

                prev = p->prev;
                dispose_of_cadaver(p);
                p = prev;
                if( !p )
                    p = (proc_t)proclist;
            }

        }
    }
}

/*
  scheduler runs as a seperate process
  which schedules processes to run

  NB: scheduler must not ever block
*/

static void
scheduler(void){
    volatile int i;
    struct Proc *p, *r, *rl;
    int plx, s;
    u_long lastt, dt;

    currproc->timeslice = 255;
    currproc->flags = PRF_NONBLOCK | PRF_AUTOREAP | PRF_IMPORTANT;

    while(1){

        /* readylist = 0 forces this process to
           run in the event it gets preempted */
        readylist = 0;
    startover:
        r = rl = 0;

        for(p=(proc_t)proclist; p; p=p->next){
            /* kprintf("sched %X\n", (u_long)p);*/
            PROCOK(p);

            p->rnext = p->rprev = 0;

            if( p == currproc )
                /* skip self */
                continue;

            if( p->flags & PRF_REALTIME ){
                if( p->rtnext || p->rtprev || realtimelist == p ){
                    /* this process is already on the realtime run list */
                    /* (this cannot happen, of course, or we wouldnt be here) */
                    continue;
                }else{
                    /* a real-time process which has used up its timeslice and been pre-empted */
                    /* add it to the run list */
                }
            }

            if( p->state & PRS_BLOCKED ){

                if( p->flags & PRF_NONBLOCK ){
                    /* force non-blocking processes to be not blocked */
                    /* (they can still be dead) */
                    sigunblock(p);
                }

                /* timeout? - how should we let the proc know it timed out? */
                if( p->timeout && p->timeout <= get_time() ){
                    p->timeout = 0;
                    sigunblock(p);
                    if( p->wchan != WCHAN_NEVER )
                        ksendmsg(p, MSG_TIMEOUT);
                }
            }

            /* handle alarm clocks */
            if( p->alarm && p->alarm <= get_time() ){
                if( p->state & PRS_BLOCKED )
                    sigunblock(p);
                ksendmsg(p, MSG_ALARM);
            }

            if( !p->pcnt ){
                if( p->state == PRS_RUNNABLE ){
                    p->pcnt = p->prio;
                    if( r ){
                        r->rnext = p;
                        p->rprev = r;
                        r = p;
                    }else{
                        r = rl = p;
                    }
                }
                /* blocked processes decr pcnt to 0 where they stay
                   until woken
                */
            }else{
                p->pcnt --;
            }

        } /* Eo for */


        if( ! r ){
            /* nothing is runnable */
            /* kprintf("sched idle\n"); */
            idle();
            goto startover;
        }

        /* add self to end of ready list */
        r->rnext = (proc_t)currproc;
        currproc->rprev = r;

        /* install readylist */
        plx = splproc();
        readylist = rl;
        spl0();

        /* kprintf("sched done\n");*/
        /* yield the remainder of our slice */
        yield();
    }
}


/*
  suspend a process
*/

void
sigsuspend(proc_t proc){
    int plx;

    PROCOK(proc);
    if( proc->flags & PRF_NONBLOCK )
        /* cannot kill */
        return;

    plx = splproc();
    proc->state |= PRS_SUSPENDED;
    if( proc == currproc )
        yield();
    else
        splx(plx);
}

/*
  continue a suspended process
*/
void
sigcont(proc_t proc){
    int plx;

    PROCOK(proc);
    plx = splproc();
    proc->state &= ~PRS_SUSPENDED;
    splx(plx);
}

void
_end_proc(proc_t proc, int rv){

    int plx = splproc();
    proc->state  |= PRS_DEAD;
    proc->exitval = rv;

    if( proc->mommy ){
        proc->mommy->flags |= PRF_DEADKID;
        ksendmsg(proc->mommy, MSG_DEADKID);
    }

    wakeup((proc_t)currproc);

    if( proc == currproc )
        yield();
    else
        splx(plx);
}

/*
  exit
  terminate a process
  parent can retrieve the value passed
*/

void
exit(int rv){
    extern void getline_cleanup(void);

    PROCOK(currproc);

    getline_cleanup();

    _end_proc((proc_t)currproc, rv);
}

/*
  kill a process dead
*/

void
sigkill(proc_t proc){

    PROCOK(proc);
    if( proc->flags & PRF_NONBLOCK )
        /* cannot kill */
        return;

    _end_proc(proc, -1);
}


/*
  unblock a blocked process
*/

void
sigunblock(proc_t proc){
    int plx;
    int w;

    PROCOK(proc);
    w = (int)proc->wchan % WAITTABLESIZE;
    plx = splproc();

    if( proc->wprev )
        proc->wprev->wnext = proc->wnext;
    if( proc->wnext )
        proc->wnext->wprev = proc->wprev;
    if( proc == waittable[w] )
        waittable[w] = proc->wnext;

    proc->wnext = proc->wprev = 0;
    proc->state &= ~ PRS_BLOCKED;
    proc->wmsg = 0;

    if( proc->flags & PRF_REALTIME && proc->state == PRS_RUNNABLE ){
        realtimelist_add(proc);
        sched_yield();
    }

    splx(plx);
}

/*
  sleep for usec microsecs
*/

void
usleep(u_long usec){
    utime_t until;

    PROCOK(currproc);
    if( !currproc || currproc->flags & PRF_NONBLOCK ){
        /* this process cannot block, do special sleep */
        until = usec + get_time();
        while( get_time() < until )
            ;
        return;
    }

    tsleep(WCHAN_NEVER, currproc->prio, "time", usec);

}

/*
  returns 0 if woken by wakeup(), or 1 if timedout
*/

int
tsleep(void *wchan, int prio, const char *wmsg, int timo){
    int plx;
    int w;

    PROCOK(currproc);
    if( currproc->flags & PRF_NONBLOCK ){
        return -1;
    }

    w = (int)wchan % WAITTABLESIZE;

    plx = splproc();
    currproc->wchan = wchan;
    currproc->wmsg  = wmsg;
    currproc->timeout = timo ? get_time() + timo : 0;

    currproc->wnext = waittable[ w ];
    currproc->wprev = 0;
    if( waittable[ w ] )
        waittable[ w ]->wprev = (proc_t)currproc;
    waittable[ w ] = (proc_t)currproc;

    currproc->state |= PRS_BLOCKED;
    yield();

    currproc->prio = prio;
    return currproc->timeout ? currproc->timeout <= get_time() : 0;
}

int
rt_tsleep(void *wchan, const char *wmsg, int timo){
    int plx;

    plx = splproc();
    currproc->flags |= PRF_REALTIME;
    tsleep(wchan, 0, wmsg, timo);
}

/*
  wakeup blocked processes
*/

void
wakeup(void *wchan){
    struct Proc *p;
    int plx;
    int w;

    w = (int)wchan % WAITTABLESIZE;

    plx = splproc();
    for(p=waittable[w]; p; p=p->wnext){
        if( p->wchan == wchan )
            sigunblock(p);
    }

    splx(plx);
}

/*
  add a process to realtime run list
*/

void
realtimelist_add(proc_t proc){

    PROCOK(proc);

    int plx = splhigh();
    proc->rtnext = 0;
    if( realtimetail ){
        realtimetail->rtnext = proc;
        proc->rtprev = (proc_t)realtimetail;
    }else{
        proc->rtprev = 0;
    }
    realtimetail = proc;

    if( !realtimelist ){
        realtimelist = proc;
    }
    sched_yield();
    splx(plx);
}

/*
  remove front process from realtime run list
*/

proc_t
realtimelist_next(void){
    proc_t next;

    if( ! realtimelist )
        return 0;

    int plx = splhigh();
    next = (proc_t)realtimelist;
    realtimelist = next->rtnext;
    next->rtnext = 0;

    if( realtimelist ){
        realtimelist->rtprev = 0;
    }else{
        realtimetail = 0;
    }

    splx(plx);
    return next;
}

proc_t
readylist_next(void){
    proc_t next;

    if( ! readylist )
        return 0;

    next = (proc_t)readylist;
    readylist = next->rnext;
    next->rnext = 0;

    if( readylist ){
        readylist->rprev = 0;
    }

    return next;
}


/*
  yield the remainder of our timeslice
*/

void
yield(void){

    if( !currproc )
        return;
    md_yield();
}

proc_t
_yield_next_proc(void){
    proc_t nextproc;

    // ARM nvic already prevents lower prio ints
#ifdef PLATFORM_I386
    splproc();
#endif

    /* who runs next? */
    if( realtimelist ){
        int pl = splhigh();
        nextproc = realtimelist_next();
        splx(pl);
    }
    else if( readylist ){
        nextproc = readylist_next();
    }
    else if( schedulerproc ){
        nextproc = schedulerproc;
    }
    else{
        PANIC("_yield: no next proc");
    }

    /* stats */
    if( timeremain > 0 )
        currproc->timeyielded += timeremain;

    /* kprintf(" ynp curr %x, next %x; curr sp %x, next sp %x\n",
       currproc, nextproc, currproc->sp, nextproc->sp); */


#ifdef CHECKPROC
    if( !nextproc || nextproc->sp < (u_long)nextproc->stack_start ){
        kprintf("stack overflow: next %x, sp %x, start %x\n", nextproc, nextproc->sp, nextproc->stack_start);
        PANIC("stack overflow");
    }
    if( nextproc->sp < nextproc->lowsp ) nextproc->lowsp = nextproc->sp;
#endif

    nextproc->timeallotted += nextproc->timeslice;
    timeremain = nextproc->timeslice;
    if( !timeremain ) timeremain = 1;

    return nextproc;
}

void
_yield_bottom(void){

    /* are there any pending msgs that need to be delivered? */
    if( (currproc->flags & PRF_MSGPEND) && !currproc->throwing ){
        currproc->throwing = 1;
        spl0();
        _xthrow();
        currproc->throwing = 0;
    }

    spl0();
}

