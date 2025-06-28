#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100

typedef struct Node {
    int v;
    struct Node* next;
} Node;

Node* adj[MAXN];
int inDegree[MAXN];
int MPL[MAXN];
int order[MAXN];
int n;

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v = v;
    newNode->next = adj[u];
    adj[u] = newNode;
    inDegree[v]++;
}

int topologicalSort() {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; ++i)
        if (inDegree[i] == 0)
            queue[rear++] = i;

    int idx = 0;
    while (front < rear) {
        int u = queue[front++];
        order[idx++] = u;
        for (Node* p = adj[u]; p; p = p->next) {
            int v = p->v;
            inDegree[v]--;
            if (inDegree[v] == 0)
                queue[rear++] = v;
        }
    }

    return idx == n;
}

void computeLongestPaths() {
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        MPL[u] = 0;
        for (Node* p = adj[u]; p; p = p->next) {
            int v = p->v;
            if (MPL[u] < MPL[v] + 1)
                MPL[u] = MPL[v] + 1;
        }
    }
}

int main() {
    char buffer[1000];
    scanf("%d", &n);
    getchar(); // consume newline
    fgets(buffer, sizeof(buffer), stdin);

    for (int i = 1; i <= n; ++i) {
        adj[i] = NULL;
        inDegree[i] = 0;
        MPL[i] = 0;
    }

    char* token = strtok(buffer, ",");
    while (token) {
        int u, v;
        sscanf(token, "%d-%d", &u, &v);
        addEdge(u, v);
        token = strtok(NULL, ",");
    }

    if (!topologicalSort()) {
        printf("Graph has a cycle.\n");
        return 1;
    }

    computeLongestPaths();

    for (int i = 1; i <= n; ++i) {
        printf("%d", MPL[i]);
        if (i < n) printf(",");
    }
    printf("\n");

    for (int i = 1; i <= n; ++i) {
        Node* p = adj[i];
        while (p) {
            Node* tmp = p;
            p = p->next;
            free(tmp);
        }
    }

    return 0;
}
