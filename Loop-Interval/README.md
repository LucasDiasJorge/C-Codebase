# Executador de Função em Intervalos Regulares em C

Este projeto demonstra como executar uma função a cada intervalo de tempo definido em um programa C. O código exibe uma mensagem a cada `LOOP_TIME` segundos.

## Descrição

O código em C configura um loop infinito que executa uma função (neste caso, apenas uma mensagem de exemplo) a cada `LOOP_TIME` segundos. O valor de `LOOP_TIME` é definido como 3 segundos por padrão, mas pode ser ajustado conforme necessário.

## Código

```c
#include <stdio.h>
#include <time.h>

#define LOOP_TIME 3

int main() {

    time_t send_time = time(NULL) + LOOP_TIME;
    time_t now = time(NULL);

    while(1){

        if (send_time <= now){
            // função aqui
            printf("Function Call example\n");
            send_time = time(NULL) + LOOP_TIME;
        }
        now = time(NULL);
    }

    return 0;

}
```

## Funcionalidade

- Define um intervalo de tempo (`LOOP_TIME`) para a execução da função.
- Executa uma função (ou código) a cada intervalo de tempo definido.
- Exibe uma mensagem "Function Call example" no console a cada `LOOP_TIME` segundos.

## Instruções para Compilação

Para compilar o código, utilize o seguinte comando:

```sh
gcc -o timed_function timed_function.c
```

## Execução

Para executar o programa compilado, utilize o comando:

```sh
./timed_function
```

## Saída Esperada

O programa exibirá a mensagem "Function Call example" no console a cada 3 segundos. O intervalo de tempo pode ser ajustado modificando o valor da constante `LOOP_TIME`.

## Notas

- O programa entra em um loop infinito e precisa ser interrompido manualmente (por exemplo, com `Ctrl+C`).
- Certifique-se de que o ambiente onde o programa está sendo executado permite a execução contínua de processos.