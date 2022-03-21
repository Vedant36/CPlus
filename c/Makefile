# Example Makefile that can be copied to new projects
CC ?= gcc
ERROR ?= -Wall -Wextra -Werror -pedantic -ggdb
STD ?= -std=c99
CFLAGS ?= -O3 ${STD}
LDFLAGS ?= -lm

name: name.c
	${CC} ${CFLAGS} ${LDFLAGS} ${ERROR} -o name name.c

noerr:
	${CC} ${CFLAGS} ${LDFLAGS} -o name name.c

run: name
	./name

clean:
	rm -f name *.o

.PHONY: noerr run clean
