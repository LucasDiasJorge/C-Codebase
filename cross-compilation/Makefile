# ============================================================================
# Makefile para Cross-Compilation em C (Linux ↔ Windows)
# ============================================================================
# Compiladores
CC_LINUX  = gcc
CC_WIN64  = x86_64-w64-mingw32-gcc
CC_WIN32  = i686-w64-mingw32-gcc

# Flags de compilação
CFLAGS_COMMON = -Wall -Wextra -pedantic -Iinclude
CFLAGS_DEBUG  = $(CFLAGS_COMMON) -g -O0 -DDEBUG
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2 -s
LDFLAGS_WIN = -static  # Empacota DLLs no .exe

# Arquivos
SRC_DIR   = src
BIN_DIR   = bin
INCLUDE   = include

MAIN_SRC  = $(SRC_DIR)/main.c $(SRC_DIR)/platform.c
TEST_SRC  = $(SRC_DIR)/test.c $(SRC_DIR)/platform.c

# Alvos Windows
WIN_MAIN_64   = $(BIN_DIR)/program-win64.exe
WIN_MAIN_32   = $(BIN_DIR)/program-win32.exe
WIN_TEST_64   = $(BIN_DIR)/test-win64.exe
WIN_TEST_32   = $(BIN_DIR)/test-win32.exe

# Alvos Linux
LINUX_MAIN    = $(BIN_DIR)/program-linux
LINUX_TEST    = $(BIN_DIR)/test-linux

# ============================================================================
# ALVOS PRINCIPAIS
# ============================================================================

.PHONY: all clean help linux windows linux-debug windows-debug test

all: linux windows

# ============================================================================
# COMPILAÇÃO PARA LINUX
# ============================================================================

linux: $(LINUX_MAIN)

linux-debug: CC = $(CC_LINUX)
linux-debug: CFLAGS = $(CFLAGS_DEBUG)
linux-debug: $(LINUX_MAIN)

$(LINUX_MAIN): $(MAIN_SRC) $(INCLUDE)/platform.h
	@echo "[LINUX] Compilando programa principal (64-bit)..."
	@mkdir -p $(BIN_DIR)
	$(CC_LINUX) $(CFLAGS_RELEASE) $(MAIN_SRC) -o $@
	@echo "[✓] Executável gerado: $@"

# ============================================================================
# COMPILAÇÃO PARA WINDOWS 64-bit
# ============================================================================

windows-64: $(WIN_MAIN_64)

$(WIN_MAIN_64): $(MAIN_SRC) $(INCLUDE)/platform.h
	@echo "[WIN64] Compilando programa principal (64-bit)..."
	@mkdir -p $(BIN_DIR)
	$(CC_WIN64) $(CFLAGS_RELEASE) $(LDFLAGS_WIN) $(MAIN_SRC) -o $@
	@echo "[✓] Executável gerado: $@"

# ============================================================================
# COMPILAÇÃO PARA WINDOWS 32-bit
# ============================================================================

windows-32: $(WIN_MAIN_32)

$(WIN_MAIN_32): $(MAIN_SRC) $(INCLUDE)/platform.h
	@echo "[WIN32] Compilando programa principal (32-bit)..."
	@mkdir -p $(BIN_DIR)
	$(CC_WIN32) $(CFLAGS_RELEASE) $(LDFLAGS_WIN) $(MAIN_SRC) -o $@
	@echo "[✓] Executável gerado: $@"

# Alvo 'windows' compila ambas versões
windows: windows-64 windows-32

# ============================================================================
# COMPILAÇÃO DE TESTES
# ============================================================================

test: test-linux test-win64

test-linux: $(LINUX_TEST)
	@echo ""
	@echo "[LINUX] Executando testes..."
	@./$(LINUX_TEST)

test-win64: $(WIN_TEST_64)
	@echo ""
	@echo "[WIN64] Teste preparado: $(WIN_TEST_64)"
	@echo "        Nota: Use 'wine $(WIN_TEST_64)' no Linux para executar"

$(LINUX_TEST): $(TEST_SRC) $(INCLUDE)/platform.h
	@echo "[LINUX] Compilando testes (64-bit)..."
	@mkdir -p $(BIN_DIR)
	$(CC_LINUX) $(CFLAGS_DEBUG) $(TEST_SRC) -o $@

$(WIN_TEST_64): $(TEST_SRC) $(INCLUDE)/platform.h
	@echo "[WIN64] Compilando testes (64-bit)..."
	@mkdir -p $(BIN_DIR)
	$(CC_WIN64) $(CFLAGS_DEBUG) $(LDFLAGS_WIN) $(TEST_SRC) -o $@

# ============================================================================
# UTILITÁRIOS
# ============================================================================

info:
	@echo "╔════════════════════════════════════════════════════════╗"
	@echo "║        CROSS-COMPILATION PROJECT - INFORMAÇÕES         ║"
	@echo "╚════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Compiladores disponíveis:"
	@which $(CC_LINUX) > /dev/null && echo "  ✓ GCC Linux: $(CC_LINUX)" || echo "  ✗ GCC Linux: $(CC_LINUX) (não instalado)"
	@which $(CC_WIN64) > /dev/null && echo "  ✓ MinGW-w64 64-bit: $(CC_WIN64)" || echo "  ✗ MinGW-w64 64-bit: $(CC_WIN64) (não instalado)"
	@which $(CC_WIN32) > /dev/null && echo "  ✓ MinGW-w64 32-bit: $(CC_WIN32)" || echo "  ✗ MinGW-w64 32-bit: $(CC_WIN32) (não instalado)"
	@echo ""
	@echo "Arquivos fonte:"
	@echo "  - $(MAIN_SRC)"
	@echo "  - $(TEST_SRC)"
	@echo ""

clean:
	@echo "Limpando arquivos compilados..."
	@rm -rf $(BIN_DIR)/*
	@echo "[✓] Limpeza concluída"

clean-all: clean
	@echo "Removendo diretório de binários..."
	@rmdir $(BIN_DIR) 2>/dev/null || true
	@echo "[✓] Limpeza completa"

help:
	@echo "╔════════════════════════════════════════════════════════╗"
	@echo "║                COMANDOS DISPONÍVEIS                    ║"
	@echo "╚════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Compilação:"
	@echo "  make linux              - Compila para Linux (64-bit)"
	@echo "  make windows            - Compila para Windows (64-bit e 32-bit)"
	@echo "  make windows-64         - Compila apenas para Windows 64-bit"
	@echo "  make windows-32         - Compila apenas para Windows 32-bit"
	@echo "  make all                - Compila para todos os alvos"
	@echo ""
	@echo "Testes:"
	@echo "  make test               - Executa testes no Linux"
	@echo "  make test-linux         - Compila e executa testes no Linux"
	@echo "  make test-win64         - Compila testes para Windows 64-bit"
	@echo ""
	@echo "Limpeza:"
	@echo "  make clean              - Remove executáveis compilados"
	@echo "  make clean-all          - Remove todas as compilações"
	@echo ""
	@echo "Informações:"
	@echo "  make info               - Verifica compiladores disponíveis"
	@echo "  make help               - Exibe esta mensagem"
	@echo ""

# ============================================================================
# TARGETS ESPECIAIS
# ============================================================================

.PHONY: info clean clean-all help

# Não remover intermediários
.SECONDARY:
