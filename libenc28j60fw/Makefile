# Sources:
C_SRC=enc28j60_fw_base.c
H_SRC=enc28j60_fw.h enc28j60_fw_macros.h

# Libs dependency
MY_LIBS = enc28j60d

# Target MCU
MCU ?= atmega16
F_CPU ?= 16000000UL

# Target library:
TARGET_LIB=libenc28j60fw.a

# Additional includes:
INC=-I../avrutils $(addprefix -I../lib,$(MY_LIBS))

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

