//gcc-14 -o main -fopenmp p5_5_trapz_parallel_bad.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f(double x); /* Function we're integrating */
double local_trap(double a, double b, int n);

int main(int argc, char *argv[]) {
    double global_result = 0.0; /* Store result in global_result */
    double a, b; /* Left and right endpoints */
    int n; /* Total number of trapezoids */
    int thread_count = strtol(argv[1], NULL, 10);
    printf("Enter a, b, and n\n");
    scanf("%lf %lf %d", &a, &b, &n);
# pragma omp parallel num_threads(thread_count)
    {
# pragma omp critical
        global_result += local_trap(a, b, n);
    }
    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %.14e\n", a, b, global_result);
    return 0;
} /* main */
double f(double x) {
    return x * x;
} /* f */
double local_trap(double a, double b, int n) {
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    double x;
    double h = (b - a) / n;
    int local_n = n / thread_count;
    double local_a = a + my_rank * local_n * h;
    double local_b = local_a + local_n * h;
    double my_result = (f(local_a) + f(local_b)) / 2.0;
    for (int i = 1; i <= local_n - 1; i++) {
        x = local_a + i * h;
        my_result += f(x);
    }
    my_result = my_result * h;
    return my_result;
} /* local_trap */