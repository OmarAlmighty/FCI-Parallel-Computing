#include <stdio.h>
#include <omp.h>

long fib(long n) {
    long i = 0; long j = 0;

    if (n <= 1) {
        return n;
    }
    i = fib(n - 1);
    j = fib(n - 2);
    return i + j;
}

int main(int argc, char *argv[]) {
    double start = omp_get_wtime();
    long res = fib(45);
    double end = omp_get_wtime();
    printf("fib(45) = %ld\n", res);
    printf("elapsed time = %lf\n", end - start);
    return 0;
}
