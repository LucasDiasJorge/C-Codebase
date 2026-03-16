SHELL := /bin/bash

BIN_DIR := bin
C_BIN := $(BIN_DIR)/bank_gateway
COBOL_BIN := $(BIN_DIR)/cobol_engine

.PHONY: all build dirs c cobol run clean reset-data setup-wsl

all: build

build: dirs cobol c

dirs:
	mkdir -p $(BIN_DIR) runtime

cobol:
	cobc -x -free -o $(COBOL_BIN) cobol/transaction_engine.cob

c:
	gcc -std=c11 -Wall -Wextra -Werror -pedantic -O2 -o $(C_BIN) c/src/main.c

run: build
	./$(C_BIN)

reset-data:
	cp data/accounts.seed.csv data/accounts.csv

clean:
	rm -rf $(BIN_DIR) runtime/request.txt runtime/response.txt

setup-wsl:
	sudo apt update
	sudo apt install -y build-essential gnucobol make
