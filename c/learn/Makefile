# C
CC ?= gcc
ERROR ?= -Wall -Wextra -Werror -pedantic
STD ?= c99
CFLAGS ?= -O3

# main file, just for testing new concepts
main: main.c
	${CC} ${CFLAGS} ${ERROR} -std=${STD} -o main main.c

bad:
	${CC} ${CFLAGS} -std=${STD} -o main main.c

run:
	./main

# this code needs support for anonymous unions, which is only available in >=c11
type-agnostic-function: type-agnostic-function.c
	${CC} ${CFLAGS} -std=c11 -o type-agnostic-function type-agnostic-function.c

clean:
	rm -f main classes classes-typedef generators type-agnostic-function

# working examples
all: classes classes-typedef generators type-agnostic-function

.PHONY: all bad run clean
