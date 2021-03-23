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
#  ifdef KSTACK_SIZE
#    define STACK_MIN	256
#  else
#    define STACK_MIN	1024
#  endif
#else
#  define STACK_MIN	4096
#endif

#ifndef INIT_STACK
#  ifdef KSTACK_SIZE
#    define INIT_STACK  2048
#  else
#    define INIT_STACK	4096
#  endif
#endif

#ifndef TIMESLICE
#  define TIMESLICE	5
#endif

/****************************************************************/

#ifdef PROCTRACE
struct crumb {
    const char *event;
    int when;
    const struct Proc *p;
    int arg1;
};
#define NR_CRUMBS       128
static struct crumb crumbs[NR_CRUMBS];
static u_long cur_crumb = 0;
static int    trace_enabled = 0;

static inline void
TRACE(const char *event, const struct Proc *p , u_long arg1) {
    if( ! trace_enabled ) return;
    struct crumb *crumb = &crumbs[cur_crumb % NR_CRUMBS];
    crumb->event = event;
    crumb->when  = get_hrtime();
    crumb->p     = p;
    crumb->arg1  = arg1;
    cur_crumb++;
}

void
proc_trace_log(void){
    int st = (cur_crumb > NR_CRUMBS) ? cur_crumb - NR_CRUMBS : 0;
    int wh = crumbs[st].when;
    short i;

    for(i=st; i<cur_crumb; i++){
        int n  = i % NR_CRUMBS;
        int dt = crumbs[n].when - wh;
        const struct Proc *p = crumbs[n].p;

        //syslog("[PTRACE] %d\t%s\t%x/%s %x\n", dt, crumbs[n].event, p, p?p->name:"*", crumbs[n].arg1);
        printf("[PTRACE] %d\t%d\t%s\t%x/%s %x\n", dt, crumbs[n].when, crumbs[n].event, p, p?p->name:"*", crumbs[n].arg1);
    }
}

void proc_trace_enable(void){  cur_crumb = 0; trace_enabled = 1; }
void proc_trace_disable(void){ trace_enabled = 0; }

void proc_trace_add(const char *event, u_long arg1){
    TRACE(event, currproc, arg1);
}

#else
#  define TRACE(a,b,c)
void proc_trace_enable(void){}
void proc_trace_disable(void){}
void proc_trace_log(void){}
void proc_trace_add(const char *event, u_long arg1){}
#endif
/****************************************************************/


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
#ifndef PROC_SMALL
    proc->memused     = asize;
    if(currproc) currproc->memused -= asize;
#endif
    proc->timeslice   = TIMESLICE;
    proc->prio        = READYLISTSIZE/2;

#ifdef CHECKPROC
    proc->magic = PROCMAGIC;
    proc->lowsp = proc->sp;
#endif
#ifdef USE_NSTDIO
    if( currproc ){
        /* copy from parent */
        proc->stdin  = STDIN;
        proc->stdout = STDOUT;
        proc->stderr = STDERR;
    }
#endif
    if( currproc ) proc->cwd = currproc->cwd;

    /* keep track of family tree */
    /* are you my mommy? */
    proc->mommy = (proc_t)currproc;

    /* siblings */
    if( currproc )
        proc->brother = currproc->booboo;

    int plx = splhigh();

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

    /* set up initial proc */
    bzero(p, sizeof(struct Proc));
    bzero(waittable, WAITTABLESIZE * sizeof(struct Proc *));

    p->timeslice = TIMESLICE;
    p->prio      = READYLISTSIZE/2;
    /* estimated size of needed stack, for run-time error checking */
    p->stack_start = _heap_limit = (char*)p - INIT_STACK;
    p->flags  = PRF_NONBLOCK | PRF_AUTOREAP;
    p->cwd    = 0;
    p->name = "init";

#ifndef PROC_SMALL
    p->timeallotted = p->timeslice;
#endif
#ifdef USE_NSTDIO
    p->stdin  = kconsole_port;
    p->stdout = kconsole_port;
    p->stderr = kconsole_port;
#endif
#ifdef CHECKPROC
    p->magic = PROCMAGIC;
    p->lowsp = (u_long)&p;
#endif
    currproc = p;

    p->next = (proc_t)proclist;
    if( proclist )
        proclist->prev = p;
    proclist = p;

    timeremain = p->timeslice;

#if defined(USE_FILESYS) && defined(MOUNT_ROOT)
    if( !chdir( MOUNT_ROOT ) ){
        bootmsg("root on %s\n", MOUNT_ROOT);
    }
#endif


