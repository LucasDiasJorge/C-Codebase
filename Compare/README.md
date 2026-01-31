# 📊 Compare - Funções de Comparação em C

Este módulo demonstra como criar funções genéricas de comparação para diferentes tipos de dados em C.

## 📝 Descrição

O código implementa funções para comparar e retornar o maior valor entre dois números, demonstrando:
- Sobrecarga de funções (através de nomes diferentes)
- Uso do operador ternário
- Trabalho com diferentes tipos numéricos (`int`, `long`)

## 📁 Estrutura

```
Compare/
└── main.c      # Implementação das funções de comparação
```

## 🔧 Funções Implementadas

### `maxInt(int a, int b)`
Compara dois valores inteiros e retorna o maior.

```c
int maxInt(int a, int b) {
    return (a > b) ? a : b;
}
```

### `maxLong(long a, long b)`
Compara dois valores long e retorna o maior.

```c
long maxLong(long a, long b) {
    return (a > b) ? a : b;
}
```

## 🚀 Compilação e Execução

```bash
gcc -o compare main.c
./compare
```

## 📤 Saída Esperada

```
O maior entre 10 e 20 é: 20
O maior entre 1000 e 2000 é: 2000
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| Operador Ternário | `(condição) ? valor_se_true : valor_se_false` |
| Tipos Numéricos | Diferença entre `int` e `long` |
| Funções de Retorno | Funções que retornam valores calculados |

## 🔄 Possíveis Extensões

- Adicionar comparação para `float` e `double`
- Implementar macros genéricas usando `_Generic` (C11)
- Criar função para comparar arrays

## 📚 Referências

- [C Data Types](https://en.cppreference.com/w/c/language/arithmetic_types)
- [Ternary Operator](https://en.cppreference.com/w/c/language/operator_other)
