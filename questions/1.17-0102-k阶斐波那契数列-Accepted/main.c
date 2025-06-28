#include <stdio.h>
#include <stdlib.h>


int k_fibo(int k, int m) {
    // f_0 = 0, ..., f_{k - 2} = 0, f_{k - 1} = 1;
    // f_n = f_{n - 1} + f_{n - 2} + ... + f_{n - k};
    // Return f_m.

    int* f = (int*) malloc((m + 1) * sizeof(int));
    for (int i = 0; i < k - 1; ++i) {
        f[i] = 0;
    }
    f[k - 1] = 1;

    if (m < k) {
        return f[m];
    }

    for (int i = 0; i < m - k + 1; ++i) {
        // f[k + i] = f[k + i - 1] + ... + f[i];
        f[k + i] = 0;
        for (int j = 0; j < k; ++j) {
            f[k + i] += f[i + j];
        }
    }

    int s = f[m];

    free(f);

    return s;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    printf("%d", k_fibo(a, b));
}