# Guia Completo: executar no WSL (Ubuntu)

## 1. Abrir WSL

No Windows PowerShell:

```powershell
wsl
```

## 2. Ir para a pasta do projeto

Dentro do WSL:

```bash
cd /mnt/c/Users/Lucas\ Jorge/Documents/Default\ Projects/Others/C-Codebase/system/c-cobol-banking
```

## 3. Instalar dependencias

```bash
make setup-wsl
```

Isso instala:

- build-essential (gcc, linker, etc)
- gnucobol (compilador COBOL)
- make

## 4. Compilar

```bash
make build
```

Binarios gerados:

- bin/bank_gateway
- bin/cobol_engine

## 5. Rodar demo completa

```bash
make reset-data
make run
```

Ou com script:

```bash
chmod +x scripts/wsl_run.sh
./scripts/wsl_run.sh
```

## 6. Resultado esperado

Voce vera quatro transacoes:

1. Deposito aprovado
2. Saque aprovado
3. Saque rejeitado por saldo insuficiente
4. Saque rejeitado por valor invalido

Ao final, data/accounts.csv refletira apenas as transacoes aprovadas.

## 7. Troubleshooting

## Erro: cobc command not found

Execute:

```bash
sudo apt update
sudo apt install -y gnucobol
```

## Erro de permissao no script

```bash
chmod +x scripts/wsl_run.sh
```

## Erro de path com espacos

Sempre escape espacos no caminho com \\ ou use aspas.

Exemplo:

```bash
cd "/mnt/c/Users/Lucas Jorge/Documents/Default Projects/Others/C-Codebase/system/c-cobol-banking"
```

## 8. Comandos uteis

Limpar build:

```bash
make clean
```

Resetar base:

```bash
make reset-data
```

Rodar novamente:

```bash
make run
```
