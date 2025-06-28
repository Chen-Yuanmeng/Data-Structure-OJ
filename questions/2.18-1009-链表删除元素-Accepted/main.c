#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义单链表节点
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 创建链表
Node* createList(int arr[], int n) {
    if (n == 0) return NULL;
    Node *head = (Node *)malloc(sizeof(Node));
    head->data = arr[0];
    head->next = NULL;
    Node *current = head;
    for (int i = 1; i < n; i++) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = arr[i];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
    return head;
}

// 删除第i个节点
Node* deleteNode(Node *head, int i) {
    if (head == NULL) return NULL;
    if (i == 0) {
        Node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    Node *current = head;
    for (int j = 0; j < i - 1 && current->next != NULL; j++) {
        current = current->next;
    }
    if (current->next != NULL) {
        Node *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    return head;
}

// 打印链表
void printList(Node *head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    Node *current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) printf(" ");
        current = current->next;
    }
    printf("\n");
}

// 主函数
int main() {
    char input[1000];
    fgets(input, sizeof(input), stdin);
    char *token = strtok(input, " ");
    int arr[100], n = 0;
    while (token != NULL) {
        arr[n++] = atoi(token);
        token = strtok(NULL, " ");
    }
    int i;
    scanf("%d", &i);

    Node *head = createList(arr, n);
    head = deleteNode(head, i);
    printList(head);

    return 0;
}