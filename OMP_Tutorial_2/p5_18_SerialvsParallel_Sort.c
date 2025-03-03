#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000

void generate_random_array(int *array, int size) {
    // Seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = rand();
    }
}

void bubble_sort(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (array[j] > array[j + 1]) {
                // Compare adjacent elements
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

void odd_even_sort(int *array, int size) {
    int phase, i, tmp;

    for (phase = 0; phase < size; phase++) {
        if (phase % 2 == 0) {
#pragma omp parallel for num_threads(4) \
shared(array, size) private(i, tmp)
            for (i = 1; i < size; i += 2) {
                if (array[i - 1] > array[i]) {
                    tmp = array[i - 1];
                    array[i - 1] = array[i];
                    array[i] = tmp;
                }
            }
        } else {
#pragma omp parallel for num_threads(4) \
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

int main(int argc, char *argv[]) {
    int array[ARRAY_SIZE];
    // Generate the random array
    generate_random_array(array, ARRAY_SIZE);

    time_t start, end;

    time(&start);
    bubble_sort(array, ARRAY_SIZE);
    time(&end);
    printf("%f\n", difftime(end, start));

    time(&start);
    odd_even_sort(array, ARRAY_SIZE);
    time(&end);
    printf("%f\n", difftime(end, start));

    return 0;
}
