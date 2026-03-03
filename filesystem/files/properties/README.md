# Leitor de Propriedades em C

Este projeto é um programa simples em C que faz a leitura de um arquivo de configuração no formato `.properties`. Ele extrai e exibe os valores das chaves `AUTH_PATH` e `AUTH_USER` especificadas no arquivo.

## Descrição

O programa realiza as seguintes tarefas:
1. Abre o arquivo `example.properties` para leitura.
2. Lê cada linha do arquivo e verifica se há correspondência com as chaves `AUTH_PATH` ou `AUTH_USER`.
3. Armazena os valores associados às chaves em variáveis.
4. Exibe os valores encontrados no terminal.

## Requisitos

- Um compilador C, como `gcc`.
- Um arquivo de configuração chamado `example.properties`, contendo as chaves `AUTH_PATH` e `AUTH_USER` no formato:

  ```properties
  AUTH_PATH=/caminho/para/autenticacao
  AUTH_USER=usuario_exemplo
  ```

## Como usar

1. Clone o repositório ou copie o código fonte.
2. Certifique-se de que você tem um arquivo chamado `example.properties` no mesmo diretório que o executável do programa.
3. Compile o programa:

   ```bash
   gcc -o leitor leitor.c
   ```

4. Execute o programa:

   ```bash
   ./leitor
   ```

5. O programa exibirá os valores das chaves `AUTH_PATH` e `AUTH_USER` no terminal:

   ```plaintext
   AUTH_PATH: /caminho/para/autenticacao
   AUTH_USER: usuario_exemplo
   ```

## Possíveis Erros

- **Erro ao abrir o arquivo**: Certifique-se de que o arquivo `example.properties` existe no diretório de execução e possui permissão de leitura.
- **Arquivo mal formatado**: O programa espera que as linhas estejam no formato `CHAVE=VALOR`.

## Expansões Futuras

- Adicionar suporte para mais chaves no arquivo de configuração.
- Implementar tratamento de erros para chaves ausentes.
- Permitir que o nome do arquivo de configuração seja especificado como argumento de linha de comando.