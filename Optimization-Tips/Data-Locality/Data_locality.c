#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000 // Tamanho da matriz

// Função com boa localidade de dados
void good_locality(int **matrix, int *result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += matrix[i][j];
        }
    }
}

// Função com má localidade de dados
void bad_locality(int **matrix, int *result, int n) {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            result[i] += matrix[i][j];
        }
    }
}

// Função para medir o tempo de execução
double benchmark(void (*func)(int**, int*, int), int **matrix, int *result, int n) {
    clock_t start, end;
    start = clock();
    func(matrix, result, n);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

int main() {
    // Alocar memória para a matriz e o array result
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(N * sizeof(int));
    }

    int *result = (int *)malloc(N * sizeof(int));
    if (matrix == NULL || result == NULL) {
        printf("Erro ao alocar memória\n");
        return 1;
    }

    // Inicializar matriz e resultado
    for (int i = 0; i < N; i++) {
        result[i] = 0;
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 1;
        }
    }

    // Medir o tempo de execução com boa localidade de dados
    double time_good = benchmark(good_locality, matrix, result, N);
    printf("Tempo de execução (boa localidade): %f segundos\n", time_good);

    // Reinicializar o array result
    for (int i = 0; i < N; i++) {
        result[i] = 0;
    }

    // Medir o tempo de execução com má localidade de dados
    double time_bad = benchmark(bad_locality, matrix, result, N);
    printf("Tempo de execução (má localidade): %f segundos\n", time_bad);

    // Liberar memória alocada
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(result);

    return 0;
}
