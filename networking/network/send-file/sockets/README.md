# Servidor HTTP Simples em C

Este projeto implementa um servidor HTTP básico que aceita conexões, processa requisições HTTP `GET`, e envia um arquivo como resposta usando a função `sendfile`.

## Pré-requisitos

- Sistema Linux (Fedora ou outra distribuição)
- Compilador GCC

## Compilação

Para compilar o projeto, utilize o seguinte comando:

```bash
gcc -o http_server main.c
```

Este comando cria o executável `http_server` a partir do código fonte `main.c`.

## Execução

Após a compilação, execute o servidor com o comando:

```bash
./http_server
```

O servidor escutará na porta `8080` (definida no código como `0x901f`, o valor hexadecimal invertido para 8080) e aceitará conexões de até 10 clientes simultaneamente.

### Acessando o Servidor

Você pode acessar o servidor utilizando um navegador da web ou uma ferramenta como `curl`. Por exemplo:

```bash
curl http://localhost:8080/file.html
```

O servidor responderá com o conteúdo do arquivo `file.html` que deve estar no diretório onde o servidor está sendo executado.

## Estrutura do Código

- **Criação de Socket:** Um socket TCP é criado usando a função `socket(AF_INET, SOCK_STREAM, 0)`.
- **Configuração de Endereço:** O servidor escuta na porta `8080`, e a estrutura `sockaddr_in` é utilizada para definir o protocolo de rede e a porta.
- **Ligação e Escuta:** O socket é associado (`bind`) ao endereço e porta, e o servidor é configurado para ouvir (`listen`) até 10 conexões.
- **Aceitação de Conexão:** O servidor aceita uma conexão de um cliente usando `accept`.
- **Processamento de Requisição:** O servidor recebe a requisição HTTP e extrai o nome do arquivo solicitado.
- **Envio de Arquivo:** O arquivo solicitado é aberto e enviado de volta ao cliente usando a função `sendfile`.
  
## Modificação do Código

- **Porta:** Caso deseje alterar a porta, modifique o valor `0x901f` para o número da porta desejada no formato hexadecimal invertido.
- **Tamanho do Arquivo:** O servidor envia um máximo de 256 bytes por vez. Para arquivos maiores, ajuste o terceiro parâmetro da função `sendfile` conforme necessário.

## Limitações

- Este servidor só processa requisições `GET`.
- A funcionalidade é limitada ao envio de arquivos pequenos.
- O código não faz tratamento de erros robusto para casos de arquivos inexistentes ou problemas de conexão.