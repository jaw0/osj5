

LD = gcc
LINK = gcc
LINK_FLAGS = -Wl,'--entry=start' -ffreestanding -nostdlib -static -lgcc
CFLAGS = -g -fno-builtin

