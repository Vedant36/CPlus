
#define NUM_LAYERS 3 /* 2 for input and output and 1 hidden */
#define COUNT_INTERATIONS 1

struct layer {
	size_t size;
	float *vals;
	float *weights;
	float *biases;
};

void usage(char *progname);
void print_array(size_t size, float *array);
void alloc_layers(const size_t layer_counts[NUM_LAYERS],
		struct layer Layers[NUM_LAYERS]);
void free_layers(struct layer Layers[NUM_LAYERS]);
void propagate(struct layer Layers[NUM_LAYERS], const float *in);
void backpropagate(struct layer Layers[NUM_LAYERS], float rate,
		const float *out);
void train(size_t num_lines, struct layer Layers[NUM_LAYERS], float rate,
		const float *in, const float *out);

