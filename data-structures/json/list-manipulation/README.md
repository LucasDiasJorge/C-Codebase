# 📋 JSON List Manipulation - Manipulação de Listas JSON

Este módulo demonstra como fazer requisições HTTP e processar arrays JSON em C.

## 📝 Descrição

O programa utiliza libcurl para fazer requisições GET a uma API REST e processa a resposta JSON, tokenizando arrays para extrair elementos individuais.

## 📁 Estrutura

```
List-manipulation/
└── main.c      # Requisição HTTP e parsing de JSON
```

## 🔧 Pré-requisitos

### Instalar libcurl

**Ubuntu/Debian:**
```bash
sudo apt-get install libcurl4-openssl-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install libcurl-devel
```

## 🔧 Como Funciona

### Requisição HTTP com Autenticação

```c
CURL *curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_URL, url);
curl_easy_setopt(curl, CURLOPT_USERPWD, "user:user");
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
curl_easy_perform(curl);
```

### Tokenização de Array JSON

```c
// Resposta: ["item1", "item2", "item3"]
char *token = strtok(copy, "[],\"");
while (token != NULL) {
    printf("Item: %s\n", token);
    token = strtok(NULL, "[],\"");
}
```

## 🚀 Compilação e Execução

```bash
gcc -o json_list main.c -lcurl
./json_list
```

## 📤 Exemplo de Uso

**Resposta da API:**
```json
["tag1", "tag2", "tag3", "tag4"]
```

**Saída do programa:**
```
Item: tag1
Item: tag2
Item: tag3
Item: tag4
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| libcurl | Biblioteca para requisições HTTP |
| Autenticação Basic | `CURLOPT_USERPWD` |
| Callbacks | Função de escrita personalizada |
| `strtok()` | Tokenização de strings |

## ⚠️ Limitações

- Parsing simplificado (não usa parser JSON real)
- Não lida com JSON aninhado
- Não escapa caracteres especiais

## 🔄 Melhorias Sugeridas

1. Usar biblioteca JSON real (cJSON, json-c)
2. Tratar erros de conexão
3. Suportar HTTPS com certificados
4. Cache de respostas

## 📚 Referências

- [libcurl Tutorial](https://curl.se/libcurl/c/libcurl-tutorial.html)
- [strtok - C Reference](https://en.cppreference.com/w/c/string/byte/strtok)
