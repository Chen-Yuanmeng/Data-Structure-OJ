#include <stdio.h>
#include <string.h>

#define MAX 1000

char str[MAX];

int cmp(int start_1, int end_1, int start_2, int end_2) {
    if (end_1 - start_1 != end_2 - start_2) {
        return 0;
    }
    for (int i = 0; i <= end_1 - start_1; i++) {
        if (str[start_1 + i] != str[start_2 + i]) {
            return 0;
        }
    }
    return 1;
}

void printstring(int start, int end) {
    for (int i = start; i <= end; i++) {
        printf("%c", str[i]);
    }
}

int main() {
    scanf("%s", str);
    int len = strlen(str);
    
    int i = len, j, k;

    for (; i >= 2; i--) {   // i = length of the substring
        for (j = 0; j <= len - i; j++) {
            for (k = j + 1; k <= len - i; k++) {
                if (cmp(j, j + i - 1, k, k + i - 1)) {
                    printstring(j, j + i - 1);
                    printf(" %d", j);
                    return 0;
                }
            }
        }
    }
    printf("-1");
    return 0;
}