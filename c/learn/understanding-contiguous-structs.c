#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test {
	size_t a;
	int a2;
};
struct test2 {
	float b;
	int c;
	char d[5];
};
struct test3 {
	char e;
};

int main(int argc, char **argv)
{
	size_t size = sizeof(struct test)
		+ sizeof(struct test2)
		+ sizeof(struct test3);
	void *collection = malloc(size);
	struct test *restrict a = collection;
	a->a = 42;
	a->a2 = 43;
	struct test2 *restrict b = (struct test2 *)(a + 1);
	/* or equivalently
	struct test2 *restrict b = (struct test2 *)&a[1];
	*/
	b->b = 44;
	b->c = 45;
	char _d[5] = { 1, 2, 3, 4, 5 };
	memcpy(b->d, _d, 5);
#if 0 /* this accesses the first array element from test2 */
	struct test3 *c = (struct test3 *)(a + 2);
	c->e = 46;
#endif
	struct test3 *restrict d = (struct test3 *)(b + 1);
	d->e = 47;
	printf("test: %u %d\n", a->a, a->a2);
	printf("test: %f %d %d:%d:%d:%d:%d\n", b->b, b->c,
			b->d[0], b->d[1], b->d[2], b->d[3], b->d[4]);
	printf("test: %d\n", c->e);
	printf("test: %d\n", d->e);
	printf("0x");
	char *f = (char *) a;
	for (size_t i = 0; i < size; i++) {
		printf("%02x ", f[i]);
		fflush(stdout);
	}
	printf("\n");
	free(a);
	return 0;
}
