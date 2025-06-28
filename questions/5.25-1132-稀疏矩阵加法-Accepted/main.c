#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 10000

int v1[MAX_SIZE], v2[MAX_SIZE];
int front1 = 0, rear1 = 0;
int front2 = 0, rear2 = 0;

// 将空格分隔的整数读入队列
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

    // 动态分配二维数组
    int **mt1 = malloc(m * sizeof(int *));
    int **mt2 = malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i) {
        mt1[i] = malloc(n * sizeof(int));
        mt2[i] = malloc(n * sizeof(int));
    }

    char line[10000];

    // 读取第一行数据到队列 v1
    if (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0'; // 去掉换行
        parse_line_to_queue(line, v1, &rear1);
    }

    // 读取 mt1 的结构
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

    // 读取第二行数据到队列 v2
    if (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0'; // 去掉换行
        parse_line_to_queue(line, v2, &rear2);
    }

    // 读取 mt2 的结构
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

    // 相加两个矩阵并重新装入 v1
    front1 = rear1 = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            mt1[i][j] += mt2[i][j];
            if (mt1[i][j]) {
                v1[rear1++] = mt1[i][j];
            }
        }
    }

    // 输出 v1 中非零元素
    if (front1 < rear1) {
        printf("%d", v1[front1++]);
        while (front1 < rear1) {
            printf(" %d", v1[front1++]);
        }
    }
    printf("\n");

    // 输出矩阵非零位置标志（1/0）
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d", mt1[i][j] ? 1 : 0);
            if (j != n - 1) printf(" ");
        }
        if (i != m - 1) printf("\n");
    }

    // 释放内存
    for (int i = 0; i < m; ++i) {
        free(mt1[i]);
        free(mt2[i]);
    }
    free(mt1);
    free(mt2);

    return 0;
}
