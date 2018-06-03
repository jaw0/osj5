/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-19 23:47 (EDT)
  Function: 

*/

#ifndef __trace_h__
#define __trace_h__

#ifdef TRACE
extern void trace_crumb1(const char *tag, const char *evt, int);
extern void trace_crumb2(const char *tag, const char *evt, int, int);
extern void trace_crumb3(const char *tag, const char *evt, int, int, int);
extern void trace_crumb4(const char *tag, const char *evt, int, int, int, int);
extern void trace_data(  const char *tag, const char *evt, int len, const char *);
extern void trace_fdata( const char *tag, const char *fmt, int n, ...);
#else

# define trace_crumb1(t, a, b)
# define trace_crumb2(t, a, b)
# define trace_crumb3(t, a, b, c)
# define trace_crumb4(t, a, b, c, d)
# define trace_data(t, l, d)
# define trace_fdata(t,f,n, args...)

#endif


#endif /* __trace_h__ */
