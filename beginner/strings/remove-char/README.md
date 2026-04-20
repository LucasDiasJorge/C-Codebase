# 🔤 Remove Character - Remoção de Caracteres em Strings

Este módulo demonstra como remover um caractere específico de uma string em C.

## 📝 Descrição

A função `removeChar()` percorre uma string e remove todas as ocorrências de um caractere especificado, modificando a string original in-place.

## 📁 Estrutura

```
Remove-char/
└── main.c      # Implementação da função de remoção
```

## 🔧 Como Funciona

### Função `removeChar()`

```c
void removeChar(char *str, char garbage) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}
```

**Algoritmo:**
1. Usa dois ponteiros: `src` (leitura) e `dst` (escrita)
2. Percorre a string com `src`
3. Copia caractere para `dst` apenas se não for o "lixo"
4. Finaliza com `\0`

## 🚀 Compilação e Execução

```bash
gcc -o remove_char main.c
./remove_char
```

## 📤 Exemplo de Uso

```c
char mac[] = "XX:XX:XX:XX:XX:XX";
removeChar(mac, ':');
// Resultado: "XXXXXXXXXXXX"
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| Ponteiros | Manipulação direta da memória |
| In-place modification | Modifica string sem alocar nova memória |
| Strings em C | Arrays de caracteres terminados em `\0` |

## ⚠️ Observações

- A função modifica a string original
- A string deve ser mutável (não pode ser literal)
- Complexidade: O(n) onde n é o tamanho da string

## 📚 Referências

- [Strings em C](https://en.cppreference.com/w/c/string/byte)
- [Ponteiros em C](https://en.cppreference.com/w/c/language/pointer)
