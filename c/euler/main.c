#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "util.h"

int main(int argc, char **argv)
{
	(void) argc; (void) argv;
	int input = 5;
	if (argc > 1)
		input = strtoull(argv[1], NULL, 0);
	printf("\nAnswer: %d\n", euler012(input));
	return 0;
}

// sums up all even fibonacci numbers less than num
int euler002(int num)
{
	int a = 2, b = 8;
	int sum = 0;
	for (int i = 0; a < num; i++) {
		sum += a;
		int c = a + 4 * b;
		a = b;
		b = c;
	}
	return sum;
}

// given the digits, calculates the largest palindrome that can be written as a
// product of two numbers with the given number of digits each
big euler004(int digits)
{
	// 999900665566009999: solution for 9 digits(took 158.854694019s)
	big ans = 0, counti = 0, countj = 0;
	big ulimit = (big) pow(10, digits) - 1;
	big llimit = ulimit / 10;

	profile(1);
	for (big i = ulimit; i >= llimit; i--) {
		for (big j = ulimit; j > i; j--) {
			if (i * j > ans && is_palindrome(i * j, 10)) {
				ans = i * j;
				llimit = ans / ulimit;
				printf("%llu, %llu, %llu\n", i, j, ans);
			}
			countj += 1;
		}
		counti += 1;
	}
	profile(0);
	printf("Ran %llu,%llu times\n", counti, countj);
	return ans;
}

// returns the lcm of all numbers i <= num
int euler005(int num)
{
	const float numlog = log(num);
	int ans = 1;
	for (int i = 2; i < num; i++) {
		if (is_prime(i)) {
			ans *= pow(i, (int) (numlog / log(i)));
		}
	}
	return ans;
}

int euler007(int num)
{
	if (num == 1) return 2;
	int count = 1, i = 3;
	for (; count < num; i += 2)
		count += is_prime(i);
	return i - 2;
}

// returns sum of all primes p < num
big euler010(big num)
{
	if (num < 2) return 0;
	big sum = 2;
	for (big i = 3; i < num; i += 2) {
		if (is_prime(i)) {
			sum += i;
			/* printf("%llu ", i); */
		}
	}

	printf("\n");
	return sum;
}

// tx and ty are the dimensions of the table
int euler011(int len, int tx, int ty, int table[tx][ty])
{
	int max = 1;
	for (int i = 0; i < tx; i++) {
		for (int j = 0; j < ty; j++) {
			if (i + len - 1 < tx) {
				if (j + len - 1 < ty) {
					int product = 1;
					for (int k = 0; k < len; k++) {
						product *= table[i + k][j + k];
					}
					if (product > max)
						max = product;
				}
				if (j >= len - 1) {
					int product = 1;
					for (int k = 0; k < len; k++) {
						product *= table[i + k][j - k];
					}
					if (product > max)
						max = product;
				}
				int product = 1;
				for (int k = 0; k < len; k++) {
					product *= table[i + k][j];
				}
				if (product > max)
					max = product;
			}

			if (j + len - 1 < ty) {
				int product = 1;
				for (int k = 0; k < len; k++) {
					product *= table[i][j + k];
				}
			if (product > max)
				max = product;
			}
		}
	}
	return max;
}

int euler012(int count)
{
	int max_divisor_count = 0;
	for (int i = 2; ; i++) {
		int divisor_count = 0;
		int num = i * (i + 1) / 2;
		for (int j = 1; j < sqrt(num); j++) {
			if (num % j == 0)
				divisor_count++;
		}
		if (2 * divisor_count > max_divisor_count)
			max_divisor_count = 2 * divisor_count;
		/* printf("\r%d: %d %d", i, num, 2 * divisor_count); */
		if (2 * divisor_count > count)
			return num;
	}
	return -1;
}
