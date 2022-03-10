#include <stdio.h>

// laughing at C++ rn
struct class {
	int property1, property2;
	int (*internal_function)(struct class *);
};

int sum(struct class *object)
{
	return object->property1 + object->property2;
}

int main()
{
	printf("Size of class: %zu\n", sizeof(struct class));
	struct class object = { 69, 351, sum };
	printf("Size of object: %zu\n", sizeof(object));
	printf("Sum of the two properties: %d\n",
			object.property1 + object.property2);
	// In Object-Oriented languages, the pointer to the struct/object itself
	// is passed to the function by default as `self`
	printf("Sum of the two properties(using an internal function): %d\n",
			object.internal_function(&object));
}

