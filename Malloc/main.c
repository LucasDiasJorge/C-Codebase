#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BLOCK_SIZE sizeof(Block)

typedef struct Block {
    size_t size;
    int free;
    struct Block *next;
} Block;

Block *freeList = NULL;

Block *findFreeBlock(size_t size) {
    Block *current = freeList;
    while (current) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Block *extendHeap(size_t size) {
    Block *block = (Block *)sbrk(size + BLOCK_SIZE);
    if (block == (void *)-1) return NULL;
    block->size = size;
    block->free = 0;
    block->next = NULL;
    return block;
}

void *my_malloc(size_t size) {
    if (size <= 0) return NULL;

    Block *block = findFreeBlock(size);
    if (!block) {
        block = extendHeap(size);
        if (!block) return NULL;
    } else {
        block->free = 0;
    }
    return (void *)(block + 1);
}

void my_free(void *ptr) {
    if (!ptr) return;

    Block *block = (Block *)ptr - 1;
    block->free = 1;
    // Coalescing logic would go here.
}

int main() {
    int *ptr = (int *)my_malloc(sizeof(int) * 10);
    if (ptr) {
        for (int i = 0; i < 10; i++) {
            ptr[i] = i * 2;
            printf("%d ", ptr[i]);
        }
        my_free(ptr);
    }
    return 0;
}
