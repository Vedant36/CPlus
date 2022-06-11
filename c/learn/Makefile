# Files from me learning C
CC = gcc
ERROR = -Wall -Wextra -Werror -pedantic -Wno-unused-parameter
LDFLAGS =
# -fsanitize=address prevents valgrind from working
CFLAGS = -Og -std=c99 -ggdb -fsanitize=address -fsanitize=undefined -fanalyzer
IGNORE = sequence-point ternary-associativity
FILES = classes classes-typedef code-profiling errorhandling garbage-collector \
		generators recursive-function-main simple-fork-pipe-dup \
		type-agnostic-function understanding-contiguous-structs vsort

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

vsort: vsort.c code-profiling.c
	${CC} ${CFLAGS} -o vsort vsort.c

errorhandling: errorhandling.c
	${CC} -o errorhandling errorhandling.c

clean:
	rm -f main ${FILES}

# working examples
all: ${FILES}

.PHONY: all noerr run clean
