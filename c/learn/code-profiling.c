#define _POSIX_C_SOURCE 199309L /* for clock_gettime */
#define _XOPEN_SOURCE 500   /* for usleep */
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#define PROFILE_IMPLEMENTATION
#include "profile.h"

int main()
{
	printf("Program start!\n");
	profile();
	/* imagine these to be some code */
	usleep(3613);
	printf("Time from last call: %.2f ms\n", 1000000 * profile());
	usleep(4719);
	printf("Time from last call: %.2f ms\n", 1000000 * profile());
}
