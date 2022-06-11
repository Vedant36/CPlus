# personal projects for practice
# sorted in the order of developement
CC = gcc
DEBUG = -ggdb -Og -fsanitize=address -fsanitize=undefined -fanalyzer
CFLAGS = ${DEBUG} -Wall -Wextra -Werror -std=c99 -pedantic
FILES = prime rpn testing testing-tester shell pascaltriangle

all: ${FILES}

test: testing prime rpn
	./testing all

# `factor` clone
prime: prime.c
	${CC} ${CFLAGS} -lm -o prime prime.c

# `dc` clone (45th on the pro/g/ramming challenges)
rpn: rpn.c
	${CC} ${CFLAGS} -lm -o rpn rpn.c

# for testing all the others
testing: testing.c
	${CC} ${CFLAGS} -o testing testing.c

testing-tester: testing-tester.c
	${CC} ${CFLAGS} -o testing-tester testing-tester.c

shell: shell.c
	${CC} ${CFLAGS} -o $@ $^

pascaltriangle: pascaltriangle.c
	${CC} ${CFLAGS} -o $@ $^

# 50th on the pro/g/ramming challenges
pi: pi.c
	${CC} ${CFLAGS} -o pi pi.c

clean:
	rm -f ${FILES}

.PHONY: all clean test
