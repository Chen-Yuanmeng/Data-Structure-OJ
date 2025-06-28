#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

char stack[MAX_SIZE];
int top = -1;

void push(char c) {
    if (top < MAX_SIZE - 1) {
        stack[++top] = c;
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0'; // Return null character if stack is empty
}

const char left_bracket[] = "({[";
const char right_bracket[] = ")}]";

int is_matching(char left, char right) {
    for (int i = 0; i < 3; i++) {
        if (left_bracket[i] == left && right_bracket[i] == right) {
            return 1;
        }
    }
    return 0;
}

int is_left_bracket(char c) {
    for (int i = 0; i < 3; i++) {
        if (left_bracket[i] == c) {
            return 1;
        }
    }
    return 0;
}

int is_right_bracket(char c) {
    for (int i = 0; i < 3; i++) {
        if (right_bracket[i] == c) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char s[MAX_SIZE], c;
    int index = 0;
    scanf("%s", s);
    int len_s = strlen(s);

    for (; index < len_s; index++) {
        if (is_left_bracket(s[index])) {
            push(s[index]);
        } else if (is_right_bracket(s[index])) {
            char top_char = pop();
            if (!is_matching(top_char, s[index])) {
                printf("0");
                return 0;
            }
        }
    }
    if (top != -1) {
        printf("0");
        return 0;
    }
    printf("1");
    return 0;
}