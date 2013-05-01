/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-05 00:24 (EDT)
  Function: stm32f1 dma
*/

#include <conf.h>
#include <stm32.h>
#include <nvic.h>

#define CCR_MINC	0x80
#define CCR_DIR		0x10	// 0: periph=>mem, 1: mem=>periph
#define CCR_TEIE	0x8
#define CCR_TCIE	0x2
#define CCR_EN		0x1


struct DMAinfo {
    u_char	status;
    void	(*on_done)();
};


dma_init(int unit){

    RCC->AHBENR |= 1;

    nvic_enable( dmairq,   IPL_DISK );

}


int
dma_start(int unit, char *pdev, char *addr, int len, u_long flags, void(*finished)()){

    dmac->CPAR  = (u_long) pdev;
    dmac->CMAR  = (u_long) addr;
    dmac->CNDTR = len ? len : 65535;
    dmac->CCR  &= ~ (CCR_DIR | CCR_MINC);
    dmac->CCR  |= flags | (len ? CCR_TEIE | CCR_TCIE : 0);
    dmac->CCR  |= CCR_EN;

}

void
dma_disable(int unit){

    ii->CCR &= ~( CCR_EN | CCR_TEIE | CCR_TCIE );
}




