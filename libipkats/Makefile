# Sources:
C_SRC=banepro_ethernet.c banepro_arp.c banepro_ipv4.c banepro_icmp.c banepro_utils.c
H_SRC=banepro_ethernet.h banepro_arp.h banepro_ipv4.h banepro_icmp.h banepro_utils.h banepro_config.h

# Target MCU
MCU ?= atmega16
F_CPU ?= 16000000UL

# Target library:
TARGET_LIB=libbanepro.a

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
%.o : %.c $(H_SRC)
	$(CC) $(CFLAGS) -o $@ -c $<

# Clean target:
clean:
	$(RM) $(TARGET_LIB) $(O_FILES)

