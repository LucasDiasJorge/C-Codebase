# 🧮 Calculator - Calculadora Simples

Este módulo implementa uma calculadora básica de linha de comando em C.

## 📝 Descrição

A calculadora aceita expressões matemáticas simples no formato `número operador número` e realiza as quatro operações básicas.

## 📁 Estrutura

```
Calculator/
└── main.c      # Implementação da calculadora
```

## 🔧 Operações Suportadas

| Operador | Operação |
|----------|----------|
| `+` | Adição |
| `-` | Subtração |
| `*` | Multiplicação |
| `/` | Divisão |

## 🔧 Funções Implementadas

```c
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        printf("Erro: Divisão por zero!\n");
        return 0;
    }
    return a / b;
}
```

## 🚀 Compilação e Execução

```bash
gcc -o calculator main.c
./calculator
```

## 📤 Exemplo de Uso

```
Digite a expressão (ex: 5 + 3): 10 * 5
Resultado: 50.00

Digite a expressão (ex: 5 + 3): 20 / 4
Resultado: 5.00

Digite a expressão (ex: 5 + 3): 100 / 0
Erro: Divisão por zero!
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `scanf()` | Leitura formatada de entrada |
| `switch/case` | Seleção de operação |
| Ponteiros de função | Alternativa elegante |
| Tratamento de erros | Divisão por zero |

## 🔄 Versão com Ponteiros de Função

```c
typedef double (*operation)(double, double);

operation get_operation(char op) {
    switch(op) {
        case '+': return add;
        case '-': return subtract;
        case '*': return multiply;
        case '/': return divide;
        default: return NULL;
    }
}

// Uso
operation func = get_operation('+');
double result = func(5, 3);  // 8.0
```

## ⚠️ Limitações

- Apenas duas operandos por vez
- Não suporta parênteses
- Não mantém histórico
- Não suporta operações encadeadas

## 🔄 Possíveis Extensões

1. Parser de expressões completas
2. Suporte a funções matemáticas (sin, cos, sqrt)
3. Histórico de operações
4. Variáveis e memória
5. Interface gráfica

## 📚 Referências

- [scanf - C Reference](https://en.cppreference.com/w/c/io/fscanf)
- [Function Pointers in C](https://www.geeksforgeeks.org/function-pointer-in-c/)
