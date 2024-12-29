# Manipulação de Arrays com Ponteiros em C  

Este projeto é um exemplo simples de como manipular arrays utilizando ponteiros em linguagem C. Ele demonstra como acessar os elementos de um array usando aritmética de ponteiros.  

## Descrição do Programa  

O programa:  
1. Declara um array de inteiros com 5 elementos.  
2. Utiliza um ponteiro para iterar sobre os elementos do array.  
3. Imprime os valores dos elementos do array utilizando aritmética de ponteiros.  

## Estrutura do Código  

O código é composto por:  
- Declaração do array `arr` contendo 5 inteiros.  
- Declaração de um ponteiro `ptr` que aponta para o início do array.  
- Um laço `for` que acessa os elementos do array usando o ponteiro e a aritmética `*(ptr + i)` para acessar os valores.  

## Exemplo de Saída  

Quando executado, o programa exibe a seguinte saída:  
```
Array elements using pointer arithmetic:  
10 20 30 40 50  
```  

## Como Compilar  

Para compilar o programa, utilize um compilador de C, como `gcc`. No terminal, execute o seguinte comando:  

```bash  
gcc -o array_pointers main.c  
```  

## Como Executar  

Após a compilação, execute o programa com o comando:  

```bash  
./array_pointers  
```  

## Requisitos  

- Um compilador de C, como GCC.  
- Ambiente de desenvolvimento que suporte a execução de código C.  

## Aprendizado  

Este projeto é útil para:  
- Aprender como os ponteiros funcionam em C.  
- Entender como acessar elementos de arrays usando ponteiros.  
- Praticar a aritmética de ponteiros.  