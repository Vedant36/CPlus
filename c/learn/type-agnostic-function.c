// This code is mainly instructive about unions for me
// Using a common type like this in usual code seems like a bad idea
#include <stdio.h>

typedef enum {
	// more types can be added
	T_CHAR,
	T_INT,
	T_FLOAT,
	T_UNKNOWN,
} Type;

typedef struct {
	Type type;
	union {
		unsigned char c;
		int i;
		float f;
	};
} atype; // type agnostic type

atype square(atype num)
{
	switch (num.type){
	case T_CHAR: num.c *= num.c; break;
	case T_INT: num.i *= num.i; break;
	case T_FLOAT: num.f *= num.f; break;
	default: num.type = T_UNKNOWN;
	}
	return num;
}

int main()
{
	atype num_char = {T_CHAR, .c = 5};
	atype num_int = {T_INT, .i = 56};
	atype num_float = {T_FLOAT, .f = 67.3f};
	printf("Squares: %d\n", square(num_char).c);
	printf("Squares: %d\n", square(num_int).i);
	printf("Squares: %f\n", square(num_float).f);
	return 0;
}
