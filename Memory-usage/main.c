#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void limit_memory_usage(size_t memory_limit_mb) {
    struct rlimit limit;
    limit.rlim_cur = memory_limit_mb * 1024 * 1024; // Convert MB to bytes
    limit.rlim_max = memory_limit_mb * 1024 * 1024; // Convert MB to bytes

    if (setrlimit(RLIMIT_AS, &limit) != 0) {
        perror("Erro ao definir limite de memória");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Define um limite de memória de 100 MB
    limit_memory_usage(100);

    // Código do programa...
    // Tentar alocar mais memória do que o limite definido causará uma falha de alocação
    char *memory = malloc(150 * 1024 * 1024); // Tenta alocar 150 MB

    if (memory == NULL) {
        perror("Falha na alocação de memória");
    } else {
        printf("Alocação de memória bem-sucedida\n");
        free(memory);
    }

    return 0;
}
