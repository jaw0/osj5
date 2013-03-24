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

#ifdef PLATFORM_ARM_CM
#  define STACK_MIN	1024
#else
#  define STACK_MIN	4096
#endif
#define INIT_STACK	4096


struct ReadyList {
    struct Proc *head;
    struct Proc *tail;
};


volatile struct Proc *proclist = 0;
volatile struct ReadyList readylist[READYLISTSIZE];
volatile long timeremain = 0;
volatile struct Proc *currproc = 0;
struct Proc *idle_proc = 0;
static struct Proc *waittable[WAITTABLESIZE];



static void sysmaint(void), idleloop(void);
static int dispose_of_cadaver(proc_t);
void readylist_add(proc_t);
void realtimelist_remove(void);
void idle(void);


/* trampoline to start proc */
void
_start_proc( void (*entry)(void) ){
    entry();
    exit(-1);
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

    /* kprintf("proc %X sp %X\n", proc, proc->sp); */
    /* change a few entries in proc */
    proc->name        = name;
    proc->alloc_size  = asize;
    proc->stack_start = stack;
    proc->memused     = asize;
    proc->timeslice   = 5;	/* QQQ */
    proc->prio        = 1;

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

    readylist_add(proc);

    return proc;

}

/*
  init_proc
  initialize multi-process stuff
*/

void
init_proc(proc_t p){

    bzero(readylist, sizeof(readylist));

    /* set up initial proc */
    bzero(p, sizeof(struct Proc));
    bzero(waittable, WAITTABLESIZE * sizeof(struct Proc *));

    p->timeslice = 5;
    p->prio      = 1;

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

#ifdef USE_NSTDIO
    p->stdin  = console_port;
    p->stdout = console_port;
    p->stderr = console_port;
#endif

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

    /* start maint proc in a child process */
    start_proc(1024, sysmaint, "sysmaint");
    bootmsg(" sysmaint");

    idle_proc = start_proc(1024, idleloop, "idleloop");
    bootmsg(" idleloop" );

    bootmsg("\nproc starting multiuser\n");

    /* this starts up multiuser mode */
    spl0();
    irq_enable();

    currproc->flags &= ~PRF_NONBLOCK;
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
    int plx, i;

    PROCOK(pid);

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

    /* remove from readylist */
    splhigh();

    for(i=0; i<READYLISTSIZE; i++){
        struct ReadyList *rl = readylist + i;

        if( rl->head == pid ) rl->head = pid->rnext;
        if( rl->tail == pid ) rl->tail = pid->rprev;
    }

    if( pid->rnext )
        pid->rnext->rprev = pid->rprev;
    if( pid->rprev )
        pid->rprev->rnext = pid->rnext;

    splx(plx);
    bzero(pid, sizeof(struct Proc));

    if( pid->alloc_size )
        /* initial process was not alloc()ed */
        free(pid->stack_start, pid->alloc_size);

    return 0;
}

static void
idleloop(void){

    currproc->timeslice = 255;
    currproc->flags = PRF_IMPORTANT;
    currproc->state = PRS_BLOCKED;
    yield();

    while(1){
        currproc->state = PRS_BLOCKED;
        currproc->wmsg  = "idle";
        idle();
        yield();
    }
}

/*
  perform system maintenance
*/

