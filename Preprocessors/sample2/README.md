# 📝 Preprocessor Sample 2 - Macros com Parâmetros

Este módulo demonstra o uso de macros com parâmetros para criar funções inline.

## 📝 Descrição

Exemplo de como criar uma macro `swap()` que troca valores de duas variáveis, usado em um algoritmo de Selection Sort.

## 📁 Estrutura

```
sample2/
└── main.c      # Exemplo de macro swap
```

## 🔧 Como Funciona

### Definição da Macro Swap

```c
#define swap(A, B) { int t = A; A = B; B = t; }
```

### Uso no Selection Sort

```c
void selection_sort(int n, int v[]) {
    for (int i = 0; i < n-1; i++) {
        int k = i;
        for (int j = i+1; j < n; j++) {
            if (v[j] < v[k]) k = j;
        }
        swap(v[i], v[k]);  // Macro expandida aqui
    }
}
```

### Após Preprocessamento

```c
// swap(v[i], v[k]) expande para:
{ int t = v[i]; v[i] = v[k]; v[k] = t; }
```

## 🚀 Compilação e Execução

```bash
gcc -o sample2 main.c
./sample2
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| Macros com parâmetros | Substituição com argumentos |
| Bloco de código | `{ }` para múltiplas instruções |
| Selection Sort | Algoritmo de ordenação |

## ⚠️ Cuidados com Macros

### Problema 1: Efeitos colaterais

```c
#define swap(A, B) { int t = A; A = B; B = t; }

// PERIGOSO:
swap(arr[i++], arr[j++]);  // i e j incrementados múltiplas vezes!
```

### Problema 2: Escopo de variável

```c
int t = 100;
swap(a, b);  // Cria outro 't' interno - OK, mas confuso
```

## 🔄 Alternativa: Função Inline

```c
static inline void swap_int(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Uso
swap_int(&v[i], &v[k]);
```

### Comparação

| Aspecto | Macro | Função Inline |
|---------|-------|---------------|
| Tipo seguro | ❌ | ✅ |
| Debug | Difícil | Fácil |
| Efeitos colaterais | Possíveis | Não |
| Performance | Igual | Igual |

## 📊 Selection Sort

```
Array inicial: [64, 25, 12, 22, 11]

Passo 1: [11, 25, 12, 22, 64]  (11 é o menor)
Passo 2: [11, 12, 25, 22, 64]  (12 é o menor)
Passo 3: [11, 12, 22, 25, 64]  (22 é o menor)
Passo 4: [11, 12, 22, 25, 64]  (já ordenado)
```

## 📚 Referências

- [Selection Sort](https://en.wikipedia.org/wiki/Selection_sort)
- [Inline Functions](https://en.cppreference.com/w/c/language/inline)
