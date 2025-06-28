#include <stdio.h>
#include <ctype.h>

#define MAX_N 1000

int get_number() {
    int c;
    int result = 0;

    while ((c = getchar()) != EOF && !isdigit(c) && c != '-');

    if (c == EOF) {
        return 0;
    }
    
    int sign = 1;
    if (c == '-') {
        sign = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        result = result * 10 + c - '0';
        c = getchar();
    }
    return result * sign;
}

int main() {
    int result = 0;

    // Input x_0 and n
    int x_0, n;
    scanf("%d %d", &x_0, &n);

    // Input a_i (i = 0 to n, -1000 < a_i < 1000)
    int a[MAX_N] = {0};
    for (int i = 0; i <= n; ++i) {
        a[i] = get_number();
    }

    for (int j = n; j >= 0; --j) {
        result = result * x_0 + a[j];
    }

    printf("%d\n", result);
}