#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX_VERTICES];
int visited[MAX_VERTICES];
int targetLength, targetVertex, found = 0;

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int u, int v) {
    Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = createNode(u);
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

void dfs(int current, int length, int destination) {
    if (length > targetLength || found)
        return;
    if (length == targetLength && current == destination) {
        found = 1;
        return;
    }

    visited[current] = 1;
    for (Node* temp = adjList[current]; temp != NULL; temp = temp->next) {
        if (!visited[temp->vertex]) {
            dfs(temp->vertex, length + 1, destination);
        }
    }
    visited[current] = 0;
}

int main() {
    int n, k;
    int start, end;
    char line[1024];

    // Read first line: number of vertices and target length
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d,%d", &n, &k);
    targetLength = k;

    // Read second line: start and end vertex
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d,%d", &start, &end);

    // Initialize adjacency list
    for (int i = 0; i <= n; i++) {
        adjList[i] = NULL;
    }

    // Read third line: edges
    fgets(line, sizeof(line), stdin);
    char* token = strtok(line, ",\n");
    while (token != NULL) {
        int u, v;
        sscanf(token, "%d-%d", &u, &v);
        addEdge(u, v);
        token = strtok(NULL, ",\n");
    }

    // DFS to find path of length k
    memset(visited, 0, sizeof(visited));
    dfs(start, 0, end);

    printf(found ? "yes\n" : "no\n");

    // Free memory
    for (int i = 1; i <= n; i++) {
        Node* temp = adjList[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }

    return 0;
}
