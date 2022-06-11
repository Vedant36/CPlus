#include <stdio.h>
#include "mandelbrot.h"


uint main(uint argc, char **argv)
{
	struct input init = {
		-2.0f, 1.0f,
		-1.5f, 1.5f,
		.resolution = 0.02f,
		.iterations = 10000
	};
	mandelbrot_draw(&init);
	return 0;
}

