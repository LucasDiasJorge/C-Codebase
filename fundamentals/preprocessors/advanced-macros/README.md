# Advanced Macros in C

Este tutorial apresenta tecnicas avancadas de macros em C, com foco em seguranca, legibilidade e uso profissional.

## Objetivos

- Entender stringification (`#`) e token pasting (`##`)
- Escrever macros de bloco com `do { ... } while (0)`
- Usar macros variadicas para logging
- Aplicar despacho por tipo com `_Generic` (C11)
- Criar tabelas centralizadas com X-Macros
- Fazer verificacoes em compilacao com `_Static_assert`

## Estrutura

```text
advanced-macros/
|- main.c
`- README.md
```

## Compilacao

```bash
gcc -std=c11 -Wall -Wextra -pedantic -o advanced main.c -lm
./advanced
```

## Inspecionar o preprocessamento

```bash
gcc -E -P main.c -o main.i
```

Arquivo gerado:

- `main.i`: codigo apos expansao do preprocessador

## Tecnicas Demonstradas

### 1) Stringification

```c
#define STR(x) #x
#define XSTR(x) STR(x)
```

- `STR(VERSION)` gera o texto literal `"VERSION"`
- `XSTR(VERSION)` expande primeiro e depois transforma em string

### 2) Token Pasting

```c
#define CAT(a, b) a##b
```

Permite formar identificadores em tempo de preprocessamento.

### 3) Macro de bloco segura

```c
#define SWAP(T, a, b)            \
    do {                         \
        T _swap_tmp_ = (a);      \
        (a) = (b);               \
        (b) = _swap_tmp_;        \
    } while (0)
```

Padrao recomendado para macros com multiplas instrucoes.

### 4) Macro variadica

```c
#define LOG_INFO(fmt, ...) \
    fprintf(stderr, "[INFO] %s:%d: " fmt "\\n", __FILE__, __LINE__, __VA_ARGS__)
```

Util para logs com contexto automatico (`__FILE__` e `__LINE__`).

### 5) `_Generic` para escolher funcao por tipo

```c
#define ABS(x) _Generic((x), int: abs_int, long: abs_long, float: abs_float, double: abs_double)(x)
```

Ajuda a manter interface simples com comportamento tipado.

### 6) X-Macros

```c
#define COLOR_TABLE(X) \
    X(RED, 31)         \
    X(GREEN, 32)       \
    X(BLUE, 34)
```

A mesma tabela gera enum, strings e codigos, evitando repeticao.

## Boas Praticas

- Sempre parentizar argumentos e expressao final em macros aritmeticas
- Evitar efeitos colaterais (`i++`) em argumentos de macro
- Preferir `static inline` quando macro nao for essencial
- Usar `_Generic` para APIs tipadas em C11
- Testar expansao com `gcc -E`

## Exercicios Propostos

1. Adicionar `YELLOW` e `MAGENTA` na `COLOR_TABLE`.
2. Criar uma macro `CLAMP(x, min, max)` segura.
3. Transformar `LOG_INFO` em `LOG(level, fmt, ...)`.
4. Criar uma versao de `ABS` para `long long` e `long double`.

## Referencias

- https://en.cppreference.com/w/c/preprocessor
- https://en.cppreference.com/w/c/language/generic
- https://gcc.gnu.org/onlinedocs/cpp/Macro-Pitfalls.html
