#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_K 32
#define MAX_BLOCKS 1024

typedef struct {
    int size;
    int blocks[MAX_BLOCKS];
    int count;
} FreeList;

FreeList freelists[MAX_K];

void add_block(int k, int addr) {
    FreeList *fl = &freelists[k];
    // Insert in order
    int i = 0;
    while (i < fl->count && fl->blocks[i] < addr) i++;
    for (int j = fl->count; j > i; --j)
        fl->blocks[j] = fl->blocks[j - 1];
    fl->blocks[i] = addr;
    fl->count++;
}

int remove_block(int k, int addr) {
    FreeList *fl = &freelists[k];
    for (int i = 0; i < fl->count; ++i) {
        if (fl->blocks[i] == addr) {
            for (int j = i; j < fl->count - 1; ++j)
                fl->blocks[j] = fl->blocks[j + 1];
            fl->count--;
            return 1;
        }
    }
    return 0;
}

void recycle(int k, int addr) {
    int size = 1 << k;
    while (1) {
        int buddy = addr ^ size;
        if (!remove_block(k, buddy))
            break;
        // Merge
        addr = addr < buddy ? addr : buddy;
        size <<= 1;
        k++;
    }
    add_block(k, addr);
}

int main() {
    char line[1024];
    
    // Read initial free list
    while (fgets(line, sizeof(line), stdin)) {
        if (strlen(line) == 1) break;  // Empty line
        int k, addr;
        char *token = strtok(line, " \n");
        if (!token) continue;
        k = atoi(token);
        freelists[k].size = 1 << k;
        while ((token = strtok(NULL, " \n")) != NULL) {
            addr = atoi(token);
            add_block(k, addr);
        }
    }

    // Read blocks to recycle
    while (fgets(line, sizeof(line), stdin)) {
        int k, addr;
        if (sscanf(line, "%d %d", &k, &addr) == 2) {
            recycle(k, addr);
        }
    }

    // Output
    for (int k = 0; k < MAX_K; ++k) {
        if (freelists[k].count > 0) {
            printf("%d", k);
            for (int i = 0; i < freelists[k].count; ++i)
                printf(" %d", freelists[k].blocks[i]);
            printf("\n");
        }
    }
    return 0;
}
