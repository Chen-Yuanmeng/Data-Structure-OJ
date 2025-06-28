#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义链表节点结构
typedef struct Node {
    char data[100];
    struct Node* next;
} Node;

// 创建新节点
Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    return newNode;
}

// 逆置链表
Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next; // 保存下一个节点
        current->next = prev; // 当前节点指向前一个节点
        prev = current;       // 更新前一个节点为当前节点
        current = next;       // 移动到下一个节点
    }
    return prev; // 新的头节点
}

// 打印链表
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) {
            printf(",");
        }
        current = current->next;
    }
    printf("\n");
}

// 释放链表内存
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    char input[1000];
    scanf("%s", input);

    // 分割输入字符串并创建链表
    Node* head = NULL;
    Node* tail = NULL;
    char* token = strtok(input, ",");
    while (token != NULL) {
        Node* newNode = createNode(token);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        token = strtok(NULL, ",");
    }

    head = reverseList(head);

    printList(head);

    // 释放链表内存
    freeList(head);

    return 0;
}