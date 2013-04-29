/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: real time clock
 
  $Id$

*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <nstdio.h>
#include <arch.h>
#include <error.h>
#include <pio.h>
#include <rtc.h>
#include <proc.h>
#include <msgs.h>
#include <dev.h>
#include <bootflags.h>
#include <calendar.h>
#include <time.h>

utime_t boottime = 0;

#ifdef PLATFORM_EMUL
struct emul_tm {
    int     tm_sec;         /* seconds after the minute [0-61] */
    int     tm_min;         /* minutes after the hour [0-59] */
    int     tm_hour;        /* hours since midnight [0-23] */
    int     tm_mday;        /* day of the month [1-31] */
    int     tm_mon;         /* months since January [0-11] */
    int     tm_year;        /* years since 1900 */
    int     tm_wday;        /* days since Sunday [0-6] */
    int     tm_yday;        /* days since January 1 [0-365] */
    int     tm_isdst;       /* Daylight Savings Time flag */
    long    tm_gmtoff;      /* offset from CUT in seconds */
    const   char *tm_zone;  /* timezone abbreviation */
};
struct timeval {
    long	tv_sec;
    long	tv_usec;
};

#endif

#define UNBCD(x)	(((x>>4)&0xF)*10 + (x&0xF))

struct rtc_time_data {
    u_char sec;
    u_char asec;
    u_char min;
    u_char amin;
    u_char hr;
    u_char ahr;
    u_char dow;
    u_char dom;
    u_char mon;
    u_char yr;
};

int
rtc_get_val(int port, int reg){
    int i;

    outb( port + RTC_ADDR, reg );
    i = inb( port + RTC_DATA );
    return i;
}

void
rtc_put_val(int port, int reg, int val){

    outb( port + RTC_ADDR, reg );
    outb( port + RTC_DATA, val );
}

static int
daysinmonth(int m, int yr){

    switch(m){
    case 8: case 3: case 5: case 10:
        return 30;
    case 1:
        return leap_year(yr) ? 29 : 28;
    default:
        return 31;
    }
}

int
rtc_get_time(int port, int verbose){
    struct rtc_time_data rt;
    utime_t t = 0;
    int yr;
    int i;

    /* XXX - if we want to call this anywhere after init
       we'll need to raise spl
    */

#ifdef PLATFORM_EMUL
    /* fake it by asking unix */
    struct emul_tm *tm;
    struct timeval tv;

    gettimeofday(&tv, 0);
    tm = localtime(&tv.tv_sec);

    rt.sec = tm->tm_sec;
    rt.min = tm->tm_min;
    rt.hr  = tm->tm_hour;
    rt.dom = tm->tm_mday;
    rt.mon = tm->tm_mon + 1;
    rt.yr  = tm->tm_year;
#else
    for(i=0; i<sizeof(rt); i++){
        ((u_char*)&rt)[i] = UNBCD( rtc_get_val(port, i) );
    }
#endif

    yr = rt.yr;
    if( yr < 90 ) yr += 100;
    yr += 1900;

    kprintf("%d-%0.2d-%0.2d %d:%0.2d:%0.2d",
            yr, rt.mon, rt.dom, rt.hr, rt.min, rt.sec);

    rt.mon --;	/* make 0 based */
    rt.dom --;	/* make 0 based */

    /* find number of days in all previous years */
    t += (yr - 1) * 365;
    t += leap_years_since_year_1(yr);
    t -= 11; /* adjust for gregorian reformation Sep/1752 */

    /* add in today */
    for(i=0; i<rt.mon; i++)
        t += daysinmonth(i, yr);
    t += rt.dom;

    /* add in current time and adjust to usec */
    t *= 24 * 60 * 60;
    t += (rt.hr * 60 + rt.min) * 60 + rt.sec;
    t *= 1000000;

    /* set time - usec since 1/1/1 */
    systime = t;

    return 0;
}

int
rtc_init(struct Device_Conf *dev){
    int port = dev->port;

#ifndef PLATFORM_EMUL
    rtc_put_val( port, RTC_A, RTC_DIV2 | RTC_RATE_1024_Hz );
    rtc_put_val( port, RTC_B, RTC_HM );
#endif
    kprintf("%s at io 0x%x => ", dev->name, port);
    rtc_get_time( port, 1 );
    kprintf("\n");
    boottime = systime;

    return 0;
}


