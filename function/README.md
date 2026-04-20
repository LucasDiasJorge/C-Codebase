# ⚙️ Function - Funções Avançadas em C

Este módulo contém exemplos avançados de uso de funções em C.

## 📝 Descrição

Demonstrações de recursos avançados de funções em C, incluindo ponteiros de função e funções com argumentos variáveis.

## 📁 Estrutura

```
function/
├── README.md    # Guia do módulo
└── (exemplos em fundamentals/function/)
```

## 📚 Tópicos Incluídos

### 1. [pointers](../fundamentals/function/pointers/)
Ponteiros de função permitem tratar funções como dados, possibilitando callbacks, tabelas de funções e polimorfismo em C.

```c
// Declaração de ponteiro de função
int (*operation)(int, int);

// Atribuição
operation = add;

// Chamada
int result = operation(5, 3);  // 8
```

### 2. [stdarg](../fundamentals/function/stdarg/)
Funções variadic aceitam número variável de argumentos, como `printf()`.

```c
#include <stdarg.h>

int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    
    va_end(args);
    return total;
}

// Uso
sum(3, 10, 20, 30);  // 60
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| Ponteiros de função | Funções como dados |
| Callbacks | Funções passadas como argumento |
| `va_list` | Lista de argumentos variáveis |
| `va_start/va_arg/va_end` | Macros para variadic |

## 📚 Referências

- [Function Pointers](https://en.cppreference.com/w/c/language/pointer#Pointers_to_functions)
- [stdarg.h](https://en.cppreference.com/w/c/variadic)
