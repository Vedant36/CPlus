# C
CC ?= gcc
ERROR ?= -Wall -Wextra -Werror -pedantic -ggdb
STD ?= c99
CFLAGS ?= -O3
LDFLAGS ?= -lm

# main file, just for testing new concepts
lambda: lambda.c lambda.h
	${CC} ${CFLAGS} ${LDFLAGS} ${ERROR} -std=${STD} -o lambda lambda.c

bad:
	${CC} ${CFLAGS} ${LDFLAGS} -std=${STD} -o lambda lambda.c

run:
	./lambda

clean:
	rm -f lambda

.PHONY: all bad run clean
