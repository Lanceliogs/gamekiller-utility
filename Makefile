CC      := gcc
WINDRES := windres

TARGET := build/gamekiller.exe

SRC_DIR := src
RES_DIR := resources
BUILD_DIR := build

CPPFLAGS := -DWIN32_LEAN_AND_MEAN
CFLAGS   := -Wall -Wextra -O2 -std=c11
LDFLAGS  := -static
LDLIBS   := -lshell32 -luser32

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

RESOURCE := $(BUILD_DIR)/resource.o

all: $(TARGET)

$(TARGET): $(OBJECTS) $(RESOURCE)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(RESOURCE): $(RES_DIR)/resource.rc $(RES_DIR)/gamekiller.ico
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(WINDRES) $< -O coff -o $@

clean:
	del /Q "$(BUILD_DIR)\*.o" "$(TARGET)" 2>NUL || exit 0

.PHONY: all clean