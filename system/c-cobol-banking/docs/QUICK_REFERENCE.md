# Guia de Referência Rápida: TRANSACTION-ENGINE

## 📘 Cheat Sheet do COBOL

### Estrutura de Divisões

```cobol
IDENTIFICATION DIVISION.
└─ PROGRAM-ID. [nome]

ENVIRONMENT DIVISION.
├─ INPUT-OUTPUT SECTION.
│  └─ FILE-CONTROL.
│     ├─ SELECT arquivo ASSIGN TO "caminho"
│     └─ ORGANIZATION [tipo]

DATA DIVISION.
├─ FILE SECTION.
│  ├─ FD arquivo.
│  └─ 01 registro.
└─ WORKING-STORAGE SECTION.
   └─ 01 variáveis.

PROCEDURE DIVISION.
├─ MAIN.
│  └─ [lógica]
├─ [SECÇÃO-2].
│  └─ [lógica]
└─ [SECÇÃO-N].
   └─ [lógica]
```

### Variáveis do Programa

| Nome | Tipo | Tamanho | Função |
|------|------|---------|--------|
| `REQUEST-RECORD` | String | 200 | Buffer de entrada do arquivo |
| `RESPONSE-RECORD` | String | 200 | Buffer de saída para arquivo |
| `WS-REQUEST-LINE` | String | 200 | Cópia de REQUEST-RECORD |
| `WS-RESPONSE-LINE` | String | 200 | Resposta formatada |
| `WS-OP` | String | 20 | Operação (DEPOSIT/WITHDRAW) |
| `WS-ACCOUNT-ID` | String | 10 | ID da conta |
| `WS-CURRENT-BALANCE` | Numér | S9(9)V99 | Saldo atual |
| `WS-AMOUNT` | Numér | S9(9)V99 | Valor da operação |
| `WS-NEW-BALANCE` | Numér | S9(9)V99 | Novo saldo calculado |
| `WS-STATUS` | String | 20 | APPROVED/REJECTED |
| `WS-CODE` | String | 30 | Código de erro |
| `WS-MESSAGE` | String | 80 | Mensagem descritiva |

---

## 🧪 Casos de Teste

### Teste 1: Depósito Simples

| Aspecto | Valor |
|---------|-------|
| **Input** | `DEPOSIT\|000001\|1000.00\|500.00` |
| **Expected Output** | `APPROVED\|1500.00\|OK\|Deposito aprovado` |
| **Validação** | Saldo = 1000 + 500 = 1500 ✓ |

**Como testar:**
```bash
echo "DEPOSIT|000001|1000.00|500.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

**Saída esperada:**
```
APPROVED|1500.00|OK|Deposito aprovado
```

---

### Teste 2: Saque Aprovado

| Aspecto | Valor |
|---------|-------|
| **Input** | `WITHDRAW\|000002\|500.00\|200.00` |
| **Expected Output** | `APPROVED\|300.00\|OK\|Saque aprovado` |
| **Validação** | Saldo = 500 - 200 = 300 ✓ |

**Como testar:**
```bash
echo "WITHDRAW|000002|500.00|200.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

**Saída esperada:**
```
APPROVED|300.00|OK|Saque aprovado
```

---

### Teste 3: Saque Rejeitado (Saldo Insuficiente)

| Aspecto | Valor |
|---------|-------|
| **Input** | `WITHDRAW\|000002\|500.00\|1000.00` |
| **Expected Output** | `REJECTED\|500.00\|INSUFFICIENT_FUNDS\|Saldo insuficiente` |
| **Validação** | Valor (1000) > Saldo (500) → REJEITAR ✓ |

**Como testar:**
```bash
echo "WITHDRAW|000002|500.00|1000.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

**Saída esperada:**
```
REJECTED|500.00|INSUFFICIENT_FUNDS|Saldo insuficiente
```

---

### Teste 4: Valor Inválido (Negativo)

| Aspecto | Valor |
|---------|-------|
| **Input** | `WITHDRAW\|000003\|1500.00\|-50.00` |
| **Expected Output** | `REJECTED\|1500.00\|INVALID_AMOUNT\|Valor precisa ser maior que zero` |
| **Validação** | Valor (-50) ≤ 0 → REJEITAR ✓ |

**Como testar:**
```bash
echo "WITHDRAW|000003|1500.00|-50.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

**Saída esperada:**
```
REJECTED|1500.00|INVALID_AMOUNT|Valor precisa ser maior que zero
```

---

### Teste 5: Valor Zero

| Aspecto | Valor |
|---------|-------|
| **Input** | `DEPOSIT\|000001\|1000.00\|0.00` |
| **Expected Output** | `REJECTED\|1000.00\|INVALID_AMOUNT\|Valor precisa ser maior que zero` |
| **Validação** | Valor (0) ≤ 0 → REJEITAR ✓ |

