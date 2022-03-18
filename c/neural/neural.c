#include <stdio.h>
#include <stdlib.h>	    // atoi
/* #include <errno.h> */
#include <string.h>
#include "neural.h"
#include "util.h"
// TODO: allocate input as a 1-dimensional array to take advantage of cache localization

/*
 * Input node  : float[len][s_in]
 * Output node : int out[len][s_out]
 * Neural net  : s_int -> layer( -> layer)* -> s_out
 * Arguments   : $0 filename num_inputs out_count
 */
int main(int argc, char **argv)
{
	if (argc < 4) {
		usage(argv[0]);
		return 1;
	}
	size_t s_in = atoi(argv[2]), s_out = atoi(argv[3]);
	int line_offset = argc >= 5 ? atoi(argv[4]) : 0;
	char *buf = NULL;
	float *in = NULL;
	float *out = NULL;
	size_t num_lines = util_setup(argv[1], &buf, line_offset, &in, &out, s_in, s_out);

	util_show(&in, &out, num_lines);

	util_free(&in, &out);
	return 0;
}

void usage(char *progname)
{
	fprintf(stderr, "Usage: %s FILENAME num_inputs out_count [offset]\n",
			progname);
}

