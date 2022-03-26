#include <stdio.h>
#include <stdlib.h>	    // atoi
#include <string.h>
#include <assert.h>
#include "neural.h"
#include "util.h"
#define COUNT_INTERATIONS 100

/*
 * Input node  : float in[s_in]
 * Output node : int out[s_out]
 * Neural net  : s_in( -> layer)+ -> s_out
 * Arguments   : $0 filename num_inputs out_count[ line_offset]
 */
int main(int argc, char **argv)
{
	if (argc < 4) {
		usage(argv[0]);
		return 1;
	}

	// Initialize input and output from file
	size_t s_in = atoi(argv[2]), s_out = atoi(argv[3]);
	int line_offset = argc >= 5 ? atoi(argv[4]) : 0;
	float *in = NULL, *out = NULL;
	size_t num_lines = util_setup(argv[1], line_offset,
			&in, &out, s_in, s_out);
	(void) num_lines;
	/* util_show(&in, &out, s_in, s_out, num_lines); */

	// allocate layers for propagation
	const size_t layer_counts[NUM_LAYERS] = {s_in, 16, s_out};
	struct layer Layers[NUM_LAYERS] = {0};
	alloc_layers(layer_counts, Layers);

	for (size_t i = 0; i < COUNT_INTERATIONS; i++) {
		propagate(Layers);
		backpropagate(Layers);
	}

	free_layers(Layers);
	util_free(&in, &out);
	return 0;
}

void usage(char *progname)
{
	fprintf(stderr, "Usage: %s FILENAME num_inputs out_count [offset]\n",
			progname);
}

// allocate memory for all layer, weight and bias for propagation
void alloc_layers(const size_t layer_counts[NUM_LAYERS],
		struct layer Layers[NUM_LAYERS])
{
	assert(NUM_LAYERS >= 2);
	Layers[0].size = layer_counts[0];
	Layers[0].vals = malloc(layer_counts[0] * sizeof(float));
	Layers[0].weights = NULL;
	Layers[0].biases = NULL;
	for (size_t i = 1; i < NUM_LAYERS; i++) {
		Layers[i].size = layer_counts[i];
		Layers[i].vals = malloc(layer_counts[i] * sizeof(float));
		Layers[i].weights = calloc(layer_counts[i] * layer_counts[i - 1], sizeof(float));
		Layers[i].biases = calloc(layer_counts[i], sizeof(float));
	}
}

void free_layers(struct layer Layers[NUM_LAYERS])
{
	for (size_t i = 0; i < NUM_LAYERS; i++) {
		free(Layers[i].vals);
		free(Layers[i].weights);
		free(Layers[i].biases);
	}
}

void propagate(struct layer Layers[NUM_LAYERS])
{
	(void) Layers;
}

void backpropagate(struct layer Layers[NUM_LAYERS])
{
	(void) Layers;
}
