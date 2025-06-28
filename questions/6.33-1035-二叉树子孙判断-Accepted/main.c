#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void read_array(int* arr) {
    char line[MAX];
    fgets(line, sizeof(line), stdin);
    char* token = strtok(line, " ");
    int i = 0;
    while (token != NULL) {
        arr[i++] = atoi(token);
        token = strtok(NULL, " ");
    }
    arr[i] = -1;  // Mark the end of the array
}


// 检查u是否为v的子孙
int check(int* L, int* R, int u, int v) {
    if (L[v] <= 0 || R[v] <= 0) {
        return 0;
    }

    if (L[v] == u || R[v] == u) {
        return 1;
    }
    return (check(L, R, u, L[v]) || check (L, R, u, R[v]));
}

int main() {
    int L[MAX];
    int R[MAX];
    read_array(L);
    read_array(R);

    int u, v;
    scanf("%d %d", &u, &v);
    printf("%d\n", check(L, R, u, v));
    return 0;
}
