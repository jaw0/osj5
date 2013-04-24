/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-23 19:39 (EDT)
  Function: time

*/


#include <conf.h>
#include <time.h>
#include <calendar.h>

static int
days_in_month(int m, int y){

    switch(m){
    case 8: case 3: case 5: case 10:
        return 30;
    case 1:
        return leap_year(y) ? 29 : 28;
    default:
        return 31;
    }
}


// http://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
int
day_of_week(int y, int m, int d){
    static char t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}


struct tm *
gmtime_r(const utime_t *t, struct tm *tres){
    utime_t val = t ? *t : get_time();

    if( !tres ) return 0;

    tres->tm_usec = val % 1000000;
    val /= 1000000;

    tres->tm_sec  = val % 60;
    val /= 60;

    tres->tm_min  = val % 60;
    val /= 60;

    tres->tm_hour = val % 24;
    val /= 24;
    /* val is now days */

    tres->tm_yday = val % 365;
    tres->tm_year = val / 365;

    tres->tm_yday -= leap_years_since_year_1(tres->tm_year);
    tres->tm_year ++;

    if( tres->tm_year > 1752 || (tres->tm_year == 1752 && tres->tm_yday > 243) )
        /* gregorian reformation */
        tres->tm_yday += 11;
    if( tres->tm_yday > (leap_year(tres->tm_year) ? 366 : 365) ){
        tres->tm_yday -= leap_year(tres->tm_year) ? 366 : 365;
        tres->tm_year ++;
    }
    while( tres->tm_yday < 0 ){
        tres->tm_year --;
        tres->tm_yday += leap_year(tres->tm_year) ? 366 : 365;
    }

    tres->tm_mon = 0;
    tres->tm_mday = tres->tm_yday;
    while( tres->tm_mday >= days_in_month(tres->tm_mon, tres->tm_year) ){
        tres->tm_mday -= days_in_month(tres->tm_mon, tres->tm_year);
        tres->tm_mon ++;
    }

    tres->tm_mday ++;	// is 1 based
    tres->tm_wday = day_of_week(tres->tm_year, tres->tm_mon, tres->tm_mday);

    return tres;
}

