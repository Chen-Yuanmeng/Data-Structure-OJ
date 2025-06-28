#include <stdio.h>


int F(int n) {
    if (n == 0) {
        return 1;
    }

    int result = 1;
    int new_n = n;

    while (new_n > 0) {
        result *= new_n;
        new_n /= 2;
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", F(n));
    return 0;
}
