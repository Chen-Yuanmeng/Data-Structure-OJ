#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

// Function to get maximum value in arr[]
int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to the digit represented by exp.
void countingSort(int arr[], int n, int exp) {
    int output[MAX_SIZE]; // output array
    int count[10] = {0};

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains the actual position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array (stable sort, so iterate backwards)
    for (int i = n - 1; i >= 0; i--) {
        int d = (arr[i] / exp) % 10;
        output[count[d] - 1] = arr[i];
        count[d]--;
    }

    // Copy the output array to arr[], so that arr[] now contains sorted numbers according to current digit
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using Radix Sort
void radixSort(int arr[], int n) {
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead of passing digit number, exp is passed.
    for (int exp = 1; m / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}

int main() {
    int arr[MAX_SIZE];
    int n = 0;

    // Read input until newline or EOF
    while (scanf("%d", &arr[n]) == 1) {
        n++;
        if (getchar() == '\n') break;
    }

    radixSort(arr, n);

    // Output sorted array
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;
}
