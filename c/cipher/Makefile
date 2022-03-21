# Cipher utilities
CC ?= gcc
ERROR ?= -Wall -Wextra -Werror -pedantic -ggdb
STD ?= c99
CFLAGS ?= -O3
LDFLAGS ?= -lm
SRC = cipher.c
OBJ = ${SRC:.c=.o}

cipher: ${SRC}
	${CC} ${CFLAGS} ${LDFLAGS} ${ERROR} -std=${STD} -o main main.c

bad:
	${CC} ${CFLAGS} ${LDFLAGS} -std=${STD} -o main main.c

run: cipher
	./cipher

clean:
	rm -f cipher *.o

.PHONY: bad run clean
