# 🔍 Starts With - Verificação de Prefixo

Este módulo demonstra como verificar se uma string começa com um determinado prefixo em C.

## 📝 Descrição

A função `starts_with()` verifica se uma string começa com um prefixo específico, usando comparação de memória eficiente.

## 📁 Estrutura

```
Starts_with/
└── main.c      # Implementação da função starts_with
```

## 🔧 Como Funciona

### Função `starts_with()`

```c
bool starts_with(const char *pre, const char *str) {
    size_t lenpre = strlen(pre);
    size_t lenstr = strlen(str);
    return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}
```

**Algoritmo:**
1. Calcula o tamanho do prefixo e da string
2. Se a string for menor que o prefixo, retorna `false`
3. Compara os primeiros `n` bytes usando `memcmp()`
4. Retorna `true` se forem iguais

## 🚀 Compilação e Execução

```bash
gcc -o starts_with main.c
./starts_with
```

## 📤 Exemplo de Uso

```c
starts_with("Hello", "Hello World");  // true
starts_with("World", "Hello World");  // false
starts_with("Hi", "Hello");           // false
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `memcmp()` | Comparação de blocos de memória |
| `strlen()` | Cálculo do tamanho de strings |
| `stdbool.h` | Tipo booleano em C |
| Operador ternário | Expressão condicional compacta |

## 🔄 Alternativas

### Usando `strncmp()`:
```c
bool starts_with(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}
```

### Loop manual:
```c
bool starts_with(const char *pre, const char *str) {
    while (*pre) {
        if (*pre++ != *str++) return false;
    }
    return true;
}
```

## 📊 Complexidade

- **Tempo:** O(n) onde n é o tamanho do prefixo
- **Espaço:** O(1)

## 📚 Referências

- [memcmp - C Reference](https://en.cppreference.com/w/c/string/byte/memcmp)
- [strncmp - C Reference](https://en.cppreference.com/w/c/string/byte/strncmp)
