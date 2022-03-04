# personal projects for practice
# sorted in the order of developement
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -std=c99 -pedantic

all: prime rpn pi

test: testing
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

# 50th on the pro/g/ramming challenges
pi: pi.c
	${CC} ${CFLAGS} -o pi pi.c

clean:
	rm -f prime testing rpn pi

.PHONY: all clean test