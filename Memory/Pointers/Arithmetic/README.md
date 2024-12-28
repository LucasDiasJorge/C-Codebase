# Projeto de Manipulação de Ponteiros em C

## Descrição

Este projeto demonstra a manipulação de ponteiros em C, utilizando aritmética de ponteiros para acessar elementos de um array. O código é simples e mostra como um ponteiro pode ser utilizado para percorrer um array, além de demonstrar como incrementar e decrementar o ponteiro para acessar diferentes elementos.

## Funcionalidades

1. **Acesso aos elementos de um array utilizando aritmética de ponteiros**: O código acessa os elementos de um array e os imprime na tela utilizando a notação de ponteiro.
   
2. **Incremento de ponteiro**: Após acessar um elemento do array, o ponteiro é incrementado para apontar para o próximo elemento.
   
3. **Decremento de ponteiro**: O ponteiro é então decrementado para voltar ao elemento anterior.

## Como Usar

1. Clone o repositório ou baixe o código fonte do arquivo `main.c`.
   
2. Compile o código utilizando um compilador de C, como o GCC. Exemplo de comando:
   ```bash
   gcc main.c -o programa
   ```

3. Execute o programa compilado:
   ```bash
   ./programa
   ```

4. O programa exibirá os elementos do array, além de demonstrar o incremento e decremento de ponteiros.

## Exemplo de Saída

```bash
Array elements using pointer arithmetic:
10 20 30 40 50 
Next element: 20
Previous element: 10
```

## Explicação do Código

- **Definição do array**: O código define um array de inteiros `arr[]` contendo os elementos `{10, 20, 30, 40, 50}`.
  
- **Uso de ponteiros**: Um ponteiro `ptr` é criado e inicializado para apontar para o primeiro elemento do array.

- **Aritmética de ponteiros**: A aritmética de ponteiros é utilizada para acessar cada elemento do array. A cada iteração, o ponteiro é incrementado para acessar o próximo elemento.

- **Incremento e Decremento de Ponteiro**: O código demonstra como o ponteiro pode ser movido para frente (incrementado) e para trás (decrementado), alterando assim o elemento que está sendo apontado.

## Conclusão

Este projeto tem como objetivo ilustrar a manipulação básica de ponteiros em C, uma habilidade essencial ao trabalhar com estruturas de dados e otimização de código. O uso de aritmética de ponteiros permite maior controle sobre o acesso e manipulação de dados em memória.
