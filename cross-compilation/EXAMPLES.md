# 🔧 Exemplos de Programas Portáveis em C

Este documento contém exemplos prontos para usar, copiando diretamente em seus projetos.

## 1. Programa de Cálculo Simples

**Arquivo: `calc.c`**

```c
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR "cls"
    #define NEWLINE "\r\n"
#else
    #define CLEAR "clear"
    #define NEWLINE "\n"
#endif

int main(void) {
    double a, b, resultado;
    char operador;
    
    printf("╔════════════════════════╗%s", NEWLINE);
    printf("║  CALCULADORA PORTÁVEL  ║%s", NEWLINE);
    printf("╚════════════════════════╝%s", NEWLINE);
    printf("%s", NEWLINE);
    
    printf("Digite primeiro número: ");
    scanf("%lf", &a);
    
    printf("Digite operador (+, -, *, /): ");
    scanf(" %c", &operador);
    
    printf("Digite segundo número: ");
    scanf("%lf", &b);
    
    switch(operador) {
        case '+':
            resultado = a + b;
            break;
        case '-':
            resultado = a - b;
            break;
        case '*':
            resultado = a * b;
            break;
        case '/':
            if (b == 0) {
                fprintf(stderr, "Erro: Divisão por zero!%s", NEWLINE);
                return 1;
            }
            resultado = a / b;
            break;
        default:
            fprintf(stderr, "Operador inválido!%s", NEWLINE);
            return 1;
    }
    
    printf("%s%s", NEWLINE, NEWLINE);
    printf("Resultado: %.2f %c %.2f = %.2f%s",
           a, operador, b, resultado, NEWLINE);
    
    return 0;
}
```

**Compilar:**
```bash
gcc calc.c -o calc
x86_64-w64-mingw32-gcc calc.c -o calc.exe -static
```

## 2. Programa de Informações do Sistema

**Arquivo: `sysinfo.c`**

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #include <shlobj.h>
    #define NEWLINE "\r\n"
    #define ARCH "x86_64"
#else
    #include <unistd.h>
    #include <sys/utsname.h>
    #include <sys/sysinfo.h>
    #define NEWLINE "\n"
    #define ARCH "x86_64"
#endif

void print_os_info(void) {
    printf("╔═════════════════════════════════════╗%s", NEWLINE);
    printf("║    INFORMAÇÕES DO SISTEMA          ║%s", NEWLINE);
    printf("╚═════════════════════════════════════╝%s", NEWLINE);
    printf("%s", NEWLINE);
    
#ifdef _WIN32
    printf("Sistema Operacional: Windows%s", NEWLINE);
    printf("Arquitetura: %s%s", ARCH, NEWLINE);
    
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    printf("Processadores: %lu%s", 
           sysinfo.dwNumberOfProcessors, NEWLINE);
    
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);
    unsigned long long total_mb = mem.ullTotalPhys / 1024 / 1024;
    unsigned long long free_mb = mem.ullAvailPhys / 1024 / 1024;
    printf("Memória Total: %llu MB%s", total_mb, NEWLINE);
    printf("Memória Livre: %llu MB%s", free_mb, NEWLINE);

#else
    struct utsname info;
    uname(&info);
    
    printf("Sistema Operacional: %s%s", info.sysname, NEWLINE);
    printf("Nome da máquina: %s%s", info.nodename, NEWLINE);
    printf("Release: %s%s", info.release, NEWLINE);
    printf("Versão: %s%s", info.version, NEWLINE);
    printf("Arquitetura: %s%s", info.machine, NEWLINE);
    
    struct sysinfo sy;
    sysinfo(&sy);
    unsigned long long total_mb = sy.totalram / 1024 / 1024;
    unsigned long long free_mb = sy.freeram / 1024 / 1024;
    printf("Memória Total: %llu MB%s", total_mb, NEWLINE);
    printf("Memória Livre: %llu MB%s", free_mb, NEWLINE);
    printf("Processadores: %d%s", 
           (int)sysconf(_SC_NPROCESSORS_ONLN), NEWLINE);
#endif

    time_t tempo = time(NULL);
    printf("Data/Hora: %s", ctime(&tempo));
    printf("%s", NEWLINE);
}

int main(void) {
    print_os_info();
    return 0;
}
```

**Compilar:**
```bash
gcc sysinfo.c -o sysinfo
x86_64-w64-mingw32-gcc sysinfo.c -o sysinfo.exe -static
```

## 3. Gerador de Hash Portável

**Arquivo: `hash_gen.c`**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define NEWLINE "\r\n"
#else
    #define NEWLINE "\n"
#endif

/* Função simples de hash (apenas para demonstração) */
unsigned long simple_hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <string>%s", argv[0], NEWLINE);
        printf("Exemplo: %s \"Hello World\"%s", argv[0], NEWLINE);
        return 1;
    }
    
    unsigned long hash = simple_hash(argv[1]);
    
    printf("String: %s%s", argv[1], NEWLINE);
    printf("Hash: %lu (0x%lx)%s", hash, hash, NEWLINE);
    
    return 0;
}
```

