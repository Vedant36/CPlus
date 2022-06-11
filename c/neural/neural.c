#include <stdio.h>
#include <stdlib.h>	    // atoi
/* #include <string.h> */
#include <assert.h>
#include <math.h>	    // expf
#include "util.h"
#include "neural.h"

/* TODO
 * complete the backpropagate implementation
 * initializing weights and biases with random numbers
 * shuffling the input array and splitting it into train and test
 * output a file containing the trained data that can be used to test cases
 * automatically detect the number of fields using the first column
 */

/* Neural structure:
 * Input node  <- float in[s_in]
 * Output node <- int out[s_out]
 * Neural net  <- s_in( -> layer)+ -> s_out
 * Arguments   <- $0 filename num_inputs out_count[ line_offset]
 */
int main(int argc, char **argv)
{
	if (argc < 4) { usage(argv[0]); return 1; }

	// Initialize input and output from file
	size_t s_in = atoi(argv[2]), s_out = atoi(argv[3]);
	int line_offset = argc >= 5 ? atoi(argv[4]) : 0;
	float *in = NULL, *out = NULL;
	size_t num_lines = util_setup(argv[1], line_offset,
			&in, &out, s_in, s_out);
	/* util_show(in, out, s_in, s_out, num_lines); */

	// allocate layers for propagation
	const size_t layer_counts[NUM_LAYERS] = {s_in, 16, s_out};
	struct layer Layers[NUM_LAYERS] = {0};
	alloc_layers(layer_counts, Layers);

	// choo choo
	train(num_lines, Layers, 0.03, in, out);

	free_layers(Layers);
	util_free(&in, &out);
	return 0;
}

void usage(char *progname)
{
	fprintf(stderr, "Usage: %s FILENAME num_inputs out_count [offset]\n",
			progname);
}

void print_array(size_t size, float *array)
{
	printf("{ %f", array[0]);
	for (size_t i = 1; i < size; i++)
		printf(", %f", array[i]);
	printf(" }\n");
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

/* activation and dreivative of the activation function */
// TODO: check for inline gain
float activation(float n)
{
	return 1 / (1 + expf(n));
}

float der_activation(float n)
{
	float tmp = expf(n);
	return tmp / (1 + tmp) / (1 + tmp);
}

void propagate(struct layer Layers[NUM_LAYERS], const float *in)
{
	size_t i, j, k;
	for (i = 0; i < Layers[0].size; i++) {
		Layers[0].vals[i] = in[i];
	}
	for (i = 1; i < NUM_LAYERS; i++) {
		for (j = 0; j < Layers[i].size; j++) {
			int tmp = 0;
			for (k = 0; k < Layers[i - 1].size; k++) {
				tmp += activation(Layers[i].biases[j]
						+ Layers[i - 1].vals[k]
						* Layers[i].weights[j * Layers[i - 1].size + k]);
			}
			Layers[i].vals[j] = 0;
		}
		/* print_array(Layers[i].size, Layers[i].vals); */
	}
}

void backpropagate(struct layer Layers[NUM_LAYERS], float rate,
		const float *out)
{
	assert(0 && "Unimplemented");
	(void) rate;
	(void) out;
	size_t i, j, k;
	for (i = 0; i < Layers[NUM_LAYERS - 1].size; i++) {
		Layers[NUM_LAYERS - 1].size = fabsf(out[i] -
				Layers[NUM_LAYERS - 1].size);
	}
	for (i = NUM_LAYERS - 1; i > 0; i--) {
		for (j = 0; j < Layers[i].size; j++) {
			for (k = 0; k < Layers[i - 1].size; k++) {
				;
			}
		}
		print_array(Layers[i].size, Layers[i].biases);
	}
}

void train(size_t num_lines, struct layer Layers[NUM_LAYERS], float rate,
		const float *in, const float *out)
{
	for (size_t i = 0; i < COUNT_INTERATIONS; i++) {
		for (size_t j = 0; j < num_lines; j++) {
			propagate(Layers, in + Layers[0].size * j);
			backpropagate(Layers, rate, out + Layers[0].size * j);
		}
		print_array(Layers[NUM_LAYERS - 1].size, Layers[NUM_LAYERS - 1].biases);
	}
}
