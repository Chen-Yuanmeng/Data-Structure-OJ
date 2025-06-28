#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool is_end;
} TrieNode;

TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (node) {
        int i;
        for (i = 0; i < ALPHABET_SIZE; ++i)
            node->children[i] = NULL;
        node->is_end = false;
    }
    return node;
}

// Insert a word into Trie
void insert(TrieNode *root, const char *word) {
    TrieNode *cur = root;
    for (int i = 0; word[i]; ++i) {
        int idx = word[i] - 'a';
        if (!cur->children[idx])
            cur->children[idx] = createNode();
        cur = cur->children[idx];
    }
    cur->is_end = true;
}

// Helper to check if a node has any children
bool hasChildren(TrieNode *node) {
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (node->children[i])
            return true;
    return false;
}

// Recursively delete a word from the Trie
bool deleteHelper(TrieNode *node, const char *word, int depth) {
    if (!node) return false;

    if (word[depth] == '\0') {
        if (node->is_end) {
            node->is_end = false;
            // If node has no children, it can be deleted by parent
            return !hasChildren(node);
        }
        return false;
    }

    int idx = word[depth] - 'a';
    if (!node->children[idx])
        return false;

    bool shouldDeleteChild = deleteHelper(node->children[idx], word, depth+1);

    if (shouldDeleteChild) {
        free(node->children[idx]);
        node->children[idx] = NULL;
        // Return true if current node is not end and has no children
        return !node->is_end && !hasChildren(node);
    }
    return false;
}

void deleteWord(TrieNode *root, const char *word) {
    deleteHelper(root, word, 0);
}

// Search for a word in Trie
bool search(TrieNode *root, const char *word) {
    TrieNode *cur = root;
    for (int i = 0; word[i]; ++i) {
        int idx = word[i] - 'a';
        if (!cur->children[idx])
            return false;
        cur = cur->children[idx];
    }
    return cur->is_end;
}

// Free the entire Trie
void freeTrie(TrieNode *root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        freeTrie(root->children[i]);
    free(root);
}

int main() {
    TrieNode *root = createNode();
    char line[100];
    while (fgets(line, sizeof(line), stdin)) {
        int op = 0;
        char word[80];
        if (sscanf(line, "%d %s", &op, word) != 2)
            continue;
        if (op == 1) {
            insert(root, word);
        } else if (op == 2) {
            deleteWord(root, word);
        } else if (op == 3) {
            if (search(root, word))
                printf("True\n");
            else
                printf("False\n");
        }
    }
    freeTrie(root);
    return 0;
}
