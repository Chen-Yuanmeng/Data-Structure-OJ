#include <stdio.h>

int main() {
    int a[100];
    int c[100];
    int n = 0;
    // Read input until EOF or newline
    while (scanf("%d", &a[n]) == 1) {
        n++;
        if (getchar() == '\n') break;
    }

    // Counting: for each a[i], count the number of elements less than a[i]
    for (int i = 0; i < n; i++) {
        c[i] = 0;
        for (int j = 0; j < n; j++) {
            if (a[j] < a[i]) {
                c[i]++;
            }
        }
    }

    // Output c[]
    for (int i = 0; i < n; i++) {
        printf("%d", c[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
