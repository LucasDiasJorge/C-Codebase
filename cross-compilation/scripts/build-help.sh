#!/bin/bash

# ============================================================================
# Script: build-help.sh
# Descrição: Script auxiliar para entender os passos de compilação cruzada
# ============================================================================

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # Sem cor

echo -e "${BLUE}╔════════════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║     GUIA DE COMPILAÇÃO CRUZADA - VERIFICAÇÕES         ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════════════╝${NC}"
echo ""

# Função para verificar comando
check_command() {
    if command -v $1 &> /dev/null; then
        echo -e "${GREEN}[✓]${NC} $1 está instalado"
        $1 --version | head -1
        return 0
    else
        echo -e "${RED}[✗]${NC} $1 NÃO está instalado"
        return 1
    fi
}

# Função para exibir informação
info() {
    echo -e "${YELLOW}[i]${NC} $1"
}

echo -e "${YELLOW}=== VERIFICAÇÃO DE COMPILADORES ===${NC}"
check_command gcc     || info "GCC: instale com 'sudo apt install gcc'"
check_command x86_64-w64-mingw32-gcc || info "MinGW-w64 64-bit: instale com 'sudo apt install mingw-w64'"
check_command i686-w64-mingw32-gcc   || info "MinGW-w64 32-bit: geralmente vem com mingw-w64"

echo ""
echo -e "${YELLOW}=== VERIFICAÇÃO DE FERRAMENTAS AUXILIARES ===${NC}"
check_command make    || info "make: instale com 'sudo apt install build-essential'"
check_command wine    || info "Wine: instale com 'sudo apt install wine wine32 wine64'"

echo ""
echo -e "${YELLOW}=== EXEMPLOS DE USO ===${NC}"
echo ""
echo -e "${BLUE}Compilação para Linux (nativa):${NC}"
echo "  gcc src/main.c src/platform.c -Iinclude -o program-linux"
echo ""
echo -e "${BLUE}Compilação para Windows 64-bit:${NC}"
echo "  x86_64-w64-mingw32-gcc src/main.c src/platform.c -Iinclude -o program-win.exe -static"
echo ""
echo -e "${BLUE}Compilação para Windows 32-bit:${NC}"
echo "  i686-w64-mingw32-gcc src/main.c src/platform.c -Iinclude -o program-win32.exe -static"
echo ""
echo -e "${BLUE}Usando Makefile (recomendado):${NC}"
echo "  make all       # Compila para Linux e Windows"
echo "  make linux     # Apenas Linux"
echo "  make windows   # Apenas Windows (ambos 32/64)"
echo "  make test      # Executa testes"
echo ""
echo -e "${YELLOW}=== EXECUÇÃO E TESTES ===${NC}"
echo ""
echo -e "${BLUE}No Linux:${NC}"
echo "  ./bin/program-linux"
echo "  ./bin/test-linux"
echo ""
echo -e "${BLUE}Windows .exe no Linux (usando Wine):${NC}"
echo "  wine bin/program-win64.exe"
echo "  wine bin/test-win64.exe"
echo ""
echo -e "${BLUE}Windows .exe no Windows nativo:${NC}"
echo "  bin\\program-win64.exe"
echo "  bin\\test-win64.exe"
echo ""
echo -e "${GREEN}Configure e compile com: make info && make${NC}"
