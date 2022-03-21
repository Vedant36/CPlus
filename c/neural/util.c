#include <stdio.h>
#include <stdlib.h>	// strtof
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "neural.h"
#include "util.h"
#define NDEBUG

/* Throwing everything here so that I can focus on the neural net algorithm
 */
size_t util_setup(char *progname, int line_offset,
		float **in, float **out, size_t s_in, size_t s_out)
{
	// combine the below two lines
	char *buf = NULL;
	size_t filesize = slurp_file(progname, &buf, line_offset);
	size_t num_lines = get_num_lines(&buf, filesize);
	printf("Filesize     : %zu\n", filesize);
	printf("No. of lines : %zu\n", num_lines);
	allocate_arrays(&buf, num_lines, filesize, in, out, s_in, s_out);
	return num_lines;
}

void util_show(float **in, float **out, size_t s_in, size_t s_out, size_t num_lines)
{
	size_t i, j;
	for (i = 0; i < num_lines; i++) {
		for (j = 0; j < s_in; j++)
			printf("%.1f,", (*in)[i * s_in + j]);
		printf("\b:");
		for (j = 0; j < s_out; j++)
			printf("%.0f,", (*out)[i * s_out + j]);
		printf("\b \n");
	}
}

size_t slurp_file(char *filename, char **buf, int line_offset)
{
	FILE *fd = fopen(filename, "r");
	if (fd == NULL) {
		perror("fopen");
		exit(errno);
	}
	fseek(fd, 0, SEEK_END);
	size_t filesize = ftell(fd);
	rewind(fd);
	*buf = malloc(filesize);
	assert(fread(*buf, 1, filesize, fd) == filesize);

	size_t i = 0;
	for (i = 0; line_offset > 0 && i < filesize; i++)
		if ((*buf)[i] == '\n')
			line_offset--;
	filesize -= i;
	free(*buf);
	fseek(fd, i, SEEK_SET);
	*buf = malloc(filesize);
	assert(fread(*buf, 1, filesize, fd) == filesize);
	fclose(fd);
	return filesize;
}


size_t get_num_lines(char **buf, size_t filesize)
{
	size_t num_lines = 0;
	size_t i;
	for (i = 0; i < filesize; i++)
		if ((*buf)[i] == '\n')
			num_lines++;
	return num_lines;
}

/*
 * reads a file and converts it to an array of floats for the input and
 * an array of ints for the output
 */
void allocate_arrays(char **buf, size_t num_lines, size_t filesize,
		float **in, float **out, size_t s_in, size_t s_out)
{
	(void) filesize;
	// allocate all the shit
	*in  = malloc(num_lines * s_in * sizeof(*in));
	*out = calloc(num_lines * s_out, sizeof(*out));
	size_t i, j;
	// assumes input is sorted according to output
	char **odict = malloc(s_out * sizeof(char *));
	size_t s_odict = 0;
	for (i = 0; i < s_out; i++) {
		odict[i] = malloc(OUTPUT_STRING_SIZE);
	}

	char* tok = NULL;
	tok = strtok(*buf, ",");
	for (i = 0; i < num_lines; i++) {
		for (j = 0; j < s_in; j++) {
			(*in)[i * s_in + j] = strtof(tok, NULL);
			tok = strtok(NULL, ",\n");
		}
		/* end = strcspn(*buf + start, "\n"); */
		if (s_odict == 0 || strcmp(odict[s_odict - 1], tok) != 0)
			strcpy(odict[s_odict++], tok);
		(*out)[i * s_out + s_odict - 1] = 1;
		tok = strtok(NULL, ",");
	}

	// (F)REEEEEEEEEEEEEEEEEEEEEE
	for (i = 0; i < s_out; i++) {
		free(odict[i]);
	}
	free(odict);
	free(*buf);
}

void util_free(float **in, float **out)
{
	free(*in);
	free(*out);
}
