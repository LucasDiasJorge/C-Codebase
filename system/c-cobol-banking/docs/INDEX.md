# 📚 Índice de Documentação - Sistema Bancário C + COBOL

## Navegação Rápida

### 🚀 Para Começar

1. **[README.md](../README.md)** - Visão geral do projeto
2. **[docs/WSL.md](WSL.md)** - Como instalar e rodar no WSL

### 🏗️ Entender a Arquitetura

1. **[docs/ARCHITECTURE.md](ARCHITECTURE.md)** - Arquitetura e responsabilidades
2. **[docs/DATA_FLOW.md](DATA_FLOW.md)** - Fluxo detalhado de dados

### 📖 Entender o Código COBOL

1. **[docs/COBOL_MANUAL.md](COBOL_MANUAL.md)** - Manual técnico completo
2. **[docs/QUICK_REFERENCE.md](QUICK_REFERENCE.md)** - Referência rápida

### 🧪 Testar e Verificar

1. **[docs/QUICK_REFERENCE.md#-casos-de-teste](QUICK_REFERENCE.md#-casos-de-teste)** - 10 casos de teste
2. **[docs/QUICK_REFERENCE.md#-troubleshooting](QUICK_REFERENCE.md#-troubleshooting)** - Problemas comuns

---

## 📋 Matriz de Documentos

| Documento | Foco | Audiência | Tamanho | Tempo Leitura |
|-----------|------|-----------|---------|--------------|
| README.md | Visão geral | Todos | Curto | 5 min |
| ARCHITECTURE.md | Design | Arquitetos | Médio | 10 min |
| WSL.md | Setup | DevOps/Desenvolvedores | Curto | 5 min |
| COBOL_MANUAL.md | Código COBOL | Programadores COBOL | Longo | 30 min |
| QUICK_REFERENCE.md | Referência + Testes | QA/Desenvolvedores | Longo | 25 min |
| DATA_FLOW.md | Fluxo de dados | Arquitetos/Debuggers | Muito Longo | 40 min |
| INDEX.md (este) | Navegação | Todos | Curto | 3 min |

---

## 🎯 Por Objetivo

### Quero entender o que é este projeto

```
1. README.md (5 min)
2. ARCHITECTURE.md (10 min)
```

### Quero rodar o projeto no meu WSL

```
1. WSL.md (5 min)
2. Execute: make setup-wsl && make run (2 min)
```

### Quero entender o código C

```
1. ARCHITECTURE.md (Responsabilidades de C)
2. Leia: c/src/main.c (comentários inline)
3. DATA_FLOW.md (Fluxo completo)
```

### Quero entender o código COBOL

```
1. COBOL_MANUAL.md (30 min)
   - Leia: Sections 1-4 (estrutura)
   - Leia: Section 4 (procedure division)
   - Consulte: Section 8 (conceitos COBOL)
2. Leia: cobol/transaction_engine.cob (10 min)
3. QUICK_REFERENCE.md (Matriz de comportamento)
```

### Quero testar o programa

```
1. QUICK_REFERENCE.md (Casos de teste)
2. Execute os 10 testes (15 min)
3. Verifique troubleshooting se necessário (5 min)
```

### Quero debugar um problema

```
1. QUICK_REFERENCE.md (Troubleshooting)
2. DATA_FLOW.md (Entender fluxo de dados)
3. COBOL_MANUAL.md (Section 6: Tratamento de erros)
```

### Quero estender o projeto

```
1. ARCHITECTURE.md (Responsabilidades)
2. QUICK_REFERENCE.md (Evolução future)
3. DATA_FLOW.md (Estruturas de dados)
4. Modifique os arquivos:
   - cobol/transaction_engine.cob (lógica de negócio)
   - c/src/main.c (orquestração)
```

---

## 📖 Descrição Completa de Cada Documento

### README.md

**Propósito:** Visão geral e entrada principal

**Conteúdo:**
- Objetivo técnico
- Estrutura de diretórios
- Como funciona (resumo)
- Instruções básicas de uso
- Limitações didáticas

**Quando ler:** Sempre que abrir o projeto

---

### ARCHITECTURE.md

**Propósito:** Entender o design da solução

**Conteúdo:**
- Visão geral da integração
- Responsabilidades (C vs COBOL)
- Contrato de integracao (request/response)
- Fluxo de execução
- Regras de negócio
- Tratamento de erros
- Relevância em ambientes legados
- Evolução recomendada

**Quando ler:** Antes de modificar a arquitetura

---

### WSL.md

**Propósito:** Guia passo-a-passo de instalação e execução

**Conteúdo:**
- Como abrir WSL
- Navegar até o projeto
- Instalar dependências
- Compilar
- Rodar demo
- Resultado esperado
- Troubleshooting de setup
- Comandos úteis

**Quando ler:** Primeira vez executando no WSL

---

### COBOL_MANUAL.md

**Propósito:** Documentação técnica completa do código COBOL

**Conteúdo:**
- Sumário executivo
- Arquitetura (4 divisões COBOL)
- Identification Division
- Environment Division (file control)
- Data Division (file section + working storage)
- Procedure Division (lógica completa)
- Explicitação de cada variável
- Tabela de códigos de transação
- Diagrama de fluxo
- 5 exemplos de execução
- Conceitos COBOL explicados
- Tratamento de erros
- Performance e escalabilidade
- Referência de funções COBOL
- Conclusão

**Quando ler:** Para entender completamente o código COBOL

---

### QUICK_REFERENCE.md

**Propósito:** Referência rápida + guia de testes

**Conteúdo:**
- Cheat sheet de estrutura COBOL
- Tabela de variáveis
- 10 casos de teste completos (com comandos)
- Troubleshooting específico
- Matriz de comportamento (DEPOSIT/WITHDRAW)
- Checklist de validação
- Comandos de backup/recuperação
- Extensões futuras propostas
- Fluxo integrado C + COBOL
- Scripts prontos para testar

**Quando ler:** Para testar, referenciar ou debugar

---

### DATA_FLOW.md

**Propósito:** Visualizar fluxo de dados em detalhe

**Conteúdo:**
- Visão geral da integração
- Passo-a-passo de uma transação (WITHDRAW)
- Exemplo de rejeição (saldo insuficiente)
- Estado de arquivos em diferentes pontos
- Estruturas de dados em memória
- Representação interna de valores
- Garantias de integridade
- Timeline de execução (ms)
- Exemplo numérico detalhado
- Matriz de transformação de dados

**Quando ler:** Para debugar, entender fluxo de dados, ou documentar

---

## 🔍 Busca Rápida por Tópico

### Conceito: UNSTRING em COBOL

```
Arquivo: COBOL_MANUAL.md
Seção: 4.2.2 Parsing da Requisição
```

### Conceito: PIC Clause

```
Arquivo: COBOL_MANUAL.md
Seção: 8.1 PIC Clause (Picture Clause)
```

### Conceito: Como validar saldo insuficiente

```
Arquivo: COBOL_MANUAL.md
Seção: 4.2.5.2 Caso: WITHDRAW (Saque)
```

### Teste: Operação desconhecida

```
Arquivo: QUICK_REFERENCE.md
Seção: 🧪 Casos de Teste → Teste 6
```

### Problema: Saldo truncado na formatação

```
Arquivo: QUICK_REFERENCE.md
Seção: 🐛 Troubleshooting → Problema: Saldo formatado incorretamente
```

### Debug: Entender fluxo de uma transação

```
Arquivo: DATA_FLOW.md
Seção: 🔄 Passo a Passo de uma Transação
```

### Extensão: Suportar transferência entre contas

```
Arquivo: QUICK_REFERENCE.md
Seção: 📈 Extensões Futuras → Suportar Operação TRANSFER
```

---

## 📊 Estatísticas da Documentação

| Métrica | Valor |
|---------|-------|
| Total de documentos | 7 (+ código) |
| Total de linhas | ~2500 |
| Seções principais | ~50 |
| Exemplos de código | ~30 |
| Casos de teste | 10 |
| Diagramas ASCII | 15+ |
| Tempo total de leitura | ~2 horas |

---

## ✅ Checklist de Familiarização

- [ ] Li README.md
- [ ] Li ARCHITECTURE.md
- [ ] Consegui rodar WSL.md com sucesso
- [ ] Entendi as 4 divisões COBOL (COBOL_MANUAL.md sections 1-3)
- [ ] Entendi a Procedure Division (COBOL_MANUAL.md section 4)
- [ ] Rodei os 10 casos de teste (QUICK_REFERENCE.md)
- [ ] Consegui debugar um erro usando DATA_FLOW.md
- [ ] Consegui estender o código (nova operação ou validação)

---

## 🔗 Estrutura de Links

```
README.md
├─ WSL.md (Como rodar)
├─ ARCHITECTURE.md (Design)
├─ COBOL_MANUAL.md (Código COBOL)
├─ QUICK_REFERENCE.md (Testes)
├─ DATA_FLOW.md (Fluxo de dados)
└─ INDEX.md (este)

c/src/main.c
├─ ARCHITECTURE.md (Responsabilidades C)
└─ DATA_FLOW.md (Fluxo C → COBOL)

cobol/transaction_engine.cob
├─ COBOL_MANUAL.md (Explicação linha-a-linha)
├─ QUICK_REFERENCE.md (Matriz de comportamento)
└─ DATA_FLOW.md (Fluxo COBOL)

data/accounts.csv
├─ ARCHITECTURE.md (Persistência)
└─ DATA_FLOW.md (Estado em diferentes pontos)

scripts/
├─ WSL.md (Instruções)
└─ QUICK_REFERENCE.md (Comandos de teste)
```

---

## 🚀 Começar Agora

### Opção 1: Rodar a demo (5 min)
```bash
cd /mnt/c/Users/Lucas\ Jorge/Documents/Default\ Projects/Others/C-Codebase/system/c-cobol-banking
make setup-wsl
make reset-data
make run
```

### Opção 2: Entender a arquitetura (15 min)
```
1. Leia: README.md
2. Leia: ARCHITECTURE.md
3. Abra: cobol/transaction_engine.cob (visualize)
```

### Opção 3: Estudar profundo (2 horas)
```
1. Leia: README.md (5 min)
2. Leia: ARCHITECTURE.md (10 min)
3. Execute: WSL.md demo (5 min)
4. Leia: COBOL_MANUAL.md (30 min)
5. Execute: QUICK_REFERENCE.md testes (15 min)
6. Leia: DATA_FLOW.md (40 min)
7. Tente estender (15 min)
```

---

## 📞 Referência Rápida

| Pergunta | Resposta |
|----------|----------|
| Como rodar? | WSL.md |
| Como funciona? | ARCHITECTURE.md |
| Como debugar? | DATA_FLOW.md + QUICK_REFERENCE.md |
| Como testar? | QUICK_REFERENCE.md |
| Como estender? | QUICK_REFERENCE.md (seção Extensões) |
| Como entender COBOL? | COBOL_MANUAL.md |

---

## 🎓 Aprendizado Gradual

### Nível 1: Iniciante (30 min)
```
README.md → WSL.md → make run
```

### Nível 2: Intermediário (1.5 horas)
```
+ ARCHITECTURE.md
+ QUICK_REFERENCE.md (testes)
+ Explorar código fonte
```

### Nível 3: Avançado (2.5 horas)
```
+ COBOL_MANUAL.md (completo)
+ DATA_FLOW.md (completo)
+ Modificar código
+ Adicionar nova operação
```

### Nível 4: Expert (4+ horas)
```
+ Todos os documentos
+ Implementar transferência entre contas
+ Adicionar auditoria
+ Otimizar performance
```

---

**Versão:** 1.0  
**Data:** 16/03/2026  
**Status:** ✅ Documentação Completa
