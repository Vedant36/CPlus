
#define BF_CELL_COUNT 65536
#define CELL_TYPE unsigned int
#define _debug(...)				\
	do {					\
		fprintf(stderr, __VA_ARGS__);	\
		fflush(stderr); 		\
	} while(0)
#if 0
#define debug(...) _debug(__VA_ARGS__)
#else
#define debug(...)
#endif
#if 0
#define logger(...) _debug(__VA_ARGS__)
#else
#define logger(...)
#endif
void interpret(char *buf, size_t size);
