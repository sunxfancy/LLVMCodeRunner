
void
dgemm_ijk(double *a, double *b, double *c, unsigned int n) {
    unsigned int i,j,k;
    /* ijk – simple triple loop algorithm with simple single register reuse*/
    for (i=0; i<n; i++)
        for (j=0; j<n; j++) {
            register double r=c[i*n+j];
            for (k=0; k<n; k++)
                r += a[i*n+k] * b[k*n+j];
            c[i*n+j]=r;
        }
}


int main() {
    double a[] = {1.0, 0.0, 3.2, 4.8,
                  1.0, 2.9, 3.2, 4.8,
                  1.0, 2.9, 3.2, 4.8,
                  1.0, 2.9, 3.2, 4.8};

    double b[] = {1.0, 0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0, 0.0,
                  0.0, 0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0, 1.0};

    double c[16];

    dgemm_ijk(a, b, c, 4);

    return 0;
}