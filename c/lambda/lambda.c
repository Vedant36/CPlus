#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "lambda.h"
#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
	FILE *fd;
	if (argc < 2) {
		fd = stdin;
	} else {
		fd = fopen(argv[1], "r");
		if (fd == NULL) {
			perror("fopen");
			exit(errno);
		}
	}

	char buf[BUFFER_SIZE];
	struct lambda_expression lambda;
	size_t read_c = fread(buf, 1, BUFFER_SIZE, fd);
	buf[read_c] = '\0';
	fclose(fd);
	if (read_c == 0)
		return 1;
	if (parse_lambda(buf, read_c, &lambda) == 0) {
		fprintf(stderr, "Invalid lambda expression!\n");
		exit(1);
	}

	printf(buf);
	printf("L_NULL        = %d\n", L_NULL);
	printf("L_UNDECIDED   = %d\n", L_UNDECIDED);
	printf("L_VARIABLE    = %d\n", L_VARIABLE);
	printf("L_LAMBDA      = %d\n", L_LAMBDA);
	printf("L_DOT         = %d\n", L_DOT);
	printf("L_COMPOSITION = %d\n", L_COMPOSITION);
	printf("L_ATTACH      = %d\n", L_ATTACH);
	printf("L_COUNT       = %d\n", L_COUNT);
	printf("Lambda function: ");
	for (size_t i = 0; i < lambda.size; i++) {
		if (lambda.list[i].type == L_VARIABLE)
			printf("%c:", lambda.list[i].name);
		printf("%d ", lambda.list[i].type);
	}
	printf("$\n");
	return 0;
}

// allocates the parsed lambda function in the buf
// return -1 when unsuccessful
// returns the character when newline is found otherwise
int parse_lambda(char *buf, size_t buf_size, struct lambda_expression *lambda)
{
	lambda->size = 0;

	enum lambda_type bracket_stack[64];
	size_t bracket_size = 0;
	for (size_t i = 0; i < buf_size; i++) {
		switch (buf[i]) {
		case '(':
			if (bracket_stack[bracket_size - 1] == L_UNDECIDED)
				bracket_stack[bracket_size - 1] = L_COMPOSITION;
			bracket_stack[bracket_size++] = L_UNDECIDED;
			break;
		case ')':
			// TODO: fix this(the if should not be needed)
			if (bracket_size > 0)
				lambda->list[lambda->size++].type = bracket_stack[bracket_size--];
			break;
		case '\\':
			lambda->list[lambda->size].type = L_LAMBDA;
			lambda->size++;
			if (bracket_stack[bracket_size - 1] == L_UNDECIDED)
				bracket_stack[bracket_size - 1] = L_ATTACH;
			break;
		case 'f':
		case 'x':
		case 'y':
		case 'z':
			lambda->list[lambda->size].type = L_VARIABLE;
			lambda->list[lambda->size].name = buf[i];
			lambda->size++;
			if (bracket_size > 0) {
				lambda->list[lambda->size].type = bracket_stack[bracket_size--];
				lambda->size++;
			}
			break;
		case ' ':
			bracket_stack[bracket_size++] = L_COMPOSITION;
			break;
		case '.':
			lambda->list[lambda->size].type = L_DOT;
			lambda->size++;
			break;
		case '\n':
		case '\r':
			break;
		}
		printf("%c %zu:", buf[i], bracket_size);
		for (size_t j = 0; j < bracket_size; j++)
			printf("%d,", bracket_stack[j]);
		printf("\n");
	}

	// this is here for debugging only, remove later
	lambda->list[lambda->size].type = L_NULL;
	lambda->size++;
	return bracket_size == 0;
}
