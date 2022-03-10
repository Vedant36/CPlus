#include <stdio.h>
#include <stdlib.h>	// for malloc
#include <string.h>	// strcpy
#include <errno.h>	// error reporting

// in this demo, i haven't typedef them for readability but one can choose to
// do that as much as they like
union gc_val {
	FILE *fd;
	char *string;
};
enum gc_type {
	C_NULL,
	C_FCLOSE,
	C_FREE,
};
struct gc_obj {
	enum gc_type type;
	union gc_val obj;
};


#define GC_SIZE 64
struct gc_obj gc_list[GC_SIZE];
size_t gc_size = 0;

void
gc_allocate (enum gc_type type, union gc_val obj)
{
	struct gc_obj tmp = {
		.type = type,
		.obj = obj
	};
	gc_list[gc_size++] = tmp;
}

// no deallocator as we can just manually deallocate resources ourselves

void
gc_cleanup ()
{
	for (size_t i = 0; i < gc_size; i++) {
		// No need to worry if the file is closed or the memory is
		// deallocated, setting the value to NULL handles that
		// We need to do this because according to the C standard,
		// refreeing and reclosing files is undefined behaviour
		switch (gc_list[i].type) {
		case C_FCLOSE:
			fclose(gc_list[i].obj.fd);
			gc_list[i].obj.fd = NULL;
			break;
		case C_FREE:
			free(gc_list[i].obj.string);
			gc_list[i].obj.string = NULL;
			break;
		}
	}
}

int
main (int argc, char **argv)
{
	union gc_val impfile = { .fd = fopen("main.c", "r") };
	gc_allocate(C_FCLOSE, impfile);
	union gc_val bankdetails = { .string = malloc(64 * sizeof(char)) };
	strcpy(bankdetails.string, "i hav lots of cash money. source: trust me\n");
	gc_allocate(C_FREE, bankdetails);
	// Imagine you need to exit because of some error before returning to
	// the end of the function where you would normally do cleanup
	// This cleanup will work even when called from other scopes/functions
	gc_cleanup();

	return 0;
}
