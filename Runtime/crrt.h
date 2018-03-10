#pragma once
#include <iostream>

typedef double (*test_func)(void *, std::ostream&);
struct crrt_Reg {
	const char* name;
	test_func   func;
};

extern void crrt_reg_test(crrt_Reg[]);