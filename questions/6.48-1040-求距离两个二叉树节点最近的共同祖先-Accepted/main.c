#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Binary tree node structure
typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;  // Parent pointer for upward traversal
} TreeNode;

// Create a new node
TreeNode* createNode(char data, TreeNode* parent) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        exit(0);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}

// Build tree from preorder sequence
TreeNode* buildTree(char* seq, int* index, TreeNode* parent) {
    // Return NULL for end of sequence or empty node marker
    if (seq[*index] == '\0' || seq[*index] == '^') {
        if (seq[*index] == '^') {
            (*index)++;  // Skip '^' symbol
        }
        return NULL;
    }
    
    // Create current node
    TreeNode* root = createNode(seq[*index], parent);
    (*index)++;
    
    // Recursively build left and right subtrees
    root->left = buildTree(seq, index, root);
    root->right = buildTree(seq, index, root);
    
    return root;
}

// Find node with specific value
TreeNode* findNode(TreeNode* root, char target) {
    if (root == NULL) return NULL;
    if (root->data == target) return root;
    
    TreeNode* leftResult = findNode(root->left, target);
    if (leftResult != NULL) return leftResult;
    
    return findNode(root->right, target);
}

// Check if one node is ancestor of another
int isAncestor(TreeNode* ancestor, TreeNode* descendant) {
    if (descendant == NULL || ancestor == NULL) return 0;
    if (ancestor == descendant) return 1;
    
    TreeNode* current = descendant->parent;
    while (current != NULL) {
        if (current == ancestor) return 1;
        current = current->parent;
    }
    
    return 0;
}

// Find lowest common ancestor of two nodes
TreeNode* findLowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // If p is ancestor of q, return p's parent (per requirement)
    if (isAncestor(p, q)) {
        // If p is root, return p
        if (p->parent == NULL) return p;
        return p->parent;
    }
    
    // If q is ancestor of p, return q's parent (per requirement)
    if (isAncestor(q, p)) {
        // If q is root, return q
        if (q->parent == NULL) return q;
        return q->parent;
    }
    
    // Search upward from p
    TreeNode* parent = p;
    while (parent != NULL) {
        // For each p ancestor, check if it's also q's ancestor
        TreeNode* qParent = q;
        while (qParent != NULL) {
            if (qParent == parent) {
                return qParent;  // Found LCA
            }
            qParent = qParent->parent;
        }
        parent = parent->parent;
    }
    
    return NULL;  // Should not happen
}

// Free tree memory
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char preOrderSeq[1000];
    char p_char, q_char;
    
    // Read preorder sequence
    scanf("%s", preOrderSeq);
    
    // Read target nodes
    scanf(" %c %c", &p_char, &q_char);
    
    // Build binary tree
    int index = 0;
    TreeNode* root = buildTree(preOrderSeq, &index, NULL);
    
    // Find p and q nodes
    TreeNode* p_node = findNode(root, p_char);
    TreeNode* q_node = findNode(root, q_char);
    
    if (p_node == NULL || q_node == NULL) {
        freeTree(root);
        return 0;
    }
    
    // Find lowest common ancestor
    TreeNode* lca = findLowestCommonAncestor(root, p_node, q_node);
    
    // Print result
    printf("%c\n", lca->data);
    
    // Free memory
    freeTree(root);
    
    return 0;
}
