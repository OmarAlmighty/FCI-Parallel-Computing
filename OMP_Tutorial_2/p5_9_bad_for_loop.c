#include <stdio.h>
#include <omp.h>

int search(int key, int arr[], int n) {
    int i;
# pragma omp parallel for
    for (i = 0; i < 5; i++) {
        if (key == arr[i])
            return i;
    }
    return -1;

}

int main(int argc, char *argv[]) {
    int n;
    int arr[] = {1, 2, 3, 4, 5};
    int key = 4;

    scanf("%d", &n);
    int res = search(key, arr, n);
    printf("%d\n", res);
    return 0;
}