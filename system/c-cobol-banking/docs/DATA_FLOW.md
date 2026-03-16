# Fluxo de Dados: C ↔ COBOL (Bancário)

## 📡 Visão Geral da Integração

```
┌──────────────────────┐
│  APLICAÇÃO C         │
│  (bank_gateway)      │
├──────────────────────┤
│ 1. Load Accounts     │ ← data/accounts.csv
│ 2. Select Operation  │
│ 3. Validate Input    │
│ 4. Write Request     │ → runtime/request.txt
│ 5. Execute COBOL     │   (via system())
│ 6. Read Response     │ ← runtime/response.txt
│ 7. Update Balance    │
│ 8. Save Accounts     │ → data/accounts.csv
└──────────────────────┘
         ↕ (arquivo de troca)
┌──────────────────────┐
│  CORE COBOL          │
│  (transaction_engine)│
├──────────────────────┤
│ 1. Read Request      │ ← runtime/request.txt
│ 2. Parse Input       │ (UNSTRING)
│ 3. Convert to Number │ (NUMVAL)
│ 4. Validate Amount   │ (> 0?)
│ 5. Evaluate Operation│ (EVALUATE)
│ 6. Calculate New Bal │ (COMPUTE)
│ 7. Format Response   │ (STRING)
│ 8. Write Response    │ → runtime/response.txt
│ 9. End Program       │ (STOP RUN)
└──────────────────────┘
```

---

## 🔄 Passo a Passo de uma Transação

### Operação: WITHDRAW (Saque de 100 da conta 000002 com saldo 500)

#### **Passo 1: C prepara dados**

```c
// Em main.c
process_transaction("WITHDRAW", "000002", 100.00);
```

#### **Passo 2: C carrega contas de arquivo**

**Arquivo: data/accounts.csv (antes)**
```
000001|ANA SILVA|1000.00
000002|BRUNO COSTA|500.00
000003|CARLA SOUZA|1500.00
```

**Estrutura na memória (C):**
```c
Account accounts[3] = {
  { "000001", "ANA SILVA", 1000.00 },
  { "000002", "BRUNO COSTA", 500.00 },     // ← Selecionada
  { "000003", "CARLA SOUZA", 1500.00 }
};
```

#### **Passo 3: C encontra a conta**

```c
// Busca conta
idx = find_account_index(accounts, 3, "000002");  // idx = 1
Account* selected = &accounts[1];  // BRUNO COSTA
```

#### **Passo 4: C escreve requisição**

**Arquivo: runtime/request.txt (criado)**
```
WITHDRAW|000002|500.00|100.00
   ↑        ↑      ↑      ↑
   │        │      │      └─ VALOR (montante da operação)
   │        │      └──────── SALDO_ATUAL (saldo antes da op)
   │        └───────────── CONTA (ID da conta)
   └──────────────────── OPERAÇÃO (DEPOSIT/WITHDRAW)
```

**Conteúdo exato:**
```
WITHDRAW|000002|500.00|100.00
```

**Bytes (hex):**
```
57 49 54 48 44 52 41 57 7c 30 30 30 30 30 32 7c 35 30 30 2e 30 30 7c 31 30 30 2e 30 30
W  I  T  H  D  R  A  W  |  0  0  0  0  0  2  |  5  0  0  .  0  0  |  1  0  0  .  0  0
```

#### **Passo 5: C invoca o COBOL**

**Comando executado (via system()):**
```bash
./bin/cobol_engine
```

#### **Passo 6: COBOL abre e lê requisição**

**Dentro do COBOL (transaction_engine.cob):**

```cobol
OPEN INPUT REQUEST-FILE.
READ REQUEST-FILE INTO WS-REQUEST-LINE.
│
├─ WS-REQUEST-LINE = "WITHDRAW|000002|500.00|100.00"
│
CLOSE REQUEST-FILE.
```

#### **Passo 7: COBOL faz parsing**

