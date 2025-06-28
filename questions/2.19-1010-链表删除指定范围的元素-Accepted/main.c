#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a linked list node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a linked list from an array
Node* createLinkedList(int arr[], int n) {
    if (n == 0) return NULL;
    Node *head = createNode(arr[0]);
    Node *current = head;
    for (int i = 1; i < n; i++) {
        current->next = createNode(arr[i]);
        current = current->next;
    }
    return head;
}

// Function to delete nodes with values in the range (mink, maxk)
void deleteRange(Node **head, int mink, int maxk) {
    Node *dummy = createNode(0); // Dummy node to simplify edge cases
    dummy->next = *head;
    Node *prev = dummy, *current = *head;

    while (current) {
        if (current->data > mink && current->data < maxk) {
            prev->next = current->next;
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }

    *head = dummy->next;
    free(dummy);
}

// Function to print the linked list
void printLinkedList(Node *head) {
    Node *current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Main function
int main() {
    // Input the linked list elements
    char buffer[1000];
    fgets(buffer, sizeof(buffer), stdin);
    int arr[100], n = 0;
    char *token = strtok(buffer, " ");
    while (token) {
        arr[n++] = atoi(token);
        token = strtok(NULL, " ");
    }

    // Input mink and maxk
    int mink, maxk;
    scanf("%d %d", &mink, &maxk);

    // Create the linked list
    Node *head = createLinkedList(arr, n);

    // Delete nodes in the range (mink, maxk)
    deleteRange(&head, mink, maxk);

    // Print the final linked list
    printLinkedList(head);

    return 0;
}