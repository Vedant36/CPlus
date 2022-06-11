#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef unsigned int u8;

/*
1
1 1
1 2 1
1 3 3 1
 */
int main(int argc, char *argv[argc])
{
	u8 count = 10;
	if (argc > 1)
		count = atoi(argv[1]);
	printf("<count:%u>", count);
	u8 *buf = malloc(2 * count);
	assert(buf != NULL);
	memset(buf, 0, count);
	buf[0] = 1;

	printf("1\n");
	for (u8 i = 2; i < count; ++i) {
		printf("<i:%u>", i);
		printf("1");
		for(u8 j = i - 1; j > 0; --j) {
			printf("<j:%u>", j);
			fflush(stdout);
			buf[j] += buf[j - 1];
			printf(" %u", buf[j]);
		}
		/* buf[i] = 1; */
		printf(" 1\n");
	}

	free(buf);
	return 0;
}
