
#include "crrt.h"
#include <stdlib.h>
#include <chrono>
using namespace std::chrono;

double*
createMatrix(unsigned int n) {
    return (double*) calloc(sizeof(double), n*n+1);
}

double*
createMatrixWithRandomData(unsigned int n) {
    double* data; unsigned int i;
    data = createMatrix(n);
    for (i = 0; i < n*n; ++i) {
        data[i] = (double)(rand() % 9987) / 100.0;
    }
    return data;
}

void
dgemm_ijk(double *a, double *b, double *c, unsigned int n) {
    unsigned int i,j,k;
    /* ijk – simple triple loop algorithm with simple single register reuse*/
    for (i=0; i<n; i++)
        for (j=0; j<n; j++) {
            double r=c[i*n+j];
            for (k=0; k<n; k++)
                r += a[i*n+k] * b[k*n+j];
            c[i*n+j]=r;
        }
}


typedef void (*func_ptr)(double*,double*,double*, unsigned int);

static double *a, *b, *c;

double test_dgemm(void* func_addr, std::ostream& os) {
    dgemm_ijk(a, b, c, 100);

    auto start = system_clock::now();
    for (int i = 0; i < 30; ++i)
        dgemm_ijk(a, b, c, 100);
    auto end = system_clock::now();
    duration<double> elapsed_seconds = end-start;
    double time_base = duration_cast<milliseconds>(elapsed_seconds).count();

    start = system_clock::now();
    for (int i = 0; i < 30; ++i)
        ((func_ptr)func_addr)(a, b, c, 100);
    end = system_clock::now();
    elapsed_seconds = end-start;
    double time_real = duration_cast<milliseconds>(elapsed_seconds).count();
    os << "time base: " << time_base << " ms" << std::endl;
    os << "time real: " << time_real << " ms" << std::endl;
    return time_base/time_real;
}

void crrt_main() {
    a = createMatrixWithRandomData(100);
    b = createMatrixWithRandomData(100);
    c = createMatrix(100);

    crrt_Reg mg[] = {{"dgemm_ijk", test_dgemm}, {nullptr, nullptr}};
    crrt_reg_test(mg);
}