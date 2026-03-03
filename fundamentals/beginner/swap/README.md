# Swap de Variáveis em C

Este projeto demonstra três métodos diferentes para trocar os valores de duas variáveis inteiras em C:

- Utilizando uma variável temporária
- Utilizando operações aritméticas
- Utilizando operações bitwise (XOR)

## Arquivos
- `main.c`: Exemplo de uso das funções de swap.
- `swap.c`: Implementação das funções de troca.
- `swap.h`: Cabeçalho esperado para declaração das funções (crie se necessário).

## Métodos de Troca

### 1. Troca com Variável Temporária
```c
void temp_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

### 2. Troca com Operações Aritméticas
```c
void arithmetic_swap(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
```

### 3. Troca com Operações Bitwise (XOR)
```c
void bitwise_swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}
```

## Exemplo de Execução

Ao executar o programa principal (`main.c`), a saída será:

```
Before swap: x = 5, y = 10
After swap: x = 10, y = 5
After arithmetic swap: x = 5, y = 10
After bitwise swap: x = 10, y = 5
```

## Como compilar

No terminal, execute:
```sh
gcc main.c swap.c -o swap
```

## Como executar

No terminal, execute:
```sh
./swap
```

## Licença
Este projeto é apenas para fins educacionais.
