#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define LAMBDA_IMPLEMENTATION
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

