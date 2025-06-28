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
int check(int* T, int* L, int* R, int u, int v) {
    int flag = 0;
    int parent = u;

    while (parent != 0) {
        parent = T[parent];
        if (parent == v) {
            flag = 1;
            break;
        }
    }
    
    return flag;
}

int main() {
    int T[MAX];
    int L[MAX];
    int R[MAX];
    read_array(T);
    read_array(L);
    read_array(R);

    int u, v;
    scanf("%d %d", &u, &v);
    printf("%d\n", check(T, L, R, u, v));
    return 0;
}
