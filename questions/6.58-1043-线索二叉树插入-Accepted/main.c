#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 110

typedef struct ThreadNode {
    int data; // Node number
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag; // 0: link, 1: thread
} ThreadNode, *ThreadTree;

// Helper arrays for mapping
int L1[MAXN], R1[MAXN], n1; // Original tree
int L2[MAXN], R2[MAXN], n2, x_root; // Subtree to insert
int offset2; // Offset for subtree node number mapping

ThreadNode *node_map[MAXN * 2]; // For mapping node number to pointer

// ---- Stack for traversal ----
typedef struct {
    ThreadNode *a[MAXN * 2];
    int top;
} Stack;
void push(Stack *s, ThreadNode *x) { s->a[++s->top] = x; }
ThreadNode *pop(Stack *s) { return s->a[s->top--]; }
int empty(Stack *s) { return s->top == 0; }
ThreadNode *top(Stack *s) { return s->a[s->top]; }

// ---- Build tree from L/R array ----
ThreadNode* build_tree(int *L, int *R, int n, int rootnum, int offset, int *map_arr) {
    if (rootnum == 0) return NULL;
    if (node_map[rootnum] != NULL) return node_map[rootnum]; // prevent duplicate
    ThreadNode *p = (ThreadNode*)malloc(sizeof(ThreadNode));
    p->data = rootnum;
    p->ltag = p->rtag = 0;
    node_map[rootnum] = p;
    int idx = rootnum - offset;
    p->lchild = (L[idx] ? build_tree(L, R, n, L[idx], offset, map_arr) : NULL);
    p->rchild = (R[idx] ? build_tree(L, R, n, R[idx], offset, map_arr) : NULL);
    return p;
}

// ---- Inorder threading ----
ThreadNode *pre = NULL;
void inorder_threading(ThreadNode *T) {
    if (T) {
        inorder_threading(T->lchild);
        if (!T->lchild) {
            T->ltag = 1;
            T->lchild = pre;
        }
        if (pre && !pre->rchild) {
            pre->rtag = 1;
            pre->rchild = T;
        }
        pre = T;
        inorder_threading(T->rchild);
    }
}

// ---- Find node pointer by number ----
ThreadNode* find_node(ThreadNode *T, int num) {
    if (!T) return NULL;
    if (T->data == num) return T;
    ThreadNode *x = find_node(T->lchild, num);
    if (x) return x;
    return find_node(T->rchild, num);
}

// ---- Find leftmost node ----
ThreadNode* leftmost(ThreadNode *T) {
    if (!T) return NULL;
    while (T->ltag == 0 && T->lchild)
        T = T->lchild;
    return T;
}

// ---- Inorder traversal using threading ----
void inorder_traverse(ThreadTree T) {
    ThreadNode *p = leftmost(T);
    while (p) {
        printf("%d", p->data);
        // Print space unless last node
        ThreadNode *next;
        if (p->rtag == 1)
            next = p->rchild;
        else
            next = leftmost(p->rchild);
        if (next) printf(" ");
        p = next;
    }
    printf("\n");
}

// ---- Insert subtree x under node p ----
void insert_left(ThreadNode *p, ThreadNode *x) {
    // 1. If p has no left child
    if (p->ltag == 1 || p->lchild == NULL) {
        // x becomes left child of p
        ThreadNode *pred = p->lchild; // predecessor (could be NULL)
        p->lchild = x;
        p->ltag = 0;
        // Find rightmost of x's tree
        ThreadNode *temp = x;
        while (temp->rtag == 0 && temp->rchild)
            temp = temp->rchild;
        // temp's rchild = p, rtag = 1 (thread)
        temp->rchild = p;
        temp->rtag = 1;
        // Find leftmost of x's tree for predecessor thread
        ThreadNode *lm = leftmost(x);
        lm->lchild = pred;
        lm->ltag = 1;
    } else {
        // p has left child, say q
        ThreadNode *q = p->lchild;
        // x becomes p's left child
        p->lchild = x;
        p->ltag = 0;
        // Find rightmost of x's tree
        ThreadNode *temp = x;
        while (temp->rtag == 0 && temp->rchild)
            temp = temp->rchild;
        // temp's rchild = q, rtag = 0 (link)
        temp->rchild = q;
        temp->rtag = 0;
        // Now, q's lchild and ltag -- must update predecessor
        // Find leftmost of x's tree
        ThreadNode *lm = leftmost(x);
        // lm's lchild and ltag: keep as is, since x's threading stays
        // But q's leftmost predecessor must point to lm's predecessor
        // Actually, q's in-threading is not broken, as temp->rchild = q
        // For safety, fix q's predecessor
        if (lm->lchild && lm->ltag == 1) {
            ThreadNode *old_pred = lm->lchild;
            // Find leftmost of q for predecessor's rchild
            ThreadNode *q_lm = leftmost(q);
            q_lm->lchild = old_pred;
            q_lm->ltag = 1;
        }
        // For p's predecessor, set lm->lchild = p's predecessor
        lm->lchild = p->lchild;
        lm->ltag = 1;
    }
}

