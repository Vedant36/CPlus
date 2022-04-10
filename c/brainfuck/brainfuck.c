/*
 * use https://github.com/rdebath/Brainfuck/blob/master/bitwidth.b for testing
 * this brainfuck interpreter
 */
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <unistd.h>
/*
 * TODO: use sth like jump tables for `[]` instead of looping to the locations
 */

int main(int argc, char **argv)
{
	if (argc < 2) {
		logger("Give file pls\n");
		return 1;
	} else {
		/* interpret(argv[1], strlen(argv[1])); */
		FILE *fd = fopen(argv[1], "r");
		if (fd == NULL) {
			perror("fopen");
			exit(errno);
		}
		if (fseek(fd, 0, SEEK_END) == -1) {
			perror("fseek");
			exit(errno);
		}
		size_t size = ftell(fd);
		rewind(fd);
		logger("Filesize: %zu\n", size);
		char *buf = malloc(size);

		if (fread(buf, 1, size, fd) == 0) {
			logger("Nothing read!\n");
		} else {
			interpret(buf, size);
		}
		fclose(fd);
		free(buf);
	}
	return 0;
}

/*
 * Two pass compiler
 * First checks for bracket balancing and calculates max loop depth
 * Second actually parses
 * Specs: cell width = 8 bits, cell count = 16 bits
 */
void interpret(char *buf, size_t size)
{
	uint32_t i, j;
	CELL_TYPE cells[BF_CELL_COUNT] = {0};
	uint32_t pos = 0;
	uint32_t count = 0;
	for (i = 0; i < size; i++) {
		logger("%c,%02u,%u: %02x", buf[i], i, pos, cells[0]);
		for (j = 1; j < BF_CELL_COUNT; j++)
			logger(" %02x", cells[j]);
		logger("\n");
		switch (buf[i]) {
		case '.': putchar(cells[pos]);    break;
		case ',': cells[pos] = getchar(); break;
		case '+': cells[pos]++;           break;
		case '-': cells[pos]--;           break;
		case '>': pos++;                  break;
		case '<': pos--;                  break;
		case '[':
			if (cells[pos] == 0) {
				count = 0;
				for (;i < size; i++) {
					if (buf[i] == '[') {
						count++;
					} else if (buf[i] == ']') {
						count--;
						if (count == 0)
							break;
					}
				}
			}
			break;
		case ']':
			if (buf[i] == 0)
				continue;
			count = 0;
			for (;i < size; i--) {
				if (buf[i] == ']') {
					count++;
				} else if (buf[i] == '[') {
					if (count == 1) {
						i--;
						break;
					}
					count--;
				}
			}
			break;
		default: continue;
		}
	}
}
