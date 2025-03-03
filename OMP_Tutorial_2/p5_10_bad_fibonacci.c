#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int fib[20];
    fib[0] = fib[1] = 1;

#pragma omp parallel for
    for (int i = 2; i < 20; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    for (int i = 0; i < 20; ++i) {
        printf("%d ", fib[i]);
    }
    return 0;
}