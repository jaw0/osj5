
CONF_PREFIX = arm-none-eabi-
CONF_FLAGS  = -mthumb -mcpu=cortex-m4 -O2

LINK_FLAGS  = -L/usr/local/arm-none-eabi/lib/thumb -L/usr/local/lib/gcc/arm-none-eabi/4.6.2/thumb/ -lgcc
LINK_SUFFIX = .elf

AS = $(CONF_PREFIX)as $(CONF_FLAGS)
LD = $(CONF_PREFIX)ld -T $(LINK_SCRIPT) -X
CC = $(CONF_PREFIX)gcc $(CONF_FLAGS)
OBJCOPY = $(CONF_PREFIX)objcopy

CFLAGS = -ffreestanding

CLEANFILES += osj5.bin

# convert elf file to binary

all: osj5.bin

osj5.bin: osj5.elf
	$(OBJCOPY) -O binary osj5.elf osj5.bin



