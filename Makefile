CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -std=c11
# Add -mwindows to LDFLAGS to disable console windows
LDFLAGS := 
TARGET  := gamekiller

SRC := src/main.c src/app.c src/proc.c src/hotkey.c src/tray.c

all: $(TARGET).exe

$(TARGET).exe: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

clean:
	del /Q $(TARGET).exe 2>NUL || exit 0
