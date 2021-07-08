/*
  Copyright (c) 2019
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2019-Mar-25 10:13 (EDT)
  Function: 

*/

#ifndef __stm32f4_dma_h__
#define __stm32f4_dma_h__

#define DMAPRIO_LOW	0
#define DMAPRIO_MED	1
#define DMAPRIO_HI	2
#define DMAPRIO_VERY_HI	3

#define DMASCR_MINC	(1<<10)
#define DMASCR_DIR_M2P  (1<<6)
#define DMASCR_DIR_P2M  0
#define DMASCR_PFCTRL	(1<<5)
#define DMASCR_TEIE	4
#define DMASCR_TCIE	16
#define DMASCR_EN	1

static const DMA_TypeDef *_dma[2] = {DMA1, DMA2};

// 0 | 1
static inline void
dma_init(int n){
    int i;

    if( n == 0 ){
        RCC->AHB1ENR |= 1<<21;
    }else{
        RCC->AHB1ENR |= 1<<22;
    }
}

static inline int
dma_clear_ints(int dman, int strn){
    DMA_TypeDef *dma = _dma[dman];
    int isr;
    int pos = (strn & 3) * 8 - (strn & 1) * 2;

    if( strn > 3 ){
        isr = (dma->HISR >> pos) & 0x3F;
        dma->HIFCR = (0x3D << pos);
    }else{
        isr = (dma->LISR >> pos) & 0x3F;
        dma->LIFCR = (0x3D << pos);
    }

    return isr;
}



static inline void
dma_stop_xfer(int dman, int strn){

    DMA_TypeDef *dma = _dma[dman];
    DMA_Stream_TypeDef *str = dma->stream + strn;

    str->CR   &= ~DMASCR_EN;
    dma_clear_ints(dman, strn);
}

static inline int
dma_start_xfer_b(int dman, int strn, int chan, void *mem, void *dr, int len, int prio, uint32_t bits){
    int max = 1000000;
    DMA_TypeDef *dma = _dma[dman];
    DMA_Stream_TypeDef *str = dma->stream + strn;

    str->CR  = 0; // zero CR
    while( (str->CR & DMASCR_EN) && max-- ){ __asm("nop"); } // wait for it

    if( str->CR & DMASCR_EN ){
        trace_crumb1("dma", "err", str->CR);
        return -1;
    }

    dma_clear_ints(dman, strn);

    str->PAR   = dr;
    str->M0AR  = mem;
    str->NDTR  = len >> 2;	// bytes -> words

    str->CR   |= (chan << 25)
        | (prio<<16)		// high prio
        | bits
        ;

    str->CR   |= DMASCR_EN;		// enable
    return 0;
}

static inline int
dma_start_xfer(int dman, int strn, int chan, void *mem, void *dr, int len, int prio, int dir){

    return dma_start_xfer_b(dman, strn, chan, mem, dr, len, prio, (0
        | DMASCR_TEIE 		// enable transfer error irq
        | DMASCR_TCIE 		// enable transfer complete irq
        | DMASCR_MINC		// inc mem
        | (2<<13) | (2<<11)	// 32 bit->32 bit
        | dir			// M2P | P2M
    ));
}

static inline int
dma_bytes_remain(int dman, int strn){
    DMA_TypeDef *dma = _dma[dman];
    DMA_Stream_TypeDef *str = dma->stream + strn;

    return str->NDTR << 2;  // words -> bytes
}


#endif /*  __stm32f4_dma_h__ */
