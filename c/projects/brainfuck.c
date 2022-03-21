#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int fuck_brain(char *buf, size_t size);

int main(int argc, char **argv)
{
	int return_code = 0;
	if (argc < 2) {
		char *buf = malloc(64);
		while (fgets(buf, 64, stdin) != NULL) {
			buf[strcspn(buf, "\n")] = '\0';
			fuck_brain(buf, strlen(buf));
		}
	} else {
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
		printf("Filesize: %zu\n", size);
		char *buf = malloc(size);

		if (fread(buf, 1, size, fd) == 0) {
			return_code = 1;
			fputs("Nothing read!\n", stderr);
		}
		fclose(fd);
		if (!return_code)
			return_code = fuck_brain(buf, size);
		free(buf);
	}
	return return_code;
}

/*
 * Two pass compiler
 * First checks for bracket balancing and calculates max loop depth
 * Second actually parses
 * Specs: cell width = 8 bits, cell count = 16 bits
 */
int fuck_brain(char *buf, size_t size)
{
	int loop_stack_s = 0, max_loop_stack_s = 0;
	size_t i;
	for (i = 0; i < size; i++) {
		switch (buf[i]) {
		case '[': loop_stack_s++; break;
		case ']': loop_stack_s--; break;
		}
		if (loop_stack_s > max_loop_stack_s)
			max_loop_stack_s = loop_stack_s;
	}

	if (loop_stack_s != 0) {
		fputs("Unbalanced parenthesis!\n", stderr);
		return 1;
	}

	unsigned short *loop_stack = calloc(max_loop_stack_s,
			sizeof(unsigned int));
	size_t l_size = 0;

	/* TODO: implement checking for infinite loops */
	unsigned char cells[BF_CELL_COUNT] = {0};
	unsigned short pos = 0;
	int skip = 0;
	for (i = 0; i < size; i++) {
		if (skip) goto skipped;

		switch (buf[i]) {
		case '.': putchar(cells[pos]);    break;
		case ',': cells[pos] = getchar(); break;
		case '+': cells[pos]++;           break;
		case '-': cells[pos]--;           break;
		case '>': pos++;                  break;
		case '<': pos--;                  break;
		case '[':
		case ']':
			break;
		default: continue;
		}

		skipped:
		if (buf[i] == '[') {
			if (cells[pos]) {
				loop_stack[l_size++] = 0;
			} else {
				skip = 1;
				loop_stack[l_size++] = i;
			}
		} else if (buf[i] == ']') {
			if (skip) {
				if (loop_stack[l_size - 1] != 0)
					skip = 0; - 1;
			} else {
				i = loop_stack[l_size - 1] - 1;
			}
			loop_stack[l_size--];
		}
		size_t j;
		fprintf(stderr, "%c%zu|%02x|%02lx: %02x", buf[i], l_size,
				loop_stack[l_size - 1], i, cells[0]);
		for (j = 1; j < BF_CELL_COUNT; j++)
			fprintf(stderr, " %02x", cells[j]);
		fprintf(stderr, "\n");
	}

	free(loop_stack);
	return 0;
}
