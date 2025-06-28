#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100

// 邻接表节点
typedef struct ArcNode {
    int adjvex;
    struct ArcNode *next;
} ArcNode;

// 顶点表结点
typedef struct VNode {
    ArcNode *first;
} VNode;

// 图结构
typedef struct {
    VNode adjList[MAX_VERTICES];
    int vexnum;
} ALGraph;

// 创建邻接表并初始化
void InitGraph(ALGraph *G, int n) {
    G->vexnum = n;
    for (int i = 0; i < n; ++i) {
        G->adjList[i].first = NULL;
    }
}

// 插入边, 顶点编号从1开始
void InsertEdge(ALGraph *G, int from, int to) {
    ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = to - 1; // 0-based index
    p->next = G->adjList[from - 1].first;
    G->adjList[from - 1].first = p;
}

// 深度优先搜索
int found = 0;
void DFS(ALGraph *G, int v, int j, int *visited) {
    if (v == j) { found = 1; return; }
    visited[v] = 1;
    for (ArcNode *p = G->adjList[v].first; p; p = p->next) {
        if (!visited[p->adjvex]) {
            DFS(G, p->adjvex, j, visited);
            if (found) return;
        }
    }
}

int main() {
    int n;
    char edges[1024], *token;
    int i, j;

    // 读取节点数量
    if (scanf("%d\n", &n) != 1) return 1;
    InitGraph(&((ALGraph){0}), 0); // just to avoid unused warning

    // 读取边
    fgets(edges, sizeof(edges), stdin);
    size_t len = strlen(edges);
    if (edges[len-1] == '\n') edges[len-1] = 0;

    // 创建图
    ALGraph G;
    InitGraph(&G, n);

    token = strtok(edges, ",");
    while (token) {
        int u, v;
        if (sscanf(token, "%d-%d", &u, &v) == 2)
            InsertEdge(&G, u, v);
        token = strtok(NULL, ",");
    }

    // 读取i, j
    int si, sj;
    scanf("%d,%d", &si, &sj);
    if (si == sj) { printf("no\n"); return 0; }
    int visited[MAX_VERTICES] = {0};
    found = 0;
    DFS(&G, si-1, sj-1, visited);
    printf(found ? "yes\n" : "no\n");
    return 0;
}
