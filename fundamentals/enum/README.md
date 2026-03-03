
# Dias da Semana em C

Este projeto é um exemplo simples em C que utiliza uma enumeração (`enum`) para representar os dias da semana. Ele exibe o dia correspondente baseado no valor atribuído a uma variável do tipo `enum`.

## 📋 Descrição

O programa define uma enumeração chamada `DiasDaSemana`, que contém os dias da semana de domingo a sábado. O código inicializa uma variável com o valor de um dia da semana (neste caso, `QUARTA`) e usa uma estrutura de controle `switch` para imprimir o nome do dia correspondente no console.

### Estrutura do Código

1. **Definição da Enumeração**: 
   ```c
   enum DiasDaSemana {
       DOMINGO,
       SEGUNDA,
       TERCA,
       QUARTA,
       QUINTA,
       SEXTA,
       SABADO
   };
   ```

2. **Lógica Principal**:
   - Uma variável do tipo `DiasDaSemana` é inicializada com um valor.
   - O programa utiliza a estrutura `switch` para imprimir o nome do dia da semana correspondente.

## 🛠️ Como Executar

### Pré-requisitos
- Um compilador C, como o GCC (GNU Compiler Collection).

### Passos
1. Clone este repositório ou copie o código-fonte para um arquivo chamado `dias_da_semana.c`.
2. Compile o código usando o comando:
   ```bash
   gcc dias_da_semana.c -o dias_da_semana
   ```
3. Execute o programa com o comando:
   ```bash
   ./dias_da_semana
   ```

## 🧪 Exemplo de Saída

Se a variável `dia` for inicializada com `QUARTA`:
```text
Quarta-feira
```

## 📂 Estrutura do Repositório

```
.
├── dias_da_semana.c  # Código-fonte principal
├── README.md         # Documentação do projeto
```

## 🚀 Funcionalidades

- Utilização de `enum` para organizar valores constantes.
- Demonstração do uso da estrutura de controle `switch` para diferentes casos.

## 📖 Aprendizados

Este projeto ilustra:
- Como usar enums no C para simplificar o gerenciamento de valores constantes.
- A criação de um programa simples e legível utilizando controle condicional.