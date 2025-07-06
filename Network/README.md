# 🌐 Programação de Rede em C

Este diretório explora programação de sockets e comunicação de rede em C, desde clientes TCP simples até servidores HTTP completos.

## 📚 Projetos Disponíveis

### 🔗 [Socket-request](socket-request/)
**Conceito**: Cliente TCP básico com requisições HTTP  
**Nível**: ⭐⭐⭐ Intermediário  
**Aprenda**: Sockets, TCP/IP, HTTP básico

### 👥 [Handle-Client](Handle-Client/)
**Conceito**: Servidor multi-cliente  
**Nível**: ⭐⭐⭐⭐ Avançado  
**Aprenda**: Concorrência, fork(), threads

### 🌐 [HTTP-header](http-header/)
**Conceito**: Manipulação de cabeçalhos HTTP  
**Nível**: ⭐⭐⭐ Intermediário  
**Aprenda**: Protocolo HTTP, parsing

### 📡 [HTTP-stream](http-stream/)
**Conceito**: Streaming HTTP  
**Nível**: ⭐⭐⭐⭐ Avançado  
**Aprenda**: Chunked transfer, streaming

### 🏷️ [Mac-Address](Mac-Address/)
**Conceito**: Obter endereço MAC da interface  
**Nível**: ⭐⭐ Intermediário  
**Aprenda**: Interfaces de rede, ioctl()

### 📁 [Send-file](send-file/)
**Conceito**: Transferência de arquivos via rede  
**Nível**: ⭐⭐⭐ Intermediário  
**Aprenda**: File transfer, protocolos binários

## 🏗️ Fundamentos de Rede

### Modelo TCP/IP
```
┌─────────────────┐
│   Aplicação     │  HTTP, FTP, SSH, Telnet
├─────────────────┤
│   Transporte    │  TCP, UDP
├─────────────────┤
│   Internet      │  IP, ICMP, ARP
├─────────────────┤
│   Enlace        │  Ethernet, WiFi
└─────────────────┘
```

### Socket API Principal
```c
// Criação
int socket(int domain, int type, int protocol);

// Servidor
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

// Cliente
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// I/O
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);

// Fechamento
int close(int sockfd);
```

## 🔧 Tipos de Socket

### TCP (SOCK_STREAM)
- **Confiável**: Garantia de entrega
- **Ordenado**: Dados chegam em ordem
- **Connection-oriented**: Estabelece conexão
- **Uso**: HTTP, FTP, SSH, Telnet

### UDP (SOCK_DGRAM)
- **Não-confiável**: Sem garantia de entrega
- **Não-ordenado**: Dados podem chegar fora de ordem
- **Connectionless**: Sem estabelecimento de conexão
- **Uso**: DNS, DHCP, Streaming, Games

## 🔄 Padrões de Servidor

### 1. Servidor Sequencial
```c
while (1) {
    client_fd = accept(server_fd, ...);
    handle_client(client_fd);  // Bloqueia até terminar
    close(client_fd);
}
```

### 2. Servidor com Fork
```c
while (1) {
    client_fd = accept(server_fd, ...);
    if (fork() == 0) {
        // Processo filho
        handle_client(client_fd);
        exit(0);
    }
    close(client_fd);  // Processo pai
}
```

### 3. Servidor com Threads
```c
void *client_thread(void *arg) {
    int client_fd = *(int*)arg;
    handle_client(client_fd);
    return NULL;
}
```

### 4. Servidor com Select/Poll
```c
fd_set readfds;
while (1) {
    select(max_fd + 1, &readfds, NULL, NULL, NULL);
    // Processar fds prontos
}
```

## 🚀 Protocolo HTTP Básico

### Request HTTP
```
GET / HTTP/1.1
Host: example.com
User-Agent: MyClient/1.0
Connection: close
```

### Response HTTP
```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 13

Hello, World!
```

## 🔧 Ferramentas de Debug

### Análise de Tráfego
```bash
# tcpdump - capturar pacotes
tcpdump -i any host example.com

# netcat - teste de conectividade
nc -l 8080                # Servidor
nc localhost 8080         # Cliente
```

### Monitor de Conexões
```bash
# netstat - conexões ativas
netstat -an | grep :80

# lsof - arquivos abertos por processo
lsof -i :8080
```

## 🎓 Progressão de Aprendizado

### Nível 1: Básico
1. **Socket básico**: Cliente TCP simples
2. **HTTP GET**: Requisições básicas
3. **Error handling**: Tratamento de erros

### Nível 2: Intermediário
1. **Servidor TCP**: Accept múltiplos clientes
2. **HTTP server**: Servidor web simples
3. **Parsing**: Processar requests HTTP

### Nível 3: Avançado
1. **Concorrência**: Fork, threads, select
2. **Protocolos**: Implementar protocolos customizados
3. **Performance**: Otimizações e profiling

## 📚 Material de Referência

**Beej's Guide to Network Programming**: https://beej.us/guide/bgnet/html/index-wide.html

**Socket Programming Tutorial**: https://www.youtube.com/watch?v=2HrYIl6GpYg

**HTTP POST Example**: https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response

## 💡 Boas Práticas

### ✅ Sempre Faça:
- **Verificar** retornos de função
- **Fechar** sockets adequadamente
- **Validar** dados de entrada
- **Configurar** timeouts

### ❌ Evite:
- **Hardcode** endereços IP
- **Ignorar** erros de rede
- **Buffer overflow** em parsing
- **Blocks infinitos** sem timeout

Este diretório fornece uma base sólida para programação de rede em C, desde conceitos básicos até implementações profissionais de servidores e clientes.