```cobol
UNSTRING WS-REQUEST-LINE DELIMITED BY "|"
    INTO WS-OP
         WS-ACCOUNT-ID
         WS-CURRENT-BALANCE-TXT
         WS-AMOUNT-TXT
END-UNSTRING.

├─ WS-OP                   = "WITHDRAW"
├─ WS-ACCOUNT-ID           = "000002"
├─ WS-CURRENT-BALANCE-TXT  = "500.00"
└─ WS-AMOUNT-TXT           = "100.00"
```

#### **Passo 8: COBOL converte para numérico**

```cobol
COMPUTE WS-CURRENT-BALANCE = FUNCTION NUMVAL("500.00");   │
COMPUTE WS-AMOUNT = FUNCTION NUMVAL("100.00");             │
MOVE WS-CURRENT-BALANCE TO WS-NEW-BALANCE;                 │

├─ WS-CURRENT-BALANCE (S9(9)V99) = 500.00 (formato interno)
├─ WS-AMOUNT (S9(9)V99)           = 100.00 (formato interno)
└─ WS-NEW-BALANCE (S9(9)V99)      = 500.00 (cópia inicial)
```

**Representação interna (COBOL):**
```
Valor     Representação
500.00 → 00050000 (8 dígitos + símbolo de posição decimal implícita)
100.00 → 00010000
```

#### **Passo 9: COBOL valida montante**

```cobol
IF WS-AMOUNT <= 0
    ├─ 100.00 <= 0? NÃO
    └─ Continua processamento
END-IF.
```

#### **Passo 10: COBOL avalia operação**

```cobol
EVALUATE FUNCTION UPPER-CASE(FUNCTION TRIM(WS-OP))
// UPPER-CASE("WITHDRAW") = "WITHDRAW"
// TRIM("WITHDRAW") = "WITHDRAW"

    WHEN "WITHDRAW"
        ├─ IF WS-AMOUNT > WS-CURRENT-BALANCE
        │  ├─ 100.00 > 500.00? NÃO
        │  └─ ELSE
        │     ├─ COMPUTE WS-NEW-BALANCE = 500.00 - 100.00
        │     │  └─ WS-NEW-BALANCE = 400.00
        │     ├─ MOVE "APPROVED" TO WS-STATUS
        │     ├─ MOVE "OK" TO WS-CODE
        │     └─ MOVE "Saque aprovado" TO WS-MESSAGE
        │
        ├─ WS-STATUS  = "APPROVED"
        ├─ WS-CODE    = "OK"
        ├─ WS-MESSAGE = "Saque aprovado"
        └─ WS-NEW-BALANCE = 400.00
END-EVALUATE.
```

#### **Passo 11: COBOL formata novo saldo**

```cobol
MOVE WS-NEW-BALANCE TO WS-NEW-BALANCE-TXT;
│
├─ Input: WS-NEW-BALANCE = 400.00 (numérico)
└─ Output: WS-NEW-BALANCE-TXT = "400.00" (string formatada, PIC -Z(9)9.99)
```

#### **Passo 12: COBOL concatena resposta**

```cobol
STRING
    FUNCTION TRIM(WS-STATUS)           "APPROVED"
    "|"                                "|"
    FUNCTION TRIM(WS-NEW-BALANCE-TXT)  "400.00"
    "|"                                "|"
    FUNCTION TRIM(WS-CODE)             "OK"
    "|"                                "|"
    FUNCTION TRIM(WS-MESSAGE)          "Saque aprovado"
    DELIMITED BY SIZE
    INTO WS-RESPONSE-LINE
END-STRING.

├─ WS-RESPONSE-LINE = "APPROVED|400.00|OK|Saque aprovado"
```

**Concatenação passo a passo:**
```
"" 
+ "APPROVED"           = "APPROVED"
+ "|"                  = "APPROVED|"
+ "400.00"             = "APPROVED|400.00"
+ "|"                  = "APPROVED|400.00|"
+ "OK"                 = "APPROVED|400.00|OK"
+ "|"                  = "APPROVED|400.00|OK|"
+ "Saque aprovado"     = "APPROVED|400.00|OK|Saque aprovado"
```

#### **Passo 13: COBOL escreve resposta**

