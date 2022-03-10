// C and most languages have the right to left associativity for ternary
// expressions, mostly because it is what one would expect when writing one
// This example shows how the ternary would be rewritten with if-else
// `cond1 ? 1 : cond2 ? 2 : cond3 ? 3 : 4`
// will be evaluated to:

// with right to left associativity
int rtl()
{
	if (cond1) {
		return 1;
	} else {
		if (cond2) {
			return 2;
		} else {
			if (cond3) {
				return 3;
			} else {
				return 4;
			}
		}
	}
}

// with left to right associativity
// ltr bad
// another reasson to hate php
int ltr()
{
	int temp;
	if (cond1)
		temp = 1;
	else
		temp = cond2;
	if (temp)
		temp = 2;
	else
		temp = cond3;
	if (temp)
		return 3;
	else
		return 4
}
