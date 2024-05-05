/*
  Copyright (c) 2024
  Author: Jeff Weisberg <tcp4me.com!jaw>
  Created: 2024-May-03 17:55 (EDT)
  Function: stm32{u5,h5,h7} dma

*/

#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <locks.h>
#include <dev.h>
#include <error.h>
#include <clock.h>
#include <stm32.h>
#include <dma.h>
#include <nvic.h>
#include <userint.h>


#ifdef DMA_TRACE
# define TRACE
#endif
#include <trace.h>


#define NCHAN 16


static const DMA_Channel_TypeDef *dmachan[] = {
    GPDMA1_Channel0,  GPDMA1_Channel1,  GPDMA1_Channel2,  GPDMA1_Channel3,
    GPDMA1_Channel4,  GPDMA1_Channel5,  GPDMA1_Channel6,  GPDMA1_Channel7,

#ifdef PLATFORM_STM32H5
    GPDMA2_Channel0,  GPDMA2_Channel1,  GPDMA2_Channel2,  GPDMA2_Channel3,
    GPDMA2_Channel4,  GPDMA2_Channel5,  GPDMA2_Channel6,  GPDMA2_Channel7,
#else
    GPDMA1_Channel8,  GPDMA1_Channel9,  GPDMA1_Channel10, GPDMA1_Channel11,
    GPDMA1_Channel12, GPDMA1_Channel13, GPDMA1_Channel14, GPDMA1_Channel15,
#endif
};

static const short dma_irqn[] = {
    GPDMA1_Channel0_IRQn,  GPDMA1_Channel1_IRQn,  GPDMA1_Channel2_IRQn,  GPDMA1_Channel3_IRQn,
    GPDMA1_Channel4_IRQn,  GPDMA1_Channel5_IRQn,  GPDMA1_Channel6_IRQn,  GPDMA1_Channel7_IRQn,

#ifdef PLATFORM_STM32H5
    GPDMA2_Channel0_IRQn,  GPDMA2_Channel1_IRQn,  GPDMA2_Channel2_IRQn,  GPDMA2_Channel3_IRQn,
    GPDMA2_Channel4_IRQn,  GPDMA2_Channel5_IRQn,  GPDMA2_Channel6_IRQn,  GPDMA2_Channel7_IRQn,
#else
    GPDMA1_Channel8_IRQn,  GPDMA1_Channel9_IRQn,  GPDMA1_Channel10_IRQn, GPDMA1_Channel11_IRQn,
    GPDMA1_Channel12_IRQn, GPDMA1_Channel13_IRQn, GPDMA1_Channel14_IRQn, GPDMA1_Channel15_IRQn,
#endif
};


static dma_req_t *dmacf[NCHAN];

int
dma_alloc(dma_req_t *req){
    int i;

    if( req->chan == -1 ){
        // find next available

        for(i=0; i<NCHAN; i++){
            if( dmacf[i] == 0 ){
                req->chan = i;
                break;
            }
        }
    }

    if( req->chan == -1 ){
        // cannot allocate
        return -1;
    }

    req->dmac = dmachan[ req->chan ];
    dmacf[ req->chan ] = req;

    trace_crumb3("dma", "irq=", req->chan, dma_irqn[ req->chan ], req->irqipl);

    RCC->AHB1ENR |= RCC_AHB1ENR_GPDMA1EN;

#ifdef PLATFORM_STM32H5
    RCC->AHB1ENR |= RCC_AHB1ENR_GPDMA2EN;
#endif

    nvic_enable( dma_irqn[ req->chan ], req->irqipl );
}

int
dma_free(dma_req_t *req){
    if( req->chan == -1 ){
        return 0;
    }
    if( dmacf[ req->chan ] != req ){
        return 1;
    }
    dmacf[ req->chan ] = 0;
    return 0;
}

int
dma_m2p(dma_req_t *req, const char *src, int len){
    DMA_Channel_TypeDef *dmac = req->dmac;

    trace_crumb1("dma", "m2p", len);

    dmac->CCR = (req->prio << 22)
        | DMA_CCR_TCIE | DMA_CCR_DTEIE | DMA_CCR_USEIE
        ;
    dmac->CTR1 = (3 << 4) // SBL (source burst length) = 4 bytes
        | DMA_CTR1_SAP	  // src on port 1
        | DMA_CTR1_SINC   // increment src addr
        ;
    dmac->CTR2 = (1 << 10) // periph is dst
        | req->req_tx;

    dmac->CBR1 = len;
    dmac->CSAR = src;
    dmac->CDAR = req->port_tx;

    dmac->CCR |= DMA_CCR_EN;

    return 0;
}

