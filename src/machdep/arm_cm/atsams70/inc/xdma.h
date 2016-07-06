/*
  Copyright (c) 2016
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2016-Jun-27 19:22 (EDT)
  Function: xdma

*/

#ifndef __osj5_atsams70_xdma_h__
#define __osj5_atsams70_xdma_h__


typedef void (*dma_handler_t)(int);

#define XDMAF_M2P	1
#define XDMAF_P2M	2
#define XDMAF_MINC	4
#define XDMAF_8BIT	0
#define XDMAF_16BIT	8
#define XDMAF_32BIT	16
#define XDMAF_CHK_1	0
#define XDMAF_CHK_2	(1<<16)
#define XDMAF_CHK_4	(2<<16)
#define XDMAF_CHK_8	(3<<16)
#define XDMAF_CHK_16	(4<<16)


// ...

extern int  dma_alloc(dma_handler_t, int);
extern void dma_free(int);
extern void dma_config(int, int, int, void *, char *, int);
extern void dma_start(int);
extern void dma_stop(int);
extern int  dma_wait_complete(int, void *, int, int);


#endif /*  __osj5_atsams70_xdma_h__ */
