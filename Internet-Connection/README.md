# 🌐 Internet Connection - Verificador de Conexão

Este módulo demonstra como verificar a conectividade com a internet usando C e comandos do sistema.

## 📝 Descrição

O programa utiliza o comando `ping` para verificar se há conexão com a internet, testando a conectividade com o servidor DNS do Google (8.8.8.8).

## 📁 Estrutura

```
Internet-Connection/
└── main.c      # Verificador de conexão
```

## 🔧 Como Funciona

### Função `check_internet_connection()`

```c
int check_internet_connection() {
    // Envia 1 pacote de ping para o DNS do Google
    int status = system("ping -c 1 8.8.8.8 > /dev/null 2>&1");
    return status == 0;
}
```

**Explicação:**
- `ping -c 1`: Envia apenas 1 pacote ICMP
- `8.8.8.8`: Servidor DNS público do Google
- `> /dev/null 2>&1`: Redireciona stdout e stderr para /dev/null (silencia a saída)
- Retorna `1` se conectado, `0` se desconectado

## 🚀 Compilação e Execução

### Linux/macOS
```bash
gcc -o internet_check main.c
./internet_check
```

### Windows
⚠️ **Nota:** Este código usa sintaxe Linux. Para Windows, modifique para:
```c
int status = system("ping -n 1 8.8.8.8 > nul 2>&1");
```

## 📤 Saída Esperada

```
Connected ...
```
ou
```
Disconnected
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `system()` | Executa comandos do shell |
| Redirecionamento | `> /dev/null 2>&1` |
| Códigos de Retorno | Verificação de sucesso/falha |

## ⚠️ Limitações

- Depende do comando `ping` estar disponível
- Pode ser bloqueado por firewalls
- Necessita permissões de rede
- Testa apenas conectividade IP, não DNS

## 🔄 Alternativas

1. **Usando sockets diretamente:**
```c
// Mais robusto, não depende de comandos externos
int sock = socket(AF_INET, SOCK_STREAM, 0);
// ... conectar ao servidor ...
```

2. **Usando libcurl:**
```c
CURL *curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
// ...
```

## 📚 Referências

- [system() function](https://man7.org/linux/man-pages/man3/system.3.html)
- [ICMP Protocol](https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol)
