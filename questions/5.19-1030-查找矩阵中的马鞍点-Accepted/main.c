#include <stdio.h>
#include <stdlib.h>

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

    int* row_min = (int *)malloc(n * sizeof(int));
    int* col_max = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < n; i++) {
        row_min[i] = matrix[i][0];
        for (int j = 1; j < m; j++) {
            if (matrix[i][j] < row_min[i]) {
                row_min[i] = matrix[i][j];
            }
        }
    }

    for (int j = 0; j < m; j++) {
        col_max[j] = matrix[0][j];
        for (int i = 1; i < n; i++) {
            if (matrix[i][j] > col_max[j]) {
                col_max[j] = matrix[i][j];
            }
        }
    }

    int flag = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == row_min[i] && matrix[i][j] == col_max[j]) {
                if (flag == 0) {
                    printf("%d", matrix[i][j]);
                    flag++;
                } else {
                    printf(" %d", matrix[i][j]);
                }
            }
        }
    }

    free(row_min);
    free(col_max);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}