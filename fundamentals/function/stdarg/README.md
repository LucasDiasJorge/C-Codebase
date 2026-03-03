# Projeto `stdarg.h` em C

## Descrição

O cabeçalho `<stdarg.h>` fornece macros e tipos úteis para a criação de funções que aceitam um número variável de argumentos. Esse cabeçalho é essencial quando você precisa definir funções sem um número fixo de argumentos, facilitando o planejamento e a implementação de funções mais flexíveis.

## Tipos

- **`va_list`**: Armazena os valores passados como argumentos em uma função que utiliza argumentos variáveis.

## Macros

- **`va_start(va_list nTermos, ...)`**: Inicializa a variável `nTermos` para acessar os argumentos variáveis passados para a função. Deve ser chamada antes de qualquer chamada a `va_arg`.

- **`va_arg(va_list nTermos, tipo)`**: Recupera o próximo argumento da lista. O tipo especificado deve corresponder ao tipo do argumento a ser recuperado.

- **`va_end(va_list nTermos)`**: Limpa a memória utilizada pela lista de argumentos. Deve ser chamada imediatamente antes de a função retornar.

## Exemplo de Código

Aqui está um exemplo de como usar o cabeçalho `<stdarg.h>` para criar uma função que multiplica um número variável de argumentos:

```c
#include <stdio.h>
#include <stdarg.h>

// Função que multiplica um número variável de argumentos
int multiplica(int nTermos, ...) {
    va_list listaTermos;
    va_start(listaTermos, nTermos);

    int resultado = 1;

    for (int i = 0; i < nTermos; i++)
        resultado = resultado * va_arg(listaTermos, int);

    va_end(listaTermos);

    return resultado;
}

int main() {
    printf("8! = %d\n", multiplica(7, 8, 7, 6, 5, 4, 3, 2)); // Primeiro 7 eh o numero de termos

    return 0;
}
```

## Compilação e Execução

Para compilar e executar o código, siga os comandos abaixo:

1. **Compilação**:

   ```bash
   gcc main.c -o main
   ```

2. **Execução**:

   ```bash
   ./main
   ```

   A saída esperada é:

   ```
   8! = 40320
   ```
