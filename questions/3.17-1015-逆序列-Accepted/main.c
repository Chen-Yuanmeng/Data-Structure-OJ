#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int main() {
    char s[MAX_SIZE];
    scanf("%s", s);
    int len_s = strlen(s);
    int index = 0;
    int to_put_0 = -1;
    int to_put_1 = -1;
    char* s1 = s;
    char* s2 = NULL;
    while (s[index] != '\0') {
        if (s[index] == '&') {
            to_put_0 = index;
        }
        else if (s[index] == '@') {
            to_put_1 = index;
        }
        index++;
    }
    if (to_put_0 == -1 || to_put_1 == -1) {
        printf("0\n");
        return 0;
    }
    if (to_put_1 != 2 * to_put_0 + 1) {
        printf("0\n");
        return 0;
    }
    if (len_s != to_put_1 + 1) {
        printf("0\n");
        return 0;
    }

    s[to_put_0] = '\0';
    s[to_put_1] = '\0';
    s2 = s + to_put_0 + 1;

    // Reverse s2
    int len = strlen(s2);
    for (int i = 0; i < len / 2; i++) {
        char temp = s2[i];
        s2[i] = s2[len - i - 1];
        s2[len - i - 1] = temp;
    }

    // Compare s1 and s2
    if (strcmp(s1, s2) == 0) {
        printf("1\n");
    } else {
        printf("0\n");
    }
}
