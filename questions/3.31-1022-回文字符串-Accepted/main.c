#include <stdio.h>
#include <string.h>

int main() {
    char s[1000];

    scanf("%s@", s);
    int len = strlen(s);

    s[len - 1] = '\0'; // Remove the '@' character
    len--;

    for (int i = 0; i < len / 2; i++) {
        if (s[i] != s[len - i - 1]) {
            printf("0\n");
            return 0;
        }
    }

    printf("1\n");
    return 0;
}