TARGET = app
CODE_SPACE_ADDRESS = 0x8000000

# Define the linker script location and chip architecture.
LD_SCRIPT = ./targets/stm32f767/STM32F767ZITx.ld
MCU_SPEC = cortex-m7

# Toolchain definitions (ARM bare metal defaults)
TOOLCHAIN = /usr
GCC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump
OS = arm-none-eabi-size

# Assembly directives.
ASFLAGS += -c
ASFLAGS += -O0
ASFLAGS += -mcpu=$(MCU_SPEC)
ASFLAGS += -mthumb
ASFLAGS += -Wall
# (Set error messages to appear on a single line.)
ASFLAGS += -fmessage-length=0

# CPP compilation directives
CPPFLAGS += -mcpu=$(MCU_SPEC)
CPPFLAGS += -mthumb
CPPFLAGS += -Wall
CPPFLAGS += -ggdb
CPPFLAGS += -ggdb3
CPPFLAGS += -fvar-tracking
# (Set error messages to appear on a single line.)
CPPFLAGS += -fmessage-length=0
# (Set system to ignore semihosted junk)
CPPFLAGS += --specs=nosys.specs

# Linker directives.
LSCRIPT = ./$(LD_SCRIPT)
LFLAGS += -mcpu=$(MCU_SPEC)
LFLAGS += -mthumb
LFLAGS += -Wall
LFLAGS += --specs=nosys.specs
LFLAGS += -nostdlib
LFLAGS += -lgcc
LFLAGS += -T$(LSCRIPT)

AS_SRC = ./targets/stm32f767/startup_stm32f767xx.s
CPP_SRC = ./src/main.cpp

INCLUDE = -I ./
INCLUDE += -I ./targets/stm32f767/headers

OBJS = $(AS_SRC:.s=.o)
OBJS += $(CPP_SRC:.cpp=.o)

.PHONY: all
all: $(TARGET).bin

%.o: %.s
	$(GCC) -x assembler-with-cpp $(ASFLAGS) $< -o $@

%.o: %.cpp
	$(GCC) -c $(CPPFLAGS) $(INCLUDE) $< -o $@

$(TARGET).elf: $(OBJS)
	$(GCC) $^ $(LFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OC) -S -O binary $< $@
	$(OS) $<

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(TARGET).elf
	rm -f $(TARGET).bin

.PHONY: flash
flash:
	st-flash --reset write $(TARGET).bin $(CODE_SPACE_ADDRESS)