static void
sysmaint(void){
    volatile int i;
    struct Proc *p, *r, *rl;
    int plx, s;
    u_long lastt = 0, dt;
    utime_t timeout;

    currproc->timeslice = 5;
    currproc->prio      = 4;
    currproc->flags     = PRF_AUTOREAP | PRF_IMPORTANT;

    while(1){
        // run sooner on first iteration - so ps output is nonzero
        timeout = lastt ? get_time() + MAINT_TIME : get_time() + PROC_TIME;
        dt      = (int)(get_time() - lastt) / PROC_TIME;
        lastt   = get_time();

        for(p=(proc_t)proclist; p; p=p->next){
            // printf("sm %x %x\n", p, p->next);
            PROCOK(p);

            if( p == currproc )
                /* skip self */
                continue;

            if( p->state & PRS_BLOCKED ){

                if( p->flags & PRF_NONBLOCK ){
                    /* force non-blocking processes to be not blocked */
                    /* (they can still be dead) */
                    sigunblock(p);
                }

                /* timeout */
                if( p->timeout && p->timeout <= get_time() ){
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

            if( p->timeout && (p->timeout < timeout) ) timeout = p->timeout;
            if( p->alarm   && (p->alarm   < timeout) ) timeout = p->alarm;


            /* statistics */
            if( lastt && dt && p->timeallotted ){
                if( p->timeallotted != p->p_allotted ){
                    int alloted = p->timeallotted - p->p_allotted;
                    int yielded = p->timeyielded  - p->p_yielded;
                    int used = alloted - yielded;
                    if( used < 0 ) used = 0;
                    int est  = 100 * KESTCPU * used / dt;
                    p->estcpu = ( est + p->estcpu ) / 2;

                    p->timeused += used;
                    p->timeused /=2;

                    p->p_allotted = p->timeallotted;
                    p->p_yielded  = p->timeyielded;

                }else{
                    p->estcpu /= 2;
                }
            }

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

        /* sleep until the next timeout */
        next_timeout = timeout;
        tsleep( &next_timeout, currproc->prio, "time", 0);
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

int
_wait_hash(int wchan){

    wchan ^= wchan >> 16;
    wchan ^= wchan >> 8;
    return wchan % WAITTABLESIZE;
}


/*
  unblock a blocked process
*/

void
sigunblock(proc_t proc){
    int plx;
    int w;

    PROCOK(proc);
    w = _wait_hash( (int) proc->wchan );
    plx = splhigh();

    /* remove from wait table */
    if( proc->wprev )
        proc->wprev->wnext = proc->wnext;
    if( proc->wnext )
        proc->wnext->wprev = proc->wprev;
    if( proc == waittable[w] )
        waittable[w] = proc->wnext;

    proc->wnext = proc->wprev = 0;
    proc->wmsg  = 0;
    proc->wchan = 0;

    if( proc->state & PRS_BLOCKED ){
        proc->state &= ~ PRS_BLOCKED;

        if( proc->state == PRS_RUNNABLE ){
            readylist_add(proc);
            if( proc->flags & PRF_REALTIME ) sched_yield();
        }
    }

    splx(plx);
}


void
_set_timeout(utime_t timeo){

    if( !next_timeout || (timeo < next_timeout) )
        wakeup( &next_timeout );
}

void
set_alarm(int timeo){
    currproc->alarm = get_time() + timeo;
    _set_timeout( currproc->alarm );
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

    if( prio < 0 ) prio = currproc->prio;
    w = _wait_hash( (int)wchan );

    // kprintf("tsleep %x %s on %s\n", currproc, currproc->name, wmsg);
    if( currproc->wchan ){
        kprintf("already waiting on %x %s s %x\n", currproc->wchan, currproc->wmsg, currproc->state);
        PANIC("tsleep dupe!");
    }

    plx = splhigh();
    currproc->wchan   = wchan;
    currproc->wmsg    = wmsg;
    currproc->timeout = timo ? get_time() + timo : 0;

    currproc->wnext = waittable[ w ];
    currproc->wprev = 0;
    if( waittable[ w ] )
        waittable[ w ]->wprev = (proc_t)currproc;
    waittable[ w ] = (proc_t)currproc;

    if( currproc->wnext == currproc || currproc->wprev == currproc )
        PANIC("insert waitlist loop");
    currproc->prio   = prio;
    currproc->state |= PRS_BLOCKED;

    if( currproc->timeout )
        _set_timeout( currproc->timeout );

    yield();

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
    struct Proc *n;
    int plx;
    int w;

    w = _wait_hash( (int)wchan );

    plx = splhigh();
    for(p=waittable[w]; p; p=n){
        n = p->wnext;
        if( p == n ) PANIC("waitlist loop!");
        if( p->wchan == wchan )
            sigunblock(p);
    }

    splx(plx);
}

/*
  add a process to ready list
*/

void
readylist_add(proc_t proc){

    PROCOK(proc);
    if( proc->rnext || proc->rprev ){
        kprintf("cannot add to readylist proc %x (%s), (%x,%x) cp %x\n",
                proc, proc->name, proc->rprev, proc->rnext, currproc);
        return;
    }

    int plx = splhigh();
    proc->rnext = 0;

    if( proc->prio >= READYLISTSIZE ) proc->prio = READYLISTSIZE - 1;
    struct ReadyList *rl = readylist + proc->prio;

    if( rl->tail ){
        rl->tail->rnext = proc;
    }
    proc->rprev = rl->tail;
    rl->tail = proc;

    if( !rl->head ){
        rl->head = proc;
    }

    splx(plx);
}

/*
  remove front process from ready list
*/

proc_t
readylist_next(void){
    proc_t next = 0;
    int i;

    int plx = splhigh();

    for(i=0; i<READYLISTSIZE; i++){
        struct ReadyList *rl = readylist + i;
        if( ! rl->head ) continue;

        next = rl->head;
        rl->head = next->rnext;
        next->rnext = 0;

        if( rl->head ){
            rl->head->rprev = 0;
        }else{
            rl->tail = 0;
        }

        /* make sure it is still runnable */
        if( next->state != PRS_RUNNABLE ){
            next = 0;
            continue;
        }

        break;
    }

    splx(plx);

    if( next ) return next;
    return idle_proc;

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

    /* NB: we are already (at least) at splproc */

    if( currproc && currproc->state == PRS_RUNNABLE )
        readylist_add( currproc );

    /* who runs next? */
    nextproc = readylist_next();

    if( ! nextproc ){
        PANIC("no nextproc!");
    }

    /* stats */
    if( currproc ){
        if( timeremain > 0 )
            currproc->timeyielded += timeremain;
    }

    //kprintf(" ynp curr %x (%s), next %x (%s); curr sp %x, next sp %x start %x\n",
    //   currproc, currproc->name, nextproc, nextproc->name, currproc->sp, nextproc->sp, nextproc->stack_start);


#ifdef CHECKPROC
    if( nextproc != currproc && nextproc->sp < (u_long)nextproc->stack_start ){
        kprintf("stack overflow: next %x (%s), sp %x, start %x\n", nextproc, nextproc->name, nextproc->sp, nextproc->stack_start);
        PANIC("stack overflow");
    }
    if( nextproc->sp && nextproc->sp < nextproc->lowsp ) nextproc->lowsp = nextproc->sp;
#endif

    nextproc->timeallotted += nextproc->timeslice;
    timeremain = nextproc->timeslice;

    return nextproc;
}

void
_yield_bottom(void){

    /* are there any pending msgs that need to be delivered? */
    if( (currproc->flags & PRF_MSGPEND) ){
        spl0();
        _xthrow();
        currproc->throwing = 0;
    }
}

int
_need_yield_bottom(void){
    /* do we need to do a yield_bottom */
    int r = ((currproc->flags & PRF_MSGPEND) && !currproc->throwing) ? 1 : 0;
    /* set flag now, to avoid recursing when we come out of interrupt mode */
    if( r ) currproc->throwing = 1;
    return r;
}

