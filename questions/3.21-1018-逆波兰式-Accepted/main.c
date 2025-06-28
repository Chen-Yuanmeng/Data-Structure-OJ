#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

void infixToPostfix(const char* expr, char* output) {
    char stack[MAX];
    int top = -1, k = 0;
    for (int i = 0; expr[i]; i++) {
        char ch = expr[i];
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            output[k++] = ch;
        } else if (ch == '(') {
            stack[++top] = ch;
        } else if (ch == ')') {
            while (top >= 0 && stack[top] != '(') {
                output[k++] = stack[top--];
            }
            if (top >= 0 && stack[top] == '(') top--;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (top >= 0 && precedence(stack[top]) >= precedence(ch)) {
                if (stack[top] == '(') break;
                output[k++] = stack[top--];
            }
            stack[++top] = ch;
        }
    }
    while (top >= 0) {
        if (stack[top] != '(')
            output[k++] = stack[top];
        top--;
    }
    output[k] = '\0';
}

int main() {
    char expr[MAX], output[MAX];
    scanf("%s", expr);
    infixToPostfix(expr, output);
    printf("%s\n", output);
    return 0;
}
