# Example Makefile that can be copied to new projects
CC ?= gcc
ERROR ?= -Wall -Wextra -Werror -pedantic -ggdb
STD ?= -std=c99
CFLAGS ?= -O3 ${STD}
LDFLAGS ?= -lSDL2 -lSDL2_image
SRC = main.c
HEADERS = util.h

run: sdl2
	./sdl2

sdl2: ${SRC} ${HEADERS}
	${CC} ${CFLAGS} ${LDFLAGS} ${ERROR} -o sdl2 ${SRC}

noerr:
	${CC} ${CFLAGS} ${LDFLAGS} -o sdl2 ${SRC}

clean:
	rm -f sdl2

.PHONY: noerr run clean
