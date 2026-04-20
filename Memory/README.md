# 🧠 Gerenciamento de Memória em C

Este diretório explora conceitos avançados de gerenciamento de memória em C, desde alocação básica até implementações personalizadas de alocadores.

## 📚 Tópicos Abordados

### 🔧 [malloc](malloc/)
**Conceito**: Implementação personalizada de malloc/free  
**Nível**: ⭐⭐⭐⭐ Avançado  
**Aprenda**: Como malloc funciona internamente

### 📊 [memset-init](memset-init/)
**Conceito**: Inicialização e preparação de memória  
**Nível**: ⭐⭐⭐ Intermediário  
**Aprenda**: Boas práticas de inicialização com `memset`

### 🏊 [memory-pool](memory-pool/)
**Conceito**: Pool de memória para performance  
**Nível**: ⭐⭐⭐⭐ Avançado  
**Aprenda**: Otimização de alocações

### 📈 [memory-usage](memory-usage/)
**Conceito**: Monitoramento de uso de memória  
**Nível**: ⭐⭐ Intermediário  
**Aprenda**: Como medir e otimizar uso de memória

### 🎯 [pointers](pointers/)
**Conceito**: Manipulação avançada de ponteiros  
**Nível**: ⭐⭐⭐ Intermediário  
**Aprenda**: Ponteiros para ponteiros, arrays de ponteiros

## 🎯 Conceitos Fundamentais

### Layout da Memória em C
```
┌─────────────────┐ ← Endereços altos
│     Stack       │   Variáveis locais, parâmetros
│        ↓        │   Cresce para baixo
├─────────────────┤
│                 │   
│     (livre)     │   
│                 │   
├─────────────────┤
│        ↑        │   
│      Heap       │   malloc(), free()
│                 │   Cresce para cima
├─────────────────┤
│      BSS        │   Variáveis não inicializadas
├─────────────────┤
│      Data       │   Variáveis globais inicializadas
├─────────────────┤
│      Text       │   Código do programa
└─────────────────┘ ← Endereços baixos
```

### Tipos de Alocação

| Tipo | Localização | Gerenciamento | Velocidade |
|------|-------------|---------------|------------|
| **Estática** | Data/BSS | Automático | Muito rápida |
| **Automática** | Stack | Automático | Rápida |
| **Dinâmica** | Heap | Manual | Mais lenta |

## 🧮 Problemas Comuns de Memória

### 1. Memory Leaks (Vazamentos)
```c
// ❌ Problema
char *ptr = malloc(100);
// Esqueceu de fazer free(ptr)

// ✅ Solução
char *ptr = malloc(100);
if (ptr != NULL) {
    // usar ptr...
    free(ptr);
    ptr = NULL;
}
```

### 2. Double Free
```c
// ❌ Problema
free(ptr);
free(ptr);  // ERRO!

// ✅ Solução
free(ptr);
ptr = NULL;
```

### 3. Use After Free
```c
// ❌ Problema
free(ptr);
*ptr = 42;  // ERRO!

// ✅ Solução
free(ptr);
ptr = NULL;
// ptr não pode mais ser usado
```

### 4. Buffer Overflow
```c
// ❌ Problema
char buffer[10];
strcpy(buffer, "string muito longa");  // ERRO!

// ✅ Solução
char buffer[50];
strncpy(buffer, source, sizeof(buffer) - 1);
buffer[sizeof(buffer) - 1] = '\0';
```

## 🛠️ Ferramentas de Debug

### Valgrind (Linux/macOS)
```bash
# Detectar vazamentos
valgrind --leak-check=full ./programa

# Detectar erros de acesso
valgrind --tool=memcheck ./programa

# Profile de memória
valgrind --tool=massif ./programa
```

### AddressSanitizer (GCC/Clang)
```bash
# Compilar com sanitizer
gcc -fsanitize=address -g -o programa fonte.c

# Executar
./programa
```

### Static Analysis
```bash
# Análise estática com Clang
clang --analyze fonte.c

# Cppcheck
cppcheck --enable=all fonte.c
```

## 📊 Estratégias de Alocação

### 1. First Fit
```
Procura primeiro bloco livre que caiba
- Rápido: O(n)
- Fragmentação: Média
```

### 2. Best Fit
```
Procura menor bloco que caiba
- Lento: O(n)
- Fragmentação: Baixa
```