int
dma_p2m(dma_req_t *req, char *dst, int len){
    DMA_Channel_TypeDef *dmac = req->dmac;

    trace_crumb1("dma", "p2m", len);

    dmac->CCR = (req->prio << 22)
        | DMA_CCR_TCIE | DMA_CCR_DTEIE | DMA_CCR_USEIE
        ;
    dmac->CTR1 = (3 << 20) // DBL (dest burst length) = 4 bytes
        | DMA_CTR1_DAP	   // dst on port 1
        | DMA_CTR1_DINC    // increment dst addr
        ;
    dmac->CTR2 = (0 << 10) // periph is src
        | req->req_rx;

    dmac->CBR1 = len;
    dmac->CSAR = req->port_rx;
    dmac->CDAR = dst;

    dmac->CCR |= DMA_CCR_EN;

    return 0;
}

void
dma_reset( dma_req_t *req ){
    DMA_Channel_TypeDef *dmac = req->dmac;

    trace_crumb1("dma", "reset", req->chan);

    dmac->CCR &= ~DMA_CCR_EN;
    dmac->CCR |= DMA_CCR_RESET;
    dmac->CFCR = 0x7f00; // clear status flags

}


static inline void
_dma_irq_handler(int n){
    dma_req_t *cf = dmacf[ n ];
    DMA_Channel_TypeDef *dev = dmachan[ n ];
    uint32_t sr = dev->CSR;

    trace_crumb2("dma", "irq!", n, sr);

    dev->CFCR = 0x7f00; // clear status flags

    if( cf && cf->callback )
        cf->callback( cf->cbarg, sr );
}

/* **************************************************************** */

#define IRQ(d, n) GPDMA ## d ##_Channel ## n ## _IRQHandler (){ _dma_irq_handler( n + ((d-1)<<3) ); }

IRQ(1, 0)
IRQ(1, 1)
IRQ(1, 2)
IRQ(1, 3)
IRQ(1, 4)
IRQ(1, 5)
IRQ(1, 6)
IRQ(1, 7)

#ifdef PLATFORM_STM32H5
IRQ(2, 0)
IRQ(2, 1)
IRQ(2, 2)
IRQ(2, 3)
IRQ(2, 4)
IRQ(2, 5)
IRQ(2, 6)
IRQ(2, 7)

#else
IRQ(1, 8)
IRQ(1, 9)
IRQ(1, 10)
IRQ(1, 11)
IRQ(1, 12)
IRQ(1, 13)
IRQ(1, 14)
IRQ(1, 15)
#endif

/* **************************************************************** */

#ifdef KTESTING

DEFUN(dmainfo, "dma info")
{
    int n = 0;
    if( argc > 1 ) n = atoi( argv[1] );

    DMA_Channel_TypeDef *dmac = dmachan[ n ];

    printf("chan %d @%08x\n", n, dmac);
    printf("CLBAR  %08x\n", dmac->CLBAR);
    printf("CLLR   %08x\n", dmac->CLLR);
    printf("CSR    %08x\n", dmac->CSR);
    printf("CCR    %08x\n", dmac->CCR);
    printf("CTR1   %08x\n", dmac->CTR1);
    printf("CTR2   %08x\n", dmac->CTR2);
    printf("CTR3   %08x\n", dmac->CTR3);
    printf("CLBR1  %08x\n", dmac->CBR1);
    printf("CLBR2  %08x\n", dmac->CBR2);
    printf("CSAR   %08x\n", dmac->CSAR);
    printf("CDAR   %08x\n", dmac->CDAR);

    return 0;
}

DEFUN(dmareset, "dma reset")
{

    int n = 0;
    if( argc > 1 ) n = atoi( argv[1] );

    DMA_Channel_TypeDef *dmac = dmachan[ n ];

    printf("CCR %08x = %08x\n", dmac, dmac->CCR);
    dmac->CCR &= ~DMA_CCR_EN;
    dmac->CCR |= DMA_CCR_RESET;
    printf("CCR %08x = %08x\n", dmac, dmac->CCR);

    return 0;
}

#endif
