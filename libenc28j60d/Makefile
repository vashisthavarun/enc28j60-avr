# Sources:
C_SRC=enc28j60_driver.c
H_SRC=enc28j60defs.h enc28j60_driver.h

# Libs dependency
MY_LIBS = enc28j60d

# Target MCU
MCU ?= atmega16
F_CPU ?= 8000000UL

# Target library:
TARGET_LIB=libenc28j60d.a

# Additional includes:
INC=

# Configuration:
HEXFORMAT=ihex
OPTLEVEL=s

# Tools:
CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
SIZE=avr-size
RM=rm -f
AR=avr-ar

# Shorts:
O_FILES=$(subst .c,.o,$(C_SRC))

# Assembler flags:
ASMFLAGS =-I. $(INC) -mmcu=$(MCU) \
	-Wa,-gstabs

# C flags:
CFLAGS=-I. $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums \
	-funsigned-bitfields -funsigned-char \
	-Wall \
	-DF_CPU=$(F_CPU)

# Archiver flags:
ARFLAGS=-rcs

# Phony targets:
.PHONY: clean

# Archive target:
$(TARGET_LIB): $(O_FILES) $(H_SRC)
	$(AR) $(ARFLAGS) $@ $(O_FILES)	

# Objects from C files:
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Clean target:
clean:
	$(RM) $(TARGET_LIB) $(O_FILES)

