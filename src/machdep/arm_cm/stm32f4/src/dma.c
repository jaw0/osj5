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



static struct {
    lock_t		lock;
    DMA_T      		*dma;
    DMAC_T		*dmac;
    
    struct DMAReq 	*req;

} dma_info[16];



// unit: 0,1
void
dma_init(int n){
    int i;

    if( n == 0 ){
        RCC->AHB1ENR |= 1<<21;
        bzero(dma_info, sizeof(dma_info)/2);

    }else{
        RCC->AHB1ENR |= 1<<22;
        bzero(dma_info+8, sizeof(dma_info)/2);

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

static inline void
disable_irq_dma(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    dev->CR2 &= ~( CR2_TXEIE | CR2_RXNEIE | CR2_TXDMAEN | CR2_RXDMAEN );
    ii->rxdma->CR &= ~(DMASCR_EN | DMASCR_TEIE | DMASCR_TCIE);
    ii->txdma->CR &= ~(DMASCR_EN | DMASCR_TEIE | DMASCR_TCIE);
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

/****************************************************************/


int
dma_xfer_start(const DMAReq *req){

    clear_irqs(
    conf;
}

void
dma_xfer_stop(int unit, int str){


}

static void
dma_irq(int n){

    int isr = _dma_isr_clear_irqs( ii->dma, dman );
    SPI_CRUMB("dma-irq", dman, isr);

    if( isr & 8 ){
        // error - done
        SPI_CRUMB("dma-err", 0, 0);
        _disable_irq_dma(ii);
        ii->state = SPI_STATE_ERROR;
        wakeup( ii );
        return;
    }

    if( isr & 0x20 ){
        // dma complete
        if( m && ((u_long)m->data == dmac->M0AR) && ! dmac->NDTR ){
            SPI_CRUMB("dma-done", ii->msg, 0);
            _disable_irq_dma(ii);
            ii->state = SPI_STATE_DMA_DONE;
            wakeup( ii );
        }
    }

}
