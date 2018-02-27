
typedef double (*test_func)(void *);
struct crrt_Reg {
	const char* name;
	test_func   func;
};

extern void crrt_reg_test(crrt_Reg[]);