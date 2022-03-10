# C
CC ?= gcc
ERROR ?= -Wall -Wextra -Werror -pedantic -ggdb
STD ?= -std=c99
LDFLAGS ?= -lm
CFLAGS ?= -O3 ${STD}
FILES = classes classes-typedef generators type-agnostic-function simple-fork-pipe-dup garbage-collector

# main file, just for testing new concepts
main: main.c
	${CC} ${CFLAGS} ${LDFLAGS} ${ERROR} -o main main.c

bad:
	${CC} ${CFLAGS} ${LDFLAGS} -o main main.c

run:
	./main

# this code needs support for anonymous unions, which is only available in >=c11
type-agnostic-function: type-agnostic-function.c
	${CC} ${CFLAGS} -std=c11 -o type-agnostic-function type-agnostic-function.c

clean:
	rm -f main ${FILES}

# working examples
all: ${FILES}

.PHONY: all bad run clean
