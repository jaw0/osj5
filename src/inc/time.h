/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-03 12:37 (EST)
  Function: 
 
  $Id$

*/
#ifndef __os_time_h__
#define __os_time_h__

typedef long long utime_t;

extern utime_t systime;

extern void systime_tick(void);

#define get_time()	(systime)

#endif
