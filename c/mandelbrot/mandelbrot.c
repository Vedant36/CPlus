#include <stdio.h>
#include <math.h>
#include "mandelbrot.h"

const char draw_char[] = ".'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
const uint draw_char_s = sizeof(draw_char) / sizeof(draw_char[0]) - 1;
inline uint mandelbrot_iterate(double x, double y, uint iterations)
{
	double fx = x, fy = y;
	for (uint i = 0; i < iterations; ++i) {
		double tmp = fx * fx - fy * fy + x;
		fy = 2 * fx * fy + y;
		fx = tmp;
		if (fx * fx + fy * fy > 4)
			return i;
	}
	return draw_char_s;
}

void mandelbrot_draw(struct input *data)
{
	printf("Topleft starting from: (%f, %f)\n\n", data->xmin, data->ymax);
	int max = 0;
	for (double y = data->ymax; y > data->ymin; y -= data->resolution) {
		for (double x = data->xmin; x < data->xmax; x += data->resolution) {
			uint i = mandelbrot_iterate(x, y, data->iterations);
			double percentage = (double) i / (double) data->iterations;
			uint index = (double) draw_char_s * pow(percentage, 0.5);
			if (index > max)
				max = index;
			/* uint index = i; */
			putchar(draw_char[index]);
			putchar(draw_char[index]);
		}
		putchar('\n');
	}
	printf("Max index: %d", max);
	printf("\nBottomleft ending from: (%f, %f)\n", data->xmax, data->ymin);
}
