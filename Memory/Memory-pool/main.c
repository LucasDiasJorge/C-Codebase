#include <stdio.h>
#include <stdlib.h>

// Define the maximum number of elements in the memory pool
#define POOL_SIZE 1000
// Define the size of each element
#define ELEMENT_SIZE sizeof(int)

// Structure to represent a memory pool
typedef struct {
    void *memory;     // Pointer to the memory pool
    int next_index;   // Index of the next available slot
} MemoryPool;

// Initialize the memory pool
void initializeMemoryPool(MemoryPool *pool) {
    // Allocate memory for the pool
    pool->memory = malloc(POOL_SIZE * ELEMENT_SIZE);
    if (pool->memory == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    // Initialize next_index to 0
    pool->next_index = 0;
}

// Allocate memory from the pool
void *poolAllocate(MemoryPool *pool) {
    // Check if there's space available in the pool
    if (pool->next_index < POOL_SIZE) {
        // Calculate the address of the next available slot
        void *address = (char *)pool->memory + (pool->next_index * ELEMENT_SIZE);
        // Increment next_index for the next allocation
        pool->next_index++;
        return address;
    } else {
        printf("Memory pool is full\n");
        return NULL;
    }
}

// Free memory pool
void freeMemoryPool(MemoryPool *pool) {
    // Free the memory allocated for the pool
    free(pool->memory);
}

int main() {
    MemoryPool pool;
    initializeMemoryPool(&pool);

    // Allocate memory from the pool
    int *ptr1 = (int *)poolAllocate(&pool);
    int *ptr2 = (int *)poolAllocate(&pool);

    // Use the allocated memory
    *ptr1 = 10;
    *ptr2 = 20;

    // Print the values
    printf("Value at ptr1: %d\n", *ptr1);
    printf("Value at ptr2: %d\n", *ptr2);

    // Free the memory pool
    freeMemoryPool(&pool);

    return 0;
}
