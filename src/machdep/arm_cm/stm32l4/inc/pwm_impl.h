
#ifndef __stm32l4_pwm_impl_h__
#define __stm32l4_pwm_impl_h__

static inline void
timer_rcc_init(int t){

    switch( t ){
    case 1:
        RCC->APB2ENR |= 11;
        break;
    case 8:
        RCC->APB2ENR |= 13;
        break;

    case 15:
    case 16:
    case 17:
        RCC->APB2ENR |= 1 << (t + 1);
        break;

    default: // 2-7
        RCC->APB1ENR1 |= 1 << (t - 2);
        break;
    }
}


static inline int
timer_clockspeed(int t){

    switch( t ){
    case 1:
    case 8:

    case 15:
    case 16:
    case 17:
        return APB2CLOCK;


    default: // 2-7
        return APB1CLOCK;
    }
}


#endif /*  __stm32l4_pwm_impl_h__ */

