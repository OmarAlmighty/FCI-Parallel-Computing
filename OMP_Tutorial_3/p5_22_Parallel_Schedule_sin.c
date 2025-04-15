#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double Sum(long n, int thread_count);
double f(long i);

int main(int argc, char *argv[]) {
    double global_result; /* Store result in global_result */
    double start, finish;

    int thread_count = 2;
    long n = 100000;

    start = omp_get_wtime();
    global_result = Sum(n, thread_count);
    finish = omp_get_wtime();


    printf("Result = %.14e\n", global_result);
    printf("Elapsed time = %f seconds\n", finish - start);


    return 0;
} /* main */


/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function in which work is
 *              proportional to the size of the first arg.
 * Input arg:   i, n
 * Return val:
 */
double f(long i) {
    long j;
    long start = i * (i + 1) / 2;
    long finish = start + i;
    double return_val = 0.0;

    for (j = start; j <= finish; j++) {
        return_val += sin(j);
    }
    return return_val;
} /* f */

/*------------------------------------------------------------------
 * Function:    Sum
 * Purpose:     Find the sum of the terms f(0), f(1), . . ., f(n),
 *              where evaluating f requires work proportional to
 *              its argument
 * Input args:
 *    n: number of terms
 *    thread_count:  number of threads
 * Return val:
 *    approx:  f(0) + f(1) + . . . + f(n)
 */
double Sum(long n, int thread_count) {
    double approx = 0.0;
    long i;

#  pragma omp parallel for num_threads(thread_count) \
reduction(+: approx) schedule(dynamic)
    for (i = 0; i <= n; i++) {
        approx += f(i);
    }

    return approx;
} /* Sum */
