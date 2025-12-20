CC = gcc
CFLAGS = -O2 -Wall -Wextra -Werror `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image

SRC = src/main.c src/app.c src/image.c
OUT = iris

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)
