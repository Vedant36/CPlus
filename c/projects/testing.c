#include <stdio.h>
#include <string.h>	// strcmp
#include <stdlib.h>	// exit(1)
#include <unistd.h>	// execvp
#include <errno.h>
#define NUM_TARGETS 2

struct target {
	char *name;
	int (*test)();
};

void test(const char *target);
int tmp();
int rpn();

struct target targetlist[NUM_TARGETS] = {
	{ "testing-tester", tmp },
	{ "rpn", rpn },
};

int main(int argc, char **argv)
{

	if (argc == 1) {
		test(0);
	} else {
		if (strcmp(argv[1], "-l") == 0) {
			for (int i = 0; i < NUM_TARGETS; i++)
				printf("%s\n", targetlist[i].name);
		} else {
			for(int i = 1; i < argc; i++)
				test(argv[i]);
		}
	}
	return 0;
}

void test (const char *target)
{
	int fail_count = 0;
	for (int i = 0; i < NUM_TARGETS; i++) {
		if (!target || strcmp(target, targetlist[i].name) == 0) {
			printf("[Info] Testing `%s`...\n", targetlist[i].name);
			int successful = targetlist[i].test();
			if (successful == 0) {
				printf("[Error] Test Failed!\n");
				fail_count += 1;
			}
			if (target)
				return;
		}
	}
	if (fail_count > 0)
		printf("[Error] %d/%d failed", fail_count, NUM_TARGETS);
}

int tmp()
{
	return 1;
}

int rpn()
{
	return 0;
}
