#!/bin/bash

# ============================================================================
# Script: setup-mingw.sh
# Descrição: Instalação dos compiladores cruzados no Linux
# ============================================================================

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}╔════════════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║         SETUP COMPILADORES CRUZADOS (MinGW-w64)       ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════════════╝${NC}"
echo ""

# Detectar distribuição
if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
else
    echo -e "${RED}[✗] Não foi possível detectar a distribuição Linux${NC}"
    exit 1
fi

echo -e "${YELLOW}Distribuição detectada: $OS${NC}"
echo ""

# Instalação por distribuição
case $OS in
    ubuntu|debian)
        echo -e "${YELLOW}[Ubuntu/Debian] Instalando MinGW-w64...${NC}"
        sudo apt update
        sudo apt install -y mingw-w64 mingw-w64-tools build-essential wine wine32 wine64
        ;;
    fedora)
        echo -e "${YELLOW}[Fedora] Instalando MinGW-w64...${NC}"
        sudo dnf install -y mingw64-gcc mingw32-gcc mingw-w64 wine winetricks
        ;;
    arch)
        echo -e "${YELLOW}[Arch Linux] Instalando MinGW-w64...${NC}"
        sudo pacman -Sy mingw-w64-gcc mingw-w64-tools wine
        ;;
    *)
        echo -e "${RED}[✗] Distribuição não suportada: $OS${NC}"
        echo "    Instale manualmente: mingw-w64, build-essential, wine"
        exit 1
        ;;
esac

echo ""
echo -e "${YELLOW}Verificando instalação...${NC}"
echo ""

command -v x86_64-w64-mingw32-gcc &> /dev/null && \
    echo -e "${GREEN}[✓] MinGW-w64 64-bit instalado${NC}" || \
    echo -e "${RED}[✗] MinGW-w64 64-bit não encontrado${NC}"

command -v i686-w64-mingw32-gcc &> /dev/null && \
    echo -e "${GREEN}[✓] MinGW-w64 32-bit instalado${NC}" || \
    echo -e "${RED}[✗] MinGW-w64 32-bit não encontrado${NC}"

echo ""
echo -e "${GREEN}Setup concluído!${NC}"
echo -e "Execute ${YELLOW}make help${NC} para ver todos os comandos disponíveis."
