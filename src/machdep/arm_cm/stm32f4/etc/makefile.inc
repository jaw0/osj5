
CONF_PREFIX = arm-none-eabi-
CONF_FLAGS  = -mthumb -mcpu=cortex-m4 -march=armv7e-m -mno-thumb-interwork -Os

INCL_FLAGS  = -I../../src/machdep/arm_cm/stm32f4/inc -I../../src/machdep/arm_cm/stm32/inc -I../../src/machdep/arm_cm/common/inc

LINK_SUFFIX = .elf

AS = $(CONF_PREFIX)as $(CONF_FLAGS)
CC = $(CONF_PREFIX)gcc $(CONF_FLAGS)
CXX = $(CONF_PREFIX)g++ $(CONF_FLAGS) -fno-rtti -fconserve-space -fno-exceptions -fno-unwind-tables
OBJCOPY = $(CONF_PREFIX)objcopy

LINK = $(CONF_PREFIX)gcc
LINK_FLAGS = -Wl,-T$(LINK_SCRIPT)  -nostartfiles
LIBS = -lm

CFLAGS = -ffreestanding

CLEANFILES += osj5.bin

# convert elf file to binary

all: osj5.bin

osj5.bin: osj5.elf
	$(OBJCOPY) -O binary osj5.elf osj5.bin
	@readelf -S osj5$(LINK_SUFFIX) | egrep 'isr|text|data|bss' | awk '{printf "%-16s %s %s\n", $$3, $$5, $$7}'

