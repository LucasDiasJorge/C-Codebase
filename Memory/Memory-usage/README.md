# Limitação de Memória em C

Este projeto demonstra como limitar o uso de memória de um processo em um programa C usando a função `setrlimit` para definir o limite de memória alocada.

## Descrição

O código em C configura um limite de memória para o processo atual e tenta alocar mais memória do que o limite definido para demonstrar como o sistema lida com tentativas de alocação de memória acima do limite.

## Funcionalidade

- Define um limite de memória de 100 MB para o processo atual.
- Tenta alocar 150 MB de memória.
- Exibe mensagens indicando se a alocação foi bem-sucedida ou se falhou devido ao limite de memória.

## Código

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void limit_memory_usage(size_t memory_limit_mb) {
    struct rlimit limit;
    limit.rlim_cur = memory_limit_mb * 1024 * 1024; // Converte MB para bytes
    limit.rlim_max = memory_limit_mb * 1024 * 1024; // Converte MB para bytes

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
```

## Instruções para Compilação

Para compilar o código, utilize o seguinte comando:

```sh
gcc -o limit_memory limit_memory.c
```

## Execução

Para executar o programa compilado, utilize o comando:

```sh
./limit_memory
```

## Saída Esperada

O programa tentará alocar 150 MB de memória, mas como o limite é definido para 100 MB, a alocação falhará e será exibida a seguinte mensagem:

```
Falha na alocação de memória
```

## Notas

- Certifique-se de que o seu sistema permite o ajuste de limites de memória para processos.
- O limite de memória definido é aplicado apenas ao processo atual e não afeta outros processos no sistema.