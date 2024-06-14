#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000 // Número de iterações

// Função que usa multiplicação
void multiply_loop(int *result, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = i * 5;
    }
}

// Função que usa adição (redução de força)
void add_loop(int *result, int n) {
    int temp = 0;
    for (int i = 0; i < n; i++) {
        result[i] = temp;
        temp += 5;
    }
}

// Função para medir o tempo de execução
double benchmark(void (*func)(int*, int), int *result, int n) {
    clock_t start, end;
    start = clock();
    func(result, n);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

int main() {
    // Alocar memória para o array result
    int *result = (int *)malloc(N * sizeof(int));
    if (result == NULL) {
        printf("Erro ao alocar memória\n");
        return 1;
    }

    // Medir o tempo de execução do loop com multiplicação
    double time_multiply = benchmark(multiply_loop, result, N);
    printf("Tempo de execução (multiplicação): %f segundos\n", time_multiply);

    // Medir o tempo de execução do loop com adição
    double time_add = benchmark(add_loop, result, N);
    printf("Tempo de execução (adição): %f segundos\n", time_add);

    // Liberar memória alocada
    free(result);

    return 0;
}
