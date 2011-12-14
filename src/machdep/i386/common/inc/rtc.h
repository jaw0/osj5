
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: rtc.h,v 1.2 2001/10/31 18:09:13 jaw Exp $ */

#ifndef __rtc_h__
#define __rtc_h__

#define RTC_PORT	0x70

#define RTC_ADDR	0	/* register select */
#define RTC_DATA	1	/* data read/write */

/*
 * The MC146818A has 16 registers.  The first 10 contain time-of-year
 * and alarm data.  The rest contain various control and status bits.
 *
 * To read or write the registers, one writes the register number to
 * the RTC's control port, then either reads from or writes the new
 * data to the RTC's data port.  Since the locations of these ports
 * and the method used to access them can be machine-dependent, the
 * low-level details of reading and writing the RTC's registers are
 * handled by machine-specific functions.
 */

#define RTC_SEC          0x0     /* Time of year: seconds (0-59) */
#define RTC_ASEC         0x1     /* Alarm: seconds */
#define RTC_MIN          0x2     /* Time of year: minutes (0-59) */
#define RTC_AMIN         0x3     /* Alarm: minutes */
#define RTC_HOUR         0x4     /* Time of year: hour 0-24 or 1-12/81-92 */
#define RTC_AHOUR        0x5     /* Alarm: hour */
#define RTC_DOW          0x6     /* Time of year: day of week (1-7) */
#define RTC_DOM          0x7     /* Time of year: day of month (1-31) */
#define RTC_MONTH        0x8     /* Time of year: month (1-12) */
#define RTC_YEAR         0x9     /* Time of year: year in century (0-99) */

/*
 * Register A definitions
 */
#define RTC_A           0x0a    /* register A address */
#define RTC_UIP         0x80    /* Update in progress bit */
#define RTC_DIV0        0x00    /* Time base of 4.194304 MHz */
#define RTC_DIV1        0x10    /* Time base of 1.048576 MHz */
#define RTC_DIV2        0x20    /* Time base of 32.768 KHz */
#define RTC_RATE6       0x06    /* interrupt rate of 976.562 */
/*
 * Periodic Interrupt Rate Select constants (Control register A)
 */
#define RTC_RATE_NONE    0x0     /* No periodic interrupt */
#define RTC_RATE_1       0x1     /* 256 Hz if MC_BASE_32_KHz, else 32768 Hz */
#define RTC_RATE_2       0x2     /* 128 Hz if MC_BASE_32_KHz, else 16384 Hz */
#define RTC_RATE_8192_Hz 0x3     /* 122.070 us period */
#define RTC_RATE_4096_Hz 0x4     /* 244.141 us period */
#define RTC_RATE_2048_Hz 0x5     /* 488.281 us period */
#define RTC_RATE_1024_Hz 0x6     /* 976.562 us period */
#define RTC_RATE_512_Hz  0x7     /* 1.953125 ms period */
#define RTC_RATE_256_Hz  0x8     /* 3.90625 ms period */
#define RTC_RATE_128_Hz  0x9     /* 7.8125 ms period */
#define RTC_RATE_64_Hz   0xa     /* 15.625 ms period */
#define RTC_RATE_32_Hz   0xb     /* 31.25 ms period */
#define RTC_RATE_16_Hz   0xc     /* 62.5 ms period */
#define RTC_RATE_8_Hz    0xd     /* 125 ms period */
#define RTC_RATE_4_Hz    0xe     /* 250 ms period */
#define RTC_RATE_2_Hz    0xf     /* 500 ms period */

/*
 * Register B definitions
 */
#define RTC_B           0x0b    /* register B address */
#define RTC_SET         0x80    /* stop updates for time set */
#define RTC_PIE         0x40    /* Periodic interrupt enable */
#define RTC_AIE         0x20    /* Alarm interrupt enable */
#define RTC_UIE         0x10    /* Update ended interrupt enable */
#define RTC_SQWE        0x08    /* Square wave enable */
#define RTC_DM          0x04    /* Date mode, 1 = binary, 0 = BCD */
#define RTC_HM          0x02    /* hour mode, 1 = 24 hour, 0 = 12 hour */
#define RTC_DSE         0x01    /* Daylight savings enable */

/* 
 * Register C definitions
 */
#define RTC_C           0x0c    /* register C address */
#define RTC_IRQF        0x80    /* IRQ flag */
#define RTC_PF          0x40    /* PF flag bit */
#define RTC_AF          0x20    /* AF flag bit */
#define RTC_UF          0x10    /* UF flag bit */

/*
 * Register D definitions
 */
#define RTC_D           0x0d    /* register D address */
#define RTC_VRT         0x80    /* Valid RAM and time bit */

#define RTC_NREG        0x0e    /* number of RTC registers */
#define RTC_NREGP       0x0a    /* number of RTC registers to set time */

#define RTC_NVRAM_START  0xe    /* start of NVRAM: offset 14 */
#define RTC_NVRAM_SIZE   50     /* 50 bytes of NVRAM */



#endif /* __rtc_h__ */