**Arquivo: runtime/response.txt (criado/sobrescrito)**
```
APPROVED|400.00|OK|Saque aprovado
```

**Bytes (hex):**
```
41 50 50 52 4f 56 45 44 7c 34 30 30 2e 30 30 7c 4f 4b 7c 53 61 71 75 65 20 61 70 72 6f 76 61 64 6f
A  P  P  R  O  V  E  D  |  4  0  0  .  0  0  |  O  K  |  S  a  q  u  e     a  p  r  o  v  a  d  o
```

#### **Passo 14: COBOL encerra**

```cobol
STOP RUN.  ← Retorna código 0 (sucesso) para C
```

#### **Passo 15: C lê resposta**

```c
read_response(&response);
// Resultado da estrutura:
// response.status = "APPROVED"
// response.new_balance = 400.00
// response.code = "OK"
// response.message = "Saque aprovado"
```

#### **Passo 16: C avalia resposta**

```c
if (strcmp(response.status, "APPROVED") == 0) {
    // Status é APPROVED? SIM
    accounts[idx].balance = response.new_balance;  // 400.00
    save_accounts(accounts, count);  // Persiste
}
```

#### **Passo 17: C persiste dados**

**Arquivo: data/accounts.csv (depois)**
```
000001|ANA SILVA|1000.00
000002|BRUNO COSTA|400.00       ← SALDO ATUALIZADO
000003|CARLA SOUZA|1500.00
```

#### **Passo 18: C exibe resultado**

**Stdout (console):**
```
[CORE COBOL] status=APPROVED code=OK message=Saque aprovado
Conta 000002 (BRUNO COSTA) | Saldo atual: 400.00
```

---

## 🚫 Exemplo de Rejeição: Saque com Saldo Insuficiente

**Operação:** WITHDRAW (Tentar sacar 1000 com saldo 500)

### **Arquivo de Request:**
```
WITHDRAW|000002|500.00|1000.00
```

### **Processamento COBOL:**

```cobol
EVALUATE FUNCTION UPPER-CASE(FUNCTION TRIM("WITHDRAW"))
    WHEN "WITHDRAW"
        IF WS-AMOUNT > WS-CURRENT-BALANCE
        │   1000.00 > 500.00? SIM ← CONDIÇÃO VERDADEIRA
        │
        ├─ MOVE "REJECTED" TO WS-STATUS
        ├─ MOVE "INSUFFICIENT_FUNDS" TO WS-CODE
        ├─ MOVE "Saldo insuficiente" TO WS-MESSAGE
        │  (WS-NEW-BALANCE permanece 500.00 - não é alterado)
        │
        ├─ WS-STATUS  = "REJECTED"
        ├─ WS-CODE    = "INSUFFICIENT_FUNDS"
        ├─ WS-MESSAGE = "Saldo insuficiente"
        └─ WS-NEW-BALANCE = 500.00 (inalterado)
END-EVALUATE.
```

### **Arquivo de Response:**
```
REJECTED|500.00|INSUFFICIENT_FUNDS|Saldo insuficiente
```

### **Processamento C:**

```c
if (strcmp(response.status, "APPROVED") == 0) {
    // "REJECTED" == "APPROVED"? NÃO
    // Saldo NÃO é atualizado
    // Arquivo data/accounts.csv NÃO é modificado
}

// Exibe:
[CORE COBOL] status=REJECTED code=INSUFFICIENT_FUNDS message=Saldo insuficiente
Conta 000002 (BRUNO COSTA) | Saldo atual: 500.00
```

### **Resultado:**
```
Saldo antes:  500.00
Saldo depois: 500.00  (inalterado)
```

---

## 📋 Estado de Arquivo em Diferentes Pontos

### **Estado Inicial (antes de qualquer operação)**

**data/accounts.csv:**
```
000001|ANA SILVA|1000.00
000002|BRUNO COSTA|500.00
000003|CARLA SOUZA|1500.00
```

**runtime/request.txt:** (não existe)

**runtime/response.txt:** (não existe)

---

### **Após primeiro DEPOSIT de 250 em 000001**

