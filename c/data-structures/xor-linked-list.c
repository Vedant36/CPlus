#include <stdio.h>

// element 0: value, pointer = &element1
// element 1: value, pointer = &element1 ^ &element2
// element 1: value, pointer = &element2
struct xor_linked_element {
	int value;
	int *xor_pointer;
};

struct xor_linked_list {
	struct xor_linked_element *ref_pointer;
	int current_value;
};

struct xor_linked_list xorNew(int value)
{
	struct xor_linked_element element = { value, NULL };
	struct xor_linked_list list = {
		.ref_pointer = &element,
		.current_value = element.value
	};
	printf("Pointer %p\n", (void *)&list);
	return list;
}

void xorInsert(struct xor_linked_list, int value)
{
	struct xor_linked_element element = { value, NULL };
	xor_linked_element.ref_pointer->xor_pointer = &element;
}

void xorNext(struct xor_linked_list)
{
	;
}

int main()
{
	struct xor_linked_list test = xorNew(0);
	printf("Pointer %p\n", (void *)&test);
	printf("Value: %d", test.current_value);
	xorInsert(test, 58);

	return 1;
}
