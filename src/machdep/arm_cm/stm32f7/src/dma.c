/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Dec-13 18:27 (EST)
  Function: dma

*/

#include <conf.h>
#include <locks.h>
#include <stm32.h>
#include <dma.h>

#define DMASCR_MINC	(1<<10)
#define DMASCR_DIR_M2P  (1<<6)
#define DMASCR_PFCTRL	(1<<5)
#define DMASCR_TEIE	4
#define DMASCR_TCIE	16
#define DMASCR_EN	1


// unit: 0,1
void
dma_init(int n){
    int i;

    if( n == 0 ){
        RCC->AHB1ENR |= 1<<21;
    }else{
        RCC->AHB1ENR |= 1<<22;
    }
}

/****************************************************************/


static inline int
clear_irqs(DMA_TypeDef *dma, int dman){
    int isr;
    int pos = (dman & 3) * 8 - (dman & 1) * 2;	// not aligned

    if( dman > 3 ){
        isr = (dma->HISR >> pos) & 0x3F;
        dma->HIFCR |= (0x3D << pos);
    }else{
        isr = (dma->LISR >> pos) & 0x3F;
        dma->LIFCR |= (0x3D << pos);
    }

    return isr;
}

void
dma_start_xfer(DMA_TypeDef *dma, DMA_Stream_TypeDef *str, void *mem, void *dr, int len){

        DMASTRI->CR  &= (0xF<<28) | (1<<20);	// zero CR
    DMA2->HIFCR  |= 0x3D << 16;			// clear ints

    DMASTRI->PAR   = & CRYP->DR;
    DMASTRI->M0AR  = in;
    DMASTRI->NDTR  = inlen >> 2;

    DMASTRI->CR   |= (DMACHAN << 25)
        | (2<<16)		// high prio
        | (2<<13) | (2<<11)	// 32 bit->32 bit
        | (1<<10)		// inc mem
        | (1<<6)		// mem->dev
        ;

    DMASTRI->CR   |= 1;		// enable
}


static void
dma_conf(DMAC_T *dmac, int chan, char *pdev, char *addr, int len, u_long flags){

    dmac->PAR   = (u_long) pdev;
    dmac->M0AR  = (u_long) addr;
    dmac->NDTR  = len ? len : 65535;
    dmac->CR   &= ~1;	// clear EN first
    dmac->CR   &= (0xF<<28) | (1<<20);
    dmac->CR   |= flags | (len ? DMASCR_TEIE | DMASCR_TCIE : 0) | (chan << 25);

    dmac->CR   |= DMASCR_EN;

}
