/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-25 17:29 (EDT)
  Function: spi
*/

#ifndef __spi_h__
#define __spi_h__


#define SPI_XFER_TIMEOUT	-1
#define SPI_XFER_OK		0


#define SPI_FLAG_READ	0x1
#define SPI_FLAG_CRC7	0x2

struct SPIConf {
    int		unit;
    u_long	flags;
    int		speed;
    int		nss;
    char	ss[8];
};


int spi_write1(const struct SPIConf *, int);
int spi_xfer(const struct SPIConf *, int, char *, int);


#endif /* __spi_h__ */
