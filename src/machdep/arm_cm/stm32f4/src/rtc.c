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



static int rtc_pre_s = 0;

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

    RCC->BDCR |= 1<<15;			// enable rtc
    rtc_unlock();
    init_enable();

    RTC->PRER  = rtc_pre_s - 1;
    RTC->PRER |= (127<<16);

    RTC->CR   &= ~CR_WUTE;		// turn off WKUP
    RTC->ISR  &= ~ISR_RSF;		// clear RSF

    init_disable();
    rtc_lock();

    get_rtc();

    bootmsg("rtc using %s: %#T\n", info, systime);
}

// set systime from rtc
int
get_rtc(void){
    struct tm ts;

    rtc_unlock();
    RTC->ISR  &= ~ISR_RSF;		// clear RSF
    while( RTC->ISR & ISR_RSF == 0 ){}	// wait for RSF
    rtc_lock();

    int ss = RTC->SSR;
    int tr = RTC->TR;
    int dr = RTC->DR;	// read DR last

    ts.tm_year = ((dr >> 16) & 0xF) + 10 * ((dr >> 20) & 0xF) + 2000;
    ts.tm_mon  = ((dr >> 8) & 0xF)  + 10 * ((dr >> 12) & 1);
    ts.tm_mday = (dr & 0xF)         + 10 * ((dr >>  4) & 3);
    ts.tm_hour = ((tr >> 16) & 0xF) + 10 * ((tr >> 20) & 3);
    ts.tm_min  = ((tr >> 8) & 0xF)  + 10 * ((tr >> 12) & 7);
    ts.tm_sec  = (tr & 0xF)         + 10 * ((tr >>  4) & 7);
    ts.tm_usec = (rtc_pre_s - ss) * 1000000 / rtc_pre_s;

    systime = timegm(&ts);
}

#define BCD(x)		(((x) % 10) | (((x)/10)*16))

// set rtc to current systime
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

    rtc_unlock();
    init_enable();

    RTC->TR = tr;
    RTC->DR = dr;

    RTC->ISR  &= ~ISR_RSF;	// clear RSF

    init_disable();
    rtc_lock();
    bootmsg("rtc updated\n");

}

int
set_rtc_wakeup(int secs){
    // secs == 0 => forever (or reset)

    // wkup - max ~36 hours (2^17 secs)

    rtc_unlock();
    RTC->ISR &= ~(1<<10);	// clear WUTF
    RTC->CR  &= ~(1<<10);	// disable WUT

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

