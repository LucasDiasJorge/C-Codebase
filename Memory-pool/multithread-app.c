#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define the size of the memory pool and the size of each memory block
#define POOL_SIZE 10000
#define BLOCK_SIZE 64

// Structure to represent a memory block
typedef struct {
    char data[BLOCK_SIZE]; // Data stored in the memory block
    int is_allocated;      // Flag indicating whether the block is currently allocated
} MemoryBlock;

// Structure to represent the memory pool
typedef struct {
    MemoryBlock blocks[POOL_SIZE]; // Array of memory blocks
    pthread_mutex_t mutex;         // Mutex for thread safety
} MemoryPool;

// Function to initialize the memory pool
void initializeMemoryPool(MemoryPool *pool) {
    pthread_mutex_init(&pool->mutex, NULL); // Initialize mutex
    for (int i = 0; i < POOL_SIZE; i++) {
        pool->blocks[i].is_allocated = 0; // Mark all blocks as unallocated
    }
}

// Function to allocate memory from the memory pool
void *poolAllocate(MemoryPool *pool) {
    pthread_mutex_lock(&pool->mutex); // Lock mutex
    for (int i = 0; i < POOL_SIZE; i++) {
        if (!pool->blocks[i].is_allocated) { // Find the first unallocated block
            pool->blocks[i].is_allocated = 1; // Mark the block as allocated
            pthread_mutex_unlock(&pool->mutex); // Unlock mutex
            return pool->blocks[i].data; // Return a pointer to the data in the block
        }
    }
    pthread_mutex_unlock(&pool->mutex); // Unlock mutex
    // Return NULL if no free block is found
    return NULL;
}

// Function to deallocate memory from the memory pool
void poolDeallocate(MemoryPool *pool, void *ptr) {
    pthread_mutex_lock(&pool->mutex); // Lock mutex
    // Find the block corresponding to the pointer
    for (int i = 0; i < POOL_SIZE; i++) {
        if (ptr == pool->blocks[i].data) {
            pool->blocks[i].is_allocated = 0; // Mark the block as unallocated
            pthread_mutex_unlock(&pool->mutex); // Unlock mutex
            return;
        }
    }
    pthread_mutex_unlock(&pool->mutex); // Unlock mutex
}

// Thread function
void *threadFunction(void *arg) {
    MemoryPool *pool = (MemoryPool *)arg;
    char *ptr = (char *)poolAllocate(pool);
    if (ptr != NULL) {
        sprintf(ptr, "Hello from thread %ld", pthread_self());
        printf("%s\n", ptr);
        poolDeallocate(pool, ptr);
    } else {
        printf("Failed to allocate memory in thread %ld\n", pthread_self());
    }
    return NULL;
}

int main() {
    MemoryPool pool;
    initializeMemoryPool(&pool);

    // Create multiple threads
    pthread_t threads[5];
    for (int i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, threadFunction, &pool) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    // Join threads
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
