/*
  Copyright (c) 2016
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2016-Jun-25 11:04 (EDT)
  Function: timer counter

*/

#include <conf.h>
#include <arch.h>
#include <proc.h>
#include <atsam.h>
#include <pmc.h>
#include <pwm.h>

#define ELEM(x)	(sizeof(x) / sizeof(x[0]))


static Tc* const _tc_addrs[] = { TC0, TC1, TC2, TC3 };

static inline TcChannel *
_tc_addr(int tim){
    tim = (tim >> 8) & 0xFF;
    if( tim > ELEM(_tc_addrs) ) return 0;
    int chan = (tim >> 4) & 0x3;
    return & _tc_addrs[tim]->TC_CHANNEL[chan];
}

static Pwm* const _pwm_addrs[] = { PWM0, PWM1 };

static inline Pwm *
_pwm_addr(int tim){
    tim = (tim >> 4) & 0xFF;
    if( tim > ELEM(_pwm_addrs) ) return 0;
    return _pwm_addrs[tim];
}

/****************************************************************/

static void
_tc_freq_set(int timer, int freq){
    TcChannel *tim = _tc_addr(timer);

    int clock  = periph_clock_freq();
    uint32_t r = tim->TC_CMR & ~ 0x7;

    if( freq == 0 ){
        // highest freq, highest resolution
        r |= TC_CMR_TCCLKS_TIMER_CLOCK2;	// MCLK/8
        tim->TC_CMR = r;
        tim->TC_RC  = 0xFFFF;
        return;
    }

    // use highest freq + highest resolution possible
    int psc = clock / freq / 8;
    int ccs = TC_CMR_TCCLKS_TIMER_CLOCK2;	// MCLK/8

    if( psc == 0 ) psc = 1;

    int afrq = clock / 8 / psc;

    if( psc > 0x3FFFF ){
        psc >>= 4;
        ccs = TC_CMR_TCCLKS_TIMER_CLOCK4;	// MCLK/128
        if( psc > 0xFFFF ) psc = 0xFFFF;
        afrq = clock / 128 / psc;
    }
    else if( psc > 0xFFFF ){
        psc >>= 2;
        ccs = TC_CMR_TCCLKS_TIMER_CLOCK3;	// MCLK/32
        afrq = clock / 32 / psc;
    }

    r |= ccs;
    tim->TC_CMR = r;
    tim->TC_RC  = psc;
}

// maxval = 64k
static void
_tc_pwm_set(int timer, int val){
    TcChannel *tim = _tc_addr(timer);

    val = (val * (tim->TC_RC + 1)) >> 16;

    uint32_t cmr = tim->TC_CMR;

    if( timer & 1 ){
        tim->TC_RB = val;
        cmr &= ~0xFF000000;

        if( val ) cmr |= TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_SET   | TC_CMR_BSWTRG_NONE;
        else      cmr |= TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR | TC_CMR_BSWTRG_NONE;

    }else{
        tim->TC_RA = val;
        cmr &= ~0xFF0000;

        if( val ) cmr |= TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET   | TC_CMR_ASWTRG_NONE;
        else      cmr |= TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_CLEAR | TC_CMR_ASWTRG_NONE;
    }

    tim->TC_CMR = cmr;
}

/****************************************************************/

static void
_tc_init(int timer, int freq, int maxval/* not used*/){
    TcChannel *tim = _tc_addr(timer);

    switch( (timer >> 8) & 0xFF ){
    case 0:	pmc_enable( ID_TC0 );	break;
    case 1:	pmc_enable( ID_TC1 );	break;
    case 2:	pmc_enable( ID_TC2 );	break;
    }

    if( !tim ) return;

    int plx = splhigh();

    // timer init
    tim->TC_CMR = TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_EEVT_XC0;

    _tc_freq_set(timer, freq);
    _tc_pwm_set( timer, 0);

    tim->TC_CCR = TC_CCR_CLKEN;
    tim->TC_CCR = TC_CCR_SWTRG;

    splx(plx);
}

/****************************************************************/
static void
_pwm_pwm_set(int timer, int val){

}

static void
_pwm_freq_set(int timer, int freq){

}

static void
_pwm_init(int timer, int freq, int maxval){
    Pwm *tim = _pwm_addr(timer);

    switch( (timer >> 8) & 0xFF ){
    case 0:	pmc_enable( ID_PWM0 );	break;
    case 1:	pmc_enable( ID_PWM1 );	break;
    }




}

/****************************************************************/

void
pwm_init(int timer, int freq, int maxval){

    if( timer & 0x10000 )
        _pwm_init(timer, freq, maxval);
    else
        _tc_init(timer, freq, maxval);
}

void
pwm_set(int timer, int val){
    if( timer & 0x10000 )
        _pwm_pwm_set(timer, val);
    else
        _tc_pwm_set(timer, val);

}

void
freq_set(int timer, int freq){
    if( timer & 0x10000 )
        _pwm_freq_set(timer, freq);
    else
        _tc_freq_set(timer, freq);
}

