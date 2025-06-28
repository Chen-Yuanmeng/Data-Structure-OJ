#include <stdio.h>
#include <string.h>

#define STR_MAX 1000

int main() {
    char _[STR_MAX], A[STR_MAX], B[STR_MAX];

    scanf("%1000[^\n]", _);
    scanf("\n");
    scanf("%1000[^\n]", A);
    scanf("\n");
    scanf("%1000[^\n]", B);

    printf("%s %s", B, A);
}