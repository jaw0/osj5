/*
  Copyright (c) 2016
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2016-Jun-15 19:27 (EDT)
  Function: 

*/

#ifndef __atsam_pmc_h__
#define __atsam_pmc_h__

static inline void
pmc_enable(int id){

    if( id > 31 )
        PMC->PMC_PCER1 |= 1<< (id-32);
    else
        PMC->PMC_PCER0 |= 1<<id;
}

static inline void
pmc_disable(int id){

    if( id > 31 )
        PMC->PMC_PCDR1 |= 1<< (id-32);
    else
        PMC->PMC_PCDR0 |= 1<<id;
}


#endif /* __atsam_pmc_h__ */
