#include <stdio.h>
#include <stdlib.h>

typedef struct ThreadedNode {
    int key;
    struct ThreadedNode *left, *right;
    int ltag, rtag; // 0: child, 1: thread
} ThreadedNode;

// Insert into normal BST
ThreadedNode* insert(ThreadedNode* root, int key) {
    if (!root) {
        ThreadedNode* node = (ThreadedNode*)malloc(sizeof(ThreadedNode));
        node->key = key;
        node->left = node->right = NULL;
        node->ltag = node->rtag = 0;
        return node;
    }
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    // Ignore duplicates
    return root;
}

// Create inorder successor threads
void createThreads(ThreadedNode* root, ThreadedNode** pre) {
    if (!root) return;
    createThreads(root->left, pre);
    if (!root->left) {
        root->ltag = 1;
        root->left = *pre;
    }
    if (*pre && !(*pre)->right) {
        (*pre)->rtag = 1;
        (*pre)->right = root;
    }
    *pre = root;
    createThreads(root->right, pre);
}

// Find the leftmost node
ThreadedNode* leftmost(ThreadedNode* root) {
    if (!root) return NULL;
    while (root->ltag == 0 && root->left)
        root = root->left;
    return root;
}

// Threaded inorder traversal with range
void printInRange(ThreadedNode* root, int a, int b) {
    ThreadedNode* cur = leftmost(root);
    int first = 1;
    while (cur) {
        if (cur->key > a && cur->key < b) {
            if (!first) printf(" ");
            printf("%d", cur->key);
            first = 0;
        }
        // Move to inorder successor
        if (cur->rtag == 1)
            cur = cur->right;
        else
            cur = leftmost(cur->right);
    }
    printf("\n");
}

int main() {
    // Read first line (keys in inorder)
    int keys[100], n = 0;
    char buf[2048], *p;
    fgets(buf, sizeof(buf), stdin);
    p = buf;
    while (sscanf(p, "%d", &keys[n]) == 1) {
        char* next_space = p;
        while (*next_space && *next_space != ' ' && *next_space != '\n') next_space++;
        while (*next_space == ' ') next_space++;
        p = next_space;
        n++;
    }
    // Read a and b
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    // Reconstruct BST from inorder sequence
    ThreadedNode* root = NULL;
    for (int i = 0; i < n; ++i)
        root = insert(root, keys[i]);

    // Create threads
    ThreadedNode* pre = NULL;
    createThreads(root, &pre);

    // Output values in (a, b)
    printInRange(root, a, b);

    return 0;
}
