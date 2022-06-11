/* gnu `dc` clone */
#include <stdio.h>
#include <math.h>
#include <string.h>

#define STACK_SIZE 32

int stack[STACK_SIZE] = {0};
int rsp = 0;
void handle_ops(char op);

int main()
{
	char buf[16];
	int val;
	while (scanf("%15s", buf) != EOF) {
		if (sscanf(buf, "%d", &val)) {
			if (rsp == STACK_SIZE) {
				fprintf(stderr, "stack full\n");
			} else {
				stack[rsp] = val;
				rsp++;
			}
		} else {
			size_t i;
			for (i = 0; i < strlen(buf); i++)
				handle_ops(buf[i]);
		}
	}
	return 0;
}

void handle_ops(char op)
{
	int a, b, c, tmp, i;
	int consumed = 1;
	switch (op) {
	case 'c':
		rsp = 0;
		break;
	case 'f':
		for (i = 0; i < rsp; i++)
			printf("%d\n", stack[i]);
		break;
	default:
		consumed = 0;
	}
	if (consumed)
		return;

	/* >=1 elements needed */
	if (rsp == 0) {
		fprintf(stderr, "stack empty\n");
		return;
	}
	consumed = 1;
	a = stack[rsp - 1];
	switch (op) {
	case 'p':
		printf("%d\n", a);
		break;
	case 'n':
		printf("%d", a);
		rsp--;
		break;
	case 'd':
		stack[rsp] = a;
		rsp++;
		break;
	case 'v':
		stack[rsp - 1] = sqrt(a);
		break;
	default:
		consumed = 0;
	}
	if (consumed)
		return;

	/* >=2 elements needed */
	if (rsp == 1) {
		fprintf(stderr, "insufficient elements on the stack\n");
		return;
	}
	consumed = 1;
	b = stack[rsp - 2];
	switch (op) {
	case 'r':
		stack[rsp - 2] = a;
		stack[rsp - 1] = b;
		return;
	case '~':
		stack[rsp - 2] = b / a;
		stack[rsp - 1] = b % a;
		return;
	case '+': tmp = b + a; break;
	case '-': tmp = b - a; break;
	case '*': tmp = b * a; break;
	case '/': tmp = b / a; break;
	case '%': tmp = b % a; break;
	case '^': tmp = pow(b, a); break;
	default:
		consumed = 0;
	}
	if (consumed) {
		stack[rsp - 2] = tmp;
		rsp--;
		return;
	}

	/* >=3 elements needed */
	if (rsp == 2) {
		fprintf(stderr, "insufficient elements on the stack\n");
		return;
	}
	c = stack[rsp - 3];
	consumed = 1;
	switch (op) {
	case 'R':
		stack[rsp - 3] = b;
		stack[rsp - 2] = a;
		stack[rsp - 1] = c;
		break;
	case '|':
		stack[rsp - 3] = 1;
		for(i = 0; i < b; i++)
			stack[rsp - 3] = (stack[rsp - 3] * c) % a;
		rsp -= 2;
		break;
	default:
		consumed = 0;
	}
	if (consumed)
		return;
	fprintf(stderr, "No such operation/Operation unimplemented\n");
}
