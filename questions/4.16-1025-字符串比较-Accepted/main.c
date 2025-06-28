#include <stdio.h>

int main() {
    char s[100], t[100];
    scanf("%s %s", s, t);

    int i = 0;
    while (s[i] != '\0' && t[i] != '\0') {
        if (s[i] < t[i]) {
            printf("-1");
            return 0;
        } else if (s[i] > t[i]) {
            printf("1");
            return 0;
        }
        i++;
    }
    printf("0");
    return 0;
}