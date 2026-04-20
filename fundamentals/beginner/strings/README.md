# 🔤 Strings - Manipulação de Strings em C

Este módulo contém exemplos de manipulação de strings em C para iniciantes.

## 📝 Descrição

Coleção de funções úteis para trabalhar com strings em C, demonstrando operações comuns que todo programador deve conhecer.

## 📁 Estrutura

```
Strings/
├── Remove-char/    # Remove caracteres de uma string
└── Starts_with/    # Verifica se string começa com prefixo
```

## 📚 Exemplos Incluídos

### 1. [Remove-char](remove-char/)
Remove todas as ocorrências de um caractere específico de uma string.

```c
char mac[] = "XX:XX:XX:XX:XX:XX";
removeChar(mac, ':');
// Resultado: "XXXXXXXXXXXX"
```

### 2. [Starts_with](starts-with/)
Verifica se uma string começa com um determinado prefixo.

```c
starts_with("Hello", "Hello World");  // true
starts_with("World", "Hello World");  // false
```

## 💡 Conceitos Abordados

| Conceito | Descrição |
|----------|-----------|
| Ponteiros | Navegação em strings |
| Modificação in-place | Alteração sem nova alocação |
| Comparação de memória | `memcmp()` para eficiência |
| Terminador null | `\0` em strings C |

## 🚀 Compilação

```bash
# Remove-char
cd Remove-char
gcc -o remove_char main.c

# Starts_with
cd Starts_with
gcc -o starts_with main.c
```

## 📖 Funções Úteis de String em C

| Função | Descrição | Header |
|--------|-----------|--------|
| `strlen()` | Tamanho da string | `<string.h>` |
| `strcpy()` | Copia string | `<string.h>` |
| `strcat()` | Concatena strings | `<string.h>` |
| `strcmp()` | Compara strings | `<string.h>` |
| `strchr()` | Encontra caractere | `<string.h>` |
| `strstr()` | Encontra substring | `<string.h>` |

## 📚 Referências

- [C String Library](https://en.cppreference.com/w/c/string/byte)
- [String Handling in C](https://www.tutorialspoint.com/c_standard_library/string_h.htm)
