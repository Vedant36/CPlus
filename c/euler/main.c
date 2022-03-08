#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"

typedef unsigned long long int big;
int euler002(int num);
big euler004(int digits);
int euler005(int num);
int euler007(int num);
big euler010(big num);
int euler011(int len, int tx, int ty, int table[][20]);

int main(int argc, char **argv)
{
	(void) argc; (void) argv;
	int table[20][20] = {
		{  8,  2, 22, 97, 38, 15,  0, 40,  0, 75,  4,  5,  7, 78, 52, 12, 50, 77, 91,  8 },
		{ 49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48,  4, 56, 62,  0 },
		{ 81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30,  3, 49, 13, 36, 65 },
		{ 52, 70, 95, 23,  4, 60, 11, 42, 69, 24, 68, 56,  1, 32, 56, 71, 37,  2, 36, 91 },
		{ 22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80 },
		{ 24, 47, 32, 60, 99,  3, 45,  2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50 },
		{ 32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70 },
		{ 67, 26, 20, 68,  2, 62, 12, 20, 95, 63, 94, 39, 63,  8, 40, 91, 66, 49, 94, 21 },
		{ 24, 55, 58,  5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72 },
		{ 21, 36, 23,  9, 75,  0, 76, 44, 20, 45, 35, 14,  0, 61, 33, 97, 34, 31, 33, 95 },
		{ 78, 17, 53, 28, 22, 75, 31, 67, 15, 94,  3, 80,  4, 62, 16, 14,  9, 53, 56, 92 },
		{ 16, 39,  5, 42, 96, 35, 31, 47, 55, 58, 88, 24,  0, 17, 54, 24, 36, 29, 85, 57 },
		{ 86, 56,  0, 48, 35, 71, 89,  7,  5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58 },
		{ 19, 80, 81, 68,  5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77,  4, 89, 55, 40 },
		{  4, 52,  8, 83, 97, 35, 99, 16,  7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66 },
		{ 88, 36, 68, 87, 57, 62, 20, 72,  3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69 },
		{  4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18,  8, 46, 29, 32, 40, 62, 76, 36 },
		{ 20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74,  4, 36, 16 },
		{ 20, 73, 35, 29, 78, 31, 90,  1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57,  5, 54 },
		{  1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52,  1, 89, 19, 67, 48 },
	};
	int input = 5;
	if (argc > 1)
		input = strtoull(argv[1], NULL, 0);
	printf("Answer: %d\n", euler011(input, 20, 20, table));
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
int euler011(int len, int tx, int ty, int table[][20])
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
