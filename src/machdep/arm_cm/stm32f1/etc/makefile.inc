
CONF_PREFIX = arm-none-eabi-
CONF_FLAGS  = -mthumb -mcpu=cortex-m3 -march=armv7-m -mno-thumb-interwork -Os

LINK_SUFFIX = .elf

AS = $(CONF_PREFIX)as $(CONF_FLAGS)
CC = $(CONF_PREFIX)gcc $(CONF_FLAGS)
OBJCOPY = $(CONF_PREFIX)objcopy

LINK = $(CONF_PREFIX)gcc
LINK_FLAGS = -Wl,-T$(LINK_SCRIPT)  -nostartfiles

CFLAGS = -ffreestanding

CLEANFILES += osj5.bin

# convert elf file to binary

all: osj5.bin

osj5.bin: osj5.elf
	$(OBJCOPY) -O binary osj5.elf osj5.bin


