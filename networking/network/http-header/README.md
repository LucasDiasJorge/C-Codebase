# Analisador de Cabeçalhos HTTP

## Descrição

Este projeto é um programa em C que faz a análise de cabeçalhos HTTP. Ele recebe uma string contendo um cabeçalho HTTP e a analisa, extraindo informações específicas, como o campo "Host" e "User-Agent", e imprimindo essas informações na saída padrão.

## Funcionalidade

O programa processa uma string que representa um cabeçalho HTTP e procura por cabeçalhos específicos, como o `Host` e `User-Agent`. Ele imprime os valores desses cabeçalhos encontrados no formato:

```
Host: www.example.com
User-Agent: Mozilla/5.0
```

Este é um exemplo de como o programa pode ser usado para analisar cabeçalhos HTTP comuns.

## Estrutura do Código

O código é dividido nas seguintes seções:

1. **Definições e Bibliotecas**
   - `MAX_HEADER_SIZE`: Define o tamanho máximo para o buffer que armazena a cópia do cabeçalho.
   - Inclui as bibliotecas `stdio.h` e `string.h` para manipulação de entrada/saída e manipulação de strings.

2. **Função `parseHttpHeader`**
   - Recebe um cabeçalho HTTP como argumento e processa linha por linha.
   - Cada linha é comparada com os cabeçalhos conhecidos (por exemplo, `Host` e `User-Agent`).
   - Para cada cabeçalho encontrado, imprime seu valor.

3. **Função `main`**
   - Define um exemplo de cabeçalho HTTP para ser analisado.
   - Chama a função `parseHttpHeader` para analisar o cabeçalho e imprimir os resultados.

## Como Usar

1. Compile o programa utilizando um compilador C:

   ```
   gcc -o parse_http_header parse_http_header.c
   ```

2. Execute o programa:

   ```
   ./parse_http_header
   ```

   O programa irá imprimir os cabeçalhos `Host` e `User-Agent` encontrados no cabeçalho HTTP fornecido.

## Exemplo de Saída

Ao executar o programa com o cabeçalho HTTP fornecido, a saída será:

```
Host: www.example.com
User-Agent: Mozilla/5.0
```