PROJECT_NAME := wolfcrypt_s210_pca10028

export OUTPUT_FILENAME
#MAKEFILE_NAME := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE_NAME := $(MAKEFILE_LIST)
MAKEFILE_DIR := $(dir $(MAKEFILE_NAME) ) 

TEMPLATE_PATH = ../../components/toolchain/gcc
SOFTDEVICE_PATH = ../../components/softdevice
ifeq ($(OS),Windows_NT)
include $(TEMPLATE_PATH)/Makefile.windows
else
include $(TEMPLATE_PATH)/Makefile.posix
endif

MK := mkdir
RM := rm -rf
MV := mv

#echo suspend
ifeq ("$(VERBOSE)","1")
NO_ECHO := 
else
NO_ECHO := @
endif

# Toolchain commands
CC              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gcc'
AS              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-as'
AR              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ar' -r
LD              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ld'
NM              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-nm'
OBJDUMP         := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objdump'
OBJCOPY         := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objcopy'
SIZE            := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-size'

#function for removing duplicates in a list
remduplicates = $(strip $(if $1,$(firstword $1) $(call remduplicates,$(filter-out $(firstword $1),$1))))

#source common to all targets
C_SOURCE_FILES = $(abspath main.c)
C_SOURCE_FILES += $(abspath ../bsp/bsp.c)
C_SOURCE_FILES += $(abspath ../../components/toolchain/system_nrf51.c)
C_SOURCE_FILES += $(abspath ../../components/libraries/util/app_error.c)
C_SOURCE_FILES += $(abspath ../../components/libraries/fifo/app_fifo.c)
C_SOURCE_FILES += $(abspath ../../components/libraries/timer/app_timer.c)
C_SOURCE_FILES += $(abspath ../../components/libraries/util/app_util_platform.c)
C_SOURCE_FILES += $(abspath ../../components/libraries/button/app_button.c)
C_SOURCE_FILES += $(abspath ../../components/libraries/util/nrf_assert.c)
C_SOURCE_FILES += $(abspath ../../components/libraries/uart/retarget.c)
C_SOURCE_FILES += $(abspath ../../components/libraries/uart/app_uart_fifo.c)
C_SOURCE_FILES += $(abspath ../../components/drivers_nrf/common/nrf_drv_common.c)
C_SOURCE_FILES += $(abspath ../../components/drivers_nrf/delay/nrf_delay.c)
C_SOURCE_FILES += $(abspath ../../components/drivers_nrf/uart/nrf_drv_uart.c)
C_SOURCE_FILES += $(abspath ../../components/drivers_nrf/rng/nrf_drv_rng.c)
C_SOURCE_FILES += $(abspath ../../components/drivers_nrf/rtc/nrf_drv_rtc.c)
C_SOURCE_FILES += $(abspath ../../components/drivers_nrf/clock/nrf_drv_clock.c)
C_SOURCE_FILES += $(abspath ../../components/drivers_nrf/hal/nrf_ecb.c)
C_SOURCE_FILES += $(abspath ../../components/softdevice/common/softdevice_handler/softdevice_handler.c)

#assembly files common to all targets
ASM_SOURCE_FILES  = $(abspath ../../components/toolchain/gcc/gcc_startup_nrf51.s)

#includes common to all targets
INC_PATHS = -I$(abspath ./)
INC_PATHS += -I$(abspath ../bsp)
INC_PATHS += -I$(abspath ../../components/libraries/util)
INC_PATHS += -I$(abspath ../../components/libraries/uart)
INC_PATHS += -I$(abspath ../../components/libraries/timer)
INC_PATHS += -I$(abspath ../../components/libraries/button)
INC_PATHS += -I$(abspath ../../components/libraries/fifo)
INC_PATHS += -I$(abspath ../../components/toolchain/gcc)
INC_PATHS += -I$(abspath ../../components/toolchain)
INC_PATHS += -I$(abspath ../../components/device)
INC_PATHS += -I$(abspath ../../components/drivers_nrf/common)
INC_PATHS += -I$(abspath ../../components/drivers_nrf/config)
INC_PATHS += -I$(abspath ../../components/drivers_nrf/gpiote)
INC_PATHS += -I$(abspath ../../components/drivers_nrf/uart)
INC_PATHS += -I$(abspath ../../components/drivers_nrf/delay)
INC_PATHS += -I$(abspath ../../components/drivers_nrf/hal)
INC_PATHS += -I$(abspath ../../components/drivers_nrf/rng)
INC_PATHS += -I$(abspath ../../components/drivers_nrf/rtc)
INC_PATHS += -I$(abspath ../../components/drivers_nrf/clock)
INC_PATHS += -I$(abspath ../../components/ant/ant_stack_config)
INC_PATHS += -I$(abspath ../../components/ant/ant_stack_config/config)
INC_PATHS += -I$(abspath ../../components/ant/ant_channel_config)
INC_PATHS += -I$(abspath ../../components/softdevice/s210/headers)
INC_PATHS += -I$(abspath ../../components/softdevice/common/softdevice_handler)

