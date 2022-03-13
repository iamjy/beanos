ARCH = armv7-a
MCPU = cortex-a9

TARGET = exynos4412
ARM_ARCH = cortexAR

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-gcc
OC = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump

OUTDIR=./out

LINKER_SCRIPT = ./build/exynos4412/ram.ld
MAP_FILE = $(OUTDIR)/rtos.map
SYM_FILE = $(OUTDIR)/rtos.sym

ASM_SRCS = $(wildcard ./boot/$(TARGET)/*.S)
ASM_OBJS = $(patsubst ./boot/$(TARGET)/%.S, $(OUTDIR)/%.os, $(ASM_SRCS))

VPATH = boot/$(TARGET)  \
        hal/$(TARGET)	\
        lib				\
	    lib/$(ARM_ARCH) \
        kernel

C_SRCS  = $(notdir $(wildcard ./boot/$(TARGET)/*.c))
C_SRCS += $(notdir $(wildcard ./hal/$(TARGET)/*.c))
C_SRCS += $(notdir $(wildcard ./lib/*.c))
C_SRCS += $(notdir $(wildcard ./lib/$(ARM_ARCH)/*.c))
C_SRCS += $(notdir $(wildcard ./kernel/*.c))
C_OBJS = $(patsubst %.c, $(OUTDIR)/%.o, $(C_SRCS))

INC_DIRS  = -I boot/$(TARGET)	\
            -I include 			\
            -I hal	   			\
            -I hal/$(TARGET)	\
            -I lib				\
            -I lib/$(ARM_ARCH)	\
            -I kernel

CFLAGS = -c -g -std=c11 -mthumb-interwork -march=armv7-a -mtune=cortex-a9 -mfloat-abi=soft -mfpu=vfpv3-d16
#CFLAGS = -c -g -std=c11 -mthumb-interwork -march=armv7-a -mtune=cortex-a9 -mfloat-abi=soft -mfpu=vfpv3-d16 --save-temps
#CFLAGS = -c -g -std=c1x -mthumb-interwork
#CFLAGS = -c -g -std=c11 -mthumb-interwork

LDFLAGS = -nostartfiles -nostdlib -nodefaultlibs -static -lgcc -march=armv7-a -mtune=cortex-a9 -mfloat-abi=soft -mfpu=vfpv3-d16
#LDFLAGS = -nostartfiles -nostdlib -nodefaultlibs -static -lgcc -march=armv7-a -mtune=cortex-a9 -mfloat-abi=soft -mfpu=vfpv3-d16 --save-temps
#LDFLAGS = -nostartfiles -nostdlib -nodefaultlibs -static -lgcc -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=soft -mfpu=vfpv3-d16
#LDFLAGS = -nostartfiles -nostdlib -nodefaultlibs -static -lgcc

rtos = $(OUTDIR)/rtos.elf
rtos_bin = $(OUTDIR)/rtos.bin

.PHONY: all clean

all: $(rtos)

clean:
	@rm -fr $(OUTDIR)
	
$(rtos): $(ASM_OBJS) $(C_OBJS) $(LINKER_SCRIPT)
	$(LD) -n -T $(LINKER_SCRIPT) -o $(rtos) $(ASM_OBJS) $(C_OBJS) -Wl,-Map=$(MAP_FILE) $(LDFLAGS)
#	$(LD) -n -T $(LINKER_SCRIPT) -o $(rtos) $(ASM_OBJS) $(C_OBJS) -Wl,--build-id=none,-Map=$(MAP_FILE) $(LDFLAGS)
	$(OD) -t $(rtos) > $(SYM_FILE)
	$(OC) -O binary $(rtos) $(rtos_bin)
	
$(OUTDIR)/%.os: %.S
	mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) -marm $(INC_DIRS) $(CFLAGS) -o $@ $<
	
$(OUTDIR)/%.o: %.c
	mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) -marm $(INC_DIRS) $(CFLAGS) -o $@ $<
	
