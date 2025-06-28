#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 110

int adj[MAXN][MAXN];
int n; // current number of vertices

void print_adj() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d", adj[i][j]);
            if (j != n - 1) printf(" ");
        }
        printf("\n");
    }
}

void InsertVex(int v) {
    // Insert new vertex at position v
    // Shift rows and columns >= v down/right
    for (int i = n; i > v; --i) {
        for (int j = 0; j < n; ++j)
            adj[i][j] = adj[i-1][j];
    }
    for (int j = n; j > v; --j) {
        for (int i = 0; i < n + 1; ++i)
            adj[i][j] = adj[i][j-1];
    }
    // Set new row and column to 0
    for (int i = 0; i < n+1; ++i) adj[v][i] = adj[i][v] = 0;
    n++;
}

void InsertArc(int v, int w) {
    if (v >= 0 && v < n && w >= 0 && w < n) {
        adj[v][w] = adj[w][v] = 1;
    }
}

void DeleteArc(int v, int w) {
    if (v >= 0 && v < n && w >= 0 && w < n) {
        adj[v][w] = adj[w][v] = 0;
    }
}

void DeleteVex(int v) {
    // Remove row v and column v
    for (int i = v; i < n-1; ++i) {
        for (int j = 0; j < n; ++j)
            adj[i][j] = adj[i+1][j];
    }
    for (int j = v; j < n-1; ++j) {
        for (int i = 0; i < n-1; ++i)
            adj[i][j] = adj[i][j+1];
    }
    n--;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &adj[i][j]);
    char op[10];
    while (scanf("%s", op) != EOF) {
        if (strcmp(op, "IV") == 0) {
            int v;
            scanf("%d", &v);
            InsertVex(v);
        } else if (strcmp(op, "IA") == 0) {
            int v, w;
            scanf("%d%d", &v, &w);
            InsertArc(v, w);
        } else if (strcmp(op, "DV") == 0) {
            int v;
            scanf("%d", &v);
            DeleteVex(v);
        } else if (strcmp(op, "DA") == 0) {
            int v, w;
            scanf("%d%d", &v, &w);
            DeleteArc(v, w);
        }
    }
    print_adj();
    return 0;
}
