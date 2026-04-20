# 🎯 Miscellaneous - Projetos Diversos

Este módulo contém uma coleção de programas diversos e utilitários em C.

## 📝 Descrição

Coleção de programas variados que demonstram diferentes técnicas e algoritmos em C.

## 📁 Estrutura

```
miscellaneous/
├── ascii.c              # Tabela ASCII
├── os.c                 # Detecção de sistema operacional
├── reverse-number.c     # Inverter número
├── anagram/             # Verificador de anagramas
├── calculator/          # Calculadora simples
├── linus/               # Citações do Linus Torvalds
├── random-generator/    # Gerador de números aleatórios
└── string/              # Manipulação de strings
```

## 📚 Programas Incluídos

### 1. [anagram](anagram/)
Verifica se duas strings são anagramas usando contagem de frequência.

### 2. [calculator](calculator/)
Calculadora de linha de comando com as 4 operações básicas.

### 3. [random-generator](random-generator/)
Gerador de números pseudo-aleatórios com seed baseado no tempo.

### 4. [string](string/)
Funções de manipulação de strings como substituição de caracteres.

### 5. ascii.c
Imprime a tabela ASCII completa.

### 6. os.c
Detecta o sistema operacional usando macros do preprocessador.

### 7. reverse-number.c
Inverte um número inteiro (ex: 123 → 321).

## 🚀 Compilação

```bash
# Compilar todos os exemplos
gcc -o ascii ascii.c
gcc -o os os.c
gcc -o reverse reverse-number.c
```

## 💡 Conceitos Demonstrados

| Programa | Conceitos |
|----------|-----------|
| Anagram | Arrays, frequência, strings |
| Calculator | scanf, switch, funções |
| Random | srand, rand, time |
| String | Ponteiros, loops |
| os.c | Preprocessadores, macros |

## 📚 Referências

- [ASCII Table](https://www.asciitable.com/)
- [Random Numbers in C](https://en.cppreference.com/w/c/numeric/random)
