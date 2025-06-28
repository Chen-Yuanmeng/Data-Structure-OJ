#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

int in(char c, char* str) {
    if (strlen(str) == 0) {
        return 0;
    }
    for (int i = 0; i < strlen(str); i++) {
        if (c == str[i]) {
            return 1;
        }
    }
    return 0;
}


int main() {
    char s[MAX_LENGTH];
    char t[MAX_LENGTH];

    scanf("%s %s", s, t);
    
    char new[MAX_LENGTH];
    int length_new = 0;
    int new_index[MAX_LENGTH];

    for (int i = 0; i < strlen(s); i++) {
        if (!in(s[i], t)) {
            if (!in(s[i], new)) {
                new[length_new] = s[i];
                new_index[length_new] = i;
                length_new++;
            }

        }
    }
    new[length_new] = '\0';

    if (length_new == 0) {
        printf("-1\n");
        return 0;
    }
    printf("%s ", new);
    for (int i = 0; i < length_new; i++) {
        printf("%d", new_index[i]);
    }
    printf("\n");
    return 0;
}