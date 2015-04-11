/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Mar-14 18:33 (EDT)
  Function: real time clock

*/

#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <msgs.h>
#include <dev.h>
#include <bootflags.h>
#include <clock.h>
#include <stm32.h>
#include <time.h>
#include <userint.h>


#define CR_WUTE		(1<<10)
#define CR_WUTIE	(1<<14)
#define ISR_RSF		(1<<5)
#define ISR_INITF	(1<<6)
#define ISR_INIT	(1<<7)
#define ISR_WUTF	(1<<10)
#define ISR_SHPF	(1<<3)


static int rtc_pre_s   = 0;
static int rtc_pre_a   = 0;
static int rtc_was_set = 0;

static utime_t get_rtc(void);
static void    set_time_from_rtc(void);
static void    rtc_clock_sync(void);

static inline void
rtc_lock(void){
    RTC->WPR = 0;
}

static inline void
rtc_unlock(void){
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
}

static inline void
init_enable(void){
    RTC->ISR = ISR_INIT;			// enter INIT mode
    while( (RTC->ISR & ISR_INITF) == 0 ){}	// wait for it
}

static inline void
init_disable(void){
    RTC->ISR  &= ~ISR_INIT;		// exit INIT
}

void
rtc_init(void){

    RCC->APB1ENR |= (1<<28);		// enable PWR system
    PWR->CR |= (1<<8);			// enable backup domain (DBP)

    rtc_pre_s = 0;
    rtc_pre_a = 128;

#ifdef LSECLOCK
    // QQQ - support other frequencies?
    RCC->BDCR |= 1;			// enable LSE
    while( (RCC->BDCR & 2) == 0 ) {}	// wait for it
    RCC->BDCR |= 1<<8;			// src = lse
    rtc_pre_s = 256;
    const char *info = "LSE 32768Hz";
#else
    // QQQ - are all chips 32kHz?
    RCC->CSR  |= 1;			// enable LSI
    while( (RCC->CSR & 2) == 0 ) {}	// wait for it
    RCC->BDCR |= 2<<8;			// src = lsi
    rtc_pre_s = 250;
    const char *info = "LSI 32kHz";
#endif

#ifdef RTC_SYNC_RTC_FROM_CLOCK
    // so we can tweak it more precisely
    rtc_pre_a >>= 4;
    rtc_pre_s <<= 4;
#endif

    RCC->BDCR |= 1<<15;			// enable rtc
    rtc_unlock();
    init_enable();

    RTC->PRER  = rtc_pre_s - 1;
    RTC->PRER |= (rtc_pre_a-1) << 16;

    RTC->CR   &= ~CR_WUTE;		// turn off WKUP
    RTC->ISR  &= ~ISR_RSF;		// clear RSF

    init_disable();
    rtc_lock();

    set_time_from_rtc();

    bootmsg("rtc using %s: %#T\n", info, systime);

#if defined(RTC_SYNC_CLOCK_FROM_RTC) || defined(RTC_SYNC_RTC_FROM_CLOCK)
    start_proc(512, rtc_clock_sync, "rtcsync");
#endif

}


static utime_t
get_rtc(void){
    struct tm ts;

    while( RTC->ISR & ISR_RSF == 0 ){}	// wait for RSF

    int ss = RTC->SSR;
    int tr = RTC->TR;
    int dr = RTC->DR;	// read DR last

    ts.tm_year = ((dr >> 16) & 0xF) + 10 * ((dr >> 20) & 0xF) + 2000;
    ts.tm_mon  = ((dr >> 8) & 0xF)  + 10 * ((dr >> 12) & 1);
    ts.tm_mday = (dr & 0xF)         + 10 * ((dr >>  4) & 3);
    ts.tm_hour = ((tr >> 16) & 0xF) + 10 * ((tr >> 20) & 3);
    ts.tm_min  = ((tr >> 8) & 0xF)  + 10 * ((tr >> 12) & 7);
    ts.tm_sec  = (tr & 0xF)         + 10 * ((tr >>  4) & 7);

    // usec can be negative. timegm does not handle that.
    ts.tm_usec = 0;
    int usec   = ((rtc_pre_s - ss) * 10000 / rtc_pre_s) * 100;

    return timegm(&ts) + usec;
}

// set systime from rtc
static void
set_time_from_rtc(void){

    systime = get_rtc();
}

#define BCD(x)		(((x) % 10) | (((x)/10)*16))

// set rtc to current systime
// this is called by cli.c when the time is set
int
set_rtc(void){
    struct tm ts;

    gmtime_r( &systime, &ts );
    ts.tm_year -= 2000;

    int tr = BCD(ts.tm_hour) << 16;
    tr |= BCD(ts.tm_min) << 8;
    tr |= BCD(ts.tm_sec);
    int dr = BCD(ts.tm_year) << 16;
    dr |= BCD(ts.tm_mon) << 8;
    dr |= BCD(ts.tm_mday);

    int ss = rtc_pre_s - ts.tm_usec * rtc_pre_s / 1000000;

    rtc_unlock();
    init_enable();

    RTC->TR  = tr;
    RTC->DR  = dr;
    // RTC->SSR = ss;		// is read-only

    RTC->ISR  &= ~ISR_RSF;	// clear RSF

    init_disable();
    rtc_lock();
    rtc_was_set = 1;
}

