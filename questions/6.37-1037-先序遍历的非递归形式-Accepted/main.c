#include <stdio.h>
#define MAXN 105

// Define the binary tree node structure
typedef struct {
    char c;    // Node value
    int l, r; // Left and right child indices
} Node;

Node tree[MAXN];
int stack[MAXN];

int main() {
    int n = 0;
    // Read all node information
    while (scanf(" %c %d %d", &tree[n+1].c, &tree[n+1].l, &tree[n+1].r) == 3) {
        n++;
    }
    // Non-recursive preorder traversal
    int top = 0;
    int res[MAXN], res_cnt = 0;
    if (n == 0) return 0;
    stack[top++] = 1; // Root node index is 1
    while (top) {
        int idx = stack[--top]; // Pop the top node index
        if (idx == -1) continue; // Skip null nodes
        printf("%c", tree[idx].c); // Print node value
        res_cnt++;
        if (res_cnt < n) printf(" ");
        if (tree[idx].r != -1) stack[top++] = tree[idx].r;
        if (tree[idx].l != -1) stack[top++] = tree[idx].l;
    }
    printf("\n");
    return 0;
}
