# Arquitetura Tecnica: C + COBOL no contexto bancario

## 1. Visao geral

O projeto reproduz um padrao comum em sistemas bancarios legados:

- Camada de integracao em C
- Core transacional em COBOL
- Contrato de dados por arquivo texto

Essa separacao permite modernizar a borda (C) sem reescrever o core de negocio (COBOL).

## 2. Responsabilidades

### C (gateway)

- Le e persiste contas (arquivo CSV)
- Monta requisicoes para o core
- Invoca o processo COBOL
- Interpreta respostas
- Decide persistencia final

### COBOL (core)

- Valida operacao
- Valida valor (> 0)
- Regra de saldo insuficiente no saque
- Calcula novo saldo quando aprovado
- Retorna status e motivo padronizados

## 3. Contrato de integracao

## Requisicao (C -> COBOL)

Arquivo: runtime/request.txt

Formato:

OPERACAO|CONTA|SALDO_ATUAL|VALOR

Exemplo:

WITHDRAW|000002|500.00|1000.00

## Resposta (COBOL -> C)

Arquivo: runtime/response.txt

Formato:

STATUS|NOVO_SALDO|CODIGO|MENSAGEM

Exemplo:

REJECTED|500.00|INSUFFICIENT_FUNDS|Saldo insuficiente

## 4. Fluxo de execucao

1. C carrega contas.
2. C seleciona conta e operacao.
3. C grava runtime/request.txt.
4. C chama binario COBOL.
5. COBOL processa e grava runtime/response.txt.
6. C le resposta:
   - APPROVED: atualiza saldo e salva data/accounts.csv.
   - REJECTED: nao altera saldo.

## 5. Regras de negocio implementadas

- DEPOSIT:
  - Valor deve ser > 0
  - Novo saldo = saldo atual + valor
- WITHDRAW:
  - Valor deve ser > 0
  - Valor nao pode exceder saldo atual
  - Novo saldo = saldo atual - valor
- Operacao desconhecida:
  - Rejeita com codigo UNKNOWN_OPERATION

## 6. Tratamento de erros

### No C

- Arquivo de contas ausente
- Falha ao gravar request
- Falha ao executar COBOL
- Resposta em formato invalido
- Conta inexistente

### No COBOL

- Request vazio
- Valor invalido
- Operacao nao suportada
- Saldo insuficiente

## 7. Por que esse desenho e relevante em bancos

- Facilita migracao incremental de legados.
- Mantem regras criticas em COBOL, onde historicamente estao consolidadas.
- Permite camada externa evolutiva sem quebrar o core.

## 8. Evolucoes recomendadas

- Trocar arquivo de troca por fila (mensageria) ou socket local.
- Introduzir idempotencia com transaction-id.
- Adicionar trilha de auditoria imutavel.
- Implementar lock otimista/pessimista de conta.
- Adotar testes automatizados de regressao de regras COBOL.
