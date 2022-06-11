
typedef unsigned int uint;

struct input {
	double xmin, xmax;
	double ymin, ymax;
	double resolution;
	uint iterations;
};

void mandelbrot_draw(struct input *data);

