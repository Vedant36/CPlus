#ifndef LAMBDA_H
#define LAMBDA_H

enum lambda_type {
	// all enums need a NULL
	L_NULL,
	// temp value, shouldn't be in the final lambda struct
	L_UNDECIDED,

	// visible components
	L_VARIABLE,
	// abstraction symbols
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

