#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;

// Function to create a new TreeNode
TreeNode* createNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

// Build a BST from pre-order input with -1 as sentinel for NULL nodes
TreeNode* buildTree() {
    int val;
    if (scanf("%d", &val) != 1 || val == -1) {
        return NULL;
    }
    TreeNode* root = createNode(val);
    root->left = buildTree();
    root->right = buildTree();
    return root;
}

// Insert a node into a BST
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return createNode(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Traverse the tree in-order and insert each node into the target BST
void mergeTrees(TreeNode* root, TreeNode** target) {
    if (!root) return;
    mergeTrees(root->left, target);
    *target = insert(*target, root->val);
    mergeTrees(root->right, target);
}

// In-order traversal to print the merged BST
void inorderPrint(TreeNode* root) {
    if (!root) return;
    inorderPrint(root->left);
    printf("%d ", root->val);
    inorderPrint(root->right);
}

// Free memory of BST
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    TreeNode *tree1 = NULL, *tree2 = NULL, *merged = NULL;

    tree1 = buildTree();
    tree2 = buildTree();

    merged = tree1;
    mergeTrees(tree2, &merged);

    inorderPrint(merged);
    printf("\n");

    freeTree(merged);  // Clean up
    return 0;
}
