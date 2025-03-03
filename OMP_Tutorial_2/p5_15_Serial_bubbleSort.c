#include <stdio.h>

int main(int argc, char *argv[]) {
    int n = 10;
    int a[] = {10, -5, 9, 1, 0, 2, 4, 3, 6, 11};

    for (int i = n-1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {  // Compare adjacent elements
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }

    // Print the array
    for (int i = 0; i < n; i++) {
        printf("a[%d] = %d\n", i, a[i]);
    }
    return 0;
}
