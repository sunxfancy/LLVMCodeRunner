#include "crrt.h"

#include <chrono>
using namespace std::chrono;
#define N 1000
double data[N][N];

#include "loop.c"

extern void mul(double a[N][N]);
typedef void (*func_ptr)(double a[N][N]);

double test_mul(void* func_addr, std::ostream& os) {
    mul(data);

    auto start = system_clock::now();
    for (int i = 0; i < 100; ++i)
        mul(data);
    auto end = system_clock::now();
    duration<double> elapsed_seconds = end-start;
    double time_base = duration_cast<milliseconds>(elapsed_seconds).count();

    start = system_clock::now();
    for (int i = 0; i < 100; ++i)
        ((func_ptr)func_addr)(data);
    end = system_clock::now();
    elapsed_seconds = end-start;
    double time_real = duration_cast<milliseconds>(elapsed_seconds).count();
    os << "time base: " << time_base << " ms" << std::endl;
    os << "time real: " << time_real << " ms" << std::endl;
    return time_base/time_real;
}

void crrt_main() {
    crrt_Reg mg[] = {{"mul", test_mul}, {nullptr, nullptr}};
    crrt_reg_test(mg);
}