**runtime/request.txt:**
```
DEPOSIT|000001|1000.00|250.00
```

**runtime/response.txt:**
```
APPROVED|1250.00|OK|Deposito aprovado
```

**data/accounts.csv:**
```
000001|ANA SILVA|1250.00        ← ATUALIZADO
000002|BRUNO COSTA|500.00
000003|CARLA SOUZA|1500.00
```

---

### **Após segundo WITHDRAW de 100 em 000002**

**runtime/request.txt:**
```
WITHDRAW|000002|500.00|100.00
```

**runtime/response.txt:**
```
APPROVED|400.00|OK|Saque aprovado
```

**data/accounts.csv:**
```
000001|ANA SILVA|1250.00
000002|BRUNO COSTA|400.00        ← ATUALIZADO
000003|CARLA SOUZA|1500.00
```

---

### **Após terceiro WITHDRAW REJEITADO de 1000 em 000002**

**runtime/request.txt:**
```
WITHDRAW|000002|400.00|1000.00
```

**runtime/response.txt:**
```
REJECTED|400.00|INSUFFICIENT_FUNDS|Saldo insuficiente
```

**data/accounts.csv:**
```
000001|ANA SILVA|1250.00
000002|BRUNO COSTA|400.00        ← NÃO ALTERADO
000003|CARLA SOUZA|1500.00
```

---

## 🔍 Estruturas de Dados Detalhadas

### **C: Account (struct)**

```c
typedef struct {
    char id[7];           // Ex: "000001"
    char name[64];        // Ex: "ANA SILVA"
    double balance;       // Ex: 1250.00 (IEEE 754 double)
} Account;

// Tamanho: 7 + 64 + 8 = 79 bytes (+ padding)

Exemplo na memória:
┌─────────────────────────────────┐
│ id[7]    = "000001\0"           │  (7 bytes)
├─────────────────────────────────┤
│ name[64] = "ANA SILVA\0...\0"   │  (64 bytes)
├─────────────────────────────────┤
│ balance  = 1250.00              │  (8 bytes, IEEE 754)
└─────────────────────────────────┘
```

### **C: EngineResponse (struct)**

```c
typedef struct {
    char status[16];      // "APPROVED" ou "REJECTED"
    double new_balance;   // Novo saldo (IEEE 754 double)
    char code[32];        // "OK", "INSUFFICIENT_FUNDS", etc.
    char message[128];    // Descrição em português
} EngineResponse;

// Tamanho: 16 + 8 + 32 + 128 = 184 bytes (+ padding)

Exemplo na memória:
┌──────────────────────────┐
│ status[16]   = "APPROVED\0" │  (16 bytes)
├──────────────────────────┤
│ new_balance = 400.00     │  (8 bytes)
├──────────────────────────┤
│ code[32]     = "OK\0"    │  (32 bytes)
├──────────────────────────┤
│ message[128] = "Saque...\0" │  (128 bytes)
└──────────────────────────┘
```

### **COBOL: Variáveis Numéricas**

```cobol
01 WS-CURRENT-BALANCE  PIC S9(9)V99.

Representação interna (packed decimal):
┌──────────────────────────────────┐
│ Formato: Sinal | 9 dígitos | 2 decimais │
├──────────────────────────────────┤
│ 500.00 internamente:           │
│ 00 05 00 00 (4 bytes packed)   │
│ ↑  ↑  ↑  ↑                     │
│ S  9  9  99                    │
└──────────────────────────────────┘

Intervalo: -999,999,999.99 a +999,999,999.99
```

### **COBOL: Variáveis de String**

```cobol
01 WS-REQUEST-LINE  PIC X(200).

Representação interna (caracteres ASCII):
┌──────────────────────────────────────────────────────┐
│ "DEPOSIT|000001|1000.00|250.00"                      │
│  01001101 01000101 01010000 01001111 ...             │
│  D        E        P        O        ...             │
│                                                      │
│ Comprimento: 34 chars + espaço até 200              │
└──────────────────────────────────────────────────────┘
```

---

## 🔐 Garantias de Integridade

