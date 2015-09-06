## General Flags
PROJECT = test
MCU = atmega2560
OBJDIR = build

TARGET = $(OBJDIR)/$(PROJECT).elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99       -DF_CPU=14745600UL -O0 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(OBJDIR)/$(*F).o -MF $(OBJDIR)/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

INCLUDES = -I"$(HOME)/.local/lib"
LIBDIRS = -L"$(HOME)/.local/lib"
LIBS = -lfirebird

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=$(OBJDIR)/$(PROJECT).map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = $(OBJDIR)/$(PROJECT).o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) $(OBJDIR)/$(PROJECT).hex $(OBJDIR)/$(PROJECT).eep $(OBJDIR)/$(PROJECT).lss size

## Compile
$(OBJDIR)/$(PROJECT).o: $(PROJECT).c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $< -o $@

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(OBJDIR)/$(PROJECT).o.d $(OBJDIR)/$(PROJECT).elf $(OBJDIR)/$(PROJECT).eep $(OBJDIR)/$(PROJECT).lss $(OBJDIR)/$(PROJECT).map



