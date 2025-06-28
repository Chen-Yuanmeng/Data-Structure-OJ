#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct Space {
    int tag;
    int addr;
    int space_size;
} Space;

int main() {
    int highbound, lowbound, size;
    scanf("%d %d %d", &lowbound, &highbound, &size);

    int num = (highbound - lowbound) / size; // Calculate the number of spaces

    int tag[30] = {0};
    char c;
    for (int i = 0; i < num; i++) {
        scanf("%d", &tag[i]);
        c = getchar();
    }

    Space sp[20];
    int j = 0, k = 0;
    
    while (j < num) {
        if (tag[j] == 0) {
            sp[k].tag = 0;
            sp[k].addr = lowbound + size * j;
            sp[k].space_size = size;
            int m = 1;
            while (tag[j + m] == 0 && j + m < num) {
                m++;
                sp[k].space_size += size;
            }
            j = j + m;
            k++;
        }
        else {
            j++;
        }
    }

    if (k == 0) {
        printf("0 0 0");
    }
    else {
        int n = 0;
        while (n < k - 1) {
            printf("%d %d %d\n", sp[n].tag, sp[n].addr, sp[n].space_size);
            n++;
        }
        printf("%d %d %d", sp[n].tag, sp[n].addr, sp[n].space_size);
    }

    return 0;
}
