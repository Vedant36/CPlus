/* Unix `factor` clone (but much slower of course) */
/* Original factor code:
 * https://github.com/coreutils/coreutils/blob/master/src/factor.c */
/* My implementatoin handles numbers upto 18446744073709551615 (ULLONG_MAX) */
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* strtoll */
#include <math.h>	/* sqrt */

typedef unsigned long int big;
int factors(big num);
void output(char *input, char *progname);

int main(int argc, char **argv)
{
	if (argc > 1) {
		int i = 1;
		for (i = 1; i < argc; i++)
			output(argv[i], argv[0]);
	} else {
		char input[32];
		while (scanf("%31s", input)!= EOF)
			output(input, argv[0]);
	}
	return 0;
}

void output(char *input, char *progname)
{
	big num = strtoul(input, NULL, 0);
	if (num == 0) {
		fprintf(stderr, "%s: '%lu' is not a valid positive integer\n",
				progname, num);
		return;
	}
	printf("%lu:", num);
	factors(num);
	printf("\n");
}

int factors(big num)
{
	big i = 3, limit = (big) sqrt(num) + 1;

	while (num % 2 == 0) {
		num /= 2;
		printf(" %d", 2);
	}

	while (i < limit && num != 1) {
		if (num % i == 0) {
			num /= i;
			limit = sqrt(num) + 1;
			printf(" %lu", i);
		} else {
			i += 2;
		}
	}

	if (num != 1)
		printf(" %lu", num);

	return 0;
}
