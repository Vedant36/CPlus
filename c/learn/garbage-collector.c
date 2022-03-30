/*
 * Demo of a possible form of garbage collector in C.
 * Note that we need to also pass the information about how to deallocate the
 * pointer. Here that is done by creating the `gc_type` enumeration.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

enum gc_type {
	GC_NULL,
	GC_FCLOSE,
	GC_FREE,
};

typedef struct {
	enum gc_type type;
	void *ptr;
} gc_obj;

#define GC_SIZE 64
static gc_obj gc_list[GC_SIZE];
static size_t gc_size = 0;

FILE *gc_fopen(const char *restrict pathname, const char *restrict mode);
void *gc_malloc(size_t size);
/*
 * the cleanup funciton can be registered to run when the program
 * exits from anywhere
 */
void gc_cleanup(void);

int main(int argc, char **argv)
{
	/* atexit(gc_cleanup); */
	char *bankdetails = gc_malloc(64 * sizeof(char));
	FILE *impfile = gc_fopen("main.c", "r");

	strcpy(bankdetails, "i hav lots of money. source: trust me");
	printf("The allocated string: `%s`\n", bankdetails);
	char buf[64];
	size_t size = fread(buf, sizeof(char), 64, impfile);
	buf[size - 1] = '\0';
	printf("Printing an important file!\n");
	printf(buf);
	printf("\n");
	gc_cleanup();

	return 0;
}

void *gc_malloc(size_t size)
{
	gc_obj ret = {
		.type = GC_FREE,
		.ptr = malloc(size)
	};
	if (ret.ptr == NULL || size == 0) {
		perror("malloc");
		exit(errno);
	}
	assert(gc_size < GC_SIZE);
	gc_list[gc_size++] = ret;
	return ret.ptr;
}

FILE *gc_fopen(const char *restrict pathname, const char *restrict mode)
{
	gc_obj ret = {
		.type = GC_FCLOSE,
		.ptr = fopen(pathname, mode)
	};
	if (ret.ptr == NULL) {
		perror("fopen");
		exit(errno);
	}
	assert(gc_size < GC_SIZE);
	gc_list[gc_size++] = ret;
	return ret.ptr;
}

void gc_cleanup(void)
{
	for (size_t i = 0; i < gc_size; i++) {
		switch (gc_list[i].type) {
		case GC_FCLOSE:
			printf("Closing file\n");
			fclose(gc_list[i].ptr);
			break;
		case GC_FREE:
			printf("Freeing memory\n");
			free(gc_list[i].ptr);
			break;
		default:
			continue;
		}
		gc_list[i].type = GC_NULL;
	}
}

