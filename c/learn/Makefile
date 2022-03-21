# Files from me learning C
CC ?= gcc
ERROR ?= -Wall -Wextra -Werror -pedantic -ggdb -fsanitize=address
STD ?= -std=c99
LDFLAGS ?=
CFLAGS ?= -O3 ${STD}
FILES = classes classes-typedef generators type-agnostic-function \
		simple-fork-pipe-dup garbage-collector code-profiling

# main file, just for testing new concepts
main: main.c
	${CC} ${CFLAGS} -lm ${ERROR} -o main main.c

noerr: main.c
	${CC} ${CFLAGS} -lm -o main main.c

run: main
	./main

# this code needs anonymous unions, which are only available in >=c11
type-agnostic-function: type-agnostic-function.c
	${CC} ${CFLAGS} -std=c11 -o type-agnostic-function type-agnostic-function.c

clean:
	rm -f main ${FILES}

# working examples
all: ${FILES}

.PHONY: all noerr run clean
