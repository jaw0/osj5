

/* $Id: error.h,v 1.1.1.1 1998/11/04 17:19:15 jaw Exp $ */

#ifndef __error_h__
#define __error_h__

#define PANIC(m)            panic(m, __LINE__, __FILE__)

extern void diag(const char *file, const char *func, int line, const char *fmt, ...);


#define _DIAG_ARGS		__FILE__, __FUNCTION__, __LINE__

#ifdef KDEBUG
#  define DEBUG(args...)	diag(_DIAG_ARGS, args)
#else
#  define DEBUG(args...)
#endif

#  define DIAG(args...)	diag(_DIAG_ARGS, args)


#endif /* __error_h__ */

