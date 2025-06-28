#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Create a new node with given value
Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

// Append node at the end of the list
void append_node(Node** head_ref, int value) {
    Node* new_node = create_node(value);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    Node* curr = *head_ref;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_node;
}

// Simple selection sort for singly linked list (swap data)
void selection_sort(Node* head) {
    Node* i = head;
    while (i != NULL) {
        Node* min_node = i;
        Node* j = i->next;
        while (j != NULL) {
            if (j->data < min_node->data) {
                min_node = j;
            }
            j = j->next;
        }
        // Swap data between i and min_node
        if (min_node != i) {
            int tmp = i->data;
            i->data = min_node->data;
            min_node->data = tmp;
        }
        i = i->next;
    }
}

// Print the linked list
void print_list(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL)
            printf(" ");
        curr = curr->next;
    }
    printf("\n");
}

// Free the linked list
void free_list(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
}

int main() {
    Node* head = NULL;
    int value;
    // Read input until EOF or newline
    while (scanf("%d", &value) == 1) {
        append_node(&head, value);
        // Stop reading if the next character is a newline
        int c = getchar();
        if (c == '\n' || c == EOF) break;
    }
    // Sort the list
    selection_sort(head);
    // Print the sorted list
    print_list(head);
    // Free memory
    free_list(head);
    return 0;
}