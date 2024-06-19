# Benchmark de Técnicas de Otimização em C

## Descrição do Projeto

Este projeto implementa e compara duas técnicas de otimização de loops em C: a multiplicação tradicional e a redução de força (strength reduction). A redução de força é uma técnica de otimização que substitui operações caras, como multiplicações, por operações mais baratas, como adições. Este projeto mede o tempo de execução de ambas as técnicas para demonstrar a eficácia da otimização.

## Estrutura do Código

O código consiste em três partes principais:

1. **Função `multiply_loop`**: Implementa um loop que utiliza a multiplicação para calcular os valores.
2. **Função `add_loop`**: Implementa um loop que utiliza a adição em vez da multiplicação, aplicando a técnica de redução de força.
3. **Função `benchmark`**: Mede o tempo de execução de uma função passada como parâmetro.

O programa principal (`main`) aloca memória para um array de inteiros, executa ambas as funções de loop, mede o tempo de execução de cada uma e imprime os resultados.

## Código

```c
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
```

## Instruções para Compilação e Execução

Salvar o Código: Salve o código acima em um arquivo chamado benchmark.c.
    
#### Compilar o Código: 

Use um compilador como gcc para compilar o código:

```sh
gcc -o benchmark benchmark.c -O2
```

A flag -O2 é usada para permitir otimizações padrão no compilador.

#### Executar o Código: 

Execute o programa compilado:

```sh
    ./benchmark
```

#### Análise dos Resultados

O programa executará os dois loops (um com multiplicação e outro com adição) e imprimirá o tempo de execução de cada um. Compare os tempos de execução para verificar a diferença de desempenho entre os dois métodos. A técnica de redução de força deve mostrar uma melhoria de desempenho, ilustrando como mudanças na forma de realizar operações aritméticas podem resultar em ganhos significativos de performance.
