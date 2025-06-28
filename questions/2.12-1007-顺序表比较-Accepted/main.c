#include <stdio.h>
#include <string.h>

#define STR_MAX 1000

int main() {
    char A[STR_MAX], B[STR_MAX];

    scanf("%1000[^\n]", A);
    scanf("\n");
    scanf("%1000[^\n]", B);

    int t = strcmp(A, B);
    if (t == 0) {}
    else if (t < 0) {
        t = 1;  // A < B
    }
    else {
        t = 2;  // A > B
    }

    printf("%d\n", t);
}