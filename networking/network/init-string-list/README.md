# Projeto: Requisição HTTP com Extração de Strings

Este projeto é uma aplicação simples em C que utiliza a biblioteca libcurl para fazer uma requisição HTTP GET a uma API e processa a resposta para extrair strings de um formato JSON. A aplicação também lida com o tempo atual, que é usado como parte da URL da requisição.

## Funcionalidades

- **Requisição HTTP GET**: A aplicação realiza uma requisição GET para uma URL configurada, incluindo o timestamp atual como parâmetro.
- **Processamento da Resposta**: A resposta recebida é processada para extrair strings do formato JSON, removendo caracteres de formatação, como aspas e colchetes.
- **Extração e Exibição de Strings**: Strings extraídas da resposta são exibidas na saída padrão e armazenadas em um array.
- **Gerenciamento de Memória**: O projeto lida com alocação dinâmica de memória para armazenar as strings extraídas, garantindo a liberação adequada ao final do uso.

## Requisitos

- **Biblioteca libcurl**: A biblioteca `libcurl` é usada para realizar a requisição HTTP. Certifique-se de ter a libcurl instalada no seu sistema.
  - No Ubuntu, você pode instalar a libcurl com o comando:
    ```
    sudo apt-get install libcurl4-openssl-dev
    ```

## Como Compilar

1. **Baixar o código fonte**: Baixe o código C do repositório ou salve o conteúdo em um arquivo, por exemplo `main.c`.

2. **Compilar o código**: Use o compilador `gcc` para compilar o código. Inclua a opção para vincular com a biblioteca `libcurl`:
    ```bash
    gcc -o requisicao main.c -lcurl
    ```

## Como Executar

Após compilar o código, execute o programa com o comando:

```bash
./requisicao
```

O programa fará uma requisição GET à URL configurada no código, processará a resposta e exibirá as strings extraídas da mesma.

## Descrição do Código

### Função `write_callback`

Essa função é chamada para escrever os dados recebidos pela requisição HTTP. Ela utiliza `strncat` para adicionar os dados ao buffer de resposta (`response`), que armazena a resposta completa.

### Função `extract_strings_from_response`

Esta função processa a resposta recebida (presumidamente no formato JSON). Ela remove os colchetes `[]` da resposta e utiliza `strtok` para separar a string em tokens individuais. Cada token é tratado para remover aspas e armazenado em um array de strings.

### Função `main`

A função principal realiza a seguinte sequência de operações:

1. Inicializa a biblioteca libcurl.
2. Cria a URL completa, concatenando a URL base com o valor do timestamp atual.
3. Configura a requisição HTTP com o método GET, adicionando credenciais de autenticação básica (usuário e senha).
4. Envia a requisição e recebe a resposta.
5. Processa a resposta, extraindo as strings.
6. Exibe as strings extraídas e libera a memória alocada.

### Parâmetros da Requisição

A URL da requisição é configurada como:
```
http://localhost:8891/api/v2/portal/event/items/001625152b59?lastModifiedDate=<timestamp>
```
Onde `<timestamp>` é o valor atual do tempo em segundos.