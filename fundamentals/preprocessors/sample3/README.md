# 📝 Preprocessor Sample 3 - Include com Arquivos Texto

Este módulo demonstra o uso de `#include` com arquivos `.txt` contendo código C.

## 📝 Descrição

Exemplo avançado mostrando que `#include` pode incluir qualquer arquivo de texto, não apenas `.h`. Demonstra compartilhamento de declarações entre múltiplos arquivos.

## 📁 Estrutura

```
sample3/
├── sample1.c     # Programa principal 1
├── sample2.c     # Programa principal 2
├── aaa.txt       # Declarações compartilhadas
└── includes.txt  # Documentação dos includes
```

## 🔧 Como Funciona

### Arquivo de Declarações (aaa.txt)

```c
int GLOB = 16;
int func(int e);
```

### Programa 1 (sample1.c)

```c
#include "aaa.txt"

int main(void) {
    while (GLOB <= 64) {
        printf("%d\n", GLOB);
        GLOB *= 2;
    }
    return EXIT_SUCCESS;
}
```

### Programa 2 (sample2.c)

```c
#include <stdio.h>
#include <math.h>
#include "aaa.txt"

#define PI 3.141592653589

int main(void) {
    double y = sin(PI/4);
    printf("%f\n", y);
    return EXIT_SUCCESS;
}
```

## 🚀 Compilação e Execução

```bash
# Compilar sample1
gcc -o sample1 sample1.c
./sample1

# Compilar sample2
gcc -o sample2 sample2.c -lm
./sample2
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `#include "arquivo"` | Inclui arquivo local |
| Compartilhamento de código | Mesmas declarações em múltiplos arquivos |
| Variáveis globais | Declaração compartilhada |

## ⚠️ Por que usar .txt?

Na prática, **não é recomendado**. Use `.h` para:
- Clareza de propósito
- IDEs reconhecem como header
- Convenção da comunidade

Este exemplo é **educacional** para mostrar que o preprocessador é uma substituição textual simples.

## 📊 Processo de Compilação

```
┌─────────────┐     ┌─────────────┐
│  sample1.c  │     │   aaa.txt   │
└──────┬──────┘     └──────┬──────┘
       │    #include       │
       └─────────┬─────────┘
                 │
         ┌───────▼───────┐
         │ Preprocessador │
         └───────┬───────┘
                 │
         ┌───────▼───────┐
         │ Código unido  │
         └───────┬───────┘
                 │
         ┌───────▼───────┐
         │  Compilador   │
         └───────┬───────┘
                 │
         ┌───────▼───────┐
         │  Executável   │
         └───────────────┘
```

## 🔄 Forma Correta (Header Guards)

```c
// declaracoes.h
#ifndef DECLARACOES_H
#define DECLARACOES_H

extern int GLOB;  // Declaração (extern)
int func(int e);

#endif

// declaracoes.c
int GLOB = 16;    // Definição

// main.c
#include "declaracoes.h"
```

## 📚 Referências

- [#include directive](https://en.cppreference.com/w/c/preprocessor/include)
- [Header Files](https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html)
