CC=gcc
CFLAGS=-O2 -Wall
SRC=src/screenshot_x11.c
OUT=screenshot

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) -lX11

clean:
	rm -f $(OUT)
