# Make file
# If there is a DS3231 clock on the board the time has to set somehow.  Maybe at
# the same time as compile by setting the struct DStm values then writing those to the clock
# on first boot up.  Save the boot count in the EEPROM to enable this.
#
#
# PROGRAM options are: torchy, pir, ir_sensor, piezo
PROGRAM = lptcap
CSRCS = main.c  adc.c  serial.c
#AsmTinySerial.S system_clock.c


MCU=attiny84
DUDE_MCU=t84

F_CPU = 8000000

# For 8MHz
FUSE_L = 0xE2
# For 1MHz
#FUSE_L = 0x62
FUSE_H = 0xDF
FUSE_E = 0xFF

##SERIAL:=$(shell ls -l /dev/serial/by-id/ | grep Arduino |  awk -F/ '{ print $$3}')
#SERIAL:=ttyUSB0
AVRDUDE = avrdude  -c stk200 -p $(DUDE_MCU)
#AVRDUDE := avrdude  -p $(DUDE_MCU) -c usbtiny -p $(DUDE_MCU)


# Place -D or -U options here
CDEFS = -DF_CPU=$(F_CPU) -D$(PROGRAM) -DMCU=$(MCU)
CXXDEFS = -DF_CPU=$(F_CPU)

# Add -Wl,-u,vfprintf -lprintf_flt -lm  to enable sprintf and float point convertion libraries
#CFLAGS = -Wl,--start-group
CFLAGS += -mmcu=$(MCU) $(CDEFS) -Os
CFLAGS += -mcall-prologues
CFLAGS += -Wno-deprecated-declarations
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -fno-inline-small-functions -mrelax
CFLAGS += -std=c99
CFLAGS += -fdata-sections -ffunction-sections
#CFLAGS += -Wl,--end-group
#CFLAGS += -Wunused-variable
# For "AVRTools/ArduinoPins.h"
#CFLAGS += -D__AT_Tiny__

# If using sprintf and want floating conversion then uncomment below.
#CFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm

# If you want VERY small code then don't use startfiles, but you'll need a start jump in crt1.s
# Precompile this with avr-gcc -c crt1.s then include the object file
#CFLAGS += -nostartfiles crt1.o
#LIBSRC = ../../lib_tiny84/src
INCLUDES = -I .
#INCLUDES = -I ../../lib_tiny84/include
#-I . -I /usr/local/avr/include/
#INCLUDES = -I AVRTools
#LDFLAGS = -L AVRTools
#INCLUDES Libs are currently only for m328
#LDFLAGS = -s -L ../../lib_tiny84/lib  -lattiny84
LDFLAGS += -Wl,-gc-sections
# -Wl,--strip-all
#LDFLAGS += -Wl,-Map=$(PROGRAM).map,--cref
#LIBDEPS = ../../../../lib/src/bluestone.c
#LIBDEPS += ../../../../lib/src/df_player.c
#LIBDEPS += ../../../../lib/src/adc.c
#LIBDEPS += ../../../../lib/src/stp16cp05.c


CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump -D

STRIP=avr-strip

COBJS = $(CSRCS:.c=.o)
OBJS += $(CSRCS:.S=.o)
HEADS := $(CSRCS:.c=.h)
AOBJS := $(COBJS:.s=.o)
CLSTS := $(CSRCS:.c=.lst)


default: all


all: gitversion $(PROGRAM).hex $(PROGRAM).eep Makefile

olist:
	@echo "$(COBJS)"

$(COBJS): $(CSRCS) $(HEADS)  Makefile
	$(CC) $(INCLUDES) $(CFLAGS)  -c $(CSRCS)

gitversion:
	echo -n "char gitversion [] EEMEM = \"Ver: $(shell date +%Y%m%d)-" > gitversion.h
	echo  "$(shell git log --since "00:00:00 $(git log -1 --pretty=format:%ci | awk '{print $1}')" | grep ^Author: | wc -l)\";" >> gitversion.h

# This can be used to set the RTC to the current UTC time on first run
# Use an EEPROM flag to check for first run.
gettime:
	echo "char * timenow = \"$(shell date +\"%Y-%m-%d  %H:%M:%S\")\";" > timenow.h
	echo "int year_now = $(shell date -u +%Y);" >> timenow.h
	echo "int mon_now = $(shell date -u +%-m);" >> timenow.h
	echo "int mday_now = $(shell date -u +%-d);" >> timenow.h
	echo "int wday_now = $(shell date -u +%-u);" >> timenow.h
	echo "int h_now = $(shell date -u +%-H);" >> timenow.h
	echo "int m_now = $(shell date -u +%-M);" >> timenow.h
	echo "int s_now = $(shell date -u +%-S);" >> timenow.h
	#echo "$(shell ./sunsets.py);"

# Link: create ELF output file from object files
$(PROGRAM).elf: $(COBJS) $(LIBDEPS)
	#$(MAKE) lib -C (LIBSRC)
	$(CC)  $(INCLUDES) $(CFLAGS)  $^ -o $@ $(LDFLAGS)
	@avr-size -C --mcu=${MCU} $(PROGRAM).elf


listings:
	$(CC) -Wa,-adhln -g $(CFLAGS)  $(INCLUDES)  $(LDFLAGS) $(CSRCS) > $(PROGRAM).s
	rm a.out


# Create hex output file from ELF output file.
$(PROGRAM).hex: $(PROGRAM).elf
	$(OBJCOPY) -R .eeprom  -g -O ihex $< $@


$(PROGRAM).eep: $(PROGRAM).elf
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex $< $@



# Target: clean project.
.PHONY: clean
clean:
	rm -f .eep .hex .elf *.o *.elf *.hex *.map *.lst *.s *.eep *.pyc

.PHONY: realclean
realclean: clean
	rm -f *~ *.bak

style: indent

indent:
	astyle -n $(CSRCS) $(CPPSRCS) $(HEADS)


# Program the AVR.
install: all
	$(AVRDUDE) -y -U flash:w:$(PROGRAM).hex:i
	$(AVRDUDE) -U eeprom:w:$(PROGRAM).eep:i

verify:
	$(AVRDUDE) -y -U flash:v:$(PROGRAM).hex:i
	$(AVRDUDE) -y -U eeprom:v:$(PROGRAM).eep:i

fuses:
	@[ "$(FUSE_H)" != "" -a "$(FUSE_L)" != "" ] || { echo "*** Edit Makefile and choose values for FUSE_L and FUSE_H!"; exit 1; }
	$(AVRDUDE)  -U lfuse:w:$(FUSE_L):m -U hfuse:w:$(FUSE_H):m -U efuse:w:$(FUSE_E):m

#-U hfuse:w:0xD9:m -U lfuse:w:0xe4:m
