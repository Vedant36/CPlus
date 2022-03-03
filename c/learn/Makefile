# C
CC=gcc

main: main.c
	${CC} -Wall -Wextra -Werror -O3 -std=c99 -pedantic main.c -o main

bad:
	${CC} -O3 -std=c99 main.c -o main

run:
	./main

clean:
	rm -f main
