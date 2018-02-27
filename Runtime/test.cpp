
#include "crrt.h"
#include <stdlib.h>
#include <time.h>

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

double timespec_diff(struct timespec *start, struct timespec *stop)
{
    double ans = 0.0;
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        ans = 1000000000.0 * (stop->tv_sec - start->tv_sec - 1);
        ans += stop->tv_nsec - start->tv_nsec + 1000000000.0;
    } else {
        ans = 1000000000.0 * (stop->tv_sec - start->tv_sec);
        ans += stop->tv_nsec - start->tv_nsec;
    }
    return ans;
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

double test_dgemm(void* func_addr) {
    dgemm_ijk(a, b, c, 100);

    struct timespec ts1,ts2;
    clock_gettime(CLOCK_REALTIME, &ts1);
    for (int i = 0; i < 30; ++i)
        dgemm_ijk(a, b, c, 100);
    clock_gettime(CLOCK_REALTIME, &ts2);
    double time_base = timespec_diff(&ts1, &ts2);

    clock_gettime(CLOCK_REALTIME, &ts1);
    for (int i = 0; i < 30; ++i)
        ((func_ptr)func_addr)(a, b, c, 100);
    clock_gettime(CLOCK_REALTIME, &ts2);
    double time_real = timespec_diff(&ts1, &ts2);
    return time_base/time_real;
}

void crrt_main() {
    a = createMatrixWithRandomData(100);
    b = createMatrixWithRandomData(100);
    c = createMatrix(100);

    crrt_Reg mg[] = {{"dgemm_ijk", test_dgemm}, {nullptr, nullptr}};
    crrt_reg_test(mg);
}