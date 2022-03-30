// don't know why this doesn't work
// it just returns 2 for all numbers greater than 1
#include <stdio.h>

int main(int argc, char **argv)
{
	printf("%d\n", argc);
	(void) argv;
	if (argc == 0)
		return 1;
	else
		return argc * main(argc - 1, NULL);
}
