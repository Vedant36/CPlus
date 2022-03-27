#ifndef FILE_UTIL_SEEN
#define FILE_UTIL_SEEN

size_t util_setup(char *progname, int line_offset,
		float **in, float **out, size_t s_in, size_t s_out);
void util_show(const float *in, const float *out,
		size_t s_in, size_t s_out, size_t num_lines);
void util_free(float **in, float **out);

#endif
