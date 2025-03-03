#include <stdio.h>

int main(int argc, char *argv[]) {
    double factor = 1.0;
    double sum = 0.0;
    for (int i = 0; i < 1000; ++i) {
        sum += factor / (2 * i + 1);
        factor = -factor;
    }
    double pi = 4 * sum;
    printf("PI = %lf", pi);
    return 0;
}
