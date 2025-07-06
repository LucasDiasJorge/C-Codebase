# 🔢 Inversão de Números - Algoritmo Matemático

## 📖 Conceito

Este programa demonstra como **inverter os dígitos de um número** usando apenas operações matemáticas (divisão e módulo). É um excelente exercício para entender manipulação numérica e operadores aritméticos.

## 🎯 Objetivos de Aprendizado

- Compreender operadores de divisão (`/`) e módulo (`%`)
- Aplicar matemática para manipulação de dígitos
- Entender posicionamento decimal
- Praticar operações aritméticas compostas

## 💻 Algoritmo Explicado

### Número Original: `123`

#### Passo 1: Extrair Dígitos
```cpp
int inicial = 123;

// Extrair cada dígito:
// Unidade (3): inicial % 10 = 123 % 10 = 3
// Dezena (2):  (inicial / 10) % 10 = (123 / 10) % 10 = 12 % 10 = 2  
// Centena (1): inicial / 100 = 123 / 100 = 1
```

#### Passo 2: Imprimir Invertido
```cpp
// Imprime na ordem inversa:
cout << inicial % 100 % 10 / 1;    // 3 (unidade)
cout << inicial % 100 / 10;        // 2 (dezena)  
cout << inicial / 100;             // 1 (centena)
// Resultado: 321
```

#### Passo 3: Calcular Número Invertido
```cpp
int final = (inicial / 100) +                    // 1 * 1 = 1
            (((inicial / 10) % 10) * 10) +       // 2 * 10 = 20  
            (((inicial % 100) % 10) * 100);      // 3 * 100 = 300
// final = 1 + 20 + 300 = 321
```

## 🔍 Análise Detalhada das Operações

### Operador Módulo (`%`)
```cpp
123 % 10 = 3    // Resto da divisão por 10 (último dígito)
123 % 100 = 23  // Resto da divisão por 100 (últimos 2 dígitos)
```

### Operador Divisão (`/`)
```cpp
123 / 10 = 12   // Divisão inteira remove último dígito
123 / 100 = 1   // Divisão inteira deixa apenas primeiro dígito
```

### Combinação de Operadores
```cpp
(123 / 10) % 10 = 12 % 10 = 2  // Extrai dígito do meio
```

## 📊 Exemplo com Diferentes Números

| Número | Unidade | Dezena | Centena | Invertido |
|--------|---------|--------|---------|-----------|
| 123 | 3 | 2 | 1 | 321 |
| 456 | 6 | 5 | 4 | 654 |
| 789 | 9 | 8 | 7 | 987 |

## 🚀 Execução do Programa

### Compilação:
```bash
g++ -o inverter inverter-numero.cpp
```

### Execução:
```bash
./inverter
```

### Saída:
```
Valor inicial:123
Valor Inverso:321
Valor final Variavel:321
```

## 🎨 Variações e Melhorias

### 1. Versão Genérica (qualquer tamanho)
```cpp
int inverterNumero(int num) {
    int invertido = 0;
    while (num > 0) {
        invertido = invertido * 10 + num % 10;
        num /= 10;
    }
    return invertido;
}
```

### 2. Versão com Validação
```cpp
#include <iostream>
using namespace std;

int main() {
    int numero;
    cout << "Digite um número: ";
    cin >> numero;
    
    if (numero < 0) {
        cout << "Número deve ser positivo!" << endl;
        return 1;
    }
    
    // ... resto do código
}
```

### 3. Versão em C Puro
```c
#include <stdio.h>

int main() {
    int inicial = 123;
    
    printf("Valor inicial: %d\n", inicial);
    printf("Valor Inverso: %d%d%d\n", 
           inicial % 10,
           (inicial / 10) % 10,
           inicial / 100);
    
    return 0;
}
```

### 4. Versão com Contagem de Dígitos
```cpp
int contarDigitos(int num) {
    int count = 0;
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}
```

## 🧮 Matemática Por Trás

### Decomposição Decimal
Um número decimal pode ser decomposto como:
```
123 = 1×10² + 2×10¹ + 3×10⁰
123 = 100 + 20 + 3
```

### Inversão = Reposicionamento
```
Original:  1×10² + 2×10¹ + 3×10⁰ = 123
Invertido: 3×10² + 2×10¹ + 1×10⁰ = 321
```

## ⚡ Otimizações

### Versão Mais Eficiente
```cpp
int inverter(int n) {
    int resultado = 0;
    while (n) {
        resultado = resultado * 10 + n % 10;
        n /= 10;
    }
    return resultado;
}
```

### Comparação de Performance
| Método | Operações | Eficiência |
|--------|-----------|------------|
| **Fixo (3 dígitos)** | 6 | O(1) |
| **Loop genérico** | ~3n | O(log n) |
| **Recursivo** | ~3n + stack | O(log n) |

## 🎯 Aplicações Práticas

### ✅ Casos de Uso:
- **Palíndromos**: Verificar se número é igual ao seu inverso
- **Processamento**: Manipulação de códigos numéricos
- **Criptografia**: Transformações numéricas simples
- **Validação**: Verificar dígitos verificadores

### Exemplo - Verificar Palíndromo:
```cpp
bool ehPalindromo(int num) {
    return num == inverterNumero(num);
}
```

## 📚 Conceitos C++ Demonstrados

- **Operadores Aritméticos**: `/`, `%`, `*`, `+`
- **Variáveis**: Declaração e manipulação
- **Stream I/O**: `cout`, `endl`
- **Precedência**: Ordem de operações matemáticas
- **Casting Implícito**: Divisão inteira
- **Algoritmos**: Lógica de manipulação numérica

## 🎓 Exercícios Propostos

1. **Modificar** para aceitar números de 4 dígitos
2. **Implementar** verificador de palíndromos
3. **Criar** versão que preserva zeros à esquerda
4. **Adicionar** validação de entrada do usuário
5. **Implementar** em outras linguagens

Este exemplo fundamental demonstra como operações matemáticas simples podem resolver problemas complexos, sendo uma excelente introdução aos algoritmos numéricos em programação.