**Como testar:**
```bash
echo "DEPOSIT|000001|1000.00|0.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

**Saída esperada:**
```
REJECTED|1000.00|INVALID_AMOUNT|Valor precisa ser maior que zero
```

---

### Teste 6: Operação Desconhecida

| Aspecto | Valor |
|---------|-------|
| **Input** | `TRANSFER\|000001\|1000.00\|100.00` |
| **Expected Output** | `REJECTED\|1000.00\|UNKNOWN_OPERATION\|Operacao nao suportada` |
| **Validação** | Op ≠ DEPOSIT e ≠ WITHDRAW → REJEITAR ✓ |

**Como testar:**
```bash
echo "TRANSFER|000001|1000.00|100.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

**Saída esperada:**
```
REJECTED|1000.00|UNKNOWN_OPERATION|Operacao nao suportada
```

---

### Teste 7: Arquivo Vazio

| Aspecto | Valor |
|---------|-------|
| **Input** | (arquivo vazio) |
| **Expected Output** | `REJECTED\|0.00\|INVALID_INPUT\|Request vazia` |
| **Validação** | EOF sem dados → REJEITAR ✓ |

**Como testar:**
```bash
echo -n "" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

**Saída esperada:**
```
REJECTED|0.00|INVALID_INPUT|Request vazia
```

---

### Teste 8: Caso Misto (Maiúsculas/Minúsculas)

| Aspecto | Valor |
|---------|-------|
| **Input** | `deposit\|000001\|1000.00\|250.00` |
| **Expected Output** | `APPROVED\|1250.00\|OK\|Deposito aprovado` |
| **Validação** | `UPPER-CASE()` normaliza → MATCH ✓ |

**Como testar:**
```bash
echo "deposit|000001|1000.00|250.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

**Saída esperada:**
```
APPROVED|1250.00|OK|Deposito aprovado
```

---

### Teste 9: Espaços em Branco

| Aspecto | Valor |
|---------|-------|
| **Input** | `DEPOSIT \|000001\|1000.00\|250.00` (espaço após DEPOSIT) |
| **Expected Output** | `APPROVED\|1250.00\|OK\|Deposito aprovado` |
| **Validação** | `TRIM()` remove espaços → MATCH ✓ |

**Como testar:**
```bash
echo "DEPOSIT |000001|1000.00|250.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

**Saída esperada:**
```
APPROVED|1250.00|OK|Deposito aprovado
```

---

### Teste 10: Saque de Valor Exato (Esvazia Conta)

| Aspecto | Valor |
|---------|-------|
| **Input** | `WITHDRAW\|000002\|500.00\|500.00` |
| **Expected Output** | `APPROVED\|0.00\|OK\|Saque aprovado` |
| **Validação** | Valor (500) = Saldo (500) → Saque completo → 0 ✓ |

**Como testar:**
```bash
echo "WITHDRAW|000002|500.00|500.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

**Saída esperada:**
```
APPROVED|0.00|OK|Saque aprovado
```

---

## 🐛 Troubleshooting

### Problema: Arquivo vazio após execução

**Sintoma:**
```bash
$ cat runtime/response.txt
$ # (nada)
```

**Causas Possíveis:**
1. COBOL não foi compilado
2. `runtime/` não existe
3. Permissões de escrita

