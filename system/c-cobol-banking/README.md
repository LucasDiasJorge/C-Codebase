# Projeto: Integracao C + COBOL para Sistema Bancario (WSL)

Este projeto demonstra uma arquitetura simples e realista de legado bancario:

- C atua como gateway de integracao e camada de persistencia.
- COBOL atua como core transacional e motor de regras de negocio.
- A comunicacao entre os dois ocorre por arquivos de troca, um padrao comum em ambientes legados.

## Objetivo tecnico

Conectar um codigo C com COBOL em um fluxo bancario com:

- Deposito
- Saque aprovado
- Saque recusado por saldo insuficiente
- Saque recusado por valor invalido

## Estrutura

- c/src/main.c: aplicacao C (orquestracao e persistencia)
- cobol/transaction_engine.cob: core COBOL de regras
- data/accounts.csv: base de contas ativa
- data/accounts.seed.csv: base inicial para reset
- runtime/request.txt: requisicao enviada pelo C ao COBOL
- runtime/response.txt: resposta do COBOL para o C
- Makefile: build e execucao no WSL
- scripts/wsl_run.sh: script unico para resetar e executar
- docs/ARCHITECTURE.md: arquitetura detalhada
- docs/WSL.md: guia detalhado de instalacao e execucao
- docs/COBOL_MANUAL.md: documentacao tecnica completa do codigo COBOL
- docs/QUICK_REFERENCE.md: guia de referencia rapida e 10 casos de teste
- docs/DATA_FLOW.md: fluxo detalhado de dados com exemplos passo-a-passo

## Como funciona

1. O C carrega contas de data/accounts.csv.
2. O C escreve uma requisicao em runtime/request.txt no formato:
   - OPERACAO|CONTA|SALDO_ATUAL|VALOR
3. O C executa o binario COBOL.
4. O COBOL valida regras e grava runtime/response.txt no formato:
   - STATUS|NOVO_SALDO|CODIGO|MENSAGEM
5. O C le a resposta:
   - Se APPROVED: persiste saldo novo em data/accounts.csv.
   - Se REJECTED: mantem saldo e apenas registra retorno.

## Executar no WSL

Siga o guia em docs/WSL.md.

Resumo rapido:

```bash
cd /mnt/c/Users/Lucas\ Jorge/Documents/Default\ Projects/Others/C-Codebase/system/c-cobol-banking
make setup-wsl
make reset-data
make run
```

## Saida esperada (resumo)

- Deposito aprovado na conta 000001.
- Saque de 100 aprovado na conta 000002.
- Saque de 1000 rejeitado na conta 000002 por saldo insuficiente.
- Saque de -10 rejeitado na conta 000003 por valor invalido.

## Limites didaticos

Este exemplo foca em integracao C + COBOL e nao implementa:

- Concorrencia simultanea
- Persistencia transacional ACID real
- Travas de arquivo por sessao
- Auditoria completa e criptografia de dados

Para evolucao, veja docs/ARCHITECTURE.md.
