CC = gcc
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS = -Wall -Wextra `sdl2-config --cflags`
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_test -lSDL2main -lSDL2_gfx -lSDL2_ttf `sdl2-config --libs` -lm
EXEC = circles

$(EXEC): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $(EXEC)

%.o: %.c
	$(CC) -g $< $(CFLAGS) -c -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC)
