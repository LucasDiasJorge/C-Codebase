# Cliente TCP HTTP Simples

Este é um cliente TCP simples escrito em C que estabelece uma conexão com um servidor, envia uma requisição HTTP `GET /`, e exibe a resposta recebida. O objetivo do projeto é demonstrar como criar uma conexão TCP, enviar dados e ler a resposta de um servidor utilizando a API de sockets.

## Requisitos

- Sistema operacional Unix (Linux ou macOS)
- Compilador GCC para C

## Compilação

Para compilar o código, execute o seguinte comando:

```bash
gcc -o tcp_client tcp_client.c
```

Isso criará o executável `tcp_client` a partir do código-fonte `tcp_client.c`.

## Uso

Para executar o cliente, use o seguinte comando:

```bash
./tcp_client <hostname> <port>
```

- `<hostname>`: O nome do host ou o endereço IP do servidor que você deseja se conectar.
- `<port>`: A porta TCP onde o servidor está escutando (por padrão, para um servidor HTTP, use a porta 80).

Exemplo de execução:

```bash
./tcp_client example.com 80
```

Este comando conecta-se ao servidor `example.com` na porta 80 e envia uma requisição HTTP `GET /`.

## Como funciona

1. O cliente resolve o nome do host para um endereço IP usando a função `gethostbyname`.
2. Estabelece uma conexão TCP com o servidor usando a função `socket` e `connect`.
3. Envia uma requisição HTTP `GET /` para o servidor.
4. Lê e exibe a resposta do servidor, que normalmente será a página de índice (`index.html` ou conteúdo equivalente).
5. Após receber a resposta, fecha a conexão.

## Estrutura do código

O código consiste em:

- Função `socket_connect`: Conecta ao servidor especificado.
- Função `main`: Controla a execução, envia o pedido HTTP e exibe a resposta.

## Detalhes Técnicos

- **Socket TCP**: A conexão é realizada com um socket TCP usando o protocolo IP.
- **Requisição HTTP**: O cliente envia uma requisição simples `GET /` sem cabeçalhos adicionais.
- **Leitura da resposta**: O conteúdo da resposta HTTP é lido em um buffer e exibido na saída padrão.
