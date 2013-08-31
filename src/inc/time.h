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

/* microsecs since epoch */
extern utime_t systime;

extern void systime_tick(void);

#define get_time()	(systime)

extern utime_t get_hrtime(void);

#define UT_ONESECOND	1000000
#define EPOCH_YEAR	1970

struct tm {
        int     tm_sec;         /* seconds after the minute [0-61] */
        int     tm_min;         /* minutes after the hour [0-59] */
        int     tm_hour;        /* hours since midnight [0-23] */
        int     tm_mday;        /* day of the month [1-31] */
        int     tm_mon;         /* month of the year [1-12] [different than posix] */
        int     tm_year;        /* year AD [different than posix] */
        int     tm_wday;        /* days since Sunday [0-6] */
        int     tm_yday;        /* days since January 1 [0-365] */

        int     tm_usec;	/* microsecs */
};


extern struct tm *gmtime_r(const utime_t *, struct tm *);
extern utime_t timegm(struct tm *);
extern utime_t timeiso(const char *);

#endif
