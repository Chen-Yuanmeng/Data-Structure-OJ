#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int n;              // number of vertices
int s[MAXN * MAXN]; // successor array
int fst[MAXN];      // start index array
int lst[MAXN];      // end index array

// state: 0 = unvisited, 1 = visiting, 2 = visited
int state[MAXN];
int found_cycle = 0;

// DFS to detect cycles
void dfs(int u) {
    state[u] = 1; // mark as visiting

    // If fst[u] > lst[u], there is no successor
    if (fst[u] <= lst[u]) {
        for (int i = fst[u]; i < lst[u]; ++i) {
            int v = s[i];
            if (v < 1 || v > n) continue; // skip invalid vertices
            if (state[v] == 1) {
                found_cycle = 1;
                return;
            }
            else if (state[v] == 0) {
                dfs(v);
                if (found_cycle) return;
            }
        }
    }

    state[u] = 2; // mark as visited
}

int main() {
    // Input
    scanf("%d", &n);

    // Read s array (index 0 is dummy)
    int s_size = 0;
    char c;
    // Read the rest of the line as a string, then parse it
    while ((c = getchar()) != '\n' && c != EOF); // skip to next line
    int tmp, idx = 0;
    while (idx < MAXN * MAXN && scanf("%d", &tmp) == 1) {
        s[idx++] = tmp;
        int ch = getchar();
        if (ch == '\n' || ch == EOF) break;
    }
    s_size = idx;

    // Read fst
    for (int i = 0; i <= n; ++i) scanf("%d", &fst[i]);
    // Read lst
    for (int i = 0; i <= n; ++i) scanf("%d", &lst[i]);

    // Detect cycle
    for (int i = 1; i <= n; ++i) state[i] = 0;
    for (int i = 1; i <= n; ++i) {
        if (state[i] == 0) {
            dfs(i);
            if (found_cycle) break;
        }
    }

    printf(found_cycle ? "yes\n" : "no\n");
    return 0;
}
