#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Create a new node
Node* createNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

// Free the entire list
void freeList(Node* head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

// Print the list
void printList(Node* head) {
    Node* p = head;
    int first = 1;
    while (p) {
        if (!first) printf(" ");
        printf("%d", p->data);
        first = 0;
        p = p->next;
    }
    printf("\n");
}

// Find and split into maximal sorted sublists
Node** splitToRuns(Node* head, int* runCount) {
    int capacity = 10, count = 0;
    Node **runs = (Node**)malloc(sizeof(Node*) * capacity);
    Node *cur = head, *runHead = NULL, *runTail = NULL;

    while (cur) {
        // New run
        runHead = cur;
        runTail = cur;
        cur = cur->next;
        // Extend this run while ascending
        while (cur && runTail->data <= cur->data) {
            runTail = cur;
            cur = cur->next;
        }
        // Cut off the run
        Node *nextRun = cur;
        runTail->next = NULL;
        // Store the run
        if (count >= capacity) {
            capacity *= 2;
            runs = (Node**)realloc(runs, sizeof(Node*) * capacity);
        }
        runs[count++] = runHead;
    }
    *runCount = count;
    return runs;
}

// Merge two sorted lists, return head and update tail
Node* mergeTwoLists(Node* l1, Node* l2) {
    Node dummy, *tail = &dummy;
    dummy.next = NULL;
    while (l1 && l2) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// Perform 2-way merges repeatedly until one run remains
Node* mergeRuns(Node** runs, int runCount) {
    while (runCount > 1) {
        int i, k = 0;
        for (i = 0; i + 1 < runCount; i += 2) {
            runs[k++] = mergeTwoLists(runs[i], runs[i+1]);
        }
        if (i < runCount) runs[k++] = runs[i]; // Odd number of runs
        runCount = k;
    }
    return runs[0];
}

int main() {
    int n, i, val;
    Node *head = NULL, *tail = NULL;

    // Read input
    if (scanf("%d", &n) != 1) return 1;
    for (i = 0; i < n; ++i) {
        if (scanf("%d", &val) != 1) return 1;
        Node* node = createNode(val);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    // Split into maximal sorted sublists ("runs")
    int runCount;
    Node **runs = splitToRuns(head, &runCount);

    // Merge all runs
    Node *sorted = mergeRuns(runs, runCount);

    // Print result
    printList(sorted);

    // Free memory
    free(runs);
    freeList(sorted);

    return 0;
}
