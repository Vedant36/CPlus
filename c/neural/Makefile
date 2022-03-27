# Neural network to train on the neural dataset
CC = gcc
ERROR = -Wall -Wextra -Werror -pedantic
CFLAGS = -Og -ggdb -std=c99
LDFLAGS = -lm
SRC = neural.c util.c

neural: ${SRC}
	${CC} ${CFLAGS} ${LDFLAGS} ${ERROR} -o neural ${SRC}

noerr:
	${CC} ${CFLAGS} ${LDFLAGS} -o neural ${SRC}

run: neural
	./neural iris.csv 4 3 1

run2: neural
	./neural seeds_dataset.csv 7 3

clean:
	rm -f neural

.PHONY: noerr run clean
