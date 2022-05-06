OUTPUT_FILE_NAME = app
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

ASSEMBLY_SOURCE = ./targets/stm32f767/startup_stm32f767xx.s
CPP_SOURCE = $(wildcard ./src/*.cpp)

INCLUDE = -I ./
INCLUDE += -I ./targets/stm32f767/headers

ASSEMBLY_OBJ = $(addprefix dist/, $(notdir $(ASSEMBLY_SOURCE:.s=.o)))
CPP_OBJ = $(addprefix dist/, $(notdir $(CPP_SOURCE:.cpp=.o)))

.PHONY: build clean flash

build: clean $(OUTPUT_FILE_NAME).bin

$(ASSEMBLY_OBJ): $(ASSEMBLY_SOURCE)
	$(GCC) -x assembler-with-cpp $(ASFLAGS) $< -o $@

$(CPP_OBJ): $(CPP_SOURCE)
	$(GCC) -c $(CPPFLAGS) $(INCLUDE) $< -o $@

$(OUTPUT_FILE_NAME).elf: $(ASSEMBLY_OBJ) $(CPP_OBJ)
	$(GCC) $^ $(LFLAGS) -o dist/$@

$(OUTPUT_FILE_NAME).bin: $(OUTPUT_FILE_NAME).elf
	$(OC) -S -O binary dist/$< dist/$@
	$(OS) dist/$<

clean: dist
	rm -rf ./dist/*

dist:
	mkdir -p dist

flash: $(OUTPUT_FILE_NAME).bin
	st-flash --reset write ./dist/$(OUTPUT_FILE_NAME).bin $(CODE_SPACE_ADDRESS)