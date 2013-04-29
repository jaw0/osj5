

LD = gcc
LINK = gcc
LINK_FLAGS = -Wl,'--entry=start' -ffreestanding -nostdlib -static -lgcc
CFLAGS = -g -fno-builtin

INCL_FLAGS = -I../../src/machdep/i386/common/inc
