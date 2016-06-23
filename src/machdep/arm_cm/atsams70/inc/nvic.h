

extern void nvic_enable(int irq, int prio);


#define EXCEPTION_NMI        2
#define EXCEPTION_HARDFAULT  3
#define EXCEPTION_MEMMANAGE  4
#define EXCEPTION_BUSFAULT   5
#define EXCEPTION_USAGEFAULT 6
#define EXCEPTION_SVCALL     11
#define EXCEPTION_PENDSV     14
#define EXCEPTION_SYSTICK    15

