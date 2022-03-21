#define _XOPEN_SOURCE 500   /* for usleep */
#include <stdio.h>
#include <unistd.h>         /* all system calls */
#include <time.h>	/* to profile code with nanosecond accuracy */

void profile(int init);

int main()
{
	printf("Program start!\n");
	profile(1);
	/* imagine these to be some code */
	usleep(613);
	profile(0);
	usleep(719);
	profile(0);
}

/*
 * Put the `profile(1);` to initialize the profiling
 * After that every `profile(0);` in the function will print the time since the
 * last call.
 */
void profile(int init)
{
	static struct timespec profile_start = {0};
	if (init) {
		clock_gettime(CLOCK_REALTIME, &profile_start);
		return;
	}
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	if (now.tv_nsec > profile_start.tv_nsec)
		printf("Time from last call: %ld.%09ld\n",
				now.tv_sec - profile_start.tv_sec,
				now.tv_nsec - profile_start.tv_nsec);
	else
		printf("Time from last call: %ld.%09ld\n",
				now.tv_sec - profile_start.tv_sec,
				1000000000 + now.tv_nsec - profile_start.tv_nsec);
	clock_gettime(CLOCK_REALTIME, &profile_start);
}

