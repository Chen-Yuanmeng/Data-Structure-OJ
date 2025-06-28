#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    char c;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} String;

void initString(String *str) {
    str->head = NULL;
    str->tail = NULL;
}

void appendChar(String *str, char c) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->c = c;
    newNode->next = NULL;

    if (str->head == NULL) {
        newNode->prev = NULL;
        str->head = newNode;
        str->tail = newNode;
    } else {
        newNode->prev = str->tail;
        str->tail->next = newNode;
        str->tail = newNode;
    }
}

void freeString(String *str) {
    Node *current = str->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    str->head = NULL;
    str->tail = NULL;
}

int main() {
    String str;
    initString(&str);

    int i;
    scanf("%d", &i);
    char c;

    for (int j = 0; j < i; j++) {
        scanf(" %c", &c);
        appendChar(&str, c);
    }

    // Check if the string is symmetric
    Node *left = str.head;
    Node *right = str.tail;
    int isSymmetric = 1;

    while (left != NULL && right != NULL && left != right && left->prev != right) {
        if (left->c != right->c) {
            isSymmetric = 0;
            break;
        }
        left = left->next;
        right = right->prev;
    }

    if (isSymmetric) {
        printf("1");
    } else {
        printf("0");
    }

    freeString(&str);
    return 0;
}