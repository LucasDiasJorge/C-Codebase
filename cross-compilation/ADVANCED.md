# 📚 Guia Avançado de Cross-Compilation

## Exemplos de Código Portável

### 1. Diretórios e Caminhos

```c
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define DIR_SEP "\\"
    #define PATH_MAX MAX_PATH
#else
    #include <unistd.h>
    #define DIR_SEP "/"
    #define PATH_MAX 256
#endif

void create_full_path(const char *filename) {
    char path[PATH_MAX];
    
#ifdef _WIN32
    sprintf(path, "%s%s%s", getenv("USERPROFILE"), DIR_SEP, filename);
#else
    sprintf(path, "%s%s%s", getenv("HOME"), DIR_SEP, filename);
#endif
    
    printf("Caminho completo: %s\n", path);
}
```

### 2. Medição de Tempo

```c
#ifdef _WIN32
    #include <windows.h>
    double get_time_seconds(void) {
        LARGE_INTEGER freq, counter;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&counter);
        return (double)counter.QuadPart / freq.QuadPart;
    }
#else
    #include <time.h>
    double get_time_seconds(void) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return ts.tv_sec + ts.tv_nsec / 1e9;
    }
#endif

void benchmark(void) {
    double start = get_time_seconds();
    // ... código a testar ...
    double elapsed = get_time_seconds() - start;
    printf("Tempo: %.4f segundos\n", elapsed);
}
```

### 3. Acesso a Memória

```c
#include <stdio.h>

void show_memory_info(void) {
#ifdef _WIN32
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);
    
    printf("Memória Total: %lld MB\n", mem.ullTotalPhys / 1024 / 1024);
    printf("Memória Livre: %lld MB\n", mem.ullAvailPhys / 1024 / 1024);
#else
    FILE *fp = fopen("/proc/meminfo", "r");
    unsigned long total, available;
    
    fscanf(fp, "MemTotal: %lu kB\n", &total);
    fscanf(fp, "MemAvailable: %lu kB\n", &available);
    fclose(fp);
    
    printf("Memória Total: %lu MB\n", total / 1024);
    printf("Memória Livre: %lu MB\n", available / 1024);
#endif
}
```

### 4. Variáveis de Ambiente

```c
#include <stdio.h>
#include <stdlib.h>

void print_environment_vars(void) {
    #ifdef _WIN32
        // Windows
        printf("PROGRAMFILES: %s\n", getenv("PROGRAMFILES"));
        printf("TEMP: %s\n", getenv("TEMP"));
    #else
        // Linux/Unix
        printf("LD_LIBRARY_PATH: %s\n", getenv("LD_LIBRARY_PATH"));
        printf("PATH: %s\n", getenv("PATH"));
    #endif
}
```

## Compilação com Bibliotecas Externas

### Exemplo: SDL2 Portável

```makefile
# Detectar flags do SDL2
SDL2_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL2_LIBS   := $(shell pkg-config --libs sdl2)

# MinGW + SDL2
SDL2_MINGW_CFLAGS = -I/usr/x86_64-w64-mingw32/include/SDL2
SDL2_MINGW_LIBS   = -L/usr/x86_64-w64-mingw32/lib -lSDL2 -lSDL2main

compile-sdl-linux:
	gcc -o app app.c $(SDL2_CFLAGS) $(SDL2_LIBS)

compile-sdl-windows:
	x86_64-w64-mingw32-gcc -o app.exe app.c $(SDL2_MINGW_CFLAGS) $(SDL2_MINGW_LIBS) -static
```

## Configuração com Autotools

```bash
# configure.in ou configure.ac
AC_INIT([crossapp], [1.0])
AC_CANONICAL_SYSTEM

# Detecção de SO
case "${host}" in
    x86_64-w64-mingw32*)
        AC_MSG_NOTICE([Compilando para Windows])
        AC_DEFINE([_WINDOWS], 1, [Windows])
        ;;
    i686-pc-linux-gnu*)
        AC_MSG_NOTICE([Compilando para Linux])
        AC_DEFINE([_LINUX], 1, [Linux])
        ;;
esac

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
```

## CMake para Cross-Compilation

```cmake
cmake_minimum_required(VERSION 3.10)
project(CrossApp C)

# Arquivo: toolchain-mingw.cmake
if(MINGW)
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
endif()

add_executable(app src/main.c src/platform.c)
target_include_directories(app PRIVATE include)

# Compilar com:
# cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake -B build
# cmake --build build
```

