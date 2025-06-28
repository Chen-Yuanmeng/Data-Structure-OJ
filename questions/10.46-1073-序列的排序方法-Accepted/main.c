#include <stdio.h>
#include <stdlib.h>

// Suppose each record has a key and a lot of heavy data
typedef struct {
    int key;
    // char data[10000]; // simulated heavy payload (not used in the sort)
} Record;

// For indirection sorting
typedef struct {
    int key;
    int idx; // original index of the record in b
} KeyIndex;

// Comparison function for qsort
int cmp_keyindex(const void *a, const void *b) {
    const KeyIndex *ka = (const KeyIndex *)a;
    const KeyIndex *kb = (const KeyIndex *)b;
    return (ka->key - kb->key);
}

int main() {
    int n;
    // Read number of records
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    Record *b = (Record *)malloc(n * sizeof(Record));
    if (!b) return 1;

    // Read records into b
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &b[i].key) != 1) {
            free(b);
            return 1;
        }
    }

    // Prepare auxiliary array of keys and their indices
    KeyIndex *arr = (KeyIndex *)malloc(n * sizeof(KeyIndex));
    if (!arr) {
        free(b);
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        arr[i].key = b[i].key;
        arr[i].idx = i;
    }

    // Sort arr by key
    qsort(arr, n, sizeof(KeyIndex), cmp_keyindex);

    // Allocate a for sorted output
    Record *a = (Record *)malloc(n * sizeof(Record));
    if (!a) {
        free(b);
        free(arr);
        return 1;
    }

    // Each record is copied only once: from b[arr[i].idx] to a[i]
    for (int i = 0; i < n; ++i) {
        a[i] = b[arr[i].idx];
    }

    // Output result
    for (int i = 0; i < n; ++i) {
        printf("%d", a[i].key);
        if (i != n - 1)
            printf(" ");
    }
    printf("\n");

    free(b);
    free(a);
    free(arr);
    return 0;
}
