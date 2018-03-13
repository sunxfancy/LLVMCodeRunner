#include "crrt.h"
#include <chrono>
using namespace std::chrono;

#include "main.c"

typedef int (*func_ptr1)(int a, int b);
typedef int (*func_ptr2)(int a, int b);

double runtest_1(void* func_addr, std::ostream& os) {
    test1(1, 2);

    auto start = system_clock::now();
    for (int i = 0; i < 300000000; ++i)
        test1(1, 2);
    auto end = system_clock::now();
    duration<double> elapsed_seconds = end-start;
    double time_base = duration_cast<milliseconds>(elapsed_seconds).count();

    start = system_clock::now();
    for (int i = 0; i < 300000000; ++i)
        ((func_ptr1)func_addr)(1, 2);
    end = system_clock::now();
    elapsed_seconds = end-start;
    double time_real = duration_cast<milliseconds>(elapsed_seconds).count();
    os << "time base: " << time_base << " ms" << std::endl;
    os << "time real: " << time_real << " ms" << std::endl;
    return time_base/time_real;
}

double runtest_2(void* func_addr, std::ostream& os) {
    test2(1, 2);

    auto start = system_clock::now();
    for (int i = 0; i < 300000000; ++i)
        test2(1, 2);
    auto end = system_clock::now();
    duration<double> elapsed_seconds = end-start;
    double time_base = duration_cast<milliseconds>(elapsed_seconds).count();

    start = system_clock::now();
    for (int i = 0; i < 300000000; ++i)
        ((func_ptr2)func_addr)(1, 2);
    end = system_clock::now();
    elapsed_seconds = end-start;
    double time_real = duration_cast<milliseconds>(elapsed_seconds).count();
    os << "time base: " << time_base << " ms" << std::endl;
    os << "time real: " << time_real << " ms" << std::endl;
    return time_base/time_real;
}

void crrt_main() {
    crrt_Reg mg[] = {{"test1", runtest_1}, {"test2", runtest_2}, {nullptr, nullptr}};
    crrt_reg_test(mg);
}