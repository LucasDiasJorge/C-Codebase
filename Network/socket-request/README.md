# 🌐 Cliente Socket TCP em C

## 📖 Conceito

Este projeto implementa um **cliente TCP simples** que se conecta a um servidor remoto e envia uma requisição HTTP GET básica. É uma introdução prática à programação de sockets em C e comunicação de rede.

## 🎯 Objetivos de Aprendizado

- Entender a programação de sockets em C
- Aprender sobre o protocolo TCP/IP
- Compreender estruturas de endereçamento de rede
- Dominar syscalls de rede (socket, connect, read, write)
- Implementar um cliente HTTP básico

## 🏗️ Arquitetura da Conexão

### Fluxo de Conexão TCP
```
Cliente                           Servidor
   |                                 |
   |------ 1. socket() --------------|
   |------ 2. gethostbyname() ------|
   |------ 3. connect() ----------->|
   |------ 4. write("GET /") ------>|
   |<----- 5. read(response) -------|
   |------ 6. close() --------------|
```

### Estruturas de Dados Principais
```c
struct hostent *hp;         // Informações do host
struct sockaddr_in addr;    // Endereço socket IPv4
int sock;                   // File descriptor do socket
```

## 💻 Implementação Detalhada

### 1. Função de Conexão
```c
int socket_connect(char *host, in_port_t port) {
    struct hostent *hp;
    struct sockaddr_in addr;
    int on = 1, sock;
    
    // Resolver nome do host para IP
    if((hp = gethostbyname(host)) == NULL) {
        herror("gethostbyname");
        exit(1);
    }
    
    // Configurar estrutura de endereço
    bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
    addr.sin_port = htons(port);        // Converter para network byte order
    addr.sin_family = AF_INET;          // IPv4
    
    // Criar socket
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // Otimização TCP: desabilitar algoritmo de Nagle
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));
    
    // Conectar ao servidor
    if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1) {
        perror("connect");
        exit(1);
    }
    
    return sock;
}
```

### 2. Programa Principal
```c
int main(int argc, char *argv[]) {
    int fd;
    char buffer[BUFFER_SIZE];
    
    // Validar argumentos
    if(argc < 3) {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        exit(1); 
    }
    
    // Conectar ao servidor
    fd = socket_connect(argv[1], atoi(argv[2])); 
    
    // Enviar requisição HTTP GET
    write(fd, "GET /\r\n", strlen("GET /\r\n"));
    
    // Ler resposta do servidor
    bzero(buffer, BUFFER_SIZE);
    while(read(fd, buffer, BUFFER_SIZE - 1) != 0) {
        fprintf(stderr, "%s", buffer);
        bzero(buffer, BUFFER_SIZE);
    }
    
    // Fechar conexão
    shutdown(fd, SHUT_RDWR); 
    close(fd); 
    
    return 0;
}
```

## 🔧 Componentes Fundamentais

### 1. Resolução de Nome (DNS)
```c
struct hostent *hp = gethostbyname(host);
```
- **Função**: Converte nome do host (ex: "google.com") para IP
- **Retorno**: Estrutura com informações do host
- **Alternativa moderna**: `getaddrinfo()`

### 2. Estrutura de Endereço
```c
struct sockaddr_in addr;
addr.sin_family = AF_INET;        // Família de protocolos IPv4
addr.sin_port = htons(port);      // Porta em network byte order
addr.sin_addr = hp->h_addr;       // Endereço IP
```

### 3. Criação do Socket
```c
int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
```
- **PF_INET**: Família de protocolos IPv4
- **SOCK_STREAM**: Socket confiável (TCP)
- **IPPROTO_TCP**: Protocolo TCP

### 4. Otimização TCP
```c
setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(int));
```
- **TCP_NODELAY**: Desabilita algoritmo de Nagle
- **Efeito**: Envia dados imediatamente (menor latência)
- **Trade-off**: Pode aumentar overhead de rede

## 🌐 Conceitos de Rede

