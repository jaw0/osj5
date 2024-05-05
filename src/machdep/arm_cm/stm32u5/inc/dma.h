/*
  Copyright (c) 2024
  Author: Jeff Weisberg <tcp4me.com!jaw>
  Created: 2024-May-03 18:12 (EDT)
  Function: dma

*/

#ifndef __stm32u5_dma_h__
#define __stm32u5_dma_h__


typedef struct {
    short    chan;
    short    req_rx;
    short    req_tx;
    uint8_t  prio;
    uint8_t  irqipl;
    void    *port_rx;
    void    *port_tx;

    DMA_Channel_TypeDef *dmac;
    void (*callback)(void*, uint32_t);
    void *cbarg;
} dma_req_t;

#define DMA_PRIO_LOW_L	0
#define DMA_PRIO_LOW_M	1
#define DMA_PRIO_LOW_H	2
#define DMA_PRIO_HIGH	3

#define DMA_SR_ERROR_MASK    (DMA_CSR_TOF | DMA_CSR_USEF | DMA_CSR_ULEF | DMA_CSR_DTEF)


extern int dma_alloc(dma_req_t *);
extern int dma_free(dma_req_t *);
extern void dma_reset(dma_req_t *);
extern int dma_m2p(dma_req_t *, const char *, int);
extern int dma_p2m(dma_req_t *, char *, int);


#endif /* __stm32u5_dma_h__ */
