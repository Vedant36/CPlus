###############################################################################
#
# Problems from the site: https://projecteuler.net
# The ones not here were either solved mathematically or using another tool
#
###############################################################################

CC = cc
CFLAGS ?= -Wall -Wextra -Werror -O3 -std=c99 -pedantic -ggdb
LDFLAGS ?= -lm
SRC = main.c util.c
HDR = $(SRC:.c=.h)

euler: $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o euler $(SRC)

clean:
	rm -f euler

run: euler
	./euler
