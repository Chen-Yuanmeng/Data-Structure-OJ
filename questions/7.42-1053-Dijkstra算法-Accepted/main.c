#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_V 105
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

Edge* adj[MAX_V];
int dist[MAX_V];
int vis[MAX_V];
int n, src;

void add_edge(int from, int to, int weight) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->weight = weight;
    e->next = adj[from];
    adj[from] = e;
}

void dijkstra(int s) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
        vis[i] = 0;
    }
    dist[s] = 0;

    for (int i = 1; i <= n; ++i) {
        int u = -1, minD = INF;
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && dist[j] < minD) {
                minD = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (Edge* e = adj[u]; e; e = e->next) {
            int v = e->to;
            if (!vis[v] && dist[u] + e->weight < dist[v]) {
                dist[v] = dist[u] + e->weight;
            }
        }
    }
}

int main() {
    // Input: first line n src
    if (scanf("%d %d", &n, &src) != 2)
        return 1;

    // Input: edge lines "u-v w"
    int u, v, w;
    char line[100];
    while (scanf("%s", line) == 1) {
        if (sscanf(line, "%d-%d", &u, &v) != 2)
            continue;
        if (scanf("%d", &w) != 1)
            continue;
        add_edge(u, v, w);
    }

    dijkstra(src);

    // Output: shortest distances from src to 1..n (excluding src), in order
    int first = 1;
    for (int i = 1; i <= n; ++i) {
        if (i == src) continue;
        if (!first) printf(",");
        printf("%d", dist[i] == INF ? -1 : dist[i]);
        first = 0;
    }
    printf("\n");

    // Cleanup
    for (int i = 1; i <= n; ++i) {
        Edge* e = adj[i];
        while (e) {
            Edge* nxt = e->next;
            free(e);
            e = nxt;
        }
    }
    return 0;
}
