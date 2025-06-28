#include <stdio.h>
#include <limits.h>

#define ARR_MAX_SIZE 20

int main() {
    int n = 0;
    int arrsize = 0;
    scanf("%d %d", &n, &arrsize);

    if (n > arrsize) {
        printf("-1");
        return 0;
    }

    // a_i = i! * 2^i
    // If some a_i > MAX_INT, then return -1

    int a[ARR_MAX_SIZE] = {0};  // actual size is: arrsize

    a[0] = 1;

    if (n > 1) {
        for (int i = 1; i < n; ++i) {
            int upper_lmt = INT_MAX / (i * 2.0);
            if (a[i - 1] > upper_lmt) {
                printf("-1");
                return 0;
            }
            a[i] = a[i - 1] * i * 2;
        }
    }

    printf("1");
    if (n > 1) {
        for (int i = 1; i < n; ++i) {
            printf(" %d", a[i]);
        }
    }
    return 0;
}