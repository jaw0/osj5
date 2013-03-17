/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: processes

  $Id$

*/

#ifndef __proc_h__
#define __proc_h__

#include <sys/types.h>
#include <conf.h>
#include <time.h>
#include <md_proc.h>
#include <fs.h>

struct Proc {
#ifdef CHECKPROC
	u_long magic;			/* for consistancy checking */
#	define	PROCMAGIC	987654321
        u_long lowsp;
#endif

	u_long sp;			/* saved stack ptr */
        int timeslice;			/* how much time per slice */
	int state;			/* state */
#define PRS_RUNNABLE	0
#define PRS_BLOCKED	1
#define PRS_DEAD	2
#define PRS_SUSPENDED	4

	int flags;
#define PRF_NONBLOCK	1	/* process is not permitted to block */
#define PRF_REALTIME	2	/* process is real-time critical */
#define PRF_DEADKID	4	/* a child process has died */
#define PRF_MSGPEND	8	/* a message is pending */
#define PRF_AUTOREAP	16	/* process will not reap dead kids, have scheduler do it */
#define PRF_IMPORTANT	32	/* important system process */

	int prio;			/* process priority - generally in the range of 0-16 */
	int nice;			/* value to adjust prio (above) */
    	int pcnt;			/* priority counter */

	void *wchan;			/* what are we waiting for */
	const char *wmsg;		/* short description of what is being waited for */

	utime_t alarm;			/* time to send an alarmclock msg */
	utime_t timeout;		/* timeout for wchan */

		/* various params for msg passing */
	struct Catch *clist;		/* catch list for msg/exception handling */
	struct Msg *msghead;
	struct Msg *msgtail;
	u_long sigmsgs;			/* msgs sent by bottom-half (signals) (bitmask) */
        int    throwing;		/* xthrow recursion */

		/* for bookkeeping */
	char *stack_start;
	int  alloc_size;

#ifdef USE_NSTDIO
	struct FILE *stdin;		/* std io for process */
	struct FILE *stdout;
	struct FILE *stderr;
#endif
	struct MountEntry *cwd;		/* current working device */

	const char *name;	        /* proc name - for diags */

		/* stats */
	u_long memused;			/* total memory in use */
	u_long timeyielded;		/* total time allotted but not used by proc */
	u_long timeallotted;		/* total time allotted to proc */
	u_long p_allotted, p_yielded;	/* previous values of above */
	u_long timeused;		/* decaying average of timeslice used */
	u_long estcpu;			/* decaying average of total cpu */

	int exitval;			/* value passed to exit */

		/* various lists we may be on */
	struct Proc *mommy,   *booboo; 	/* parent and child */
	struct Proc *brother, *sister;	/* siblings */
	struct Proc *next,    *prev;	/* proclist */
	struct Proc *rnext,   *rprev;	/* readylist */
	struct Proc *rtnext,  *rtprev;	/* realtimelist */
	struct Proc *wnext,   *wprev;	/* wait table */

#ifdef GETLINEHIST
	void *getlinedata;		/* getline history data */
#endif

};

typedef struct Proc *proc_t;


#define getpid()		(currproc)
#define getppid()		(currproc ? currproc->mommy : 0)
#define setprio(pid, pri)	((pid)->prio = (pri))
#define setslice(pid, slice)	((pid)->timeslice = (slice))

#ifdef CHECKPROC
#	define	PROCOK(p)	{ if( (p)->magic != PROCMAGIC ) PANIC("proc: bad magic"); }
#else
#	define	PROCOK(p)
#endif

#ifndef PROC_TIME
#  define PROC_TIME	50000		/* usec - timer int rate */
#endif
#define PRIO_TIME	1000000		/* usec - how often to recalc priorities */
#define WAITTABLESIZE	23
#define WCHAN_NEVER	0		/* a wchan that is never woken */


extern volatile struct Proc *proclist;
extern volatile struct Proc *currproc;
extern struct Proc *schedulerproc;
extern volatile long timeremain;		/* NB: yes, this must be signed */

extern void  yield(void);
extern void  usleep(u_long);
extern void  sigsuspend(proc_t);
extern void  sigcont(proc_t);
extern void  sigkill(proc_t);
extern void  sigunblock(proc_t);
extern proc_t start_proc(int, void*, const char *);
extern void  exit(int);
extern int   wait(proc_t);
extern int   tsleep(void *, int, const char *, int);
extern void  wakeup(void *);
extern int   alarm(int);

#endif /* __proc_h__ */

