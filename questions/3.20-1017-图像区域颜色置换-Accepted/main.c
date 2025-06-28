#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_MAX 256

void dye(int** map, int x, int y, int row, int col) {
    // Check if the coordinates are out of bounds
    if (x < 0 || x >= row || y < 0 || y >= col) {
        return;
    }

    // Check if the current cell is 1
    if (map[x][y] != 1) {
        return;
    }

    // If the current cell is 1, change it to 2
    map[x][y] = 2;

    // Recursively call the function for the adjacent cells
    dye(map, x - 1, y, row, col); // Up
    dye(map, x + 1, y, row, col); // Down
    dye(map, x, y - 1, row, col); // Left
    dye(map, x, y + 1, row, col); // Right

    return;
}



int main() {
    int row, col, start_x, start_y, first_direction;
    scanf("%d %d %d %d %d\n", &row, &col, &start_x, &start_y, &first_direction);

    char row_char[ROW_MAX];

    int** map = (int**)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++) {
        map[i] = (int*)malloc(col * sizeof(int));
    }

    for (int i = 0; i < row; i++) {
        fgets(row_char, sizeof(row_char), stdin);
        char* p = strtok(row_char, " \n");
        for (int j = 0; j < col; j++) {
            map[i][j] = atoi(p);
            p = strtok(NULL, " \n");
        }
    }

    dye(map, start_x, start_y, row, col);

    // Print the map
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
}
