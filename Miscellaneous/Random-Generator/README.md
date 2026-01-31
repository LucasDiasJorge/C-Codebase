# 🎲 Random Generator - Gerador de Números Aleatórios

Este módulo demonstra como gerar números aleatórios em C usando `srand()` e `rand()`.

## 📝 Descrição

O programa gera uma sequência de números pseudo-aleatórios usando o tempo atual como seed, garantindo sequências diferentes a cada execução.

## 📁 Estrutura

```
Random-Generator/
└── main.c      # Gerador de números aleatórios
```

## 🔧 Como Funciona

### Inicialização do Seed

```c
#include <stdlib.h>
#include <time.h>

srand(time(NULL));  // Seed baseado no tempo atual
```

### Geração de Números

```c
for (int i = 0; i < 5; i++) {
    printf("%d\n", rand());
}
```

## 🚀 Compilação e Execução

```bash
gcc -o random main.c
./random
```

## 📤 Exemplo de Saída

```
1804289383
846930886
1681692777
1714636915
1957747793
```
*Os valores mudam a cada execução*

## 💡 Técnicas Úteis

### Número em um intervalo [min, max]
```c
int random_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Exemplo: número entre 1 e 100
int n = random_range(1, 100);
```

### Número decimal [0.0, 1.0]
```c
double random_double() {
    return (double)rand() / RAND_MAX;
}
```

### Embaralhar array (Fisher-Yates)
```c
void shuffle(int *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `srand()` | Define a seed do gerador |
| `rand()` | Gera próximo número da sequência |
| `time()` | Obtém tempo atual em segundos |
| `RAND_MAX` | Valor máximo de `rand()` |

## ⚠️ Observações

- `rand()` gera números pseudo-aleatórios
- Mesma seed = mesma sequência
- Não usar para criptografia!
- `RAND_MAX` varia por sistema (geralmente 32767)

## 🔒 Para Criptografia

Use funções específicas:

```c
// Linux
#include <sys/random.h>
unsigned int secure_random;
getrandom(&secure_random, sizeof(secure_random), 0);

// OpenSSL
#include <openssl/rand.h>
unsigned char buffer[16];
RAND_bytes(buffer, sizeof(buffer));
```

## 📊 Qualidade do Gerador

| Uso | Adequado? |
|-----|-----------|
| Jogos simples | ✅ Sim |
| Simulações básicas | ✅ Sim |
| Amostragem estatística | ⚠️ Com cuidado |
| Criptografia | ❌ Não |
| Loteria/Apostas | ❌ Não |

## 📚 Referências

- [rand - C Reference](https://en.cppreference.com/w/c/numeric/random/rand)
- [Mersenne Twister](https://en.wikipedia.org/wiki/Mersenne_Twister)
- [CSPRNG](https://en.wikipedia.org/wiki/Cryptographically_secure_pseudorandom_number_generator)
