// just a sorting method I discovered and implemented. its faster than the
// builtin inplace quicksort for arrays with less than 15 elements so
// practically useless but I INVENTED A SORTING ALGORITHM
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>         /* standard library definitions */
#include <unistd.h>
#include <time.h>           /* to profile code with nanosecond accuracy */
#define PROFILE_IMPLEMENTATION
#include "profile.h"

void array_show(int *array, size_t size);
int* vsort(const int *array, size_t size);
int compar(const void *a, const void *b) {
	return (int *) a - (int *) b;
}

int main()
{
	struct timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	srand(time.tv_nsec);
	// prints the time it takes to sort for both algorithms which can be
	// redirected to a file that can be plotted using gnuplot with
	//     > plot 'filename' using 1:2, 'filename' using 1:3
	for (size_t i = 2; i < 30; i++) {
		int *array = malloc(i * sizeof(int));
		for (size_t j = 0; j < i; j++)
			array[j] = rand() % 100;
		printf("%03zu", i);
		profile();
		int *sorted_array = vsort(array, i);
		printf(" %f", profile());
		qsort(array, i, sizeof(int), compar);
		printf(" %f\n", profile());
		free(array);
		free(sorted_array);
	}
	return 0;
}

int* vsort(const int *array, size_t size)
{
	int *sorted_array = calloc(size, sizeof(int));
	for (size_t i = 0; i < size; i++) {
		size_t lesscount = 0, equalcount = 0;
		for (size_t j = 0; j < size; j++) {
			lesscount += (array[j] < array[i]);
			equalcount += (array[j] == array[i]);
		}
		for (size_t j = 0; j < equalcount; j++)
			sorted_array[lesscount + j] = array[i];
	}
	return sorted_array;
}

