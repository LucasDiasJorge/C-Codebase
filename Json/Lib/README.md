# 📚 JSON Library - Biblioteca JSON Manual

Este módulo implementa uma biblioteca JSON simples usando lista encadeada em C.

## 📝 Descrição

Implementação de uma estrutura de dados JSON básica que permite criar, manipular e consultar objetos JSON com pares chave-valor.

## 📁 Estrutura

```
Lib/
└── main.c      # Implementação da biblioteca JSON
```

## 🔧 Estrutura de Dados

```c
typedef struct JSON {
    char *key;           // Chave do par
    char *value;         // Valor associado
    struct JSON *next;   // Próximo elemento
} JSON;
```

## 🔧 Funções Implementadas

### `createJSON()`
Cria um novo objeto JSON vazio.

```c
JSON* createJSON() {
    return NULL;
}
```

### `addJSON()`
Adiciona um novo par chave-valor.

```c
JSON* addJSON(JSON *json, const char *key, const char *value);
```

### `getValue()`
Busca um valor pela chave.

```c
const char* getValue(JSON *json, const char *key);
```

### `printJSON()`
Imprime o JSON formatado.

```c
void printJSON(JSON *json);
```

### `freeJSON()`
Libera a memória alocada.

```c
void freeJSON(JSON *json);
```

## 🚀 Compilação e Execução

```bash
gcc -o json_lib main.c
./json_lib
```

## 📤 Exemplo de Uso

```c
JSON *json = createJSON();

json = addJSON(json, "nome", "Lucas");
json = addJSON(json, "idade", "25");
json = addJSON(json, "cidade", "São Paulo");

printf("Nome: %s\n", getValue(json, "nome"));

printJSON(json);

freeJSON(json);
```

**Saída:**
```json
{
  "nome": "Lucas",
  "idade": "25",
  "cidade": "São Paulo"
}
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| Lista Encadeada | Estrutura de dados dinâmica |
| Alocação Dinâmica | `malloc()`, `strdup()`, `free()` |
| Ponteiros | Manipulação de estruturas |
| Strings | Cópia e comparação |

## ⚠️ Limitações

- Suporta apenas valores string
- Não suporta arrays ou objetos aninhados
- Não faz parse de JSON externo
- Não valida sintaxe JSON

## 🔄 Possíveis Extensões

1. Suporte a tipos numéricos
2. Arrays JSON
3. Objetos aninhados
4. Parser de JSON string
5. Serialização para arquivo

## 📚 Referências

- [JSON Specification](https://www.json.org/)
- [cJSON Library](https://github.com/DaveGamble/cJSON)
