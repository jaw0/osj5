/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-25 17:29 (EDT)
  Function: spi
*/

#ifndef __spi_h__
#define __spi_h__



struct SPIConf {
    int		unit;
    int		speed;
    int		nss;
    char	ss[8];
};



typedef struct spi_msg {
    u_char	mode;
# define SPIMO_READ	1
# define SPIMO_WRITE	2
# define SPIMO_UNTIL	3
# define SPIMO_DELAY	4
# define SPIMO_FINISH	5	// wait for last byte to finish
# define SPIMO_PINSOFF	6
# define SPIMO_PINSON	7
    u_char	response;
    short	dlen;
    char	*data;
    int		(*until)(int);

} spi_msg;

int spi_xfer(const struct SPIConf *, int, spi_msg*, int);

#define SPI_XFER_OK		0
#define SPI_XFER_TIMEOUT	-1
#define SPI_XFER_ERROR		-2

#endif /* __spi_h__ */