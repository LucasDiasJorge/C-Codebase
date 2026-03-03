# 🤖 Autômatos (DFA) em C

Este exemplo implementa um **autômato finito determinístico (DFA)** para validar se uma string pertence a um pequeno conjunto de palavras reservadas.

No estado atual, o DFA reconhece:
- `for`
- `float`
- `char`

## 📌 Como funciona

- Cada estado é representado pelo enum `State`.
- A função `next_state()` define as transições de estado, caractere a caractere.
- A string é **aceita** quando o processamento termina em um estado final (`Q4_END` ou `Q7_END`).

## ▶️ Como compilar e executar

### Linux / WSL
```bash
gcc -Wall -Wextra -std=c11 -O2 -o automatus main.c
./automatus
```

### Windows (MinGW/MSYS2)
```powershell
gcc -Wall -Wextra -std=c11 -O2 -o automatus.exe main.c
.\automatus.exe
```

## 🧪 Exemplos

O `main()` chama `proccess_string()` com algumas entradas para demonstrar aceitação/rejeição.

Sugestão: troque/adicione chamadas como:
- `proccess_string("char");`
- `proccess_string("float");`
- `proccess_string("for");`
- `proccess_string("while");`

## 💡 Ideias de extensão

- Adicionar novas palavras reservadas (criando novos estados e transições).
- Exibir o caminho de estados percorrido durante o processamento.
- Separar o DFA em um módulo (`automatus.c/.h`) para reutilização.
