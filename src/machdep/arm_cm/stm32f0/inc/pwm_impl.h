
#ifndef __stm32f0_pwm_impl_h__
#define __stm32f0_pwm_impl_h__

static inline void
timer_rcc_init(int t){

switch( t ){
    case 1:
        RCC->APB2ENR |= 1 << 11;
        break;
    case 8:
        RCC->APB2ENR |= 1 << 13;
        break;

    case 9:
    case 10:
    case 11:
        break;

    case 12:
    case 13:
    case 14:
        RCC->APB1ENR = 1 << (t - 6);
        break;

    case 15:
    case 16:
    case 17:
        RCC->APB2ENR |= 1 << (t + 1);
        break;

    default: // 2-7
        RCC->APB1ENR |= 1 << (t - 2);
        break;
    }
}



static inline int
timer_clockspeed(int t){

    switch( t ){
    case 1:
    case 8:
    case 9:
    case 10:
    case 11:
        return APB2CLOCK;

    case 12:
    case 13:
    case 14:
        return APB1CLOCK;

    case 15:
    case 16:
    case 17:
        return APB2CLOCK;

    default: // 2-7
        return APB1CLOCK;
    }
}


#endif /*  __stm32f0_pwm_impl_h__ */

