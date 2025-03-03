#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 500000

void generate_random_array(int *array, int size) {
    // Seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = rand();
    }
}

void odd_even_sort(int *array, int size) {
    int phase, i, tmp;

    for (phase = 0; phase < size; phase++) {
        if (phase % 2 == 0) {
#pragma omp parallel for \
shared(array, size) private(i, tmp)
            for (i = 1; i < size; i += 2) {
                if (array[i - 1] > array[i]) {
                    tmp = array[i - 1];
                    array[i - 1] = array[i];
                    array[i] = tmp;
                }
            }
        } else {
#pragma omp parallel for \
shared(array, size) private(i, tmp)
            for (i = 1; i < size - 1; i += 2) {
                if (array[i] > array[i + 1]) {
                    tmp = array[i + 1];
                    array[i + 1] = array[i];
                    array[i] = tmp;
                }
            }
        }
    }
}

void enhanced_odd_even_sort(int *array, int size) {
    int phase, i, tmp;
#pragma omp parallel shared(array, size) private(i, tmp, phase)
    for (phase = 0; phase < size; phase++) {
        if (phase % 2 == 0) {
#pragma omp for
            for (i = 1; i < size; i += 2) {
                if (array[i - 1] > array[i]) {
                    tmp = array[i - 1];
                    array[i - 1] = array[i];
                    array[i] = tmp;
                }
            }
        } else {
#pragma omp for
            for (i = 1; i < size - 1; i += 2) {
                if (array[i] > array[i + 1]) {
                    tmp = array[i + 1];
                    array[i + 1] = array[i];
                    array[i] = tmp;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int array[ARRAY_SIZE];
    // Generate the random array
    generate_random_array(array, ARRAY_SIZE);

    time_t start, end;

    // time(&start);
    // odd_even_sort(array, ARRAY_SIZE);
    // time(&end);
    // printf("%f\n", difftime(end, start));

    time(&start);
    enhanced_odd_even_sort(array, ARRAY_SIZE);
    time(&end);
    printf("%f\n", difftime(end, start));

    return 0;
}
