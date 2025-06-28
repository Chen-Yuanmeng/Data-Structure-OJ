#include <stdio.h>
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

void print_array(int* arr) {
    for (int i = 0; arr[i] != -1; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}

int main() {
    int left[MAX], right[MAX];
    read_array(left);
    read_array(right);

    print_array(right);
    print_array(left);
}