### TCP vs UDP
| Aspecto | TCP | UDP |
|---------|-----|-----|
| **Confiabilidade** | Garantida | Não garantida |
| **Ordem** | Preservada | Não preservada |
| **Overhead** | Alto | Baixo |
| **Uso** | HTTP, FTP, SSH | DNS, Games, Streaming |

### Network Byte Order
```c
uint16_t htons(uint16_t hostshort);  // Host to Network Short
uint32_t htonl(uint32_t hostlong);   // Host to Network Long
uint16_t ntohs(uint16_t netshort);   // Network to Host Short
uint32_t ntohl(uint32_t netlong);    // Network to Host Long
```

**Por que?** Diferentes arquiteturas podem usar diferentes ordenações de bytes (endianness).

## 🚀 Uso Prático

### Compilação:
```bash
gcc -o socket_client socket_request.c
```

### Execução:
```bash
# Conectar ao Google na porta 80
./socket_client google.com 80

# Conectar a servidor local
./socket_client localhost 8080

# Conectar a servidor SSH
./socket_client example.com 22
```

### Exemplo de Saída (HTTP):
```
HTTP/1.1 200 OK
Date: Mon, 01 Jan 2024 12:00:00 GMT
Server: Apache/2.4.41
Content-Type: text/html
Content-Length: 1234

<!DOCTYPE html>
<html>
<head><title>Hello World</title></head>
...
```

## 🔍 Debugging e Análise

### Ferramentas de Debug:
```bash
# Monitorar syscalls
strace ./socket_client google.com 80

# Analisar tráfego de rede
tcpdump -i any host google.com

# Wireshark para análise visual
wireshark

# Netstat para conexões ativas
netstat -an | grep :80
```

### Debug com GDB:
```bash
gcc -g -o socket_client socket_request.c
gdb socket_client
(gdb) break socket_connect
(gdb) run google.com 80
(gdb) print hp->h_name
(gdb) print addr
```

## ⚡ Melhorias e Extensões

### 1. Tratamento de Erro Robusto
```c
if (sock == -1) {
    perror("socket creation failed");
    return -1;
}
```

### 2. Timeout de Conexão
```c
struct timeval timeout;
timeout.tv_sec = 5;
timeout.tv_usec = 0;
setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
```

### 3. Requisição HTTP Completa
```c
char request[] = "GET / HTTP/1.1\r\n"
                 "Host: example.com\r\n"
                 "Connection: close\r\n"
                 "\r\n";
write(fd, request, strlen(request));
```

### 4. IPv6 Support
```c
struct sockaddr_in6 addr6;
addr6.sin6_family = AF_INET6;
// ...
```

## 🎯 Casos de Uso

### ✅ Aplicações Práticas:
- **HTTP Clients**: Clientes web simples
- **API Clients**: Consumir APIs REST
- **Monitoring**: Verificar se serviços estão online
- **Testing**: Testar conectividade de rede
- **Proxy**: Base para proxy TCP

### 🚨 Limitações:
- Apenas IPv4
- Sem suporte a SSL/TLS
- HTTP/1.0 básico (sem keep-alive)
- Tratamento de erro limitado

## 📚 Conceitos C Demonstrados

- **Structs**: `sockaddr_in`, `hostent`
- **Ponteiros**: Manipulação de estruturas de rede
- **System Calls**: socket(), connect(), read(), write()
- **String Manipulation**: `bcopy()`, `bzero()`, `strlen()`
- **Error Handling**: `perror()`, `herror()`
- **Network Programming**: Sockets, TCP/IP

## 🎓 Próximos Passos

1. **SSL/TLS**: Adicionar criptografia com OpenSSL
2. **HTTP Parser**: Implementar parser de resposta HTTP
3. **Async I/O**: Usar select() ou epoll() para I/O não-bloqueante
4. **Connection Pooling**: Reutilizar conexões
5. **IPv6**: Suporte para endereços IPv6

Este exemplo fornece uma base sólida para entender comunicação de rede em C e serve como ponto de partida para aplicações mais complexas como servidores web, clientes HTTP, e sistemas distribuídos.

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
