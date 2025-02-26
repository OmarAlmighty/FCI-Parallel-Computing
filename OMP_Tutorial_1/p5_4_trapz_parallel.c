//gcc-14 -o main -fopenmp p5_4_trapz_parallel.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f(double x);    /* Function we're integrating */
void local_trap(double a, double b, int n, double *global_result_p);

int main(int argc, char *argv[]) {
    double global_result = 0.0;  /* Store result in global_result */
    double a, b;                 /* Left and right endpoints      */
    int n;                    /* Total number of trapezoids    */

    int thread_count = 4;//strtol(argv[1], NULL, 10);
    printf("Enter a, b, and n\n");
    scanf("%lf %lf %d", &a, &b, &n);

#  pragma omp parallel num_threads(thread_count)
    local_trap(a, b, n, &global_result);

    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %.14f\n", a, b, global_result);
    return 0;
}  /* main */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input arg:   x
 * Return val:  f(x)
 */
double f(double x) {
    return x * x;
}  /* f */

/*------------------------------------------------------------------
 * Function:    local_trap
 * Purpose:     Use trapezoidal rule to estimate definite integral
 * Input args:  
 *    a: left endpoint
 *    b: right endpoint
 *    n: number of trapezoids
 * Output arg:
 *    integral:  estimate of integral from a to b of f(x)
 */
void local_trap(double a, double b, int n, double *global_result_p) {
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    double x;

    double h = (b - a) / n;
    int local_n = n / thread_count;
    double local_a = a + my_rank * local_n * h;
    double local_b = local_a + local_n * h;
    printf("Thread %d: %lf to %lf\n", my_rank, local_a, local_b);
    double my_result = (f(local_a) + f(local_b)) / 2.0;
    for (int i = 1; i <= local_n - 1; i++) {
        x = local_a + i * h;
        my_result += f(x);
    }
    my_result = my_result * h;

#  pragma omp critical
    *global_result_p += my_result;
}  /* local_trap */
