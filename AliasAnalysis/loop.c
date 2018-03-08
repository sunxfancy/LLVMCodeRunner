#include <stdio.h>
#define N 1000
double data[N][N];

void mul(double a[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a[j][i] = a[j][i] * 0.01;
        }
    }
}

int main() {
    mul(data);
    return 0;
}