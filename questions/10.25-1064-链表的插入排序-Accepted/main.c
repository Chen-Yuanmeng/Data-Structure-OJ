#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Function to create a new node with given data
Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("Failed to allocate node");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Function to insert a node into the sorted part of the list
void sorted_insert(Node **sorted_head, Node *new_node) {
    Node *curr = *sorted_head;
    Node *prev = NULL;
    // Find the correct position to insert
    while (curr != NULL && curr->data < new_node->data) {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL) {
        // Insert at the head
        new_node->next = *sorted_head;
        *sorted_head = new_node;
    } else {
        prev->next = new_node;
        new_node->next = curr;
    }
}

// Insertion sort for linked list
Node* insertion_sort(Node *head) {
    Node *sorted = NULL;
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next;
        curr->next = NULL;
        sorted_insert(&sorted, curr);
        curr = next;
    }
    return sorted;
}

// Free the linked list
void free_list(Node *head) {
    Node *curr;
    while (head != NULL) {
        curr = head;
        head = head->next;
        free(curr);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 1;
    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) {
            free_list(head);
            return 1;
        }
        Node *new_node = create_node(x);
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    head = insertion_sort(head);

    Node *curr = head;
    for (int i = 0; i < n; ++i) {
        printf("%d", curr->data);
        if (i != n-1) printf(" ");
        curr = curr->next;
    }
    printf("\n");

    free_list(head);
    return 0;
}