#if defined(USE_CONSOLE) && defined(USE_CLI)
    if( (bootflags & BOOT_SINGLE) && kconsole_port ){
        bootmsg("proc starting single user\nexit to continue with multi user startup\n");
        splx(IPL_PROC);
        shell();
    }
#endif

#ifdef USE_NSTDIO
    p->stdin  = console_port;
    p->stdout = console_port;
    p->stderr = console_port;
#endif

    bootmsg("proc starting: init");

    /* start maint proc in a child process */
    start_proc(256, sysmaint, "sysmaint");
    bootmsg(" sysmaint");

    idle_proc = start_proc(256, idleloop, "idleloop");
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
  become detached orphan
*/

void
proc_detach(proc_t pid){

    if( !pid ) pid = currproc;

    int plx = splproc();

    /* remove from sibling list */
    if( pid->brother )
        pid->brother->sister = pid->sister;
    if( pid->sister )
        pid->sister->brother = pid->brother;

    /* remove from parent */
    if( pid->mommy && pid->mommy->booboo == pid ){
        if( pid->sister )
            pid->mommy->booboo = pid->sister;
        else
            pid->mommy->booboo = pid->brother;
    }

    pid->sister = pid->brother = 0;
    pid->mommy = 0;

    splx(plx);
}


/*
  do the work of cleaning up a dead process
*/

static int
dispose_of_cadaver(proc_t pid){
    struct Proc *p;
    int plx, i, m;

    PROCOK(pid);

    if( ! (pid->state & PRS_DEAD) )
        /* attempt to dispose of the living */
        return -1;

    m = (int) pid->mommy;

    sigunblock(pid);

    plx = splproc();

    /* need to orphan any children it had */
    for(p=pid->booboo; p; p=p->brother){
        proc_detach( p );
    }

    /* remove from sibling list */
    proc_detach( pid );

    splhigh();

    /* remove from proclist ... */
    if( pid->prev )
        pid->prev->next = pid->next;
    if( pid->next )
        pid->next->prev = pid->prev;
    if( proclist == pid )
        proclist = pid->next;

    /* remove from readylist */
    for(i=0; i<READYLISTSIZE; i++){
        struct ReadyList *rl = (struct ReadyList*)readylist + i;

        if( rl->head == pid ) rl->head = pid->rnext;
        if( rl->tail == pid ) rl->tail = pid->rprev;
    }

    if( pid->rnext )
        pid->rnext->rprev = pid->rprev;
    if( pid->rprev )
        pid->rprev->rnext = pid->rnext;

    splx(plx);

    if( m ){
        /* initial process was not alloc()ed */
#ifdef PROC_SMALL
        zfree(pid->stack_start, 0);
#else
        zfree(pid->stack_start, pid->alloc_size);
#endif
    }
    return 0;
}


static void
idleloop(void){

    currproc->timeslice = 255;
    currproc->flags = PRF_IMPORTANT;
    currproc->state = PRS_BLOCKED;
    currproc->prio  = READYLISTSIZE - 1;
    yield();

    while(1){
        currproc->state = PRS_BLOCKED;
        currproc->wmsg  = "idle";
        TRACE("idle", currproc, 0);
        idle();
        yield();
    }
}

/*
  perform system maintenance
*/