void clear_threading(ThreadNode *T) {
    if (!T) return;
    if (T->ltag == 1) T->lchild = NULL;
    if (T->rtag == 1) T->rchild = NULL;
    T->ltag = T->rtag = 0;
    clear_threading(T->lchild);
    clear_threading(T->rchild);
}

// ---- Main ----
int main() {
    // 1. Read the first tree (Original)
    char buf[500];
    // Read L1
    fgets(buf, sizeof(buf), stdin);
    char *tok = strtok(buf, " \n");
    n1 = 0;
    int root1;
    int arr[MAXN];
    while (tok) {
        arr[n1++] = atoi(tok);
        tok = strtok(NULL, " \n");
    }
    for (int i = 0; i < n1; ++i) L1[i] = arr[i];
    // Read R1
    fgets(buf, sizeof(buf), stdin);
    tok = strtok(buf, " \n");
    int idx = 0;
    while (tok) {
        arr[idx++] = atoi(tok);
        tok = strtok(NULL, " \n");
    }
    for (int i = 0; i < n1; ++i) R1[i] = arr[i];
    root1 = L1[0]; // root node number

    // 2. Read p node number
    int pnum;
    scanf("%d", &pnum);
    getchar(); // eat newline

    // 3. Read the subtree to insert (x-rooted)
    // Read L2
    fgets(buf, sizeof(buf), stdin);
    n2 = 0;
    tok = strtok(buf, " \n");
    while (tok) {
        arr[n2++] = atoi(tok);
        tok = strtok(NULL, " \n");
    }
    for (int i = 0; i < n2; ++i) L2[i] = arr[i];
    // Read R2
    fgets(buf, sizeof(buf), stdin);
    tok = strtok(buf, " \n");
    idx = 0;
    while (tok) {
        arr[idx++] = atoi(tok);
        tok = strtok(NULL, " \n");
    }
    for (int i = 0; i < n2; ++i) R2[i] = arr[i];

    // Calculate subtree root and offset
    x_root = L2[0];
    offset2 = x_root - 1;

    // 4. Build both trees
    memset(node_map, 0, sizeof(node_map));
    ThreadNode *T1 = build_tree(L1, R1, n1, root1, 0, L1);
    // Save mapping for original
    ThreadNode *p = find_node(T1, pnum);

    // Build subtree, but clear map for subtree nodes
    for (int i = 0; i < MAXN * 2; ++i) node_map[i] = NULL;
    ThreadNode *T2 = build_tree(L2, R2, n2, x_root, offset2, L2);

    // 5. Thread both trees
    pre = NULL;
    inorder_threading(T2);
    pre = NULL;
    inorder_threading(T1);

    // 6. Insert T2 under p
    insert_left(p, T2);

    // 7. Re-thread the entire tree (to keep all links valid)
    // First, clear all tags and children for threading
    // We'll do this by traversing and resetting tags for all nodes
    clear_threading(T1);
    pre = NULL;
    inorder_threading(T1);

    // 8. Output inorder traversal
    inorder_traverse(T1);

    // Free memory if desired
    return 0;
}
