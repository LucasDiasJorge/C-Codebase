#!/bin/bash

# ============================================================================
# Script: test-wine.sh
# Descrição: Testa executáveis Windows usando Wine no Linux
# ============================================================================

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}╔════════════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║           TESTE DE EXECUTÁVEIS WINDOWS COM WINE        ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════════════╝${NC}"
echo ""

# Verificar Wine
if ! command -v wine &> /dev/null; then
    echo -e "${RED}[✗] Wine não está instalado${NC}"
    echo "    Instale com: sudo apt install wine wine32 wine64"
    exit 1
fi

echo -e "${GREEN}[✓] Wine detectado${NC}"
echo "    Versão: $(wine --version)"
echo ""

# Verificar arquivos compilados
PROGRAMS=(
    "bin/program-win64.exe"
    "bin/program-win32.exe"
    "bin/test-win64.exe"
)

for prog in "${PROGRAMS[@]}"; do
    if [ -f "$prog" ]; then
        echo -e "${YELLOW}Testando: $prog${NC}"
        wine "$prog" 2>/dev/null || {
            echo -e "${RED}[✗] Erro ao executar $prog${NC}"
        }
        echo ""
    fi
done

echo -e "${GREEN}Testes concluídos!${NC}"
