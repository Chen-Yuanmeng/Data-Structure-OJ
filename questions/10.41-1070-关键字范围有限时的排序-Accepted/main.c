#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_KEY 10000

int main() {
    int n = MAX_N;
    int a[MAX_N];
    int count[MAX_KEY + 1];
    int i, num;

    // Initialize counting array
    memset(count, 0, sizeof(count));

    // Read input
    for (i = 0; i < n; ++i) {
        scanf("%d", &num);
        a[i] = num;
        count[num]++;
    }

    // Output sorted numbers
    int printed = 0;
    for (i = 0; i <= MAX_KEY; ++i) {
        while (count[i]-- > 0) {
            printf("%d", i);
            printed++;
            if (printed < n) {
                printf(" ");
            }
        }
    }
    printf("\n");
    return 0;
}
