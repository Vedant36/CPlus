
size_t util_setup(char *progname, int line_offset,
		float **in, float **out, size_t s_in, size_t s_out);
void util_show(float **in, float **out, size_t s_in, size_t s_out,
		size_t num_lines);
size_t slurp_file(char *filename, char **buf, int line_offset);
size_t get_num_lines(char **buf, size_t filesize);
#define OUTPUT_STRING_SIZE 64
void allocate_arrays(char **buf, size_t num_lines,
		float **in, float **out, size_t s_in, size_t s_out);
void util_free(float **in, float **out);
