#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 10000

int v1[MAX_SIZE], v2[MAX_SIZE];
int front1 = 0, rear1 = 0;
int front2 = 0, rear2 = 0;

void parse_line_to_queue(char *line, int *queue, int *rear) {
    char *token = strtok(line, " ");
    while (token != NULL) {
        queue[(*rear)++] = atoi(token);
        token = strtok(NULL, " ");
    }
}

int main() {
    int m, n;
    scanf("%d%d", &m, &n);
    getchar();  // consume leftover newline

    int **mt1 = malloc(m * sizeof(int *));
    int **mt2 = malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i) {
        mt1[i] = malloc(n * sizeof(int));
        mt2[i] = malloc(n * sizeof(int));
    }

    char line[10000];

    if (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0'; // 去掉换行
        parse_line_to_queue(line, v1, &rear1);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int t;
            scanf("%d", &t);
            if (t) {
                mt1[i][j] = v1[front1++];
            } else {
                mt1[i][j] = 0;
            }
        }
        getchar();  // consume newline
    }

    if (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0'; // 去掉换行
        parse_line_to_queue(line, v2, &rear2);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int t;
            scanf("%d", &t);
            if (t) {
                mt2[i][j] = v2[front2++];
            } else {
                mt2[i][j] = 0;
            }
        }
        getchar();  // consume newline
    }

    front1 = rear1 = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            mt1[i][j] += mt2[i][j];
            if (mt1[i][j]) {
                v1[rear1++] = mt1[i][j];
            }
        }
    }

    if (front1 < rear1) {
        printf("%d", v1[front1++]);
        while (front1 < rear1) {
            printf(" %d", v1[front1++]);
        }
    }
    printf("\n");

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d", mt1[i][j] ? 1 : 0);
            if (j != n - 1) printf(" ");
        }
        if (i != m - 1) printf("\n");
    }

    for (int i = 0; i < m; ++i) {
        free(mt1[i]);
        free(mt2[i]);
    }
    free(mt1);
    free(mt2);

    return 0;
}
