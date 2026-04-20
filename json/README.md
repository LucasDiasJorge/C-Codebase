# 📚 JSON - Manipulação de JSON em C

Este módulo contém diferentes abordagens para trabalhar com JSON em C.

## 📝 Descrição

JSON (JavaScript Object Notation) é um formato de dados leve amplamente usado para troca de dados. Este módulo demonstra várias formas de manipular JSON em C.

## 📁 Estrutura

```
json/
├── lib/               # Biblioteca JSON manual
└── list-manipulation/ # Processamento de arrays JSON
```

## 📚 Exemplos Incluídos

### 1. [lib](lib/)
Implementação manual de uma estrutura JSON usando lista encadeada.
- Criação de objetos JSON
- Adição de pares chave-valor
- Busca por chave
- Serialização simples

### 2. [list-manipulation](list-manipulation/)
Processamento de arrays JSON recebidos via HTTP.
- Requisição HTTP com libcurl
- Tokenização de arrays JSON
- Extração de elementos

### 3. [simple (referência)](../data-structures/json/simple/)
Exemplos usando a biblioteca cJSON (neste repositório, localizados em `data-structures/json/simple/`).
- Parse de JSON de arquivo
- Parse de JSON de string
- Acesso a campos

## 💡 Bibliotecas JSON Populares

| Biblioteca | Características |
|------------|-----------------|
| [cJSON](https://github.com/DaveGamble/cJSON) | Leve, single-file |
| [json-c](https://github.com/json-c/json-c) | Completa, feature-rich |
| [jansson](https://github.com/akheron/jansson) | API elegante |
| [yyjson](https://github.com/ibireme/yyjson) | Mais rápida |

## 🚀 Exemplo com cJSON

```c
#include "cJSON.h"

// Parse
cJSON *json = cJSON_Parse("{\"name\": \"Lucas\", \"age\": 25}");

// Acesso
cJSON *name = cJSON_GetObjectItem(json, "name");
printf("Nome: %s\n", name->valuestring);

// Cleanup
cJSON_Delete(json);
```

## 📚 Referências

- [JSON Specification](https://www.json.org/)
- [cJSON GitHub](https://github.com/DaveGamble/cJSON)
