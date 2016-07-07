/*
  Copyright (c) 2016
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2016-Jun-27 19:38 (EDT)
  Function: xdma

*/

#include <conf.h>
#include <proc.h>
#include <dev.h>
#include <error.h>
#include <atsam.h>
#include <pmc.h>
#include <nvic.h>
#include <xdma.h>

#define MAXCHAN	24
#define DMA_P2M		0
#define DMA_M2P		1

static uint32_t	xdma_alloced = 0;

static struct {
    dma_handler_t	callback;
    int			arg;
} xdmacf[MAXCHAN];


int
xdma_init(void){

    nvic_enable( XDMAC_IRQn, IPL_DISK );
    pmc_enable( ID_XDMAC  );
    return 0;
}


// allocate an available channel
int
dma_alloc(dma_handler_t handler, int arg){
    int i;

    for(i=0; i<MAXCHAN; i++){
        if( (xdma_alloced & (1<<i)) == 0 ){
            xdmacf[i].callback = handler;
            xdmacf[i].arg      = arg;
            xdma_alloced      |= 1<<i;
            xdma_init();
            return i;
        }
    }

    return -1;
}

void
dma_free(int ch){

    XDMAC->XDMAC_GD = 1<<ch;
    xdma_alloced &= ~(1<<ch);
}


void
XDMAC_Handler(void){
    int i, sr;

    for(i=0; i<MAXCHAN; i++)
        if( XDMAC->XDMAC_GIS & (1<<i) ){

            if( xdmacf[i].callback ){
                xdmacf[i].callback( xdmacf[i].arg );
            }else
                XDMAC->XDMAC_GID = 1<<i;	// no callback - disable


            // read status to clear irq
            sr = XDMAC->XDMAC_CHID[ i ].XDMAC_CIS;
        }

}

/****************************************************************/

