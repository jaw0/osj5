OUTPUT_FORMAT("a.out-i386-netbsd", "a.out-i386-netbsd",
	      "a.out-i386-netbsd")
OUTPUT_ARCH(i386)
SEARCH_DIR(/usr/lib);
PROVIDE (__stack = 0);

SECTIONS
{
  . = 0;
  .text :
  {
    CREATE_OBJECT_SYMBOLS
    *(.text)
    *(.rodata)
    /* The next six sections are for SunOS dynamic linking.  The order
       is important.  */
    *(.dynrel)
    *(.hash)
    *(.dynsym)
    *(.dynstr)
    *(.rules)
    *(.need)
    etext = .;
    _etext = .;
  }

  . = ALIGN(0x1000);
  .data :
  {
    /* The first three sections are for SunOS dynamic linking.  */
    *(.dynamic)
    *(.got)
    *(.plt)
    *(.data)
    *(.linux-dynamic) /* For Linux dynamic linking.  */
    CONSTRUCTORS
    edata  =  .;
    _edata  =  .;
  }

  .bss :
  {
    __bss_start = .;
   *(.bss)
   *(COMMON)
   end = ALIGN(4) ;
   _end = ALIGN(4) ;
  }

  /DISCARD/ :
  {
    *(.note)
    *(.stab)
    *(.stabstr)
    *(.debug*)
    *(.comment*)
  }
}
