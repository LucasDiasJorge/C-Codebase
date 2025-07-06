# 🧠 Implementação Personalizada de Malloc

## 📖 Conceito

Este projeto implementa um **alocador de memória personalizado** que replica o comportamento das funções `malloc()` e `free()` da biblioteca padrão. É uma excelente forma de entender como o gerenciamento de memória funciona internamente.

## 🎯 Objetivos de Aprendizado

- Compreender como malloc/free funcionam internamente
- Aprender sobre heap e gerenciamento de memória
- Entender linked lists para gerenciar blocos livres
- Dominar syscalls como `sbrk()`
- Implementar algoritmos de busca de blocos livres

## 🏗️ Arquitetura do Alocador

### Estrutura de Bloco
```c
typedef struct Block {
    size_t size;        // Tamanho do bloco
    int free;           // 1 = livre, 0 = ocupado
    struct Block *next; // Próximo bloco na lista
} Block;
```

### Lista de Blocos Livres
```c
Block *freeList = NULL; // Lista global de blocos livres
```

## 🔄 Fluxo de Operação

### 1. Alocação de Memória (`my_malloc`)
```
1. Verificar se size > 0
2. Procurar bloco livre suficiente
3. Se encontrou: marcar como ocupado
4. Se não encontrou: estender heap
5. Retornar ponteiro para dados
```

### 2. Liberação de Memória (`my_free`)
```
1. Verificar se ptr é válido
2. Encontrar bloco correspondente
3. Marcar como livre
4. [Futuro] Coalescer blocos adjacentes
```

## 💻 Implementação Detalhada

### Busca de Bloco Livre
```c
Block *findFreeBlock(size_t size) {
    Block *current = freeList;
    while (current) {
        if (current->free && current->size >= size) {
            return current;  // Primeiro bloco que serve (First Fit)
        }
        current = current->next;
    }
    return NULL;  // Nenhum bloco disponível
}
```

**Algoritmo**: First Fit
- **Vantagem**: Rápido (O(n) no pior caso)
- **Desvantagem**: Pode causar fragmentação

### Extensão do Heap
```c
Block *extendHeap(size_t size) {
    Block *block = (Block *)sbrk(size + BLOCK_SIZE);
    if (block == (void *)-1) return NULL;  // Erro no sbrk
    
    block->size = size;
    block->free = 0;      // Marcado como ocupado
    block->next = NULL;
    return block;
}
```

**`sbrk()`**: Syscall que estende o heap do processo
- Aumenta o "break" (fim do heap)
- Retorna ponteiro para nova área
- Retorna -1 em caso de erro

### Função my_malloc
```c
void *my_malloc(size_t size) {
    if (size <= 0) return NULL;

    Block *block = findFreeBlock(size);
    if (!block) {
        block = extendHeap(size);    // Criar novo bloco
        if (!block) return NULL;
    } else {
        block->free = 0;             // Marcar como ocupado
    }
    return (void *)(block + 1);      // Retornar dados (após header)
}
```

**Retorno**: `block + 1` 
- Pula o header (struct Block)
- Retorna ponteiro para área de dados

### Função my_free
```c
void my_free(void *ptr) {
    if (!ptr) return;

    Block *block = (Block *)ptr - 1;  // Voltar para o header
    block->free = 1;                  // Marcar como livre
    // TODO: Implementar coalescing
}
```

**Pointer Arithmetic**: `ptr - 1`
- Volta do ponteiro de dados para o header
- Permite acesso aos metadados do bloco

## 📊 Layout da Memória

```
Heap Memory Layout:
┌─────────────────┬─────────────────┬─────────────────┐
│   Block Header  │   User Data     │   Block Header  │
│   (metadata)    │   (retornado)   │   (metadata)    │
└─────────────────┴─────────────────┴─────────────────┘
    ↑                   ↑
    block            block + 1
                    (retornado ao usuário)
```

### Metadados vs Dados
- **Header**: Informações de controle (size, free, next)
- **Data**: Área utilizável pelo usuário
- **Overhead**: Header consome espaço adicional

## 🎯 Exemplo de Uso

```c
int main() {
    // Alocar array de 10 inteiros
    int *ptr = (int *)my_malloc(sizeof(int) * 10);
    
    if (ptr) {
        // Usar a memória
        for (int i = 0; i < 10; i++) {
            ptr[i] = i * 2;
            printf("%d ", ptr[i]);  // 0 2 4 6 8 10 12 14 16 18
        }
        
        // Liberar memória
        my_free(ptr);
    }
    
    return 0;
}
```

## 🔍 Comparação com malloc() Padrão

| Aspecto | my_malloc | malloc padrão |
|---------|-----------|---------------|
| **Algoritmo** | First Fit | Best Fit/Next Fit |
| **Coalescing** | Não implementado | Sim |
| **Thread Safety** | Não | Sim |
| **Fragmentação** | Alta | Otimizada |
| **Performance** | Básica | Altamente otimizada |

## 🚀 Melhorias Possíveis

### 1. Coalescing (Coalescência)
```c
void coalesce() {
    Block *current = freeList;
    while (current && current->next) {
        if (current->free && current->next->free) {
            // Juntar blocos adjacentes
            current->size += current->next->size + BLOCK_SIZE;
            current->next = current->next->next;
        }
        current = current->next;
    }
}
```

### 2. Algoritmos de Busca
- **Best Fit**: Menor bloco que serve
- **Worst Fit**: Maior bloco disponível
- **Next Fit**: Continua da última posição

