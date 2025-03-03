#include <stdio.h>

int main(int argc, char *argv[]) {
    double factor = 1.0;
    double sum = 0.0;
    int i;
    int n = 1000;
#pragma omp parallel for default(none) reduction(+:sum)\
        private(i, factor) shared(n)
    for (i = 0; i < n; ++i) {
        factor = (i % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * i + 1);
    }
    double pi = 4 * sum;
    printf("PI = %lf", pi);
    return 0;
}
