#include <stdio.h>

int main(int argc, char *argv[]) {
    int phase, i, tmp;
    int n = 10;
    int a[] = {10, -5, 9, 1, 0, 2, 4, 3, 6, 11};

    for (phase = 0; phase < n; phase++) {
        if (phase % 2 == 0) {
#pragma omp parallel for num_threads(4) \
    shared(a, n) private(i, tmp)
            for (i = 1; i < n; i += 2) {
                if (a[i - 1] > a[i]) {
                    tmp = a[i - 1];
                    a[i - 1] = a[i];
                    a[i] = tmp;
                }
            }
        } else {
#pragma omp parallel for num_threads(4) \
shared(a, n) private(i, tmp)
            for (i = 1; i < n - 1; i += 2) {
                if (a[i] > a[i + 1]) {
                    tmp = a[i + 1];
                    a[i + 1] = a[i];
                    a[i] = tmp;
                }
            }
        }
    }
    for (i = 0; i < n; i++) {
        printf("a[%d] = %d\n", i, a[i]);
    }
    return 0;
}
