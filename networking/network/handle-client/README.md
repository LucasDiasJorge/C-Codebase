# Projeto HTTP Request Handler

Este projeto implementa um pequeno analisador de requisições HTTP utilizando a linguagem C. Ele demonstra o uso de funções simples para verificar qual método HTTP (GET, POST, DELETE, PUT) é utilizado em um cabeçalho HTTP específico.

## Descrição

O objetivo deste código é identificar o método HTTP presente em um cabeçalho de solicitação e executar ações específicas com base nesse método. O código pode ser expandido para incluir mais métodos HTTP ou outras funcionalidades.

## Estrutura do Código

O código está estruturado da seguinte forma:

1. **Função `starts_with`**: 
   Verifica se uma string (`str`) começa com uma sequência de caracteres específica (`pre`).

2. **Função `main`**: 
   - Um cabeçalho HTTP de exemplo é fornecido.
   - A função `starts_with` é usada para verificar qual método HTTP está presente no cabeçalho, e uma mensagem é exibida de acordo com o método encontrado.
   
## Funcionalidades

- Verifica os seguintes métodos HTTP:
  - `GET`
  - `POST`
  - `DELETE`
  - `PUT`

No exemplo atual, ele verifica se a requisição HTTP contém os métodos `GET`, `POST`, `DELETE` ou `PUT` seguidos de `/index.html`, imprimindo uma mensagem correspondente.

## Como Executar

1. Compile o código com o compilador `gcc` (ou qualquer outro compilador C de sua preferência):
   ```bash
   gcc -o http_handler http_handler.c
   ```

2. Execute o programa:
   ```bash
   ./http_handler
   ```

   Saída esperada:
   ```bash
   Hello GET /index.html
   ```

   Isso indica que a requisição HTTP exemplo fornecida começa com o método `GET` seguido de `/index.html`.

## Possíveis Melhorias

- Expandir para outros métodos HTTP (como `HEAD`, `PATCH`, etc.).
- Adicionar verificação de diferentes URLs além de `/index.html`.
- Usar uma estrutura de dados como árvore ou tabela de hash para armazenar os diferentes métodos HTTP e suas ações correspondentes.

## Dependências

Não há dependências externas para este projeto, apenas a biblioteca padrão de C (`stdio.h`, `string.h`, `stdlib.h`, e `stdbool.h`).