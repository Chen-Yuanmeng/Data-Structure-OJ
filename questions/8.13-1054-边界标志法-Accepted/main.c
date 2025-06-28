#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

typedef struct {
    int flag;  // 0: free, 1: allocated
    int start; // start address
    int size;  // size of block
} Block;

int compare_start(const void *a, const void *b) {
    Block *ba = (Block *)a;
    Block *bb = (Block *)b;
    return ba->start - bb->start;
}

void insert_and_merge(Block free_blocks[], int *n, Block new_block) {
    // Insert new block into list
    free_blocks[*n] = new_block;
    (*n)++;

    // Sort by start address
    qsort(free_blocks, *n, sizeof(Block), compare_start);

    // Merge adjacent blocks
    int i = 0;
    for (int j = 1; j < *n; j++) {
        if (free_blocks[i].start + free_blocks[i].size == free_blocks[j].start) {
            // merge j into i
            free_blocks[i].size += free_blocks[j].size;
        }
        else {
            i++;
            if (i != j)
                free_blocks[i] = free_blocks[j];
        }
    }
    *n = i + 1;
}

int main() {
    Block free_blocks[MAX_BLOCKS];
    Block reclaim_blocks[MAX_BLOCKS];
    int n_free = 0, n_reclaim = 0;

    // Read initial free blocks
    while (1) {
        int flag, start, size;
        if (scanf("%d %d %d", &flag, &start, &size) != 3)
            break;
        if (flag != 0 && flag != 1)
            break;
        if (flag == 0) {
            free_blocks[n_free].flag = 0;
            free_blocks[n_free].start = start;
            free_blocks[n_free].size = size;
            n_free++;
        }
        else {
            reclaim_blocks[n_reclaim].flag = 0; // Will be free
            reclaim_blocks[n_reclaim].start = start;
            reclaim_blocks[n_reclaim].size = size;
            n_reclaim++;
        }
    }

    // Reclaim each block using first-fit and boundary tag merge
    for (int i = 0; i < n_reclaim; i++) {
        insert_and_merge(free_blocks, &n_free, reclaim_blocks[i]);
    }

    // Sort again for output
    qsort(free_blocks, n_free, sizeof(Block), compare_start);

    for (int i = 0; i < n_free; i++) {
        printf("0 %d %d\n", free_blocks[i].start, free_blocks[i].size);
    }

    return 0;
}
