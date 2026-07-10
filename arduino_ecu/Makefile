# Arduino ECU Makefile (ATmega328P)

.PHONY: all clean test

TARGET := hermes_av

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
ELF_DIR := $(BUILD_DIR)/elf
HEX_DIR := $(BUILD_DIR)/hex
MAP_DIR := $(BUILD_DIR)/map

MCU := atmega328p
F_CPU := 16000000UL

CC := avr-gcc
OBJCOPY := avr-objcopy
SIZE := avr-size

CFLAGS := \
-mmcu=$(MCU) \
-DF_CPU=$(F_CPU) \
-std=c11 \
-Os \
-Wall \
-Wextra \
-MMD \
-MP \
-Iapp \
-Imcal/gpio

LDFLAGS := -mmcu=$(MCU)

SRCS := $(shell find app mcal -name "*.c")

OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

all: $(HEX_DIR)/$(TARGET).hex

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF_DIR)/$(TARGET).elf: $(OBJS)
	@mkdir -p $(ELF_DIR)
	@mkdir -p $(MAP_DIR)
	$(CC) $(LDFLAGS) $^ -o $@ -Wl,-Map,$(MAP_DIR)/$(TARGET).map
	$(SIZE) $@

$(HEX_DIR)/$(TARGET).hex: $(ELF_DIR)/$(TARGET).elf
	@mkdir -p $(HEX_DIR)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

clean:
	rm -rf $(BUILD_DIR)

test:
	@echo "GPIO SWCT will be added here."

-include $(DEPS)