# ⚡ Quick Start - Começar em 5 Minutos

## 🚀 Para Linux (Ideal para começar)

### 1. Instalar Ferramentas
```bash
sudo apt install build-essential gcc mingw-w64 wine wine64
```

### 2. Entrar no Diretório
```bash
cd cross-compilation
```

### 3. Compilar
```bash
make all        # Compila tudo (Linux → Linux, Linux → Windows)
```

### 4. Executar
```bash
# Programa principal no Linux
./bin/program-linux

# Testes no Linux
make test

# Programa no Windows com Wine
wine ./bin/program-win64.exe
```

---

## 🪟 Para Windows (WSL Recomendado)

### 1. Instalar WSL
```powershell
# PowerShell como administrador
wsl --install
wsl -d Ubuntu
```

### 2. Dentro do WSL
```bash
sudo apt install build-essential gcc mingw-w64 wine wine64
cd /mnt/c/Users/SEU_USUARIO/Documents/...cross-compilation
make all
```

### 3. Executar
```bash
./bin/program-linux      # No WSL
wine ./bin/program-win64.exe  # Teste Windows dentro do WSL
```

---

## 📋 Estrutura Rápida

```
cross-compilation/
├── src/              ← Código C
├── include/          ← Headers
├── bin/              ← Executáveis (gerados)
├── Makefile          ← Automação
├── README.md         ← Documentação completa
├── ADVANCED.md       ← Técnicas avançadas
└── EXAMPLES.md       ← Exemplos prontos
```

---

## 🎯 Comandos Essenciais

| Comando | O que faz |
|---------|-----------|
| `make help` | Lista todos os comandos |
| `make info` | Verifica compiladores instalados |
| `make linux` | Compila para Linux |
| `make windows` | Compila para Windows (ambos 32/64-bit) |
| `make all` | Compila tudo |
| `make test` | Executa testes |
| `make clean` | Remove binários |

---

## 💡 Exemplos Rápidos

### Compilar um único arquivo
```bash
# Linux
gcc src/seu_programa.c -Iinclude -o bin/seu_programa

# Windows
x86_64-w64-mingw32-gcc src/seu_programa.c -Iinclude -o bin/seu_programa.exe -static
```

### Compilar com seu próprio código
1. Coloque seu arquivo `.c` em `src/`
2. Atualize o `Makefile` (procure por `MAIN_SRC`)
3. Execute `make`

### Adicionar nova função portável
1. Declare em `include/platform.h`
2. Implemente em `src/platform.c` com `#ifdef _WIN32`
3. Use em seu programa

---

## 🔍 Verificação Rápida

```bash
# 1. Verificar compiladores
make info

# 2. Compilar tudo
make all

# 3. Testar no Linux
./bin/program-linux

# 4. Testar Windows com Wine
wine ./bin/program-win64.exe
```

---

## 📚 Próximos Passos

1. **Ler README.md** para entender a estrutura completa
2. **Explorar EXAMPLES.md** para ver programas prontos
3. **Checar ADVANCED.md** para técnicas sofisticadas
4. **Colocar seu código** em `src/` e compilar

---

## ❓ Troubleshooting Rápido

| Problema | Solução |
|----------|---------|
| "gcc: command not found" | `sudo apt install gcc` |
| "mingw32-gcc not found" | `sudo apt install mingw-w64` |
| "wine: command not found" | `sudo apt install wine wine64` |
| "Permission denied" | `chmod +x scripts/*.sh` |
| ".exe não executa | Instale Wine ou execute no Windows |

---

## 🎬 Exemplo Completo

```bash
# 1. Clonar/entrar no projeto
cd cross-compilation

# 2. Verificar tudo tá ok
make info

# 3. Compilar tudo
make all

# 4. Testar no Linux
./bin/program-linux

# 5. (Opcional) Testar Windows com Wine
wine ./bin/program-win64.exe

# 6. Explorar arquivos binários gerados
ls -la bin/
```

**Resultado esperado:**
```
bin/program-linux       → 15 KB (executável Linux)
bin/program-win64.exe   → 250 KB (executável Windows)
bin/program-win32.exe   → 200 KB (executável Windows 32-bit)
bin/test-linux          → 20 KB (testes Linux)
bin/test-win64.exe      → 260 KB (testes Windows)
```

---

**Dúvidas?** Use `make help` para ver todos os comandos!

**Primeiro programa?** Veja em `EXAMPLES.md` (calc.c, sysinfo.c, etc.)

**Portabilidade?** Sempre use `#ifdef _WIN32` para diferenças entre plataformas.
