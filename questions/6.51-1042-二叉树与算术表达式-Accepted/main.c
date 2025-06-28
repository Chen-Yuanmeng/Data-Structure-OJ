#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char val;
    struct Node *left;
    struct Node *right;
} Node;

const char *input;
int pos = 0;

// Create a node from the input string
Node* build_tree() {
    if (input[pos] == '\0') return NULL;
    char c = input[pos++];
    if (c == '#') return NULL;

    Node *node = (Node *)malloc(sizeof(Node));
    node->val = c;
    node->left = build_tree();
    node->right = build_tree();
    return node;
}

// Check if a character is an operator
int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// In-order traversal with parentheses where needed
void print_inorder(Node *node, int parent_prec) {
    if (!node) return;

    int need_paren = 0;
    int curr_prec = precedence(node->val);

    if (is_operator(node->val)) {
        if (curr_prec < parent_prec) {
            need_paren = 1;
            printf("(");
        }
        print_inorder(node->left, curr_prec);
        printf("%c", node->val);
        print_inorder(node->right, curr_prec + 1); // right-associativity
        if (need_paren) printf(")");
    } else {
        printf("%c", node->val);
    }
}

// Free memory
void free_tree(Node *node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main() {
    char buffer[1001];
    if (scanf("%1000s", buffer) != 1) return 1;

    input = buffer;
    pos = 0;

    Node *root = build_tree();
    print_inorder(root, 0);
    printf("\n");
    free_tree(root);

    return 0;
}