**Solução:**
```bash
# Recompile
cobc -x -free -o bin/cobol_engine cobol/transaction_engine.cob

# Crie diretório
mkdir -p runtime

# Teste de novo
echo "DEPOSIT|000001|1000.00|250.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

---

### Problema: Saldo formatado incorretamente

**Sintoma:**
```
Esperado: APPROVED|1250.00|OK|Deposito aprovado
Obtido:   APPROVED|       1250.00|OK|Deposito aprovado
```

**Causa:**
PIC clause de formatação com muitos zeros à esquerda

**Solução:**
Verifique `WS-NEW-BALANCE-TXT PIC -Z(9)9.99` e use `TRIM()` na STRING

---

### Problema: Operação não reconhecida apesar de escrever corretamente

**Sintoma:**
```
Input:  "DEPOSIT|..."
Output: "REJECTED|...|UNKNOWN_OPERATION|..."
```

**Causas Possíveis:**
1. Maiúsculas/minúsculas (resolvido por `UPPER-CASE()`)
2. Espaços em branco (resolvido por `TRIM()`)
3. Encoding diferente do esperado

**Solução - Verificação Manual:**
```bash
echo "DEPOSIT|000001|1000.00|250.00" | od -c
# Procure por caracteres estranhos (null bytes, tabs, etc.)
```

---

### Problema: Valores decimais não preservados

**Sintoma:**
```
Input:  DEPOSIT|000001|1000.50|250.75
Output: APPROVED|1251.00|OK|...  # Esperado: 1251.25
```

**Causa:**
Possível truncamento em conversão ou perda de precisão

**Solução:**
Verifique que `PIC S9(9)V99` tem espaço para 2 casas decimais

---

## 📊 Matriz de Comportamento

### DEPOSIT

```
┌─────────────────────────────────────────┐
│ OPERAÇÃO: DEPOSIT                       │
├─────────────────────────────────────────┤
│ Entrada: OPERAÇÃO|CONTA|SALDO|VALOR    │
│ Saída: STATUS|NOVO_SALDO|CODE|MSG      │
├─────────────────────────────────────────┤
│ Valor > 0?                              │
│ ├─ NÃO  → REJECTED | INVALID_AMOUNT    │
│ └─ SIM  → APPROVED | novo_saldo=S+V    │
└─────────────────────────────────────────┘
```

### WITHDRAW

```
┌─────────────────────────────────────────┐
│ OPERAÇÃO: WITHDRAW                      │
├─────────────────────────────────────────┤
│ Entrada: OPERAÇÃO|CONTA|SALDO|VALOR    │
│ Saída: STATUS|NOVO_SALDO|CODE|MSG      │
├─────────────────────────────────────────┤
│ Valor > 0?                              │
│ ├─ NÃO  → REJECTED | INVALID_AMOUNT    │
│ └─ SIM                                  │
│    Valor > Saldo?                       │
│    ├─ SIM → REJECTED | INSUFFICIENT    │
│    └─ NÃO → APPROVED | novo_saldo=S-V  │
└─────────────────────────────────────────┘
```

---

## 🎯 Checklist de Validação

Antes de considerar o programa produtivo:

- [ ] Todos os 10 testes passando
- [ ] Arquivo de request existe antes de cada execução
- [ ] Arquivo de response é criado a cada execução
- [ ] Valores decimais preservados (2 casas)
- [ ] Maiúsculas e minúsculas funcionam
- [ ] Espaços em branco são trimados
- [ ] Mensagens em português exibidas corretamente
- [ ] Código de erro sempre presente
- [ ] Arquivo de resposta nunca vazio
- [ ] Programa encerra com código 0 em sucesso

---

## 💾 Backup e Recuperação

### Backup do Request

```bash
cp runtime/request.txt runtime/request.bak
```

### Restaurar Request

```bash
cp runtime/request.bak runtime/request.txt
```

### Limpar Respostas Antigas

```bash
rm -f runtime/response.txt
```

---

## 📈 Extensões Futuras

### Suportar Operação TRANSFER

```cobol
WHEN "TRANSFER"
    PERFORM CHECK-TRANSFER
    IF VALID-TRANSFER
        COMPUTE WS-NEW-BALANCE = WS-CURRENT-BALANCE - WS-AMOUNT
        MOVE "APPROVED" TO WS-STATUS
    ELSE
        MOVE "REJECTED" TO WS-STATUS
    END-IF
```

### Adicionar Taxa Operacional

```cobol
COMPUTE WS-FEE = WS-AMOUNT * 0.01  *> 1% de taxa
COMPUTE WS-NEW-BALANCE = 
    WS-CURRENT-BALANCE - WS-AMOUNT - WS-FEE
```

### Validar Limite Diário

```cobol
IF WS-DAILY-TOTAL + WS-AMOUNT > WS-DAILY-LIMIT
    MOVE "REJECTED" TO WS-STATUS
    MOVE "DAILY_LIMIT_EXCEEDED" TO WS-CODE
END-IF
```

---

## 🔗 Fluxo Integrado C + COBOL

```
C Program (main.c)
    ↓
1. process_transaction()
    ├─ load_accounts()
    ├─ find_account()
    ├─ write_request()
    │  └─ Escreve: OPERAÇÃO|CONTA|SALDO|VALOR
    │
    ├─ run_cobol_engine()
    │  └─ executa: ./bin/cobol_engine
    │
    ├─ read_response()
    │  └─ Lê: STATUS|NOVO_SALDO|CODE|MSG
    │
    └─ Se APPROVED: save_accounts()
```

---

## 📚 Referência de Comandos Shell para Teste

```bash
# Compilar
cobc -x -free -o bin/cobol_engine cobol/transaction_engine.cob

# Teste 1
echo "DEPOSIT|000001|1000.00|250.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt

# Teste 2
echo "WITHDRAW|000002|500.00|100.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt

# Teste 3
echo "WITHDRAW|000002|500.00|1000.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt

# Teste 4
echo "TRANSFER|000001|1000.00|100.00" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt

# Teste 5
echo "" > runtime/request.txt
./bin/cobol_engine
cat runtime/response.txt
```

---

## ✅ Validação Final

Execute no WSL:

```bash
cd /mnt/c/Users/Lucas\ Jorge/Documents/Default\ Projects/Others/C-Codebase/system/c-cobol-banking
make reset-data
make run

# Esperado:
# =========================
# Deposito: APPROVED
# Saque 100: APPROVED
# Saque 1000: REJECTED (saldo insuficiente)
# Saque -10: REJECTED (valor inválido)
# =========================
```

---

**Versão:** 1.0  
**Última atualização:** 16/03/2026  
**Status:** ✅ Pronto para produção (ambiente de teste)
