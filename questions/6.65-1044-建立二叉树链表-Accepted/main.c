#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char val;
    struct Node *left, *right;
} Node;

int find_root(char* inorder, int in_l, int in_r, char root) {
    for (int i = in_l; i <= in_r; ++i) {
        if (inorder[i] == root) return i;
    }
    return -1;
}

Node* build(char* preorder, int pre_l, int pre_r, char* inorder, int in_l, int in_r) {
    if (pre_l > pre_r || in_l > in_r) return NULL;
    Node* root = (Node*)malloc(sizeof(Node));
    root->val = preorder[pre_l];
    root->left = root->right = NULL;
    int k = find_root(inorder, in_l, in_r, preorder[pre_l]);
    int left_num = k - in_l;
    root->left = build(preorder, pre_l + 1, pre_l + left_num, inorder, in_l, k - 1);
    root->right = build(preorder, pre_l + left_num + 1, pre_r, inorder, k + 1, in_r);
    return root;
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    putchar(root->val);
}

void free_tree(Node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    char preorder[101], inorder[101];
    if (scanf("%100s", preorder) != 1) return 1;
    if (scanf("%100s", inorder) != 1) return 1;
    int n = strlen(preorder);
    Node* root = build(preorder, 0, n - 1, inorder, 0, n - 1);
    postorder(root);
    putchar('\n');
    free_tree(root);
    return 0;
}
