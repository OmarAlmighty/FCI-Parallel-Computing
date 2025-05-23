#include <stdio.h>

double f(double x);    /* Function we're integrating */
double Trap(double a, double b, int n, double h);

int main(void) {
    double integral;   /* Store result in integral   */
    double a, b;       /* Left and right endpoints   */
    int n;          /* Number of trapezoids       */
    double h;          /* Height of trapezoids       */

    printf("Enter a, b, and n\n");
    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%d", &n);

    h = (b - a) / n;
    integral = Trap(a, b, n, h);

    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %.15f\n", a, b, integral);

    return 0;
}  /* main */

/*------------------------------------------------------------------
 * Function:    Trap
 * Purpose:     Estimate integral from a to b of f using local_trap rule and
 *              n trapezoids
 * Input args:  a, b, n, h
 * Return val:  Estimate of the integral
 */
double Trap(double a, double b, int n, double h) {
    double integral = (f(a) + f(b)) / 2.0;

#pragma omp parallel for num_threads(4) reduction(+:integral)
    for (int k = 1; k <= n - 1; k++) {
        integral += f(a + k * h);
    }
    integral = integral * h;

    return integral;
}  /* Trap */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) {
    return x * x;
}  /* f */
