CC      := gcc
WINDRES := windres

TARGET := build/gamekiller.exe

SRC_DIR   := src
RES_DIR   := resources
BUILD_DIR := build

CPPFLAGS := -DWIN32_LEAN_AND_MEAN

CFLAGS_COMMON := -Wall -Wextra -std=c11
CFLAGS_DEBUG  := $(CFLAGS_COMMON) -O0 -g
CFLAGS_RELEASE := $(CFLAGS_COMMON) -O2 -DNDEBUG

LDFLAGS_COMMON  := -static
LDFLAGS_DEBUG   := $(LDFLAGS_COMMON)
LDFLAGS_RELEASE := $(LDFLAGS_COMMON) -mwindows -s

LDLIBS  := -lshell32 -luser32 -lwinmm -mwindows

SOURCES := $(wildcard $(SRC_DIR)/*.c)

DEBUG_DIR   := $(BUILD_DIR)/debug
RELEASE_DIR := $(BUILD_DIR)/release

DEBUG_OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(DEBUG_DIR)/%.o,$(SOURCES))
RELEASE_OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(RELEASE_DIR)/%.o,$(SOURCES))

DEBUG_RESOURCE := $(DEBUG_DIR)/resource.o
RELEASE_RESOURCE := $(RELEASE_DIR)/resource.o

DEBUG_TARGET := $(DEBUG_DIR)/gamekiller.exe
RELEASE_TARGET := $(RELEASE_DIR)/gamekiller.exe

.PHONY: all debug release clean

all: debug

debug: $(DEBUG_TARGET)

release: $(RELEASE_TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJECTS) $(DEBUG_RESOURCE)
	@mkdir -p "$(DEBUG_DIR)"
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(RELEASE_TARGET): $(RELEASE_OBJECTS) $(RELEASE_RESOURCE)
	@mkdir -p "$(RELEASE_DIR)"
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p "$(DEBUG_DIR)"
	$(CC) $(CPPFLAGS) $(CFLAGS_DEBUG) -c $< -o $@

$(RELEASE_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p "$(RELEASE_DIR)"
	$(CC) $(CPPFLAGS) $(CFLAGS_RELEASE) -c $< -o $@

$(DEBUG_RESOURCE): $(RES_DIR)/resource.rc
	@mkdir -p "$(DEBUG_DIR)"
	$(WINDRES) -Isrc $< -O coff -o $@

$(RELEASE_RESOURCE): $(RES_DIR)/resource.rc
	@mkdir -p "$(RELEASE_DIR)"
	$(WINDRES) -Isrc $< -O coff -o $@

clean:
	rm -rf "$(BUILD_DIR)"