/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-19 23:47 (EDT)
  Function: 

*/

#ifndef __trace_h__
#define __trace_h__

#ifdef TRACE
extern void trace_crumb(const char *tag, const char *evt, int n, ...);
extern void trace_data( const char *tag, const char *evt, int len, const char *);
extern void trace_fdata(const char *tag, const char *fmt, int n, ...);
extern void trace_mark_start(const char *);
extern void trace_mark_stop(const char *);

# define trace_crumb0(t, e)					trace_crumb(t, e, 0)
# define trace_crumb1(t, e, a1)					trace_crumb(t, e, 1, a1)
# define trace_crumb2(t, e, a1, a2)				trace_crumb(t, e, 2, a1, a2)
# define trace_crumb3(t, e, a1, a2, a3)				trace_crumb(t, e, 3, a1, a2, a3)
# define trace_crumb4(t, e, a1, a2, a3, a4)			trace_crumb(t, e, 4, a1, a2, a3, a4)
# define trace_crumb5(t, e, a1, a2, a3, a4, a5)	 		trace_crumb(t, e, 5, a1, a2, a3, a4, a5)
# define trace_crumb6(t, e, a1, a2, a3, a4, a5, a6)		trace_crumb(t, e, 6, a1, a2, a3, a4, a5, a6)
# define trace_crumb7(t, e, a1, a2, a3, a4, a5, a6, a7)		trace_crumb(t, e, 7, a1, a2, a3, a4, a5, a6, a7)
# define trace_crumb8(t, e, a1, a2, a3, a4, a5, a6, a7, a8)	trace_crumb(t, e, 8, a1, a2, a3, a4, a5, a6, a7, a8)
#else

# define trace_crumb0(t, e)
# define trace_crumb1(t, e, a)
# define trace_crumb2(t, e, a, b)
# define trace_crumb3(t, e, a, b, c)
# define trace_crumb4(t, e, a, b, c, d)
# define trace_crumb5(t, e, a, b, c, d, f)
# define trace_crumb6(t, e, a, b, c, d, f, g)
# define trace_crumb7(t, e, a, b, c, d, f, g, h)
# define trace_crumb8(t, e, a, b, c, d, f, g, h, i)
# define trace_data(t, e, l, d)
# define trace_fdata(t,f,n, args...)
# define trace_init()
# define trace_reset()
# define trace_mark_start()
# define trace_mark_stop()
#endif


#endif /* __trace_h__ */