### **Invariantes Mantidas**

1. **Request sempre bem-formado:**
   ```
   ✓ OPERACAO|CONTA|SALDO|VALOR (formatado)
   ✗ Nunca vazio ou truncado
   ```

2. **Response sempre gerada:**
   ```
   ✓ STATUS|NOVO_SALDO|CODIGO|MENSAGEM (sempre 4 campos)
   ✗ Nunca incompleto
   ```

3. **Saldo nunca fica negativo (excepto rejeição):**
   ```
   ✓ Se WITHDRAW > SALDO → REJECTED (saldo não altera)
   ✗ Nunca persiste transação que torna saldo negativo
   ```

4. **Transação é atômica (C):**
   ```
   ✓ Se APPROVED → altera saldo E salva arquivo
   ✓ Se REJECTED → não altera saldo
   ✗ Nunca estado intermediário
   ```

---

## ⏱️ Timeline de Execução

```
Tempo (ms)  Evento

0           C: inicia process_transaction("WITHDRAW", ...)
1           C: load_accounts() completa
3           C: find_account_index() encontra conta
5           C: write_request() cria runtime/request.txt
7           C: system() invoca ./bin/cobol_engine

8           COBOL: OPEN INPUT REQUEST-FILE
9           COBOL: READ REQUEST-FILE
10          COBOL: UNSTRING parsing
12          COBOL: NUMVAL conversão
14          COBOL: Validações
15          COBOL: COMPUTE novo saldo
16          COBOL: STRING concatena resposta
17          COBOL: OPEN OUTPUT RESPONSE-FILE
18          COBOL: WRITE RESPONSE-FILE
19          COBOL: STOP RUN (retorna ao C)

20          C: run_cobol_engine() retorna
21          C: read_response() abre e lê arquivo
23          C: parse resposta
25          C: strcmp(status, "APPROVED") 
26          C: save_accounts() persiste
28          C: printf() exibe resultado

30          Total: ~30ms por transação
```

---

## 🧮 Exemplo Numérico Detalhado

### **Cenário: Depósito de 542.37**

**Valores em diferentes representações:**

| Ponto | Representação | Valor |
|-------|---------------|-------|
| C (double) | IEEE 754 | 542.37 |
| C (string) | "%\.2f" | "542.37" |
| Arquivo | ASCII | 542.37 |
| COBOL (text) | PIC X(30) | "542.37" |
| COBOL (num) | PIC S9(9)V99 | 54237 (em unidades de 0.01) |
| Formatação | PIC -Z(9)9.99 | "542.37" |

**Cálculo de novo saldo:**

```
Saldo anterior (C): 1000.00 (double)
Montante: 542.37 (double)
         ↓
Arquivo request: "DEPOSIT|000001|1000.00|542.37"
         ↓
COBOL NUMVAL: 100000 (unidades de 0.01), 54237
         ↓
COMPUTE: 100000 + 54237 = 154237
         ↓
MOVE para formatação: 154237 → "1542.37"
         ↓
Arquivo response: "APPROVED|1542.37|OK|Deposito aprovado"
         ↓
C STRTOD: "1542.37" → 1542.37 (double)
         ↓
Persiste: accounts[0].balance = 1542.37
         ↓
Arquivo accounts.csv: "000001|ANA SILVA|1542.37"
```

---

## 📊 Matriz de Transformação de Dados

```
┌─────────────────────────────────────────────────────────────┐
│ Transformação de Dados através das Camadas                 │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  C (double)    →  String    →  Arquivo  →  String  →  COBOL │
│                                                             │
│  500.00        → "500.00"   → 500.00    → "500.00" → 50000 │
│                                                   (V99)    │
│                                                             │
│  Operação (C)   →  Request  →  Response  →  Result    (C)  │
│                                                             │
│  WITHDRAW      → write_req  → run_cobol  → read_resp      │
│  100.00        → 100.00     → COMPUTE   → 400.00         │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

**Versão:** 1.0  
**Última atualização:** 16/03/2026  
**Requisito:** Entendimento básico de C e COBOL
