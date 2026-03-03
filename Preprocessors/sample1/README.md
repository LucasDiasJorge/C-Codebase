# 📝 Preprocessor Sample 1 - Constantes com #define

Este módulo demonstra o uso básico de `#define` para criar constantes em C.

## 📝 Descrição

Exemplo simples de como usar diretivas de preprocessador para definir constantes que são substituídas em tempo de compilação.

## 📁 Estrutura

```
sample1/
└── main.c      # Exemplo de #define
```

## 🔧 Como Funciona

### Definição de Constante

```c
#define MAX 1000

int main(void) {
    int v[MAX];  // Array de 1000 elementos
    
    for (int i = 0; i < MAX; ++i) {
        printf("%i\n", i);
    }
    
    return EXIT_SUCCESS;
}
```

### Após Preprocessamento

```c
// MAX é substituído por 1000
int main(void) {
    int v[1000];
    
    for (int i = 0; i < 1000; ++i) {
        printf("%i\n", i);
    }
    
    return 0;
}
```

## 🚀 Compilação e Execução

```bash
gcc -o sample1 main.c
./sample1
```

### Ver resultado do preprocessador

```bash
gcc -E main.c -o main.i
cat main.i
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `#define` | Definição de macro |
| Substituição textual | Troca em tempo de compilação |
| Constantes simbólicas | Nomes significativos |

## 🔄 Alternativa Moderna: const

```c
// #define (macro)
#define MAX 1000

// const (variável)
const int MAX = 1000;

// enum (para inteiros)
enum { MAX = 1000 };
```

### Diferenças

| Aspecto | #define | const |
|---------|---------|-------|
| Tipo | Nenhum | Tipado |
| Escopo | Global | Pode ser local |
| Debug | Substituído | Visível |
| Memória | Nenhuma | Pode usar |

## ⚠️ Cuidados com #define

```c
// PROBLEMA: Falta parênteses
#define SQUARE(x) x * x
int a = SQUARE(2 + 3);  // 2 + 3 * 2 + 3 = 11, não 25!

// CORRETO
#define SQUARE(x) ((x) * (x))
int a = SQUARE(2 + 3);  // ((2 + 3) * (2 + 3)) = 25
```

## 📚 Referências

- [C Preprocessor](https://en.cppreference.com/w/c/preprocessor)
- [#define directive](https://en.cppreference.com/w/c/preprocessor/replace)
