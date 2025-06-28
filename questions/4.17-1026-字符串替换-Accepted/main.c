#include <stdio.h>
#include <string.h>

#define MAX 1000

int main() {
    char s[MAX], t[MAX], v[MAX];
    scanf("%s %s %s", s, t, v);

    // Replace t in s with v
    char *pos = strstr(s, t);
    if (pos != NULL) {
        // Found t in s, replace it with v
        char temp[MAX];
        strncpy(temp, s, pos - s);
        temp[pos - s] = '\0';
        strcat(temp, v);
        strcat(temp, pos + strlen(t));
        strcpy(s, temp);
    }

    printf("%s\n", s);
    return 0;
}