OBJECT_DIRECTORY = _build
LISTING_DIRECTORY = _build
OUTPUT_BINARY_DIRECTORY = _build
OUTPUT_FILENAME = firmware

# Sorting removes duplicates
BUILD_DIRECTORIES := $(sort $(OBJECT_DIRECTORY) $(OUTPUT_BINARY_DIRECTORY) $(LISTING_DIRECTORY) )

#flags common to all targets
CFLAGS  = -DS210
CFLAGS += -DBOARD_PCA10028
#CFLAGS += -DSOFTDEVICE_PRESENT
CFLAGS += -DNRF51
CFLAGS += -DANT_STACK_SUPPORT_REQD
CFLAGS += -DSWI_DISABLE0
CFLAGS += -DCPU_LOAD_TRACE
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs --std=gnu99
CFLAGS += -Wall -Werror
CFLAGS += -mfloat-abi=soft
#optimization level
CFLAGS += -Os
#debugging symbols
CFLAGS += -g
# keep every function in separate section. This will allow linker to dump unused functions
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums

# keep every function in separate section. This will allow linker to dump unused functions
LDFLAGS += -Xlinker -Map=$(LISTING_DIRECTORY)/$(OUTPUT_FILENAME).map
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys

# Assembler flags
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DS210
ASMFLAGS += -DBOARD_PCA10028
#ASMFLAGS += -DSOFTDEVICE_PRESENT
ASMFLAGS += -DNRF51
ASMFLAGS += -DANT_STACK_SUPPORT_REQD
ASMFLAGS += -DSWI_DISABLE0
ASMFLAGS += -DCPU_LOAD_TRACE

## ----------------------------------------------------------------------------- ##
## wolfSSL ##
## ----------------------------------------------------------------------------- ##
#wolfSSL source files
# core
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/random.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/logging.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/memory.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/wc_encrypt.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/wc_port.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/error.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/signature.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/hash.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/asn.c)
# crypto
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/aes.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/sha256.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/sha512.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/curve25519.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/ed25519.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/ecc.c)
# math libraries
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/tfm.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/integer.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/wolfmath.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/fe_low_mem.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/ge_low_mem.c)
# port
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/port/nrf51.c)
#wolfSSL includes
INC_PATHS += -I$(abspath ../../external/wolfssl)
#wolfSSL preprocessor (use the user_settings.h)
CFLAGS += -DWOLFSSL_USER_SETTINGS

#wolfTest
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/test/test.c)
#wolfBenchmark
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/benchmark/benchmark.c)
## ----------------------------------------------------------------------------- ##

LINKER_SCRIPT=wolfcrypt_gcc_nrf51.ld


#default target - first one defined
default: all

#building all targets
all:
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e wolfcrypt_test
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e wolfcrypt_bench

#target for printing all targets
help:
	@echo following targets are available:
	@echo 	wolfcrypt_test
	@echo 	wolfcrypt_bench
	@echo 	flash TARGET=wolfcrypt_test
	@echo 	flash.segger TARGET=wolfcrypt_test
	@echo 	flash_softdevice
	@echo 	flash_softdevice.segger
	@echo 	run-debug.segger

C_SOURCE_FILE_NAMES = $(notdir $(C_SOURCE_FILES))
C_PATHS = $(call remduplicates, $(dir $(C_SOURCE_FILES) ) )
C_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(C_SOURCE_FILE_NAMES:.c=.o) )

