#include <stdio.h>

int main(int argc, char *argv[]) {
    double factor = 1.0;
    double sum = 0.0;
#pragma omp parallel for reduction(+:sum) private(factor)
    for (int i = 0; i < 1000; ++i) {
        factor = (i % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * i + 1);
    }
    double pi = 4 * sum;
    printf("PI = %lf", pi);
    return 0;
}
