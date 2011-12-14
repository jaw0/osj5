
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: serial.h,v 1.4 2001/10/31 18:09:13 jaw Exp $ */

#ifndef __serial_h__
#define __serial_h__

#define COM1BASE        0x3F8   /*  Base port address for COM1  */
#define COM2BASE        0x2F8   /*  Base port address for COM2  */

/*
    The 8250 UART has 10 registers accessible through 7 port addresses.
    Here are their addresses relative to COM1BASE and COM2BASE. Note
    that the baud rate registers, (DLL) and (DLH) are active only when
    the Divisor-Latch Access-Bit (DLAB) is on. The (DLAB) is bit 7 of
    the (LCR).

        o TBR Output data to the serial port.
        o RBR Input data from the serial port.
        o LCR Initialize the serial port.
        o IER Controls interrupt generation.
        o IIR Identifies interrupts.
        o MCR Send contorl signals to the modem.
        o LSR Monitor the status of the serial port.
        o MSR Receive status of the modem.
        o DLL Low byte of baud rate divisor.
        o DHH High byte of baud rate divisor.
*/
#define TBR             0       /*  Transmit register (WRITE) */
#define RBR             0       /*  Receive register  (READ)  */
#define IER             1       /*  Interrupt Enable          */
#define IIR             2       /*  Interrupt ID              */
#define LCR             3       /*  Line control              */
#define MCR             4       /*  Modem control             */
#define LSR             5       /*  Line Status               */
#define MSR             6       /*  Modem Status              */
#define DLL             0       /*  Divisor Latch Low         */
#define DLH             1       /*  Divisor latch High        */


/*-------------------------------------------------------------------*
  Bit values held in the Line Control Register (LCR).
        bit             meaning
        ---             -------
        0-1             00=5 bits, 01=6 bits, 10=7 bits, 11=8 bits.
        2               Stop bits.
        3               0=parity off, 1=parity on.
        4               0=parity odd, 1=parity even.
        5               Sticky parity.
        6               Set break.
        7               Toggle port addresses - DL.
 *-------------------------------------------------------------------*/
#define LCR_7BITS	2
#define LCR_8BITS	3
#define LCR_1STOPBIT	0
#define LCR_2STOPBITS	4
#define LCR_NO_PARITY   0
#define LCR_EVEN_PARITY	0x18
#define LCR_ODD_PARITY	0x08
#define LCR_DLAB	0x80

/*-------------------------------------------------------------------*
  Bit values held in the Line Status Register (LSR).
        bit             meaning
        ---             -------
        0               Data ready.
        1               Overrun error - Data register overwritten.
        2               Parity error - bad transmission.
        3               Framing error - No stop bit was found.
        4               Break detect - End to transmission requested.
        5               Transmitter holding register is empty.
        6               Transmitter shift register is empty.
        7               Time out - off line.
 *-------------------------------------------------------------------*/
#define LSR_RCVFULL	1
#define LSR_OVERRUN	2
#define LSR_PARITYERR	4
#define LSR_FRAMERR	8
#define LSR_BREAK	16
#define LSR_TXBMT	32
#define LSR_TXMT	64

/*------------------------------------------------------------------*
  Bit values held in the Interrupt Enable Register (IER).
        bit             meaning
        ---             -------
        0               Interrupt when data received.
        1               Interrupt when transmitter holding reg. empty.
        2               Interrupt when data reception error.
        3               Interrupt when change in modem status register.
        4-7             Not used.
 *------------------------------------------------------------------*/
#define IER_RCVFULL	1
#define IER_TXBMT	2
#define IER_LINE	4
#define IER_MODEM	8


/*------------------------------------------------------------------*
  Bit values held in the Interrupt Identification Register (IIR).
        bit             meaning
        ---             -------
        0               Interrupt pending
        1-2             Interrupt ID code
                        00=Change in modem status register,
                        01=Transmitter holding register empty,
                        10=Data received,
                        11=reception error, or break encountered.
        3-7             Not used.
 *------------------------------------------------------------------*/
#define IIR_PENDING	1
#define IIR_SRC_MASK	6
#define IIR_MODEM	0
#define IIR_TXBMT	2
#define IIR_RCVFULL	4
#define IIR_LINE	6



/*-------------------------------------------------------------------*
  Bit values held in the Modem Output Control Register (MCR).
        bit             meaning
        ---             -------
        0               Data Terminal Ready. Computer ready to go.
        1               Request To Send. Computer wants to send data.
        2               auxillary output #1.
        3               auxillary output #2.(Note: This bit must be
                        set to allow the communications card to send
                        interrupts to the system)
        4               UART ouput looped back as input.
        5-7             not used.
 *------------------------------------------------------------------*/
#define MCR_DTR		1
#define MCR_RTS		2
#define MCR_AUX1	4
#define MCR_AUX2	8

/*------------------------------------------------------------------*
  Bit values held in the Modem Input Status Register (MSR).
        bit             meaning
        ---             -------
        0               delta Clear To Send.
        1               delta Data Set Ready.
        2               delta Ring Indicator.
        3               delta Data Carrier Detect.
        4               Clear To Send.
        5               Data Set Ready.
        6               Ring Indicator.
        7               Data Carrier Detect.
 *------------------------------------------------------------------*/
#define MSR_DCTS	1
#define MSR_DDSR	2
#define MSR_TERI	4
#define MSR_DDCD	8
#define MSR_CTS		16
#define MSR_DSR		32
#define MSR_RI		64
#define MSR_DCD		128


/*
    These are the port addresses of the 8259 Programmable Interrupt
    Controller (PIC).
*/
#define IMR             0x21   /* Interrupt Mask Register port */
#define ICR             0x20   /* Interrupt Control Port       */


#endif /* __serial_h__ */

