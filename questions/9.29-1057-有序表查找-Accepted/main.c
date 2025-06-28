#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the node structure
typedef struct Node {
    int key;
    struct Node* next;
} Node;

// Create a single circular linked list from sorted array
Node* create_circular_list(int* arr, int n) {
    if (n == 0) return NULL;
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < n; ++i) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->key = arr[i];
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    tail->next = head; // make it circular
    return head;
}

// Find a key using the described algorithm
// h points to min key node, t is a float pointer (updated after each search)
int search(Node* h, Node** t, int k) {
    if (!h) return 0;
    if ((*t)->key == k) return 1;
    Node* start;
    if (k < (*t)->key) {
        start = h;
    } else {
        start = (*t)->next;
    }
    Node* p = start;
    do {
        if (p->key == k) {
            *t = p; // update t to found node
            return 1;
        }
        // Since it's sorted and keys are increasing, if we pass k, no need to continue
        if (p->key > k) break;
        p = p->next;
    } while (p != start);
    return 0;
}

// Parse input line into array of ints, return count
int parse_line(char* line, int* arr) {
    int cnt = 0;
    char* token = strtok(line, " \n\r");
    while (token) {
        arr[cnt++] = atoi(token);
        token = strtok(NULL, " \n\r");
    }
    return cnt;
}

int main() {
    char line1[1024], line2[1024];
    int arr[100], search_keys[100];
    // Read first line
    if (!fgets(line1, sizeof(line1), stdin)) return 1;
    int n = parse_line(line1, arr);
    // Read second line
    if (!fgets(line2, sizeof(line2), stdin)) return 1;
    int m = parse_line(line2, search_keys);

    // Build the circular list
    Node* h = create_circular_list(arr, n);
    Node* t = h; // t starts at h

    // For each search key, perform search and output result
    for (int i = 0; i < m; ++i) {
        int found = search(h, &t, search_keys[i]);
        printf("%d", found);
        if (i != m - 1) printf(" ");
    }
    printf("\n");

    // Free list nodes
    if (h) {
        Node* p = h->next;
        while (p != h) {
            Node* tmp = p;
            p = p->next;
            free(tmp);
        }
        free(h);
    }

    return 0;
}
