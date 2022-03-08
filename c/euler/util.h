
// \param num                  input
// \param base                 base in which to check
unsigned int is_palindrome(unsigned long long int num, int base)
{
	unsigned long long int reverse = 0;
	if (num % base == 0) return 0;
	while (num) {
		reverse = reverse * base + num % base;
		if (reverse == num) return 1;
		num /= base;
		if (reverse == num) return 1;
	}
	return 0;
}

int is_prime(int num)
{
	if (num < 2) return 0;
	if (num == 2) return 1;
	if (num % 2 == 0) return 0;
	for (int i = 3; i < sqrt(num) + 1; i++)
		if (num % i == 0)
			return 0;
	return 1;
}

struct timespec profile_start;

// Put the `profile(1);` to start the profiling
// After that every `profile(0);` in the function will print the time since the
// last call.
void profile(int init)
{
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
