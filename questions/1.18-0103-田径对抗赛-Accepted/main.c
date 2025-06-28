#include <stdio.h>
#include <string.h>

#define STR_MAX 100

typedef struct _School {
    char name;
    int score_male;
    int score_female;
} School;

School schools[5] = {
    {'A', 0, 0},
    {'B', 0, 0},
    {'C', 0, 0},
    {'D', 0, 0},
    {'E', 0, 0}
};

int print_school(School *school);
void print_all();
int comp_str(char* s);
int getline(char* s, int lim);

int print_school(School *school) {
    if (school->score_male != 0) {
        printf("%c M %d\n", school->name, school->score_male);
    }
    if (school->score_female != 0) {
        printf("%c F %d\n", school->name, school->score_female);
    }
    if (school->score_male + school->score_female != 0) {
        printf("%c %d\n", school->name, school->score_female + school->score_male);
    }
}

void print_all() {
    for (int i = 0; i < 5; i++) {
        print_school(&schools[i]);
    }
}

int comp_str(char* s) {
    char gender = EOF;
    char school = EOF;  // 0-4 for A-E
    int score = 0;

    while (*s != ' ') {
        s++;
    }
    s++;
    gender = *s;
    s += 2;
    school = *s - 'A';
    s += 2;

    while (*s != '\0') {
        score = score * 10 + *s - '0';
        s++;
    }

    // Add this info to `schools`
    if (gender == 'M') {
        schools[school].score_male += score;
    }
    else {
        schools[school].score_female += score;
    }
}

int getline(char* s, int lim) {
    int c, i = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (i < lim - 1) {
            s[i++] = c;
        }
        else {
            break;
        }
    }
    s[i] = '\0';
    return i;
}

int main() {
    // Input: Project_name M/F School_name Score
    // Output: use `print_school` to print the result

    int p;

    char s[STR_MAX];
    while (1) {
        p = getline(s, STR_MAX);
        if (p == 0) {
            break;
        }
        comp_str(s);
    }

    print_all();
}
