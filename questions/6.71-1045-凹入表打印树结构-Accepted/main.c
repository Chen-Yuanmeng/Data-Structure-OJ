#include <stdio.h>
#include <stdlib.h>

// Define the tree node structure
typedef struct TreeNode {
    char data;                // The character data
    struct TreeNode* child;   // Pointer to the first child
    struct TreeNode* sibling; // Pointer to the next sibling
} TreeNode;

// Function to create a new node
TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Function to print the tree in indented format
void printTree(TreeNode* root, int level) {
    if (root == NULL) return;
    
    // Print the current node with appropriate indentation
    for (int i = 0; i < level; i++) {
        printf("-");
    }
    printf("%c\n", root->data);
    
    // Print child subtree with increased indentation
    printTree(root->child, level + 1);
    
    // Print sibling subtree with the same indentation
    printTree(root->sibling, level);
}

int main() {
    // Define a maximum number of nodes
    #define MAX_NODES 100
    
    // Create nodes array
    TreeNode* nodes[MAX_NODES + 1]; // +1 because we're using 1-based indexing
    
    // Initialize all nodes to NULL
    for (int i = 0; i <= MAX_NODES; i++) {
        nodes[i] = NULL;
    }
    
    int nodeIndex = 0;
    char data;
    int childIdx, siblingIdx;
    
    // Read input and create nodes
    while (scanf(" %c %d %d", &data, &childIdx, &siblingIdx) == 3) {
        nodeIndex++;
        
        // Create or update the current node
        if (nodes[nodeIndex] == NULL) {
            nodes[nodeIndex] = createNode(data);
        } else {
            nodes[nodeIndex]->data = data;
        }
        
        // Connect child if it exists
        if (childIdx != -1) {
            if (nodes[childIdx] == NULL) {
                nodes[childIdx] = createNode(' '); // Create placeholder
            }
            nodes[nodeIndex]->child = nodes[childIdx];
        }
        
        // Connect sibling if it exists
        if (siblingIdx != -1) {
            if (nodes[siblingIdx] == NULL) {
                nodes[siblingIdx] = createNode(' '); // Create placeholder
            }
            nodes[nodeIndex]->sibling = nodes[siblingIdx];
        }
    }
    
    // Print the tree starting from root (node 1)
    printTree(nodes[1], 0);
    
    // Free allocated memory
    for (int i = 1; i <= nodeIndex; i++) {
        free(nodes[i]);
    }
    
    return 0;
}
