

LD = gcc
LINK = gcc
OBJCOPY = objcopy

LINK_FLAGS = -Wl,'--entry=crt_init' -ffreestanding -nostdlib -static -nostartfiles -Wl,-T$(LINK_SCRIPT) -Wl,-n
#LINK_FLAGS = -Wl,'--entry=crt_init' -ffreestanding -nostdlib -static -nostartfiles 

CFLAGS = -g -fno-builtin
#LIBS = -lgcc

INCL_FLAGS = -I../../src/machdep/i386/common/inc


