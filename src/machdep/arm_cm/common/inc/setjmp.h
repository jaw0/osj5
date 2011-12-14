
/* $Id: setjmp.h,v 1.1 1999/04/14 19:41:29 jaw Exp $ */

#ifndef __setjmp_h__
#define __setjmp_h__

typedef long jmp_buf[32];

extern int setjmp(jmp_buf);
extern void longjmp(jmp_buf, int);

#endif /* __setjmp_h__ */
