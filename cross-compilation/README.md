# 🔵 Cross-Compilation em C: Linux ↔ Windows

Um projeto completo demonstrando técnicas de cross-compilation para compilar programas C que rodem em Linux e Windows a partir de uma única base de código.

## 📋 Visão Geral

Este projeto mostra como:

- **Linux → Windows**: Usar MinGW-w64 para compilar no Linux e gerar `.exe` para Windows
- **Windows → Linux**: Usar WSL (Windows Subsystem for Linux) para compilar no Windows gerando binários Linux
- **Portabilidade**: Escrever código C portável usando `#ifdef` para diferenças de plataforma
- **Automação**: Usar Makefile para simplificar a compilação cruzada

## 📁 Estrutura do Projeto

```
cross-compilation/
├── include/
│   └── platform.h              # Header com macros e funções portáveis
├── src/
│   ├── platform.c              # Implementação específica de cada plataforma
│   ├── main.c                  # Programa principal (demonstração)
│   └── test.c                  # Suite de testes
├── bin/                        # Executáveis compilados (gerados)
├── scripts/
│   ├── build-help.sh           # Ajuda para compilação
│   ├── setup-mingw.sh          # Script de instalação do MinGW
│   └── test-wine.sh            # Teste de .exe com Wine
├── Makefile                    # Automação de compilação
└── README.md                   # Este arquivo
```

## 🛠️ Instalação

### Pré-requisitos (Linux)

**Ubuntu/Debian:**
```bash
sudo apt install build-essential mingw-w64 wine wine32 wine64
```

**Fedora:**
```bash
sudo dnf install gcc mingw64-gcc mingw32-gcc wine
```

**Arch Linux:**
```bash
sudo pacman -S gcc mingw-w64-gcc wine
```

### Setup Automático

```bash
chmod +x scripts/setup-mingw.sh
./scripts/setup-mingw.sh
```

### Verifique a Instalação

```bash
make help      # Exibe todos os comandos
make info      # Verifica compiladores instalados
```

## 🚀 Compilação

### Compilar para Linux (64-bit nativo)
```bash
make linux
# Resultado: bin/program-linux
```

### Compilar para Windows (ambos 32 e 64-bit)
```bash
make windows
# Resultado: bin/program-win64.exe e bin/program-win32.exe
```

### Compilar para Windows 64-bit apenas
```bash
make windows-64
# Resultado: bin/program-win64.exe
```

### Compilar para Windows 32-bit apenas
```bash
make windows-32
# Resultado: bin/program-win32.exe
```

### Compilar tudo (Linux + Windows)
```bash
make all
```

## 🧪 Testes

### Executar testes no Linux
```bash
make test-linux
# Executa: bin/test-linux
```

### Executar todos os testes
```bash
make test
# Compila e executa testes no Linux
# Prepara testes Windows
```

### Testar .exe no Linux com Wine
```bash
chmod +x scripts/test-wine.sh
./scripts/test-wine.sh
```

## 📝 Código Portável

### Exemplo de Detecção de Plataforma

O arquivo `include/platform.h` demonstra como detectar e adaptar código:

```c
#ifdef _WIN32
    #define PLATFORM_WINDOWS 1
    #define NEWLINE "\r\n"
#else
    #define PLATFORM_LINUX 1
    #define NEWLINE "\n"
#endif
```

### Funções Portáveis

- **`get_system_info()`**: Retorna informações do SO
- **`clear_screen()`**: `cls` no Windows, `clear` no Linux
- **`pause_program()`**: `pause` no Windows, `getchar()` no Linux
- **`get_home_directory()`**: `USERPROFILE` ou `HOME`

## 🔧 Opções de Compilação

### Flags Utilizadas

#### GCC/MinGW
- `-Wall -Wextra -pedantic`: Avisos rigorosos
- `-O2`: Otimização nível 2
- `-g`: Símbolos de debug
- `-static`: Empacota DLLs no `.exe`

