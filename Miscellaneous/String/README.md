# 🔄 String Replace - Substituição de Caracteres

Este módulo demonstra como substituir caracteres em uma string em C.

## 📝 Descrição

A função `replace_char()` percorre uma string e substitui todas as ocorrências de um caractere por outro.

## 📁 Estrutura

```
String/
└── main.c      # Implementação da substituição
```

## 🔧 Como Funciona

### Função `replace_char()`

```c
void replace_char(char *str, char find, char replace) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == find) {
            str[i] = replace;
        }
    }
}
```

**Algoritmo:**
1. Percorre cada caractere da string
2. Se encontrar o caractere alvo, substitui
3. Modifica a string in-place

## 🚀 Compilação e Execução

```bash
gcc -o string_replace main.c
./string_replace
```

## 📤 Exemplo de Uso

```c
char nome[] = "Lucas Dias Borge";
replace_char(nome, 'B', 'J');
printf("%s\n", nome);  // "Lucas Dias Jorge"
```

## 💡 Variações Úteis

### Substituir todas as ocorrências (case-insensitive)
```c
void replace_char_ci(char *str, char find, char replace) {
    char find_lower = tolower(find);
    char find_upper = toupper(find);
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == find_lower || str[i] == find_upper) {
            str[i] = replace;
        }
    }
}
```

### Substituir string por string
```c
char* str_replace(const char *str, const char *old, const char *new) {
    // Implementação mais complexa com realocação
}
```

### Remover caractere (substituir por nada)
```c
void remove_char(char *str, char c) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != c) dst++;
    }
    *dst = '\0';
}
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| Arrays de caracteres | Strings em C |
| Modificação in-place | Sem alocação extra |
| Loops | Iteração sobre string |

## ⚠️ Observações

- A string deve ser mutável (não literal)
- Modifica a string original
- Para preservar original, faça cópia antes

```c
char original[] = "Hello";
char copia[100];
strcpy(copia, original);
replace_char(copia, 'l', 'x');
// original ainda é "Hello"
// copia agora é "Hexxo"
```

## 📊 Complexidade

- **Tempo:** O(n)
- **Espaço:** O(1)

## 📚 Referências

- [Strings em C](https://en.cppreference.com/w/c/string/byte)
- [strchr - encontrar caractere](https://en.cppreference.com/w/c/string/byte/strchr)
