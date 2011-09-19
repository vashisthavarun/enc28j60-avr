# Sources:
C_SRC=ipk.c ipk_arp.c
H_SRC=ipk.h ipk_arp.h ipk_config.h

# Target MCU
MCU ?= atmega16
F_CPU ?= 16000000UL

# Target library:
TARGET_LIB=libipkats.a

# Additional includes:
INC=-I../libbanepro -I../libenc28j60fw -I../libenc28j60d

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