```makefile
# Compilação com otimização
x86_64-w64-mingw32-gcc program.c -o program.exe -O2 -static

# Compilação com debug
gcc program.c -o program -g -O0 -DDEBUG
```

## 🌐 Cross-Compilation: Detalhes Técnicos

### Linux → Windows (Usando MinGW-w64)

```bash
# 64-bit
x86_64-w64-mingw32-gcc meu_programa.c -o meu_programa.exe -static

# 32-bit
i686-w64-mingw32-gcc meu_programa.c -o meu_programa.exe -static
```

**MinGW-w64** é um compilador cross-platform que:
- Roda no Linux
- Gera executáveis `.exe` para Windows
- Suporta bibliotecas Windows (WinAPI)
- A flag `-static` empacota todas as DLLs no binário

### Windows → Linux (Usando WSL)

No Windows, instale WSL:

```powershell
# PowerShell como administrador
wsl --install
```

Depois dentro do WSL:

```bash
gcc meu_programa.c -o meu_programa
```

Alternativa com Docker (sem WSL):

```powershell
docker run --rm -v ${PWD}:/src gcc:latest gcc /src/program.c -o /src/program
```

### Testando .exe no Linux com Wine

```bash
# Instalar Wine
sudo apt install wine wine64

# Executar programa Windows
wine bin/program-win64.exe
```

## ⚠️ Pontos de Atenção

| Situação | Cuidado |
|----------|---------|
| **APIs de Sistema** | WinAPI e POSIX não são portáveis → Use `#ifdef _WIN32` |
| **Caminhos de Arquivo** | Windows: `\\` vs Linux: `/` |
| **Line Endings** | Windows: `\r\n` vs Linux: `\n` |
| **Bibliotecas Externas** | Precisam versão para o alvo (ex: SDL2 para Windows) |
| **-static Flag** | Empacota DLLs, aumenta tamanho do `.exe` |
| **Testes Cross** | Use Wine para testar `.exe` no Linux antes de entregar no Windows |

## 📊 Exemplo de Compilação com Makefile

```bash
$ make info
[✓] GCC Linux: gcc
[✓] MinGW-w64 64-bit: x86_64-w64-mingw32-gcc
[✓] MinGW-w64 32-bit: i686-w64-mingw32-gcc

$ make all
[LINUX] Compilando programa principal (64-bit)...
[✓] Executável gerado: bin/program-linux
[WIN64] Compilando programa principal (64-bit)...
[✓] Executável gerado: bin/program-win64.exe
[WIN32] Compilando programa principal (32-bit)...
[✓] Executável gerado: bin/program-win32.exe
```

## 🧬 Macros Importantes

```c
// Detecção de compilador
#ifdef __GNUC__
    // GCC/Clang/MinGW
#endif

// Detecção de plataforma
#ifdef _WIN32
    // Windows (32 ou 64-bit)
#elif __linux__
    // Linux
#elif __APPLE__
    // macOS
#endif

// Tamanho de dados
#include <stdint.h>
int32_t x;    // 32 bits garantido
int64_t y;    // 64 bits garantido
uintptr_t p;  // Tamanho de ponteiro
```

## 📚 Recursos Adicionais

- [MinGW-w64 Official](https://www.mingw-w64.org/)
- [GCC Documentation](https://gcc.gnu.org/onlinedocs/)
- [Wine - Run Windows on Linux](https://www.winehq.org/)
- [WSL - Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/)
- [Cross-compilation Guide](https://wiki.osdev.org/Meaty_Skeleton)

## 🎯 Próximas Etapas

1. **Adicionar Bibliotecas**: Integrar SDL2, cURL, OpenSSL portáveis
2. **CI/CD**: GitHub Actions para compilar automaticamente
3. **Versionamento**: Tags de versão com releases para Windows e Linux
4. **Performance**: Benchmarks comparativos entre plataformas
5. **GUI**: Criar interface com plataforma nativa (WinAPI/GTK)

## 📄 Licença

Este projeto está disponível para fins educacionais e comerciais.

---

**Dúvidas?** Verifique `scripts/build-help.sh` ou execute:

```bash
make help
```
