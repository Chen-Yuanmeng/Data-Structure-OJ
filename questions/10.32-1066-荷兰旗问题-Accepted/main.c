#include <stdio.h>

#define RED   1
#define WHITE 2
#define BLUE  3

// Function to sort the array using Dutch National Flag algorithm
void dutch_flag_sort(int arr[], int n) {
    int low = 0;        // position for RED (1)
    int mid = 0;        // current pointer
    int high = n - 1;   // position for BLUE (3)
    while (mid <= high) {
        if (arr[mid] == RED) {
            // Swap arr[low] and arr[mid], increment both pointers
            int temp = arr[low];
            arr[low] = arr[mid];
            arr[mid] = temp;
            low++;
            mid++;
        } else if (arr[mid] == WHITE) {
            // White stays in the middle
            mid++;
        } else if (arr[mid] == BLUE) {
            // Swap arr[mid] and arr[high], decrement high pointer only
            int temp = arr[mid];
            arr[mid] = arr[high];
            arr[high] = temp;
            high--;
        }
    }
}

int main() {
    int arr[1000];
    int n = 0;
    // Read input until EOF or end of line
    while (scanf("%d", &arr[n]) == 1) {
        n++;
    }

    dutch_flag_sort(arr, n);

    // Output the sorted sequence
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;
}
