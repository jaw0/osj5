/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-05 00:24 (EDT)
  Function: stm32f1 dma
*/



struct DMAinfo {
    u_char	status;
    void	(*on_done)();
};


dma_init(int unit){

    // rcc
    // nvic

}


int
dma_start(int unit, char *pdev, char *addr, int len, u_long flags, void(*finished)()){

    dmac->CPAR  = (u_long) pdev;
    dmac->CMAR  = (u_long) addr;
    dmac->CNDTR = len ? len : 65535;
    dmac->CCR  &= ~ (DMACCR_DIR | DMACCR_MINC);
    dmac->CCR  |= flags | (len ? DMACCR_TEIE | DMACCR_TCIE : 0);
    dmac->CCR  |= DMACCR_EN;

}

void
dma_disable(int unit){


    ii->CCR &= ~( DMACCR_EN | DMACCR_TEIE | DMACCR_TCIE );
}




