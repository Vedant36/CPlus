
struct layer {
	size_t size;
	float *weights;
	struct layer *next;
};

void usage(char *progname);

