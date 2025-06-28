#include <stdio.h>

#define MAXN 1000

// Swap two integers
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Sort 2 or 3 elements directly via comparison
void small_sort(int arr[], int left, int right) {
    int n = right - left + 1;
    if (n <= 1) return;
    if (n == 2) {
        if (arr[left] > arr[right]) {
            swap(&arr[left], &arr[right]);
        }
    } else if (n == 3) {
        if (arr[left] > arr[left+1]) swap(&arr[left], &arr[left+1]);
        if (arr[left+1] > arr[right]) swap(&arr[left+1], &arr[right]);
        if (arr[left] > arr[left+1]) swap(&arr[left], &arr[left+1]);
    }
}

// Partition function, returns pivot index
int partition(int arr[], int left, int right) {
    int pivot = arr[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && arr[j] >= pivot) j--;
        if (i < j) arr[i++] = arr[j];
        while (i < j && arr[i] <= pivot) i++;
        if (i < j) arr[j--] = arr[i];
    }
    arr[i] = pivot;
    return i;
}

typedef struct {
    int l, r;
} StackNode;

int main() {
    int arr[MAXN], n = 0;
    // Read input
    while (scanf("%d", &arr[n]) == 1) n++;

    // Non-recursive quicksort using stack
    StackNode stack[MAXN];
    int top = -1;
    // push the whole range
    if (n > 1) {
        stack[++top] = (StackNode){0, n-1};
    }

    while (top >= 0) {
        StackNode cur = stack[top--];
        int l = cur.l, r = cur.r;
        if (r - l + 1 <= 3) {
            small_sort(arr, l, r);
            continue;
        }
        int p = partition(arr, l, r);

        // left: l ~ p-1, right: p+1 ~ r
        int lenL = p - l;
        int lenR = r - p;
        // Always process the shorter segment first
        if (lenL < lenR) {
            // Push the longer segment first (right), so shorter (left) is processed next
            if (lenR > 0) stack[++top] = (StackNode){p+1, r};
            if (lenL > 0) stack[++top] = (StackNode){l, p-1};
        } else {
            if (lenL > 0) stack[++top] = (StackNode){l, p-1};
            if (lenR > 0) stack[++top] = (StackNode){p+1, r};
        }
    }

    // Output
    for (int i = 0; i < n; ++i) {
        if (i) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;
}
