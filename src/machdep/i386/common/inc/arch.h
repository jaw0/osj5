
#include <conf.h>

#ifdef USE_E9_DEBUGGING
#  define XE9(x)        outb(0xE9, (x))
#  define E9PRINTF(x)   e9printf x
#else
#  ifdef E9_EMUL_DEBUGGING
#    define XE9(x)	{ char a = x; write(2,&a,1); }
#    define E9PRINTF(x)	write(2,x,strlen(x))
#  else
#  define XE9(x)        /* x */
#  define E9PRINTF(x)   /* x */
#endif
#endif


#define ALIGNMENT       16       /* memory alignment */

