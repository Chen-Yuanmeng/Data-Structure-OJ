#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100

// Definition of a binary search tree node
typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

// Insert a value into BST
Node* insert(Node* root, int val) {
    if (!root) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->val = val;
        node->left = node->right = NULL;
        return node;
    }
    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Recursively output values >= x in descending order
void print_desc_ge_x(Node* root, int x) {
    if (!root) return;
    // Traverse right subtree first for descending order
    print_desc_ge_x(root->right, x);
    if (root->val >= x)
        printf("%d ", root->val);
    // Only traverse left if there could be larger or equal values
    if (root->val >= x)
        print_desc_ge_x(root->left, x);
}

// Free the BST
void free_tree(Node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// Read a line of integers into arr, set *n to count. Returns 1 if line read, 0 otherwise.
int read_line_ints(int arr[], int *n) {
    char buf[1024];
    if (!fgets(buf, sizeof(buf), stdin))
        return 0;
    *n = 0;
    char *token = strtok(buf, " \n\r");
    while (token) {
        arr[(*n)++] = atoi(token);
        token = strtok(NULL, " \n\r");
    }
    return 1;
}

int main() {
    int arr[MAXN], n = 0, x;
    // Read first line: BST elements
    if (!read_line_ints(arr, &n) || n == 0)
        return 0;
    // Build BST
    Node* root = NULL;
    for (int i = 0; i < n; ++i)
        root = insert(root, arr[i]);
    // Read x
    if (scanf("%d", &x) != 1) {
        free_tree(root);
        return 0;
    }
    // Output results
    print_desc_ge_x(root, x);
    printf("\n");
    free_tree(root);
    return 0;
}