**Compilar:**
```bash
gcc hash_gen.c -o hash_gen
x86_64-w64-mingw32-gcc hash_gen.c -o hash_gen.exe -static
```

## 4. Processador de Arquivos

**Arquivo: `file_proc.c`**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <io.h>
    #define NEWLINE "\r\n"
    #define PATH_SEP "\\"
#else
    #include <unistd.h>
    #define NEWLINE "\n"
    #define PATH_SEP "/"
    #define _access access
    #define F_OK 0
#endif

void print_file_stats(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Erro: Não consegui abrir %s%s", 
                filename, NEWLINE);
        return;
    }
    
    fseek(fp, 0, SEEK_END);
    long tamanho = ftell(fp);
    rewind(fp);
    
    int linhas = 0, palavras = 0, caracteres = 0;
    int c;
    int em_palavra = 0;
    
    while ((c = fgetc(fp)) != EOF) {
        caracteres++;
        
        if (c == '\n') linhas++;
        if (c == ' ' || c == '\t' || c == '\n') {
            if (em_palavra) palavras++;
            em_palavra = 0;
        } else {
            em_palavra = 1;
        }
    }
    
    fclose(fp);
    
    printf("Arquivo: %s%s", filename, NEWLINE);
    printf("Tamanho: %ld bytes%s", tamanho, NEWLINE);
    printf("Linhas: %d%s", linhas, NEWLINE);
    printf("Palavras: %d%s", palavras, NEWLINE);
    printf("Caracteres: %d%s", caracteres, NEWLINE);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo>%s", argv[0], NEWLINE);
        return 1;
    }
    
    if (_access(argv[1], F_OK) == -1) {
        fprintf(stderr, "Arquivo não encontrado: %s%s", 
                argv[1], NEWLINE);
        return 1;
    }
    
    print_file_stats(argv[1]);
    return 0;
}
```

**Compilar:**
```bash
gcc file_proc.c -o file_proc
x86_64-w64-mingw32-gcc file_proc.c -o file_proc.exe -static
```

## 5. Benchmark de Performance

**Arquivo: `benchmark.c`**

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>
    #define NEWLINE "\r\n"
    
    double get_time(void) {
        LARGE_INTEGER freq, counter;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&counter);
        return (double)counter.QuadPart / freq.QuadPart;
    }
#else
    #include <sys/time.h>
    #define NEWLINE "\n"
    
    double get_time(void) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return ts.tv_sec + ts.tv_nsec / 1e9;
    }
#endif

void benchmark_arithmetic(void) {
    printf("=== Benchmark Aritmética ===%s", NEWLINE);
    
    double start = get_time();
    volatile double resultado = 0.0;
    
    for (int i = 0; i < 100000000; i++) {
        resultado += sin((double)i) * cos((double)i);
    }
    
    double elapsed = get_time() - start;
    printf("Tempo: %.4f segundos%s", elapsed, NEWLINE);
    printf("Resultado: %.10f%s", resultado, NEWLINE);
}

void benchmark_memory(void) {
    printf("%s=== Benchmark Memória ===%s", NEWLINE, NEWLINE);
    
    int iterations = 10;
    size_t size = 1024 * 1024;  // 1 MB
    
    double start = get_time();
    for (int i = 0; i < iterations; i++) {
        char *buffer = malloc(size);
        for (size_t j = 0; j < size; j++) {
            buffer[j] = (char)i;
        }
        free(buffer);
    }
    double elapsed = get_time() - start;
    
    printf("Alocação/Liberação: %zu bytes x %d vezes%s",
           size, iterations, NEWLINE);
    printf("Tempo total: %.4f segundos%s", elapsed, NEWLINE);
    printf("Tempo médio: %.6f segundos%s", 
           elapsed / iterations, NEWLINE);
}

int main(void) {
    printf("╔════════════════════════════════════╗%s", NEWLINE);
    printf("║      BENCHMARK MULTI-PLATAFORMA   ║%s", NEWLINE);
    printf("╚════════════════════════════════════╝%s%s", NEWLINE, NEWLINE);
    
    benchmark_arithmetic();
    benchmark_memory();
    
    printf("%s[Benchmark concluído]%s", NEWLINE, NEWLINE);
    return 0;
}
```

**Compilar:**
```bash
gcc benchmark.c -o benchmark -lm
x86_64-w64-mingw32-gcc benchmark.c -o benchmark.exe -lm -static
```

---

**Dica**: Todos esses exemplos funcionam em Linux e Windows sem modificação!

Copie qualquer um desses programas para `src/`, atualize o Makefile e compile com:

```bash
make linux      # Compila para Linux
make windows    # Compila para Windows
make test       # Testa no Linux
```
