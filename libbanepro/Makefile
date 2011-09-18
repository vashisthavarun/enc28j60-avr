# Sources:
C_SRC=ethernet.c arp.c ipv4.c icmp.c utils.c
H_SRC=ethernet.h arp.h ipv4.h icmp.h utils.h

# Target MCU
MCU ?= atmega16
F_CPU ?= 8000000UL

# Target library:
TARGET_LIB=libavrbanepro.a

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

