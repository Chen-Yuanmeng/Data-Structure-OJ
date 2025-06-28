#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int coef; // Coefficient
    int exp;  // Exponent
} PolyTerm;

typedef struct PolyNode {
    PolyTerm data;
    struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;

LinkedPoly createPoly() {
    LinkedPoly head = (PolyNode*)malloc(sizeof(PolyNode));
    head->next = head;
    return head;
}

void insertTerm(LinkedPoly head, int coef, int exp) {
    if (coef == 0) return;
    PolyLink p = head, q = head->next;
    while (q != head && q->data.exp > exp) {
        p = q;
        q = q->next;
    }
    if (q != head && q->data.exp == exp) {
        q->data.coef += coef;
        if (q->data.coef == 0) {
            p->next = q->next;
            free(q);
        }
    } else {
        PolyLink node = (PolyNode*)malloc(sizeof(PolyNode));
        node->data.coef = coef;
        node->data.exp = exp;
        node->next = q;
        p->next = node;
    }
}

void parseInput(LinkedPoly head, char *s) {
    int i = 0, len = strlen(s);
    while (i < len) {
        while (i < len && isspace(s[i])) i++;
        int sign = 1;
        if (i < len && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') sign = -1;
            i++;
        }
        while (i < len && isspace(s[i])) i++;
        int coef = 0, coef_set = 0;
        while (i < len && isdigit(s[i])) {
            coef = coef * 10 + (s[i] - '0');
            i++;
            coef_set = 1;
        }
        if (!coef_set) coef = 1; // Coefficient is 1 if ignored
        coef *= sign;
        int exp = 0;
        if (i < len && s[i] == 'x') {
            i++;
            exp = 1;
            if (i < len && s[i] == '^') {
                i++;
                exp = 0;
                while (i < len && isdigit(s[i])) {
                    exp = exp * 10 + (s[i] - '0');
                    i++;
                }
            }
        } else {
            exp = 0;
        }
        insertTerm(head, coef, exp);
    }
}

void derivative(LinkedPoly head) {
    PolyLink p = head, q = head->next;
    while (q != head) {
        if (q->data.exp == 0) {
            // Delete constant term
            p->next = q->next;
            free(q);
            q = p->next;
        } else {
            q->data.coef = q->data.coef * q->data.exp;
            q->data.exp--;
            if (q->data.coef == 0) {
                p->next = q->next;
                free(q);
                q = p->next;
            } else {
                p = q;
                q = q->next;
            }
        }
    }
}

int isZero(LinkedPoly head) {
    return head->next == head;
}


void printPoly(LinkedPoly head) {
    PolyLink p = head->next;
    if (p == head) {
        printf("0\n");
        return;
    }
    int first = 1;
    while (p != head) {
        int c = p->data.coef, e = p->data.exp;
        if (!first) {
            if (c > 0) printf(" + ");
            else printf(" - ");
        } else {
            if (c < 0) printf("- ");
        }
        if (abs(c) != 1 || e == 0) printf("%d", abs(c));
        if (e > 0) {
            printf("x");
            if (e > 1) printf("^%d", e);
        }
        first = 0;
        p = p->next;
    }
    printf("\n");
}

int main() {
    char buf[1024];
    fgets(buf, sizeof(buf), stdin);
    // Remove trailing newline
    int len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = 0;
    LinkedPoly poly = createPoly();
    parseInput(poly, buf);
    derivative(poly);
    printPoly(poly);

    // Free memory
    PolyLink p = poly->next;
    while (p != poly) {
        PolyLink tmp = p;
        p = p->next;
        free(tmp);
    }
    free(poly);
    return 0;
}