## Detecção Automática de Compilador

```c
#ifdef __GNUC__
    #define CC "GCC"
    #define CC_VERSION __GNUC__.__GNUC_MINOR__
#elif _MSC_VER
    #define CC "MSVC"
    #define CC_VERSION _MSC_VER
#elif __clang__
    #define CC "Clang"
    #define CC_VERSION __clang_major__.__clang_minor__
#endif

#if __SIZEOF_POINTER__ == 8
    #define ARCH "x86_64"
#elif __SIZEOF_POINTER__ == 4
    #define ARCH "x86"
#endif

printf("Compilador: %s %d\n", CC, CC_VERSION);
printf("Arquitetura: %s\n", ARCH);
```

## Testes Unitários Portáveis

```c
#include <stdio.h>
#include <assert.h>

#ifdef _WIN32
    #define TEST_FPRINTF(fmt, ...) \
        fprintf(stderr, fmt, ##__VA_ARGS__)
#else
    #define TEST_FPRINTF(fmt, ...) \
        fprintf(stderr, fmt, ##__VA_ARGS__)
#endif

#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            TEST_FPRINTF("FALHA: %s (em %s:%d)\n", \
                         msg, __FILE__, __LINE__); \
            return 1; \
        } \
    } while (0)

int test_suite(void) {
    TEST_ASSERT(1 == 1, "1 == 1");
    TEST_ASSERT(2 > 1, "2 > 1");
    return 0;
}
```

## Performance: Inline e Otimização

```c
#ifdef _WIN32
    #define INLINE __inline
#else
    #define INLINE inline
#endif

// Função crítica em performance
INLINE int add(int a, int b) {
    return a + b;
}

// Compilar com -O2 ou -O3 para ativar inlining
```

## Debug Multi-Plataforma

```c
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
    
    #ifdef _WIN32
        #define DEBUG_BREAK() __debugbreak()
    #else
        #include <signal.h>
        #define DEBUG_BREAK() raise(SIGTRAP)
    #endif
#else
    #define DEBUG_PRINT(fmt, ...)
    #define DEBUG_BREAK()
#endif

void example_debug(void) {
    DEBUG_PRINT("Valor de x: %d", 42);
    DEBUG_BREAK();  // Para o debugger
}
```

## GitHub Actions: CI/CD para Multi-Plataforma

```yaml
# .github/workflows/build.yml
name: Cross-Compile

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v2
    
    - name: Install MinGW
      run: sudo apt install -y mingw-w64
    
    - name: Build Linux
      run: make linux
    
    - name: Build Windows
      run: make windows
    
    - name: Run Tests
      run: make test
    
    - name: Upload Artifacts
      uses: actions/upload-artifact@v2
      with:
        name: binaries
        path: bin/
```

## Troubleshooting Comum

### Erro: "command not found: x86_64-w64-mingw32-gcc"

```bash
# Instalar MinGW
sudo apt install mingw-w64

# Ou especificar caminho completo
/usr/bin/x86_64-w64-mingw32-gcc ...
```

### Erro: "undefined reference to"

```bash
# Verificar se a biblioteca está linkada
gcc -o program program.c -lm  # Link math library

# Para MinGW
x86_64-w64-mingw32-gcc -o program.exe program.c \
    -L/usr/x86_64-w64-mingw32/lib -lm
```

### Wine não funciona

```bash
# Limpar configuração Wine
wineserver -kill
rm -rf ~/.wine

# Reinstalar
sudo apt reinstall wine wine64
```

### Tamanho do executável muito grande

```bash
# Sem -static (vai precisar de DLLs)
x86_64-w64-mingw32-gcc -o program.exe program.c -O2

# Com -static (tudo empacotado)
x86_64-w64-mingw32-gcc -o program.exe program.c -O2 -static
```

## Checklist: Antes de Entregar

- [ ] Compilou sem warnings
- [ ] Testou no Linux
- [ ] Testou no Windows (Wine ou nativo)
- [ ] Verificou line endings (LF vs CRLF)
- [ ] Testou com caminhos com espaços
- [ ] Verificou variáveis de ambiente
- [ ] Documentou dependências externas
- [ ] Criou arquivo INSTALL.md
- [ ] Adicionou informações de versão
- [ ] Testou em arquitetura 32 e 64-bit

---

**Próximo Passo**: Explore os exemplos em `src/` e adapte para seu projeto!
