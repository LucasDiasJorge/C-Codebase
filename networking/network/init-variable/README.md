# 🌐 Init Variable - Inicialização de Variáveis com HTTP

Este módulo demonstra como inicializar variáveis com dados de uma API REST usando libcurl.

## 📝 Descrição

O programa faz uma requisição HTTP GET com autenticação básica e armazena a resposta em uma variável para uso posterior.

## 📁 Estrutura

```
Init-variable/
└── main.c      # Requisição HTTP e inicialização
```

## 🔧 Pré-requisitos

### Instalar libcurl

**Ubuntu/Debian:**
```bash
sudo apt-get install libcurl4-openssl-dev
```

**Windows (MinGW):**
```bash
pacman -S mingw-w64-x86_64-curl
```

## 🔧 Como Funciona

### Estrutura de Resposta

```c
struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(1);
    s->ptr[0] = '\0';
}
```

### Callback de Escrita

```c
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;
    return size * nmemb;
}
```

### Requisição com Autenticação

```c
CURL *curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8010/api/v1/ping");
curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
curl_easy_perform(curl);
```

## 🚀 Compilação e Execução

```bash
gcc -o init_var main.c -lcurl
./init_var
```

## 📤 Exemplo de Uso

```c
struct string response;
init_string(&response);

// Após a requisição
printf("Resposta: %s\n", response.ptr);
printf("Tamanho: %zu bytes\n", response.len);

// Usar os dados
if (strcmp(response.ptr, "pong") == 0) {
    printf("API está online!\n");
}

free(response.ptr);
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| libcurl | Biblioteca HTTP |
| Autenticação Basic | `user:password` |
| Callbacks | Processamento de resposta |
| Alocação dinâmica | `malloc()`, `realloc()` |

## ⚠️ Boas Práticas

### Sempre verificar erros
```c
CURLcode res = curl_easy_perform(curl);
if (res != CURLE_OK) {
    fprintf(stderr, "Erro: %s\n", curl_easy_strerror(res));
}
```

### Verificar código HTTP
```c
long http_code;
curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
if (http_code != 200) {
    fprintf(stderr, "HTTP Error: %ld\n", http_code);
}
```

### Timeout
```c
curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);  // 10 segundos
```

## 📚 Referências

- [libcurl Easy Interface](https://curl.se/libcurl/c/libcurl-easy.html)
- [CURLOPT_USERPWD](https://curl.se/libcurl/c/CURLOPT_USERPWD.html)