// set the wakeup timer
int
set_rtc_wakeup(int secs){
    // secs == 0 => forever (or reset)

    // wkup - max ~36 hours (2^17 secs)

    rtc_unlock();
    RTC->ISR &= ~ISR_WUTF;	// clear WUTF
    RTC->CR  &= ~CR_WUTE;	// disable WUT

    if( secs ){
        while( (RTC->ISR & (1<<2)) == 0 ) {}	// wait for it

        if( secs > 0xFFFF ){
            secs &= 0xFFFF;
            RTC->CR |= 6;		// 1Hz + 2^16
        }else{
            RTC->CR |= 4;		// 1Hz
        }

        RTC->WUTR = secs;

        RTC->CR |= (1<<14);		// enable WT interrupt
        RTC->CR |= (1<<10);		// enable
    }

    rtc_lock();

    // then call stm32_init: power_down();
}

// was the system woken up by a wakeup event?
int
was_rtc_wakeup(void){

    return (RTC->ISR & ISR_WUTF) ? 1 : 0;
}

//################################################################

#if defined(RTC_SYNC_CLOCK_FROM_RTC) || defined(RTC_SYNC_RTC_FROM_CLOCK)

#define MAXSHIFT	1000
static utime_t prev_syst=0,  prev_rtct=0;
static utime_t curr_syst=0,  curr_rtct=0, curr_rtca=0;
static int     targ_count=0, base_count=0, max_adj=0;
static int     stat_freq=0,  stat_offset=0;

// this is run as a process to keep the rtc + systime in sync

static void
rtc_clock_sync(void){

    prev_rtct  = get_rtc()  / 1000;	// millisecs
    prev_syst  = get_hrtime() / 1000;
# if defined(RTC_SYNC_CLOCK_FROM_RTC)
    targ_count = SysTick->LOAD;
    base_count = SysTick->LOAD;
    max_adj    = base_count >> 4;
#else
    targ_count = rtc_pre_s;
    base_count = rtc_pre_s;
    max_adj    = base_count >> 4;
#endif

    currproc->prio   = 12;
    currproc->flags |= PRF_IMPORTANT;

    while(1){
        sleep(10);

        curr_rtca = get_rtc();
        curr_rtct = curr_rtca  / 1000;
        curr_syst = get_hrtime() / 1000;

        if( rtc_was_set ){
            // don't adjust if the clock was changed
            prev_rtct = curr_rtct;
            prev_syst = curr_syst;
            rtc_was_set = 0;
            continue;
        }

        // millisecs
        int terr = curr_rtct - curr_syst;
        int dsys = curr_syst - prev_syst;
        int drtc = curr_rtct - prev_rtct;

        stat_offset = (3 * stat_offset + terr) / 4;

        if( terr >  MAXSHIFT ) terr =  MAXSHIFT;
        if( terr < -MAXSHIFT ) terr = -MAXSHIFT;

# if defined(RTC_SYNC_CLOCK_FROM_RTC)
        // RTC is more accurate, tweak systick to match

        // determine freq difference
        // tweak sysclock reload
        int targ   = (targ_count * dsys + drtc/2) / drtc;
        targ_count = (3 * targ_count + targ) / 4;

        if( targ_count > base_count + max_adj ) targ_count = base_count + max_adj;
        if( targ_count < base_count - max_adj ) targ_count = base_count - max_adj;

        int adj    = (targ_count * terr + 5000) / 10000;
        int load   = targ_count - adj;

        stat_freq  = dsys * 1000 / drtc;

        //bootmsg("tick adj: terr %d, dsys %d, drtc %d\t=> %d,%d\n", terr, dsys, drtc, targ_count, adj);
        SysTick->LOAD = load;

        prev_rtct = curr_rtct;
        prev_syst = curr_syst + terr;

# elif defined(RTC_SYNC_RTC_FROM_CLOCK)

        // determine offset
        // set shiftr + pre_s + calr

        int targ   = (rtc_pre_s * drtc + dsys/2) / dsys;
        targ_count = (3 * targ_count + targ) / 4;

        if( targ_count > base_count + max_adj ) targ_count = base_count + max_adj;
        if( targ_count < base_count - max_adj ) targ_count = base_count - max_adj;

        int adj    = (rtc_pre_s * terr + 500) / 1000;

        stat_freq  = drtc * 1000 / dsys;

        rtc_unlock();

        if( adj < 0 ){
            adj = rtc_pre_s + adj;
            if( adj < 0 ) adj = 0;
            if( adj > rtc_pre_s-1 ) adj = rtc_pre_s - 1;
            RTC->SHIFTR = adj | (1<<31);
        }else{
            if( adj > rtc_pre_s-1 ) adj = rtc_pre_s - 1;
            RTC->SHIFTR = adj;
        }

        rtc_lock();
        while( RTC->ISR & ISR_SHPF ) {}		// wait for shift
        while( RTC->ISR & ISR_RSF == 0 ){}	// wait for RSF

        if( rtc_pre_s != targ_count ){
            rtc_unlock();
            init_enable();

            rtc_pre_s = targ_count;
            RTC->PRER  = rtc_pre_s - 1;
            RTC->PRER |= (rtc_pre_a-1)<<16;

            RTC->ISR  &= ~ISR_RSF;	// clear RSF
            init_disable();
            rtc_lock();
        }

        //bootmsg("tick adj: terr %d, dsys %d, drtc %d\t=> %d,%d,%d\n", terr, dsys, drtc, targ,targ_count, adj);

        prev_rtct = get_rtc() /1000;
        prev_syst = get_time()/1000;

# endif
    }
}

#endif

#if defined(USE_CLI)
DEFUN(rtcstats, "show rtc stats")
{

#if defined(RTC_SYNC_CLOCK_FROM_RTC) || defined(RTC_SYNC_RTC_FROM_CLOCK)
    printf("offset: %d\n", stat_offset);
    printf("freq:   %d\n", stat_freq);
#endif

    return 0;
}
#endif
