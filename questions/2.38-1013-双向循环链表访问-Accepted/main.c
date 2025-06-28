#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 110

typedef struct Node {
    int data;
    int freq;
    int order;
    struct Node *prev, *next;
} Node;

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->freq = 0;
    node->order = -1;
    node->prev = node->next = NULL;
    return node;
}

int main() {
    int n;
    int elements[MAXN], accesses[MAXN*10], access_cnt = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &elements[i]);
    char buf[1000];
    getchar();
    fgets(buf, sizeof(buf), stdin);
    char *p = strtok(buf, " \n");
    while (p) {
        accesses[access_cnt++] = atoi(p);
        p = strtok(NULL, " \n");
    }

    Node *head = createNode(-1);
    Node *tail = head;
    Node *nodes[MAXN];
    for (int i = 0; i < n; ++i) {
        nodes[i] = createNode(elements[i]);
        tail->next = nodes[i];
        nodes[i]->prev = tail;
        tail = nodes[i];
    }
    tail->next = head;
    head->prev = tail;

    int visit_order = 0;
    for (int i = 0; i < access_cnt; ++i) {
        int x = accesses[i];
        Node *cur = head->next;
        while (cur != head) {
            if (cur->data == x) {
                cur->freq++;
                if (cur->order == -1) cur->order = visit_order++;
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;

                Node *ins = head->next;
                while (ins != head && (ins->freq > cur->freq || (ins->freq == cur->freq && ins->order < cur->order))) {
                    ins = ins->next;
                }

                cur->next = ins;
                cur->prev = ins->prev;
                ins->prev->next = cur;
                ins->prev = cur;
                break;
            }
            cur = cur->next;
        }
    }
    // Print
    Node *cur = head->next;
    int first = 1;
    while (cur != head) {
        if (!first) printf(" ");
        printf("%d", cur->data);
        first = 0;
        cur = cur->next;
    }
    printf("\n");
    // Free memory
    cur = head->next;
    while (cur != head) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(head);
    return 0;
}