void
dma_config(int dman, int flags, int id, void *per, char *mem, int len){

    XdmacChid *dmac = & XDMAC->XDMAC_CHID[ dman ];
    uint32_t cc;

// 2. Clear the pending Interrupt Status bit(s) by reading the chosen XDMAC Channel x Interrupt Status Register
// (XDMAC_CISx).

    int x = dmac->XDMAC_CIS;

// 3. Write the XDMAC Channel x Source Address Register (XDMAC_CSAx) for channel x.
// 4. Write the XDMAC Channel x Destination Address Register (XDMAC_CDAx) for channel x.

    // NB - periphs + flash are on AHB_IF1, RAM on IF0+1
    // the periphs that have their own DMA all use RAM-IF1

    if( flags & XDMAF_M2P ){
        dmac->XDMAC_CSA = (uint32_t)mem;
        dmac->XDMAC_CDA = (uint32_t)per;
        // RSN - SIF=IF0 if RAM and USB/ETHER are enabled?
        cc = XDMAC_CC_DSYNC_MEM2PER | XDMAC_CC_SIF_AHB_IF1 | XDMAC_CC_DIF_AHB_IF1;
        if( flags & XDMAF_MINC )
            cc |= XDMAC_CC_SAM_INCREMENTED_AM;
    }else{
        dmac->XDMAC_CSA = (uint32_t)per;
        dmac->XDMAC_CDA = (uint32_t)mem;
        cc = XDMAC_CC_DSYNC_PER2MEM | XDMAC_CC_SIF_AHB_IF1 | XDMAC_CC_DIF_AHB_IF0;
        if( flags & XDMAF_MINC )
            cc |= XDMAC_CC_DAM_INCREMENTED_AM;
    }

    if( flags & XDMAF_16BIT )
        cc |= XDMAC_CC_DWIDTH_HALFWORD;
    if( flags & XDMAF_32BIT )
        cc |= XDMAC_CC_DWIDTH_WORD;

    // chunk + mem size
    switch( (flags>>16) & 0xF ){
    case 0:	cc |=  XDMAC_CC_MBSIZE_FOUR    | XDMAC_CC_CSIZE_CHK_1;	break;
    case 1:	cc |=  XDMAC_CC_MBSIZE_FOUR    | XDMAC_CC_CSIZE_CHK_2;	break;
    case 2:	cc |=  XDMAC_CC_MBSIZE_EIGHT   | XDMAC_CC_CSIZE_CHK_4;	break;
    case 3:	cc |=  XDMAC_CC_MBSIZE_EIGHT   | XDMAC_CC_CSIZE_CHK_8;	break;
    case 4:	cc |=  XDMAC_CC_MBSIZE_SIXTEEN | XDMAC_CC_CSIZE_CHK_16;	break;
    }

// 5. Program field UBLEN in the XDMAC Channel x Microblock Control Register (XDMAC_CUBCx) with the
// number of data.

    dmac->XDMAC_CUBC = len;

// 6. Program the XDMAC Channel x Configuration Register (XDMAC_CCx):
// a. Clear XDMAC_CCx.TYPE for a memory to memory transfer, otherwise set this bit.
// b. Program XDMAC_CCx.MBSIZE to the memory burst size used.
// c. Program XDMAC_CCx.SAM/DAM to the memory addressing scheme.
// d. Program XDMAC_CCx.SYNC to select the peripheral transfer direction.
// e. Program XDMAC_CCx.CSIZE to configure the channel chunk size (only relevant for peripheral syn- chronized transfer).
// f. Program XDMAC_CCx.DWIDTH to configure the transfer data width.
// g. Program XDMAC_CCx.SIF, XDMAC_CCx.DIF to configure the master interface used to read data and write data respectively.
// h. Program XDMAC_CCx.PERID to select the active hardware request line (only relevant for a periph- eral synchronized transfer).
// i. Set XDMAC_CCx.SWREQ to use software request (only relevant for a peripheral synchronized transfer).

    dmac->XDMAC_CC = cc
        | XDMAC_CC_TYPE_PER_TRAN
        // periph bus is on IF1, RAM on 0+1 (RSN - 0 might be better)
        | XDMAC_CC_SIF_AHB_IF1 | XDMAC_CC_DIF_AHB_IF1
        | (id << XDMAC_CC_PERID_Pos);

// 7. Clear the following five registers:
// XDMAC Channel x Next Descriptor Control Register (XDMAC_CNDCx)
// XDMAC Channel x Block Control Register (XDMAC_CBCx)
// XDMAC Channel x Data Stride Memory Set Pattern Register (XDMAC_CDS_MSPx)
// XDMAC Channel x Source Microblock Stride Register (XDMAC_CSUSx)
// XDMAC Channel x Destination Microblock Stride Register (XDMAC_CDUSx)

    dmac->XDMAC_CNDC    = 0;
    dmac->XDMAC_CBC     = 0;
    dmac->XDMAC_CDS_MSP = 0;
    dmac->XDMAC_CSUS    = 0;
    dmac->XDMAC_CDUS    = 0;

// 8. Enable the Microblock interrupt by writing a 1 to bit BIE in the XDMAC Channel x Interrupt Enable Register (XDMAC_CIEx), enable the Channel x Interrupt Enable bit by writing a 1 to bit IEx in the XDMAC Global Interrupt Enable Register (XDMAC_GIE).

    dmac->XDMAC_CIE  = XDMAC_CIE_BIE;
    XDMAC->XDMAC_GIE = 1<<dman;


// 10. Oncecompleted,theDMAchannelsetsXDMAC_CISx.BIS(EndofBlockInterruptStatusbit)andgenerates an interrupt. XDMAC_GS.STx is cleared by hardware. The software can either wait for an interrupt or poll the channel status bit.


}

void
dma_start(int dman){

    // 9. Enable channel x by writing a 1 to bit ENx in the XDMAC Global Channel Enable Register (XDMAC_GE). XDMAC_GS.STx (XDMAC Channel x Status bit) is set by hardware.

    XDMAC->XDMAC_GE  = 1<<dman;
}

void
dma_stop(int dman){

    XDMAC->XDMAC_GD = 1<<dman;
    // and read the status
    int x = XDMAC->XDMAC_GS;
}

#define XDMAC_ERROR	(XDMAC_CIS_RBEIS | XDMAC_CIS_WBEIS | XDMAC_CIS_ROIS)

int
dma_wait_complete(int dman, void *wchan, int prio, int timo){
    XdmacChid *dmac = & XDMAC->XDMAC_CHID[ dman ];
    utime_t to = get_time() + (timo ? timo : 1000000);
    uint32_t sr;

    while( 1 ){
        asleep( wchan, "xdma" );

        if( (XDMAC->XDMAC_GS & (1 << dman)) == 0 ) break;
        sr = dmac->XDMAC_CIS;
        if( sr & XDMAC_CIS_BIS ) break;
        if( sr & XDMAC_ERROR )   break;

        await( prio, to - get_time() );

        if( (XDMAC->XDMAC_GS & (1 << dman)) == 0 ) break;
        sr = dmac->XDMAC_CIS;
        if( sr & XDMAC_CIS_BIS ) break;
        if( sr & XDMAC_ERROR )   break;
        if( get_time() > to )    return -1;
    }

    aunsleep();

    if( sr & XDMAC_CIS_BIS ) return 0;
    return sr & XDMAC_ERROR;

}
