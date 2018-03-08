
#define NOINLINE __attribute__ ((noinline)) 

NOINLINE int test1() {
	int a, b, d;
	int* c;
	a = 1; b = 2;
	c = &d;
	*c = 3;
	d = a + b;
	// if the compiler know *c is an alias of a, 
	// *c = a + b will be marked as a dead code
	return d;
}

NOINLINE int test2() {
	int a, b, e, f;
	int *c, *d;
	a = 1; b = 2;
	c = &a; d = &a;
	e = *c + b;
	f = *d + b;
	// if *c and *d is aliased, the last calculation will be redundent
	return f;
}


int main() {
	test1();
	test2();
	return 0;
}
