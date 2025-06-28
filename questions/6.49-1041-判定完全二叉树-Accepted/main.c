#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

typedef struct Node {
    char val;
    int left;
    int right;
} Node;

Node tree[MAXN];
int isChild[MAXN] = {0};

typedef struct {
    int data[MAXN];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int x) {
    q->data[q->rear++] = x;
}

int dequeue(Queue *q) {
    return q->data[q->front++];
}

int isCompleteBinaryTree(int root, int n) {
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    int foundNull = 0;

    while (!isEmpty(&q)) {
        int curr = dequeue(&q);
        int l = tree[curr].left;
        int r = tree[curr].right;

        if (l != -1) {
            if (foundNull) return 0;
            enqueue(&q, l);
        } else {
            foundNull = 1;
        }

        if (r != -1) {
            if (foundNull) return 0;
            enqueue(&q, r);
        } else {
            foundNull = 1;
        }
    }

    return 1;
}

int main() {
    int n = 0;
    while (scanf(" %c %d %d", &tree[n + 1].val, &tree[n + 1].left, &tree[n + 1].right) == 3) {
        int l = tree[n + 1].left;
        int r = tree[n + 1].right;
        if (l != -1) isChild[l] = 1;
        if (r != -1) isChild[r] = 1;
        n++;
    }

    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (!isChild[i]) {
            root = i;
            break;
        }
    }

    if (isCompleteBinaryTree(root, n)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}
