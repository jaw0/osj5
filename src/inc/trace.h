/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-19 23:47 (EDT)
  Function: 

*/

#ifndef __trace_h__
#define __trace_h__

#ifdef TRACE
//extern void trace_crumb1(const char *tag, const char *evt, int);
//extern void trace_crumb2(const char *tag, const char *evt, int, int);
//extern void trace_crumb3(const char *tag, const char *evt, int, int, int);
//extern void trace_crumb4(const char *tag, const char *evt, int, int, int, int);
extern void trace_crumb(const char *tag, const char *evt, int n, ...);
extern void trace_data( const char *tag, const char *evt, int len, const char *);
extern void trace_fdata(const char *tag, const char *fmt, int n, ...);

# define trace_crumb1(t, e, a1)			trace_crumb(t, e, 1, a1)
# define trace_crumb2(t, e, a1, a2)		trace_crumb(t, e, 2, a1, a2)
# define trace_crumb3(t, e, a1, a2, a3)		trace_crumb(t, e, 3, a1, a2, a3)
# define trace_crumb4(t, e, a1, a2, a3, a4)	trace_crumb(t, e, 4, a1, a2, a3, a4)
#else

# define trace_crumb1(t, e, a)
# define trace_crumb2(t, e, a, b)
# define trace_crumb3(t, e, a, b, c)
# define trace_crumb4(t, e, a, b, c, d)
# define trace_data(t, e, l, d)
# define trace_fdata(t,f,n, args...)

#endif


#endif /* __trace_h__ */
