# Lambda function library
CC ?= gcc
ERROR ?= -Wall -Wextra -Werror -pedantic -ggdb
STD ?= c99
CFLAGS ?= -O3
LDFLAGS ?= -lm

lambda: lambda.c lambda.h
	${CC} ${CFLAGS} ${LDFLAGS} ${ERROR} -std=${STD} -o lambda lambda.c

noerr:
	${CC} ${CFLAGS} ${LDFLAGS} -std=${STD} -o lambda lambda.c

run: lambda
	./lambda test.lb

clean:
	rm -f lambda

.PHONY: all noerr run clean
