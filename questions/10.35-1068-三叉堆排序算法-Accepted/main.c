#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000

// Swap two integers
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Heapify a ternary heap with root at index i in array arr of size n
void ternary_heapify(int arr[], int n, int i) {
    int largest = i;
    int c1 = 3 * i + 1;
    int c2 = 3 * i + 2;
    int c3 = 3 * i + 3;

    if (c1 < n && arr[c1] > arr[largest]) largest = c1;
    if (c2 < n && arr[c2] > arr[largest]) largest = c2;
    if (c3 < n && arr[c3] > arr[largest]) largest = c3;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        ternary_heapify(arr, n, largest);
    }
}

// Build a ternary heap from array arr of size n
void build_ternary_heap(int arr[], int n) {
    for (int i = (n - 2) / 3; i >= 0; i--) {
        ternary_heapify(arr, n, i);
    }
}

// Ternary heap sort
void ternary_heapsort(int arr[], int n) {
    build_ternary_heap(arr, n);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]); // Move current root to end
        ternary_heapify(arr, i, 0); // Heapify reduced heap
    }
}

// Read integers from a line
int read_input(int arr[]) {
    char line[4096];
    if (!fgets(line, sizeof(line), stdin)) return 0;
    int n = 0;
    char *token = strtok(line, " \t\r\n");
    while (token && n < MAXN) {
        arr[n++] = atoi(token);
        token = strtok(NULL, " \t\r\n");
    }
    return n;
}

int main() {
    int arr[MAXN];
    int n = read_input(arr);

    ternary_heapsort(arr, n);

    for (int i = 0; i < n; ++i) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;
}

/*
时间复杂度分析：
- 构建三元堆的时间复杂度为 O(n)，与二元堆类似。
- 排序阶段的每次堆化操作都需要 O(log₃ n) 的时间复杂度，并且会被调用 n 次。
- 因此，总复杂度为 O(n log₃ n)。
*/
