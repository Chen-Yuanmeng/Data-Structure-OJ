#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

typedef struct {
    int key;
    int lidx, ridx;
} RawNode;

Node* build_tree(RawNode *raw, int idx, Node **nodes, int n) {
    if (idx < 0 || idx >= n) return NULL;
    if (nodes[idx] != NULL) return nodes[idx];
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = raw[idx].key;
    node->left = build_tree(raw, raw[idx].lidx, nodes, n);
    node->right = build_tree(raw, raw[idx].ridx, nodes, n);
    nodes[idx] = node;
    return node;
}

// Inorder traversal, returns 1 if BST, 0 otherwise. prev is pointer to last visited key.
int inorder(Node *root, int *prev, int *valid) {
    if (!root || !(*valid)) return 1;
    inorder(root->left, prev, valid);
    if (root->key <= *prev) {
        *valid = 0;
        return 0;
    }
    *prev = root->key;
    inorder(root->right, prev, valid);
    return *valid;
}

int main() {
    RawNode raw[MAX_NODES];
    Node *nodes[MAX_NODES] = {0};
    int n = 0;
    int key, lidx, ridx;
    // Read all input nodes
    while (scanf("%d %d %d", &key, &lidx, &ridx) == 3) {
        raw[n].key = key;
        raw[n].lidx = lidx;
        raw[n].ridx = ridx;
        n++;
    }
    if (n == 0) {
        printf("1\n"); // Empty tree is BST
        return 0;
    }
    // Build the tree from the first node (index 0)
    Node *root = build_tree(raw, 0, nodes, n);

    int prev = -2147483648; // INT_MIN
    int valid = 1;
    inorder(root, &prev, &valid);

    printf("%d\n", valid ? 1 : 0);

    // Free memory
    for (int i = 0; i < n; i++) {
        if (nodes[i]) free(nodes[i]);
    }
    return 0;
}
