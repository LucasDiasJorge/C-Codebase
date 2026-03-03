# 📊 Data Locality - Localidade de Dados

Este módulo demonstra o impacto da localidade de cache no desempenho de programas em C.

## 📝 Descrição

O programa compara duas formas de percorrer uma matriz 2D, mostrando como o acesso sequencial (cache-friendly) é significativamente mais rápido que o acesso não-sequencial.

## 📁 Estrutura

```
Data-Locality/
└── main.c      # Comparação de localidade
```

## 🔧 Como Funciona

### Boa Localidade (Row-major order)

```c
// Percorre linha por linha - CACHE FRIENDLY
void good_locality(int **matrix, int *result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += matrix[i][j];  // Acesso sequencial
        }
    }
}
```

### Má Localidade (Column-major order)

```c
// Percorre coluna por coluna - CACHE UNFRIENDLY
void bad_locality(int **matrix, int *result, int n) {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            result[i] += matrix[i][j];  // Pula na memória
        }
    }
}
```

## 🚀 Compilação e Execução

```bash
gcc -O0 -o locality main.c  # Sem otimização para ver diferença
./locality
```

## 📤 Resultado Esperado (Matriz 10000x10000)

```
Boa localidade: 0.45 segundos
Má localidade:  2.80 segundos
Diferença: ~6x mais lento!
```

## 💡 Por que isso acontece?

### Layout da Memória (Row-major em C)

```
Matriz 3x3 na memória:
┌─────────────────────────────────┐
│ [0,0] [0,1] [0,2] [1,0] [1,1] [1,2] [2,0] [2,1] [2,2] │
└─────────────────────────────────┘
         Endereços crescentes →
```

### Cache Line

```
Uma cache line típica: 64 bytes = 16 ints

Acesso sequencial: ████████████████ (16 hits por miss)
Acesso por coluna: █___█___█___█___ (1 hit por miss)
```

## 📊 Hierarquia de Memória

| Nível | Tamanho | Latência |
|-------|---------|----------|
| Registradores | ~1 KB | 0 ciclos |
| L1 Cache | 32-64 KB | 4 ciclos |
| L2 Cache | 256 KB | 10 ciclos |
| L3 Cache | 8-32 MB | 40 ciclos |
| RAM | 8-64 GB | 200 ciclos |
| SSD | 256 GB+ | 10,000+ ciclos |

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| Localidade Espacial | Dados próximos acessados juntos |
| Localidade Temporal | Dados recentes reutilizados |
| Cache Miss | Dado não encontrado no cache |
| Cache Line | Unidade mínima de transferência |

## 🔄 Boas Práticas

### 1. Percorrer arrays na ordem correta
```c
// BOM (C usa row-major)
for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
        a[i][j] = ...
```

### 2. Usar Structure of Arrays (SoA)
```c
// Array of Structures (AoS) - pode ser ruim
struct Particle { float x, y, z, vx, vy, vz; };
struct Particle particles[N];

// Structure of Arrays (SoA) - melhor localidade
struct Particles {
    float x[N], y[N], z[N];
    float vx[N], vy[N], vz[N];
};
```

### 3. Blocking/Tiling
```c
// Processar em blocos que cabem no cache
for (ii = 0; ii < N; ii += BLOCK)
    for (jj = 0; jj < N; jj += BLOCK)
        for (i = ii; i < min(ii+BLOCK, N); i++)
            for (j = jj; j < min(jj+BLOCK, N); j++)
                // processar
```

## 📚 Referências

- [What Every Programmer Should Know About Memory](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)
- [Cache-Oblivious Algorithms](https://en.wikipedia.org/wiki/Cache-oblivious_algorithm)
- [Data-Oriented Design](https://www.dataorienteddesign.com/dodbook/)