### 3. Worst Fit
```
Procura maior bloco disponível
- Lento: O(n)
- Fragmentação: Alta
```

### 4. Next Fit
```
Continua busca da última posição
- Rápido: O(1) amortizado
- Fragmentação: Média
```

## ⚡ Otimizações de Performance

### 1. Memory Pools
```c
typedef struct {
    void *memory;
    size_t block_size;
    size_t total_blocks;
    char *free_list;
} MemoryPool;

void* pool_alloc(MemoryPool *pool);
void pool_free(MemoryPool *pool, void *ptr);
```

### 2. Stack Allocator
```c
typedef struct {
    char *memory;
    size_t size;
    size_t offset;
} StackAllocator;

void* stack_alloc(StackAllocator *stack, size_t size);
void stack_reset(StackAllocator *stack);
```

### 3. Ring Buffer
```c
typedef struct {
    char *buffer;
    size_t size;
    size_t head;
    size_t tail;
} RingBuffer;
```

## 🔧 Técnicas Avançadas

### 1. Garbage Collection
```c
// Mark and Sweep simples
void gc_mark(void *ptr);
void gc_sweep(void);
void gc_collect(void);
```

### 2. Reference Counting
```c
typedef struct {
    int ref_count;
    void *data;
} RefCounted;

void ref_retain(RefCounted *obj);
void ref_release(RefCounted *obj);
```

### 3. Memory Mapping
```c
#include <sys/mman.h>

void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
munmap(ptr, size);
```

## 📚 Casos de Uso por Categoria

### 🎮 Games/Real-time
- **Memory Pools**: Objetos de tamanho fixo
- **Stack Allocators**: Dados temporários
- **Custom Allocators**: Performance previsível

### 🌐 Servidores/Web
- **tcmalloc/jemalloc**: Performance multi-thread
- **Memory Pools**: Conexões/requests
- **Slab Allocators**: Objetos frequentes

### 📱 Embedded/IoT
- **Static Allocation**: Memória limitada
- **Stack-based**: Sem heap disponível
- **Custom Allocators**: Controle fino

### 🔬 Scientific Computing
- **Aligned Allocation**: SIMD/vectorização
- **Large Pages**: Reduzir TLB misses
- **NUMA-aware**: Multi-socket systems

## 🎓 Progressão de Aprendizado

### Nível 1: Básico
1. **Stack vs Heap**: Entender diferenças
2. **malloc/free**: Uso básico
3. **Ponteiros**: Conceitos fundamentais

### Nível 2: Intermediário
1. **Memory leaks**: Detectar e corrigir
2. **Valgrind**: Ferramentas de debug
3. **Arrays dinâmicos**: Implementar crescimento

### Nível 3: Avançado
1. **Custom malloc**: Implementar alocador
2. **Memory pools**: Otimizar performance
3. **Garbage collection**: Algoritmos básicos

### Nível 4: Expert
1. **Lock-free allocators**: Programação concorrente
2. **NUMA optimization**: Sistemas multi-socket
3. **Kernel allocators**: Programação de sistema

## 🎯 Projetos Práticos

1. **Implementar** alocador com diferentes estratégias
2. **Criar** memory pool para estruturas específicas
3. **Desenvolver** garbage collector simples
4. **Otimizar** aplicação real com profiling
5. **Comparar** performance de diferentes alocadores

## 💡 Boas Práticas

### ✅ Sempre Faça:
- **Verificar** retorno de malloc()
- **Fazer free()** de toda memória alocada
- **Inicializar** ponteiros como NULL
- **Usar** ferramentas de debug regularmente

### ❌ Nunca Faça:
- **Assumir** que malloc() sempre sucede
- **Usar** ponteiros após free()
- **Fazer** free() de ponteiros não alocados
- **Ignorar** warnings do compilador

## 📖 Recursos Complementares

### Livros:
- "The C Programming Language" - Kernighan & Ritchie
- "Expert C Programming" - Peter van der Linden
- "Understanding and Using C Pointers" - Richard Reese

### Papers:
- "The Slab Allocator" - Jeff Bonwick
- "Hoard: A Scalable Memory Allocator" - Berger et al.
- "TCMalloc: Thread-Caching Malloc" - Google

Este diretório fornece uma compreensão profunda do gerenciamento de memória, fundamental para programação de sistemas eficiente e robusta.
