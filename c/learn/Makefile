# C
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -std=c99 -pedantic

# main file, just for testing new concepts
main: main.c
	${CC} ${CFLAGS} -o main main.c

bad:
	${CC} -O3 -std=c99 -o main main.c

run:
	./main

clean:
	rm -f main classes classes-typedef generators

# working examples
all: classes classes-typedef generators

.PHONY: all bad run clean
