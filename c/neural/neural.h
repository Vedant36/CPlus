
#define NUM_LAYERS 3 /* 2 for input and output and 1 hidden */

struct layer {
	size_t size;
	float *vals;
	float *weights;
	float *biases;
};

void usage(char *progname);
void alloc_layers(const size_t layer_counts[NUM_LAYERS],
		struct layer Layers[NUM_LAYERS]);
void free_layers(struct layer Layers[NUM_LAYERS]);
void propagate(struct layer Layers[NUM_LAYERS]);
void backpropagate(struct layer Layers[NUM_LAYERS]);

