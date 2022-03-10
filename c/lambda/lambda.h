#ifndef LAMBDA_H
#define LAMBDA_H

enum lambda_type {
	// all enums need a NULL
	L_NULL,
	// temp value, shouldn't be in the final lambda struct
	L_UNDECIDED,

	// visible components
	L_VARIABLE,
	L_LAMBDA,
	L_DOT,

	L_COMPOSITION,
	// attach all members of the stack since the last lambda
	L_ATTACH,

	L_COUNT
};

struct lambda_element {
	enum lambda_type type;
	// only for variables
	char name;
};

struct lambda_expression {
	size_t size;
	struct lambda_element list[64];
};

int parse_lambda(char *buf, size_t buf_size, struct lambda_expression *lambda);
int normal_order_reduce();

#endif	/* LAMBDA_H */

/*****************************************************************************/

#ifdef LAMBDA_IMPLEMENTATION

// allocates the parsed lambda function in the buf
// return -1 when unsuccessful
// returns the character when newline is found otherwise
int parse_lambda(char *buf, size_t buf_size, struct lambda_expression *lambda)
{
	lambda->size = 0;

	enum lambda_type bracket_stack[64];
	size_t bracket_size = 0;
	for (size_t i = 0; i < buf_size; i++) {
		switch (buf[i]) {
		case '(':
			if (bracket_stack[bracket_size - 1] == L_UNDECIDED)
				bracket_stack[bracket_size - 1] = L_COMPOSITION;
			bracket_stack[bracket_size++] = L_UNDECIDED;
			break;
		case ')':
			// TODO: fix this(the if should not be needed)
			if (bracket_size > 0)
				lambda->list[lambda->size++].type = bracket_stack[bracket_size--];
			break;
		case '\\':
			lambda->list[lambda->size].type = L_LAMBDA;
			lambda->size++;
			if (bracket_stack[bracket_size - 1] == L_UNDECIDED)
				bracket_stack[bracket_size - 1] = L_ATTACH;
			break;
		case 'f':
		case 'x':
		case 'y':
		case 'z':
			lambda->list[lambda->size].type = L_VARIABLE;
			lambda->list[lambda->size].name = buf[i];
			lambda->size++;
			if (bracket_size > 0) {
				lambda->list[lambda->size].type = bracket_stack[bracket_size--];
				lambda->size++;
			}
			break;
		case ' ':
			bracket_stack[bracket_size++] = L_COMPOSITION;
			break;
		case '.':
			lambda->list[lambda->size].type = L_DOT;
			lambda->size++;
			break;
		case '\n':
		case '\r':
			break;
		}
		printf("%c %zu:", buf[i], bracket_size);
		for (size_t j = 0; j < bracket_size; j++)
			printf("%d,", bracket_stack[j]);
		printf("\n");
	}

	// this is here for debugging only, remove later
	lambda->list[lambda->size].type = L_NULL;
	lambda->size++;
	return bracket_size == 0;
}

#endif /* LAMBDA_IMPLEMENTATION */
