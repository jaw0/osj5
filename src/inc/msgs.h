
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: msgs.h,v 1.4 2001/10/31 18:09:11 jaw Exp $ */

#ifndef __msgs_h__
#define __msgs_h__

#include <setjmp.h>
#include <error.h>

struct Catch {
	jmp_buf jb;
	u_long msgval;
	u_long retval;
	void (*func)(u_long,u_long);
	struct Catch *next;
};

typedef struct Catch Catchframe;

extern void uncatch(struct Catch *);
extern void throw(u_long, u_long);
extern void xthrow(void);

#define CATCH(cf, tag, fun, flg, label) {	\
	cf.func   = fun;			\
	cf.msgval = tag;			\
						\
	if( _setjmp(cf.jb)){			\
            if( !cf.retval)			\
                cf.retval = 1;                  \
            goto label;                         \
	}					\
						\
	cf.next = currproc->clist;		\
	currproc->clist = &cf;			\
}
#define CATCHL(cf, tag, label)		CATCH(cf,tag,0,0,label)
#define CATCHF(cf, tag, fun) {			\
	cf.func = fun;				\
	cf.msgval = tag;			\
						\
	if( _setjmp(cf.jb)){			\
            PANIC("catchf botched");            \
	}					\
						\
	cf.next = currproc->clist;		\
	currproc->clist = &cf;			\
}


#define UNCATCH(cf) {				\
	currproc->clist = cf.next;		\
}

struct Msg {
	struct Msg *next;
	u_long msgval;
	u_long retval;
};

#define MSG_TIMEOUT		1
#define MSG_DEADKID		2
#define MSG_INFO		3
#define MSG_ALARM		4

#define MSG_CCHAR_0		5
#define MSG_CCHAR_1		6
#define MSG_CCHAR_2		7
#define MSG_CCHAR_3		8


extern int sendmsg(proc_t, u_long, u_long);
extern void ksendmsg(proc_t, u_long);

#endif /* __msgs_h__ */

