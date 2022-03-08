###############################################################################
#
# Problems from the site: https://projecteuler.net
# The ones not here were either solved mathematically or using another tool
#
###############################################################################

CC = cc
CFLAGS ?= -Wall -Wextra -Werror -O3 -std=c99 -pedantic -ggdb
LDFLAGS ?= -lm

euler: main.c $(wildcard *.h)
	$(CC) $(CFLAGS) $(LDFLAGS) -o euler main.c

run:
	./euler
