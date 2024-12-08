# Uso de `union` em C

## Descrição

Este projeto demonstra o uso de uma `union` em C. A `union` é uma estrutura de dados que permite armazenar diferentes tipos de dados na mesma região de memória. No exemplo, utilizamos uma `union` chamada `Data`, que pode armazenar um `int`, um `float` ou uma string (`char[20]`). O objetivo é ilustrar como os dados são sobrescritos ao atribuir novos valores a diferentes membros da `union`.

## Estrutura de Dados

A `union` definida neste projeto contém três membros:
- `int i`: um inteiro.
- `float f`: um número de ponto flutuante.
- `char str[20]`: um vetor de caracteres para armazenar uma string.

### Exemplo de Uso

```c
union Data {
    int i;
    float f;
    char str[20];
};
```

## Funcionalidade

1. Inicializa a `union` com o valor `10` para o membro `i` (inteiro), e exibe o valor.
2. Atribui o valor `220.5` ao membro `f` (float) e exibe o valor.
3. Atribui a string `"C Programming"` ao membro `str`, sobrescrevendo os valores anteriores de `i` e `f`, e exibe a string.

## Resultado Esperado

A execução do programa irá gerar a seguinte saída:

```
data.i: 10
data.f: 220.50
data.str: C Programming
```

Observe que, como a `union` compartilha a mesma área de memória para todos os seus membros, a atribuição de um valor para um membro sobrescreve os valores dos outros membros.

## Compilação

Para compilar o código, você pode usar o seguinte comando:

```bash
gcc -o programa main.c
```

## Execução

Após compilar, execute o programa com:

```bash
./programa
```