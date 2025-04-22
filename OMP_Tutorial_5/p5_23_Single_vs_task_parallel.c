#include <stdio.h>
#include <omp.h>

// int main() {
// #pragma omp parallel num_threads(4)
// #pragma omp single
//     {
//         for (int i = 0; i < 4; i++) {
// #pragma omp task
//             printf("I am thread no. %d.\n", omp_get_thread_num());
//         }
//     }
//     return 0;
// }

int main() {
#pragma omp parallel num_threads(4)
    {
        for (int i = 0; i < 4; i++) {
#pragma omp task
            printf("I am thread no. %d.\n", omp_get_thread_num());
        }
    }
    return 0;
}