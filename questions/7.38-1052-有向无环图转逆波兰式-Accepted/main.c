#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 20

// 定义邻接表中的节点结构
struct ListNode {
    char vertex;
    struct ListNode *next;
};

// 定义图结构
struct Graph {
    int numVertices;
    struct ListNode *adjLists[MAX_VERTICES];
};

// 创建邻接表中的节点
struct ListNode *
createListNode(char v) {
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 创建图
struct Graph *
createGraph(int vertices) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; ++i) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// 添加边
void addEdge(struct Graph *graph, int src, char dest) {
    // 添加从src到dest的边
    struct ListNode *newNode = createListNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void Transverse(struct Graph *graph, char *res, int m, int *i) {
    if (graph->adjLists[m]->vertex <= 'z' && graph->adjLists[m]->vertex >= 'a') {
        res[*i] = graph->adjLists[m]->vertex;
        (*i)++;
    }
    else {
        Transverse(graph, res, graph->adjLists[m]->vertex - '0', i);
        Transverse(graph, res, graph->adjLists[m]->next->vertex - '0', i);
        res[*i] = graph->adjLists[m]->next->next->vertex;
        (*i)++;
    }
}

int main() {
    int v;
    scanf("%d\n", &v);
    // 创建图
    struct Graph *graph = createGraph(v);

    for (int i = 0; i < v; i++) {
        char c, ch;
        do {
            scanf("%c%c", &ch, &c);
            addEdge(graph, i, ch);
        } while (c != '\n');
    }

    char res[100];

    int k = 0;
    int *p = &k;

    Transverse(graph, res, 0, p);

    res[*p] = '\0';

    printf("%s", res);

    return 0;
}
