#include <stdio.h>

int pow2generator();

int main()
{
	printf("Powers of 2:");
	printf(" %d", pow2generator());
	printf(" %d", pow2generator());
	printf(" %d", pow2generator());
	printf(" %d", pow2generator());
	printf("\n");
	// prints: `Powers of 2: 2 4 8 16\n`
}

// Unlike other languages(i only know of python), a `generator` in C runs the
// whole code instead of continuing execution from when the function last
// returned.
int pow2generator()
{
	// Declaring a variable as static causes it to retain its value until
	// the next function call.
	// Note: a static variable can only be initialized to a constant
	// because it happens only once during the first function call but this
	// feature can be used in a variety of ways.
	static int i = 1;
	i *= 2;
	return 2;
}
