/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-23 19:39 (EDT)
  Function: time

*/


#include <conf.h>
#include <time.h>
#include <calendar.h>
#include <ctype.h>

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
    tres->tm_year = val / 365 + EPOCH_YEAR;

    tres->tm_yday -= leap_years_since_year_1(tres->tm_year) - leap_years_since_year_1(EPOCH_YEAR);

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

    tres->tm_mon  ++;	// 1 based
    tres->tm_mday ++;	// is 1 based
    tres->tm_wday = day_of_week(tres->tm_year, tres->tm_mon, tres->tm_mday);

    return tres;
}

/* a < b => -1
   a > b => 1
*/
static int
tm_compare(struct tm *a, struct tm *b){

#define CMP(a,b,f)			\
    if( a->f < b->f ) return -1;	\
    if( a->f > b->f ) return  1;

    CMP(a, b, tm_year );
    CMP(a, b, tm_mon );
    CMP(a, b, tm_mday );
    CMP(a, b, tm_hour );
    CMP(a, b, tm_min );
    CMP(a, b, tm_sec );
    CMP(a, b, tm_usec );

    return 0;
#undef CMP
}


utime_t
timegm(struct tm *ti){
    struct tm tg;
    /* we probably don't need to start this high (year 75039) */
    utime_t lo=0, hi=(1LL<<62), mid;

    /* in case they were not initialized: */
    if( ti->tm_usec < 0 || ti->tm_usec >= 1000000 ) ti->tm_usec = 0;
    if( ti->tm_sec  < 0 || ti->tm_sec  >= 60 ) ti->tm_sec = 0;

    if( ti->tm_mon <= 0 || ti->tm_mon > 12 )   ti->tm_mon = 1;

    /* binary search */
    while(lo <= hi){
        mid = lo/2 + hi/2;
        gmtime_r( &mid, &tg );
        int c = tm_compare(&tg, ti);

        if( c < 0 ){
            lo = mid + 1;
        }
        else if( c > 0 ){
            hi = mid - 1;
        }
        else{
            return mid;
        }
    }

    /* QQQ */
    return mid;
}

static int
parse_num(const char **src, int maxlen){
    int num = 0;

    /* skip non-numeric */
    while( **src && !isdigit(**src) ) (*src)++;

    /* parse digits */
    while( **src && isdigit(**src) && maxlen ){
        num *= 10;
        num += **src - '0';
        maxlen --;
        (*src)++;
    }

    return num;
}

utime_t
timeiso(const char *iso){
    struct tm t;

    bzero(&t, sizeof(t));

    t.tm_year = parse_num(&iso, 4);
    t.tm_mon  = parse_num(&iso, 2);
    t.tm_mday = parse_num(&iso, 2);
    t.tm_hour = parse_num(&iso, 2);
    t.tm_min  = parse_num(&iso, 2);
    t.tm_sec  = parse_num(&iso, 2);

    return timegm(&t);
}
