#define _POSIX_C_SOURCE 199309L /* for clock_gettime */
#define _XOPEN_SOURCE 500   /* for usleep */
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "code-profiling.h"

#ifndef PROFILE_IMPLEMENTATION
int main()
{
	printf("Program start!\n");
	profile();
	/* imagine these to be some code */
	usleep(3613);
	printf("Time from last call: %f\n", profile());
	usleep(4719);
	printf("Time from last call: %f\n", profile());
}
#endif

/*
 * returns time difference in double between the last call. Returns the time since
 * epoch for the first call
 */
double profile()
{
	static struct timespec profile_start = {0};
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	double ret = now.tv_sec - profile_start.tv_sec
		 + (now.tv_nsec <= profile_start.tv_nsec)
		 + (now.tv_nsec - profile_start.tv_nsec) / 1000000000.00;
	clock_gettime(CLOCK_REALTIME, &profile_start);
	return ret;
}

