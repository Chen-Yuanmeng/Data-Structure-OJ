#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    char data[100];
    struct Node* next;
} Node;

Node* initLinkedList() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

void deleteNode(Node* head, char* data) {
    Node* current = head->next;
    Node* previous = head;

    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            previous->next = current->next;
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void printList(Node* head) {
    Node* current = head->next;
    while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) {
            printf(",");
        }
        current = current->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* current = head;
    Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

Node* createList(char* str) {
    Node* head = initLinkedList();
    Node* current = head;
    char* token = strtok(str, ",");
    while (token != NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        strcpy(newNode->data, token);
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
        token = strtok(NULL, ",");
    }

    return head;
}

int searchList(Node* head, char* data) {
    Node* current = head->next;
    int index = 0;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; // Not found
}

int main() {
    Node* head_A;
    Node* head_B;
    Node* head_C;

    char str_A[1000];
    char str_B[1000];
    char str_C[1000];

    scanf("%s", str_A);
    scanf("%s", str_B);
    scanf("%s", str_C);

    head_A = createList(str_A);
    head_B = createList(str_B);
    head_C = createList(str_C);

    // Enumerate the elements in list A
    Node* node = head_A;
    while (node != NULL) {
        if (searchList(head_B, node->data) != -1) {
            if (searchList(head_C, node->data) != -1) {
                deleteNode(head_A, node->data);
            }
        }
        node = node->next;
    }

    printList(head_A);
}

