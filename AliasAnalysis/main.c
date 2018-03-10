
#define NOINLINE __attribute__ ((noinline)) 

NOINLINE int test1(int a, int b) {
	int d;
	int* c;
	c = &d;
	d = a + b;
	*c = 3;
	// if the compiler know *c is an alias of a, 
	// *c = a + b will be marked as a dead code
	return d;
}

NOINLINE int test2(int a, int b) {
	int e, f;
	int *c, *d;
	c = &a; d = &a;
	e = *c + b;
	f = *d + b;
	// if *c and *d is aliased, the last calculation will be redundent
	return f;
}

int main() {
	test1(1, 2);
	test2(2, 3);
	return 0;
}