static void
sysmaint(void){
    struct Proc *p;
    utime_t lastt = 0, dt;

    currproc->timeslice = TIMESLICE;
    currproc->prio      = (READYLISTSIZE*3)/4;
    currproc->flags     = PRF_AUTOREAP | PRF_IMPORTANT;

    while(1){
#ifdef PROC_HIRES
        utime_t now = get_hrtime();
#else
        utime_t now = get_time();
#endif
        dt      = now - lastt;
        lastt   = now;

        splproc();
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
            }


#ifndef PROC_SMALL
            /* statistics */
            if( lastt && dt && p->timeallotted ){
                if( p->timeallotted != p->p_allotted ){
                    int alloted = p->timeallotted - p->p_allotted;
                    int yielded = p->timeyielded  - p->p_yielded;
                    int used = alloted - yielded;
                    if( used < 0 ) used = 0;

                    p->timeused += used;
                    p->timeused /=2;
#  ifdef PROC_HIRES
                    /* use hrtime */
                    int est = 100 * KESTCPU * p->hrtimeused / dt;
                    p->hrtimeused = 0;
#  else
                    /* timeslices used */
                    int est  = 100 * KESTCPU * used  * PROC_TIME / dt;
#  endif
                    if( !p->p_allotted ) p->estcpu = est;	/* initial value */
                    p->estcpu = ( est + p->estcpu ) / 2;
                    p->p_allotted = p->timeallotted;
                    p->p_yielded  = p->timeyielded;

                }else{
                    p->estcpu /= 2;
                }
            }
#endif

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
        // run sooner on first iteration - so ps output is nonzero
        usleep( lastt ? MAINT_TIME : PROC_TIME );
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

static int
_wait_hash(int wchan){

    wchan ^= wchan >> 16;
    wchan ^= wchan >> 8;
    return wchan % WAITTABLESIZE;
}

static inline void
_remove_from_waitlist(proc_t proc, int w){

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

}

/*
  unblock a blocked process
*/

void
sigunblock(proc_t proc){

    PROCOK(proc);

    int w = _wait_hash( (int) proc->wchan );
    int plx = splhigh();
    _remove_from_waitlist(proc, w);

    if( proc->state & PRS_BLOCKED ){
        proc->state &= ~ PRS_BLOCKED;

        if( proc->state == PRS_RUNNABLE ){
            readylist_add(proc);
            if( proc->flags & PRF_REALTIME ){
                TRACE("unbl/rt", proc, 0);
                sched_yield();
            }else{
                TRACE("unbl/r", proc, 0);
            }
        }else{
            TRACE("unbl/nr", proc, 0);
        }
    }else{
        TRACE("unbl/nb", proc, 0);
    }

    splx(plx);
}


void
_set_timeout(utime_t timeo){
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

    if( usec <= 0 ) return;

    if( !currproc || (currproc->flags & PRF_NONBLOCK) ){
        /* this process cannot block, do special sleep */
        until = usec + get_time();
        while( get_time() < until )
            ;
        return;
    }

    PROCOK(currproc);
    tsleep((void*)WCHAN_NEVER, currproc->prio, "time", usec);
}

/* asynchronous sleep - add to waitlist, and return
   call await() to block
*/

void
asleep(void *wchan, const char *wmsg){

    if(!currproc) return;
    PROCOK(currproc);
    if( currproc->flags & PRF_NONBLOCK ){
        return;
    }

    int nw = _wait_hash( (int)wchan );
    int ow = _wait_hash( (int)currproc->wchan );

    int plx = splhigh();

    // already on waitlist? remove
    if( currproc->wchan ){
        _remove_from_waitlist( (proc_t)currproc, ow );
    }

    // add to waitlist
    currproc->wchan   = wchan;
    currproc->wmsg    = wmsg;

    if( wchan != (void*)WCHAN_NEVER ){
        currproc->wnext = waittable[ nw ];
        currproc->wprev = 0;
        if( waittable[ nw ] )
            waittable[ nw ]->wprev = (proc_t)currproc;
        waittable[ nw ] = (proc_t)currproc;

        if( currproc->wnext == currproc || currproc->wprev == currproc )
            PANIC("insert waitlist loop");
    }

    splx(plx);
}

void
aunsleep(void){

    if(!currproc) return;
    PROCOK(currproc);

    int ow  = _wait_hash( (int)currproc->wchan );
    int plx = splhigh();

    // already on waitlist? remove
    _remove_from_waitlist( (proc_t)currproc, ow );

    splx(plx);
}

int
await(int prio, int timo){

    if(!currproc) return;
    PROCOK(currproc);
    if( currproc->flags & PRF_NONBLOCK ){
        return;
    }

    if( prio < 0 ) prio = currproc->prio;
    u_char oprio = currproc->prio;
    u_char ofrt  = currproc->flags & PRF_REALTIME;

    int plx = splhigh();
    if( !currproc->wmsg ) return;

    // prio | 0x80 => realtime
    currproc->prio = prio & 0x7F;
    if( prio & 0x80 ) currproc->flags |= PRF_REALTIME;

    currproc->timeout = timo ? get_time() + timo : 0;
    utime_t to = currproc->timeout;

    if( currproc->timeout )
        _set_timeout( currproc->timeout );

    currproc->state |= PRS_BLOCKED;
    yield();

    currproc->prio = oprio;
    if( !ofrt ) currproc->flags &= ~PRF_REALTIME;

    return to ? to <= get_time() : 0;
}


/*
  returns 0 if woken by wakeup(), or 1 if timedout
*/

int
tsleep(void *wchan, int prio, const char *wmsg, int timo){
    int plx = splproc();
    asleep( wchan, wmsg );
    int r = await( prio, timo );
    splx(plx);
    return r;
}

/*
  wakeup blocked processes
*/

int
wakeup(void *wchan){
    struct Proc *p;
    struct Proc *n;
    int plx;
    int w, r=0;

    TRACE("wake", 0, (int)wchan);

    w = _wait_hash( (int)wchan );

    plx = splhigh();
    for(p=waittable[w]; p; p=n){
        n = p->wnext;
        if( p == n ) PANIC("waitlist loop!");
        if( p->wchan == wchan ){
            sigunblock(p);
            r ++;
        }
    }

    splx(plx);

    TRACE("woke", 0, plx);
    extern int logger_state;
    TRACE("woke", 0, logger_state);

    /* return bool - did we wake something? */
    return r;
}

/*
  add a process to ready list
*/

void
readylist_add(proc_t proc){

    PROCOK(proc);
    int plx = splhigh();
    if( proc->rnext || proc->rprev ){
        // NB: it is possible for a process to be woken during the yield(),
        // y_n_p will then attept to re-add to th ready list. check + skip the dupe.
        // alternatively, we could splhigh for the whole time, but that'd not be fun.

        // kprintf("cannot add to readylist proc %x (%s), (%x,%x) cp %x; tr %x %x\n",
        //         proc, proc->name, proc->rprev, proc->rnext, currproc, proc->trace, proc->trace2);

        splx(plx);
        return;
    }

    TRACE("rladd", proc, proc->prio);

    proc->rnext = 0;

    if( proc->prio >= READYLISTSIZE ) proc->prio = READYLISTSIZE - 1;
    struct ReadyList *rl = (struct ReadyList*)readylist + proc->prio;

    if( rl->head == proc ){
        // already on the runlist (the only thing on)
        splx(plx);
        return;
    }

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
        struct ReadyList *rl = (struct ReadyList*)readylist + i;
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

    // if( next && next->rprev )
    //     kprintf("rlnext has prev cp=%x next=%x, prev=%x\n", currproc, next, next->rprev);

    if( next ) return next;
    return idle_proc;

}


/*
  yield the remainder of our timeslice
*/

void
yield(void){

    TRACE("yield", currproc, 0);
    if( !currproc )
        return;
    md_yield();
}

proc_t
_yield_next_proc(void){
    proc_t nextproc;

    /* NB: we are already (at least) at splproc */
    //kprintf("ynp sp %x, psp %x, msp %x, control %x\n",
    //        get_sp(), get_psp(), get_msp(), get_control());

    TRACE("ynp", currproc, currproc->state);
#ifdef PROC_HIRES
    utime_t now = get_hrtime();
#endif

    int plx = splhigh();
    if( currproc && currproc->state == PRS_RUNNABLE ){
        TRACE("ynp/rl+", currproc, 0);
        readylist_add( (proc_t)currproc );
    }

    splx(plx);

    /* who runs next? */
    nextproc = readylist_next();

    if( ! nextproc ){
        PANIC("no nextproc!");
    }

    if( currproc ){ TRACE("y/prev", currproc, 0); }
    TRACE("y/next", nextproc, 0 );

#ifndef PROC_SMALL
    /* stats */
    if( currproc ){
        if( timeremain > 0 )
            currproc->timeyielded += timeremain;
#  ifdef PROC_HIRES
        currproc->hrtimeused += now - currproc->hrtimestart;
#  endif
    }
#endif
    //kprintf(" ynp curr %x (%s), next %x (%s); curr sp %x, next sp %x start %x\n",
    //   currproc, currproc->name, nextproc, nextproc->name, currproc->sp, nextproc->sp, nextproc->stack_start);


#ifdef CHECKPROC
    if( nextproc != currproc && nextproc->sp < (u_long)nextproc->stack_start ){
        kprintf("stack overflow: next %x (%s), sp %x, start %x\n", nextproc, nextproc->name, nextproc->sp, nextproc->stack_start);
        PANIC("stack overflow");
    }
    if( nextproc->sp && nextproc->sp < nextproc->lowsp ) nextproc->lowsp = nextproc->sp;
#endif

#ifndef PROC_SMALL
    nextproc->timeallotted += nextproc->timeslice;
#  ifdef PROC_HIRES
    nextproc->hrtimestart = now;
#  endif
#endif
    timeremain = nextproc->timeslice;

    TRACE("/ynp", currproc, nextproc);
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
    /* signals disabled? */
    if( r && (currproc->flags & PRF_SIGBLOCK) ) r = 0;
    /* set flag now, to avoid recursing when we come out of interrupt mode */
    if( r ) currproc->throwing = 1;
    return r;
}

void
_yield_bottom_cancel(void){
    currproc->throwing = 0;
}


/* enable/disable delivery of signals/messages
   see also sigdisable() in proc.h
*/
void
sigenable(void){
    currproc->flags &=  ~PRF_SIGBLOCK;
    if( currproc->flags & PRF_MSGPEND ) yield();
}

