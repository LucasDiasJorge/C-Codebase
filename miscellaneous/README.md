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
├── calculator/          # Calculadora simples
├── random-generator/    # Gerador de números aleatórios
└── string/              # Manipulação de strings
```

## 📚 Programas Incluídos

### 1. [calculator](calculator/)
Calculadora de linha de comando com as 4 operações básicas.

### 2. [random-generator](random-generator/)
Gerador de números pseudo-aleatórios com seed baseado no tempo.

### 3. [string](string/)
Funções de manipulação de strings como substituição de caracteres.

### 4. ascii.c
Imprime a tabela ASCII completa.

### 5. os.c
Detecta o sistema operacional usando macros do preprocessador.

### 6. reverse-number.c
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
| Calculator | scanf, switch, funções |
| Random | srand, rand, time |
| String | Ponteiros, loops |
| os.c | Preprocessadores, macros |

## 📚 Referências

- [ASCII Table](https://www.asciitable.com/)
- [Random Numbers in C](https://en.cppreference.com/w/c/numeric/random)
