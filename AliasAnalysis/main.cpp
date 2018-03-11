int test1(int a, int b) {
	int d;
	int* c;
	c = &d;
	d = a + b;
	*c = 3;
	// if the compiler know *c is an alias of a, 
	// *c = a + b will be marked as a dead code
	// and d will directly fold to constant 3
	return d;
}

int test2(int a, int b) {
	int e, f;
	int *c, *d;
	c = &a; d = &a;
	e = *c + b;
	f = *d + b;
	// if *c and *d is aliased, the last calculation will be redundent
	return f;
}
