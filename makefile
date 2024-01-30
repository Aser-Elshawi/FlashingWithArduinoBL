#==== Main Options =============================================================

COMPORT = COM3
MCU = atmega328p
F_CPU = 16000000
TARGET_NAME = Arduino


#==== Programming Options (avrdude) ============================================

AVRDUDE_PROGRAMMER = arduino
CONFIG_FILE = "avrdude.conf"

AVRDUDE_FLAGS := -v -p$(MCU) -c$(AVRDUDE_PROGRAMMER) -C$(CONFIG_FILE)
SHELL = C:\cygwin64\bin\sh.exe
#============== C files in thier respective Directories ========================
CSRCS =
		
		

SRCS = 	Services/TIMER1/TIMER1.cpp \
		MdUART/UART.cpp \
		Md_QUEUE/Md_QUEUE.cpp \
		SPI/SPI.cpp \
		OS/OStimer.cpp \
		OS/OS.cpp \
		main.cpp

		
INCS = 	OS/


#===============================================================================
#==== Targets ==================================================================
# Prepare target files path and name
FOLDER := Targets
TARGET := $(FOLDER)/$(TARGET_NAME)
MAPFILE := $(FOLDER)/$(TARGET_NAME)

# Convert c files to Object files in OBJ
COBJ := $(CSRCS:.c=.o)
OBJ := $(SRCS:.cpp=.o)
AOBJS := $(COBJ) $(OBJ)
CPPS :=$(SRCS:.cpp=.s)

# include path
INCLUDE := $(foreach dir, $(dir $(SRCS)), -I$(dir))
INCLUDE += $(foreach dir, $(dir $(CSRCS)), -I$(dir))
INCLUDE += $(foreach dir, $(dir $(INCS)), -I$(dir))
INCLUDE := $(sort $(INCLUDE)) 

#================================================================================

#==== Compile Options ==========================================================

FLAGS := -mmcu=$(MCU)
FLAGS += -DF_CPU=$(F_CPU)UL
FLAGS += -D__AVR_ATmega328P__
FLAGS += -DARDUINO
FLAGS += -Os
FLAGS += -g
FLAGS += -ffunction-sections
FLAGS += -fdata-sections
#FLAGS += -MD

CFLAGS := -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -Wall
#CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
#CFLAGS += -std=gnu99
CFLAGS += $(INCLUDE)

CPPFLAGS := -fpermissive
CPPFLAGS += -std=gnu++11
CPPFLAGS += -fno-exceptions
CPPFLAGS += -fno-threadsafe-statics
CPPFLAGS += -flto
CPPFLAGS += -Wwrite-strings
CPPFLAGS += $(INCLUDE)

LFLAGS := -fuse-linker-plugin
LFLAGS += -Wl,--gc-sections
LFLAGS += -lm
LFLAGS += -Wl,-Map=$(MAPFILE).map
LFLAGS += -flto

#=======  Build Tools   ===========================================================
CC := avr-gcc
CPP := avr-g++
OBJCOPY := avr-objcopy
AVRDUDE := avrdude
REMOVE := rm -f
SIZE := avr-size 


#to do all, there is a prerequisites the hex file, if the hex file doesn't exist, make will
#look for a rule to build the hex file
all: $(FOLDER) $(TARGET).hex

# Rule to build the hex file, requires the elf file to exist as a prerequisite, if the elf doesn't exit
# look for a rule to build it
%.hex: %.elf
	@echo '****************** Generating $@ file  *********************'
	@$(OBJCOPY) -O ihex -j .text -j .data $^ $@
	@$(SIZE) --format=avr --mcu=$(MCU) $^
# Rule to build the elf file, requires all the objects files to exist and up to date, otherwise look for
# a rule to build the object files
$(TARGET).elf: $(AOBJS) $(CPPS)
	@echo '********************  Linking $(AOBJS) **********************'
	@$(CPP) $(LFLAGS) $(FLAGS) -o $(TARGET).elf $(AOBJS)
	

# Rule to build objects from cpp files
%.o:%.cpp %.s
	@echo '**************  Building $< *****************************'
	@$(CPP) -MD $(FLAGS) $(CPPFLAGS) -c $< -o $@
%.s:%.cpp
	@$(CPP) $(FLAGS) $(CPPFLAGS) -S $< -o $*.s


program: all
	$(AVRDUDE) $(AVRDUDE_FLAGS) -P$(COMPORT) -b115200 -D -U flash:w:$(TARGET).hex:i
	
fuse:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0xe4:m -U hfuse:w:0xd9:m

clean:
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(AOBJS)
	$(REMOVE) $(CSRCS:.c=.s) $(SRCS:.cpp=.s)
	$(REMOVE) $(CSRCS:.c=.d) $(SRCS:.cpp=.d)
	
$(FOLDER):
	@if not exist "$(FOLDER)" mkdir $(FOLDER) && echo Folder $(FOLDER) created.

	
-include $(subst .c,.d,$(CSRCS))
-include $(subst .cpp,.d,$(SRCS))
