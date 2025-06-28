#include <stdio.h>
#include <ctype.h>

#define ARR_LENGTH 101
#define MAX_LENGTH 1000


int main() {
    int n, i = 0, p = 0;
    int a[ARR_LENGTH];
    char input[MAX_LENGTH];

    scanf("%1000[^\n]", input);

    // number to insert
    scanf("%d", &n);

    // parse input
    for (; i < ARR_LENGTH; ++i) {
        if (input[p] == '\0') {
            break;
        }

        a[i] = 0;
        while (isdigit(input[p])) {
            a[i] = 10 * a[i] + (input[p] - '0');
            ++p;
        }

        if (input[p] == ' ') {
            ++p;
        }

        if (input[p] == '\0') {
            break;
        }
    }
    ++i;

    // insert number
    int j, s;
    for (j = 0; j < i; ++j) {
        if (a[j] > n) {
            break;
        }
    }
    for (; j < i; ++j) {
        s = a[j];
        a[j] = n;
        n = s;
    }
    a[j] = n;

    for (j = 0; j < i; ++j) {
        printf("%d ", a[j]);
    }
    printf("%d", a[j]);
}
