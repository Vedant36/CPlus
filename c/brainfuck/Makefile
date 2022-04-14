# brainfuck compiler
# Note: for some reason, this program becomes much slower with -O1 or lower
CC = gcc
DEBUG = -ggdb -Og -fsanitize=address -fsanitize=undefined -fanalyzer
CFLAGS = ${DEBUG} -Wall -Wextra -Werror -std=c99 -pedantic -O3

brainfuck: brainfuck.c
	${CC} ${CFLAGS} -o brainfuck brainfuck.c

clean:
	rm -f brainfuck
