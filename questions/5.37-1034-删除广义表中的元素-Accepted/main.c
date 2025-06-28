#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

typedef struct Node {
    int is_atom; // 1 for atom, 0 for sublist
    char atom;
    struct Node *sublist;
    struct Node *next;
} Node;

void skip_spaces(const char **p) {
    while (**p == ' ') (*p)++;
}

Node* parse(const char **p) {
    skip_spaces(p);
    if (**p == '\0') return NULL;

    if (**p == '(') {
        (*p)++;
        Node *head = NULL, *tail = NULL;
        while (**p && **p != ')') {
            Node *elem = parse(p);
            if (elem) {
                if (!head) head = tail = elem;
                else {
                    tail->next = elem;
                    tail = elem;
                }
            }
            skip_spaces(p);
            if (**p == ',') (*p)++;
        }
        if (**p == ')') (*p)++;
        Node *list_node = malloc(sizeof(Node));
        list_node->is_atom = 0;
        list_node->sublist = head;
        list_node->next = NULL;
        return list_node;
    } else if (isalpha(**p)) {
        Node *atom = malloc(sizeof(Node));
        atom->is_atom = 1;
        atom->atom = **p;
        atom->next = NULL;
        (*p)++;
        return atom;
    }

    return NULL;
}

int remove_atoms(Node **node, char target) {
    Node *curr = *node, *prev = NULL;
    while (curr) {
        if (curr->is_atom) {
            if (curr->atom == target) {
                Node *to_free = curr;
                if (prev) prev->next = curr->next;
                else *node = curr->next;
                curr = curr->next;
                free(to_free);
                continue;
            }
        } else {
            if (remove_atoms(&curr->sublist, target)) {
                Node *to_free = curr;
                if (prev) prev->next = curr->next;
                else *node = curr->next;
                curr = curr->next;
                free(to_free);
                continue;
            }
        }
        prev = curr;
        curr = curr->next;
    }

    return *node == NULL;
}

void print_list(Node *node) {
    if (!node) return;

    Node *curr = node;
    printf("(");
    while (curr) {
        if (curr->is_atom) {
            printf("%c", curr->atom);
        } else {
            if (curr->sublist)
                print_list(curr->sublist);
        }
        if (curr->next) printf(",");
        curr = curr->next;
    }
    printf(")");
}

int is_empty(Node *node) {
    return node == NULL;
}

void free_list(Node *node) {
    while (node) {
        Node *next = node->next;
        if (!node->is_atom)
            free_list(node->sublist);
        free(node);
        node = next;
    }
}

int main() {
    char input[MAX_LEN];
    fgets(input, MAX_LEN, stdin);
    size_t len = strlen(input);
    if (len && input[len - 1] == '\n') input[len - 1] = '\0';

    char *space = strrchr(input, ' ');
    if (!space) {
        printf("-1\n");
        return 0;
    }

    char target = space[1];
    *space = '\0';

    const char *p = input;
    Node *root = parse(&p);

    int empty = remove_atoms(&root, target);

    if (!root || is_empty(root)) {
        printf("-1\n");
    } else {
        print_list(root->sublist);
        printf("\n");
    }

    free_list(root);
    return 0;
}
