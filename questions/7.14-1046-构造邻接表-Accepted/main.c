#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXV 110   // Maximum number of vertices
#define MAXE 10010 // Maximum number of edges

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *next;
} ArcNode;

typedef struct {
    int data;
    ArcNode *firstarc;
} VNode;

VNode adjlist[MAXV];
int vnum, anum;
int vbase = 1; // 0 if node index starts from 0, otherwise 1
int exist[MAXV]; // mark exist vertex
int vert[MAXV];  // map order

// Compare function for qsort (descending order)
int cmp_desc(const void *a, const void *b) {
    return (*(int *)b) - (*(int *)a);
}

// Insert in descending order into adjacency list
void insert_desc(ArcNode **head, int val) {
    ArcNode *p = *head, *prev = NULL;
    while (p && p->adjvex > val) {
        prev = p;
        p = p->next;
    }
    if (p && p->adjvex == val) return; // Avoid duplicate
    ArcNode *node = (ArcNode *)malloc(sizeof(ArcNode));
    node->adjvex = val;
    if (prev == NULL) {
        node->next = *head;
        *head = node;
    } else {
        node->next = prev->next;
        prev->next = node;
    }
}

// Parse a single edge like "1-4"
void parse_edge(const char *str, int *from, int *to) {
    sscanf(str, "%d-%d", from, to);
}

int main() {
    char line1[256], line2[MAXE * 8];
    // Input: first line (vertex count, edge count)
    fgets(line1, sizeof(line1), stdin);
    sscanf(line1, "%d,%d", &vnum, &anum);
    // Input: second line (all edge info)
    fgets(line2, sizeof(line2), stdin);

    // Preprocessing: split all edge definitions
    char *edges[MAXE];
    int edge_from[MAXE], edge_to[MAXE];
    int edge_cnt = 0, minidx = 1000000;
    char *token = strtok(line2, ",\n\r");
    while (token && edge_cnt < anum) {
        edges[edge_cnt++] = token;
        int f, t;
        parse_edge(token, &f, &t);
        edge_from[edge_cnt - 1] = f;
        edge_to[edge_cnt - 1] = t;
        if (f < minidx) minidx = f;
        if (t < minidx) minidx = t;
        token = strtok(NULL, ",\n\r");
    }
    // Decide if node index starts from 0 or 1
    if (minidx == 0) vbase = 0;
    else vbase = 1;

    // Build adjacency list
    for (int i = 0; i < vnum; ++i) {
        adjlist[i].data = i + vbase;
        adjlist[i].firstarc = NULL;
        exist[i + vbase] = 1; // Mark exist
        vert[i] = i + vbase;
    }
    // Insert edges
    for (int i = 0; i < edge_cnt; ++i) {
        int from = edge_from[i], to = edge_to[i];
        insert_desc(&adjlist[from - vbase].firstarc, to);
        exist[from] = exist[to] = 1;
    }

    // Output adjacency list as specified
    for (int i = 0; i < vnum; ++i) {
        int id = vert[i];
        printf("%d", id);
        ArcNode *p = adjlist[id - vbase].firstarc;
        if (p) printf(" ");
        int first = 1;
        while (p) {
            if (!first) printf(",");
            printf("%d", p->adjvex);
            first = 0;
            p = p->next;
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < vnum; ++i) {
        ArcNode *p = adjlist[i].firstarc;
        while (p) {
            ArcNode *tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    return 0;
}
