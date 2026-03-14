# 🧠 Preprocessor Sample 4 - Advanced Macros

Este modulo documenta um tutorial avancado de macros em C.

## Conteudo

- Stringification (`#`) e token pasting (`##`)
- Macros variadicas para logging
- Macros seguras com `do { ... } while (0)`
- `_Generic` para despacho por tipo (C11)
- X-Macros para gerar enum/tabelas sem duplicacao
- `_Static_assert` para validacoes em compilacao

## Tutorial Completo

O codigo executavel e a explicacao completa estao em:

- `fundamentals/preprocessors/advanced-macros/main.c`
- `fundamentals/preprocessors/advanced-macros/README.md`

## Compilacao

```bash
cd fundamentals/preprocessors/advanced-macros
gcc -std=c11 -Wall -Wextra -pedantic -o advanced main.c -lm
./advanced
```
