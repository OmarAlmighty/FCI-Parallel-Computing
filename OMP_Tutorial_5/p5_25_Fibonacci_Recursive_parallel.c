#include <stdio.h>
#include <omp.h>

long fib(long n) {
    long i = 0;
    long j = 0;

    if (n <= 1) {
        return n;
    }
#pragma omp task shared(i) firstprivate(n) if (n>40)
    i = fib(n - 1);

#pragma omp task shared(j) firstprivate(n) if (n>40)
    j = fib(n - 2);

#pragma omp taskwait
    return i + j;
}

int main(int argc, char *argv[]) {
    long res;
    double start = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        res = fib(45);
    }

    double end = omp_get_wtime();
    printf("fib(45) = %ld\n", res);
    printf("elapsed time = %lf\n", end - start);
    return 0;
}