ASM_SOURCE_FILE_NAMES = $(notdir $(ASM_SOURCE_FILES))
ASM_PATHS = $(call remduplicates, $(dir $(ASM_SOURCE_FILES) ))
ASM_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(ASM_SOURCE_FILE_NAMES:.s=.o) )

vpath %.c $(C_PATHS)
vpath %.s $(ASM_PATHS)

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)


.PHONY: wolfcrypt_test
wolfcrypt_test: CFLAGS += -DNO_CRYPT_BENCHMARK
wolfcrypt_test: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e cleanobj TARGET=$@
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e finalize TARGET=$@

.PHONY: wolfcrypt_bench
wolfcrypt_bench: CFLAGS += -DNO_CRYPT_TEST
wolfcrypt_bench: LDFLAGS += -u _printf_float
wolfcrypt_bench: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e cleanobj TARGET=$@
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e finalize TARGET=$@


## Create build directories
$(BUILD_DIRECTORIES):
	echo $(MAKEFILE_NAME)
	$(MK) $@

# Create objects from C SRC files
$(OBJECT_DIRECTORY)/%.o: %.c
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC_PATHS) -c -o $@ $<

# Assemble files
$(OBJECT_DIRECTORY)/%.o: %.s
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(ASMFLAGS) $(INC_PATHS) -c -o $@ $<


# Link
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out


## Create binary .bin file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

finalize: genbin genhex movetofinal echosize

genbin:
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
genhex: 
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

getjlinkfile:
	
echosize:
	-@echo ''
	$(NO_ECHO)$(SIZE) $(OUTPUT_BINARY_DIRECTORY)_$(TARGET)/$(OUTPUT_FILENAME).out
	-@echo ''

clean:
	$(RM) $(BUILD_DIRECTORIES)
	$(RM) $(BUILD_DIRECTORIES)_wolfcrypt_test
	$(RM) $(BUILD_DIRECTORIES)_wolfcrypt_bench

cleanobj:
	$(RM) $(BUILD_DIRECTORIES)_$(TARGET)/*.o

movetofinal:
	$(RM) $(OUTPUT_BINARY_DIRECTORY)_$(TARGET)
	$(MV) $(OUTPUT_BINARY_DIRECTORY) $(OUTPUT_BINARY_DIRECTORY)_$(TARGET)

flash:
	@echo Flashing: $(OUTPUT_BINARY_DIRECTORY)_$(TARGET)/$(OUTPUT_FILENAME).hex
	nrfjprog --program $(OUTPUT_BINARY_DIRECTORY)_$(TARGET)/$(OUTPUT_FILENAME).hex -f nrf51  --sectorerase
	nrfjprog --reset

## Flash softdevice
flash_softdevice:
	@echo Flashing: s210_nrf51422_5.0.0_softdevice.hex
	nrfjprog --program $(SOFTDEVICE_PATH)/s210/hex/s210_nrf51422_5.0.0_softdevice.hex -f nrf51 --chiperase
	nrfjprog --reset


## Segger J-Link
flash.segger:
	@echo Preparing: flash.jlink
	printf "loadbin $(OUTPUT_BINARY_DIRECTORY)_$(TARGET)/$(OUTPUT_FILENAME).bin, $(FLASH_START_ADDR)\nr\ng\nexit\n" > $(OUTPUT_BINARY_DIRECTORY)_$(TARGET)/flash.jlink
	$(JLINK) $(OUTPUT_BINARY_DIRECTORY)_$(TARGET)/flash.jlink

flash_softdevice.segger:
	@echo Preparing: flash softdevice.jlink
	$(OBJCOPY) -I ihex -O binary $(SOFTDEVICE_PATH)/s210/hex/s210_nrf51422_5.0.0_softdevice.hex $(SOFTDEVICE_PATH)/s210/hex/s210_nrf51422_5.0.0_softdevice.bin
	printf "loadbin $(SOFTDEVICE_PATH)/s210/hex/s210_nrf51422_5.0.0_softdevice.bin, 0\nr\ng\nexit\n" > $(SOFTDEVICE_PATH)/s210/flash-soft.jlink
	$(JLINK) $(SOFTDEVICE_PATH)/s210/flash-soft.jlink

run-debug.segger:
	@echo Preparing: GDB run debug
	$(JLINKD_GDB) $(JLINK_OPTS) $(JLINK_GDB_OPTS) -port $(GDB_PORT_NUMBER)
