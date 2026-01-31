# 🗃️ Shared Hashtable - Tabela Hash com Tags RFID

Este módulo implementa uma tabela hash otimizada para armazenamento e busca rápida de tags RFID (EPC).

## 📝 Descrição

Implementação completa de uma tabela hash em C, projetada para armazenar dados de tags RFID com suporte a:
- Tratamento de colisões por encadeamento (chaining)
- Inserção, busca e remoção eficientes
- Armazenamento de timestamp para cada tag

## 📁 Estrutura

```
Shared-Hashtable/
├── main.c          # Programa principal de demonstração
├── hashtable.h     # Header da tabela hash
├── hashtable.c     # Implementação da tabela hash
├── tag.h           # Definição da estrutura de tag
├── tag.c           # Funções auxiliares de tag
├── insert.h        # Header de inserção
└── insert.c        # Funções de inserção
```

## 🔧 Estruturas de Dados

### Tag (tag.h)
```c
typedef struct tag {
    char epc[MAX_EPC];           // Código EPC da tag RFID
    char time_datetime[32];      // Timestamp da leitura
    struct tag *next;            // Ponteiro para próxima tag (colisão)
} tag;
```

### Tabela Hash (hashtable.h)
```c
#define MAX_EPC 24
#define TABLE_SIZE 11000

extern tag *hash_table[TABLE_SIZE];
```

## 🔧 Funções Implementadas

### `unsigned int hash(char *name)`
Função de hash que converte string EPC em índice.

```c
unsigned int hash(char *name) {
    int length = strnlen(name, MAX_EPC);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}
```

### `void init_hash_table()`
Inicializa todos os slots da tabela com NULL.

### `bool hash_table_insert(tag *t)`
Insere uma nova tag na tabela.

### `tag *hash_table_lookup(char *name)`
Busca uma tag pelo EPC.

### `tag *hash_table_delete(char *name)`
Remove uma tag da tabela.

### `void print_table()`
Imprime toda a tabela (para debug).

## 🚀 Compilação e Execução

```bash
gcc -o hashtable main.c hashtable.c tag.c insert.c
./hashtable
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| Hash Function | Função de dispersão para índices |
| Chaining | Tratamento de colisões com listas |
| Ponteiros | Manipulação avançada de ponteiros |
| Structs | Estruturas de dados complexas |
| Modularização | Separação em múltiplos arquivos |

## 📊 Complexidade

| Operação | Caso Médio | Pior Caso |
|----------|------------|-----------|
| Inserção | O(1) | O(n) |
| Busca | O(1) | O(n) |
| Remoção | O(1) | O(n) |

## 🔄 Tratamento de Colisões

O método de **encadeamento (chaining)** é usado:

```
Índice 0: NULL
Índice 1: [Tag A] -> [Tag B] -> NULL
Índice 2: [Tag C] -> NULL
...
```

Quando duas tags têm o mesmo hash, elas são encadeadas em uma lista ligada.

## ⚙️ Configuração

| Parâmetro | Valor | Descrição |
|-----------|-------|-----------|
| `TABLE_SIZE` | 11000 | Tamanho da tabela |
| `MAX_EPC` | 24 | Tamanho máximo do EPC |

## 🔧 Uso Típico

```c
#include "hashtable.h"
#include "tag.h"

int main() {
    // Inicializar tabela
    init_hash_table();
    
    // Criar e inserir tag
    tag *nova_tag = malloc(sizeof(tag));
    strcpy(nova_tag->epc, "E2001234567890ABCDEF1234");
    strcpy(nova_tag->time_datetime, "2024-01-15 10:30:00");
    nova_tag->next = NULL;
    
    hash_table_insert(nova_tag);
    
    // Buscar tag
    tag *encontrada = hash_table_lookup("E2001234567890ABCDEF1234");
    
    // Remover tag
    tag *removida = hash_table_delete("E2001234567890ABCDEF1234");
    free(removida);
    
    return 0;
}
```

## ⚠️ Considerações

- O `TABLE_SIZE` deve ser ajustado conforme a quantidade esperada de tags
- Valores primos para `TABLE_SIZE` reduzem colisões
- A função hash pode ser melhorada para melhor distribuição

## 📚 Referências

- [Hash Tables - Wikipedia](https://en.wikipedia.org/wiki/Hash_table)
- [RFID EPC Standard](https://www.gs1.org/standards/epc-rfid)
- [Open Addressing vs Chaining](https://www.geeksforgeeks.org/hashing-set-3-open-addressing/)
