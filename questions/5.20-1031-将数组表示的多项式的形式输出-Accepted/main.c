#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

void print_term(int coeff, int i, int j) {
    if (coeff == 0) return; // Skip zero coefficients
    if (coeff == 1) {
        // skip
    } else {
        printf("%d", coeff);
    }
    
    if (i > 0) {
        printf("xE%d", i);
    }
    if (j > 0) {
        printf("yE%d", j);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    // n: number of rows, m: number of columns

    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(m * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int flag = 1;

    // For matrix[i][j] = c, it means c x^i y^j
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (matrix[i][j] != 0) {
                if (flag) {
                    print_term(matrix[i][j], i, j);
                    flag = 0;
                } else {
                    printf("+");
                    print_term(matrix[i][j], i, j);
                }
            }
        }
    }
    if (flag) {
        printf("0");
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;

}