### 3. Thread Safety
```c
#include <pthread.h>
pthread_mutex_t malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void *my_malloc(size_t size) {
    pthread_mutex_lock(&malloc_mutex);
    // ... código de alocação ...
    pthread_mutex_unlock(&malloc_mutex);
}
```

## 🛠️ Compilação e Teste

```bash
# Compilar
gcc -o malloc_test main.c

# Executar
./malloc_test
# Saída: 0 2 4 6 8 10 12 14 16 18

# Debug com Valgrind (detectar vazamentos)
valgrind --leak-check=full ./malloc_test

# Análise de performance
time ./malloc_test
```

## 🔧 Debugging e Análise

### Debugging com GDB:
```bash
gcc -g -o malloc_test main.c
gdb malloc_test
(gdb) break my_malloc
(gdb) run
(gdb) print *block
(gdb) print freeList
```

### Análise de Heap:
```bash
# Ver uso de memória
ps aux | grep malloc_test

# Monitorar chamadas de sistema
strace ./malloc_test

# Profile de memória
valgrind --tool=massif ./malloc_test
```

## ⚠️ Limitações e Considerações

### 🚨 Problemas Atuais:
1. **Fragmentação**: Sem coalescing, blocos ficam fragmentados
2. **Thread Safety**: Não é thread-safe
3. **Validação**: Pouca validação de ponteiros
4. **Overhead**: Header em cada bloco

### 🎯 Casos de Uso:
- **Educacional**: Entender malloc internamente
- **Embedded Systems**: Controle fino de memória
- **Custom Allocators**: Pool de memória específico
- **Debug**: Rastreamento de alocações

## 📚 Conceitos C Demonstrados

- **Ponteiros**: Aritmética de ponteiros complexa
- **Structs**: Metadados e linked lists
- **Syscalls**: Interface com kernel (sbrk)
- **Memory Layout**: Organização da memória
- **Dynamic Memory**: Alocação dinâmica
- **Pointer Casting**: Conversão entre tipos

## 🎓 Comparação com Alocadores Reais

### malloc() da glibc:
- Usa múltiplas estratégias (ptmalloc2)
- Bins para diferentes tamanhos
- Thread-safe com arenas
- Coalescing automático
- Otimizações para casos comuns

### jemalloc (Facebook):
- Thread-centric design
- Redução de fragmentação
- Profiling integrado
- Otimizado para aplicações modernas

Este projeto demonstra os fundamentos do gerenciamento de memória em sistemas operacionais e serve como base para entender implementações mais complexas como malloc(), jemalloc, e tcmalloc.

- **`my_malloc`**: Aloca dinamicamente um bloco de memória do heap, similar à função `malloc` padrão. Ele busca blocos livres na lista livre (`freeList`) e, caso não haja blocos disponíveis, expande o heap usando a função `sbrk`.
- **`my_free`**: Libera a memória alocada, marcando o bloco como livre para reutilização futura. A funcionalidade de "coalescing" (junção de blocos adjacentes livres) pode ser implementada para melhorar o gerenciamento de memória.

## Funcionalidades

- Alocação de blocos de memória com base no tamanho solicitado.
- Manutenção de uma lista de blocos livres para reutilização eficiente.
- Expansão do heap quando necessário usando `sbrk`.
- Liberação de blocos de memória para reutilização.

## Estrutura do Código

### `Block`

Cada bloco de memória alocado contém as seguintes informações:
- **`size`**: Tamanho do bloco alocado.
- **`free`**: Indicador de se o bloco está livre ou ocupado.
- **`next`**: Ponteiro para o próximo bloco na lista de blocos.

### Funções

1. **`my_malloc(size_t size)`**: Aloca um bloco de memória do tamanho especificado.
    - Primeiro, procura por blocos livres na lista livre.
    - Se nenhum bloco livre estiver disponível, a função expande o heap e cria um novo bloco.
    - Retorna um ponteiro para o espaço de dados utilizável.

2. **`my_free(void *ptr)`**: Libera o bloco de memória referenciado por `ptr`.
    - Marca o bloco como livre, permitindo que ele seja reutilizado em futuras chamadas de alocação.

3. **`findFreeBlock(size_t size)`**: Procura por um bloco livre com tamanho suficiente na lista livre.
    - Retorna o primeiro bloco livre que pode ser reutilizado ou `NULL` se não houver blocos disponíveis.

4. **`extendHeap(size_t size)`**: Expande o heap e aloca um novo bloco de memória quando nenhum bloco livre é encontrado.
    - Usa a função `sbrk` para solicitar mais memória ao sistema.

## Compilação e Execução

### Compilação

Compile o código com o seguinte comando:

```bash
gcc -o custom_malloc main.c
```

### Execução

Após a compilação, você pode executar o programa da seguinte forma:

```bash
./custom_malloc
```

Se o código estiver correto, ele alocará espaço para 10 inteiros, preencherá o array com números múltiplos de 2 e imprimirá os resultados.

### Exemplo de Saída

```bash
0 2 4 6 8 10 12 14 16 18
```

## Limitações

- O código não implementa a lógica de "coalescing", que uniria blocos adjacentes livres para evitar fragmentação.
- Não há gerenciamento de blocos pequenos ou realocação eficiente, como em implementações mais sofisticadas de `malloc`.
- A função `my_malloc` não possui a capacidade de redimensionar blocos já alocados, como `realloc`.

## Próximos Passos

- **Coalescing**: Implementar a lógica de coalescência para combinar blocos de memória adjacentes que estão livres.
- **Divisão de Blocos**: Implementar a capacidade de dividir um bloco grande em dois menores quando apenas uma parte do bloco é necessária.
- **`realloc`**: Adicionar uma função `my_realloc` para redimensionar blocos de memória já alocados.