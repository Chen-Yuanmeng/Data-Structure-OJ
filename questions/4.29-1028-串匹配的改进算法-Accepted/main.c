#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int main() {
    int n, m;
    char a[MAX], b[MAX];

    scanf("%d %d", &n, &m);
    getchar();
    for (int i = 0; i < n; i++) {
        scanf("%c", &a[i]);
    }
    a[n] = '\0';
    getchar();
    for (int i = 0; i < m; i++) {
        scanf("%c", &b[i]);
    }
    b[m] = '\0';

    int i, j;

    for (i = 0; i < n - m + 1; ++i) {
        for (j = 0; j < m; ++j) {
            if (a[i + j] == b[j]) {
            }
            else {
                break;
            }
        }

        // match found
        if (j == m) {
            printf("%d", i);
            return 0;
        }
    }
    printf("-1");

    return 0;
}