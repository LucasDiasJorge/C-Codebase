#!/bin/bash
# ============================================================================
# Script: run-tests.sh
# Descrição: Executa todos os testes do projeto
# ============================================================================

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}╔════════════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║            SUITE DE TESTES - CROSS-COMPILATION         ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════════════╝${NC}"
echo ""

# Verificar se Makefile existe
if [ ! -f Makefile ]; then
    echo -e "${RED}[✗] Makefile não encontrado${NC}"
    exit 1
fi

echo -e "${YELLOW}[1/3] Compilando testes para Linux...${NC}"
make test-linux > /dev/null 2>&1 || {
    echo -e "${RED}[✗] Erro na compilação${NC}"
    exit 1
}
echo -e "${GREEN}[✓] Testes Linux compilados${NC}"
echo ""

echo -e "${YELLOW}[2/3] Executando testes no Linux...${NC}"
if ./bin/test-linux; then
    echo -e "${GREEN}[✓] Testes Linux passaram${NC}"
else
    echo -e "${RED}[✗] Testes Linux falharam${NC}"
    exit 1
fi
echo ""

echo -e "${YELLOW}[3/3] Compilando testes para Windows 64-bit...${NC}"
make test-win64 > /dev/null 2>&1 || {
    echo -e "${RED}[✗] Erro na compilação Windows${NC}"
    exit 1
}
echo -e "${GREEN}[✓] Testes Windows compilados${NC}"
echo ""

echo -e "${BLUE}═══════════════════════════════════════════════════════${NC}"
echo -e "${GREEN}[✓] TODOS OS TESTES PASSARAM COM SUCESSO!${NC}"
echo -e "${BLUE}═══════════════════════════════════════════════════════${NC}"
echo ""
echo "Resultados:"
echo "  • Linux (nativo): ./bin/test-linux"
echo "  • Windows (Wine): wine ./bin/test-win64.exe"
echo ""
