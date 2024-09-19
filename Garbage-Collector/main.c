#include <stdio.h>
#include <stdlib.h>

typedef struct MemBlock {
    void *ptr;
    struct MemBlock *next;
} MemBlock;

MemBlock *head = NULL;

// Função para adicionar um bloco de memória à lista
void add_mem_block(void *ptr) {
    MemBlock *block = (MemBlock *)malloc(sizeof(MemBlock));
    block->ptr = ptr;
    block->next = head;
    head = block;
}

// Função para remover um bloco de memória da lista
void remove_mem_block(void *ptr) {
    MemBlock *current = head;
    MemBlock *previous = NULL;

    while (current != NULL) {
        if (current->ptr == ptr) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }
}

// Função para simular "malloc" com gerenciamento
void* gc_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    add_mem_block(ptr);
    return ptr;
}

// Função para simular "free" com gerenciamento
void gc_free(void *ptr) {
    remove_mem_block(ptr);
    free(ptr);
}

// Função que atua como um "garbage collector", liberando toda a memória rastreada
void gc_collect() {
    MemBlock *current = head;
    while (current != NULL) {
        free(current->ptr);
        MemBlock *temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

int main() {
    // Alocando memória
    int *arr = (int *)gc_malloc(10 * sizeof(int));
    char *str = (char *)gc_malloc(50 * sizeof(char));

    // Fazendo algo com a memória
    for (int i = 0; i < 10; i++) {
        arr[i] = i * 2;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Liberando memória individualmente
    gc_free(arr);

    // Simulação de "garbage collection"
    gc_collect(); // Liberando toda a memória restante

    return 0;
}
