
/* $Id: timer.h,v 1.2 1999/04/14 19:41:30 jaw Exp $ */

#ifndef __timer_h__
#define __timer_h__


#define MHZ	25	/* chip clock speed */
#define PSCLK	1	/* prescaled clock speed */

#define IO_PIT	0x40
#define PIT_0	0
#define PIT_1	1
#define PIT_2	2
#define PIT_CTL	3

#define CTL_CNTSHFT	6
#define CTL_RWLSB	(1<<4)
#define CTL_RWMSB	(2<<4)
#define CTL_RWLTM	(3<<4)
#define CTL_MODESHFT	1
#define CTL_BCD		1

#define CTL_MODE(n)		((n) << CTL_MODESHFT)




#endif /* __timer_h__ */

