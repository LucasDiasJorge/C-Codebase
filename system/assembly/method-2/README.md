# 🔗 Assembly Externo em C - Método 2

## 📖 Conceito

Este diretório demonstra como criar e usar **funções Assembly externas** em programas C. Diferente do inline assembly, aqui criamos arquivos `.s` separados que são compilados e linkados com o código C.

## 🎯 Objetivos de Aprendizado

- Criar funções Assembly em arquivos separados
- Entender o processo de linking entre C e Assembly
- Aprender convenções de chamada (calling conventions)
- Dominar a sintaxe Intel Assembly
- Compreender o ABI (Application Binary Interface)

## 📁 Arquivos

### 1. `main.c` - Programa Principal C
Chama a função Assembly externa `addNumbers()`.

### 2. `ext.s` - Função Assembly Externa
Implementa a função `addNumbers` em Assembly puro.

### 3. `ext.o` - Arquivo Objeto Compilado
Resultado da compilação do arquivo Assembly.

## 🧠 Conceitos Fundamentais

### Convenção de Chamada x86_64 (System V ABI)
- **1º parâmetro**: `rdi`
- **2º parâmetro**: `rsi`
- **3º parâmetro**: `rdx`
- **4º parâmetro**: `rcx`
- **Valor de retorno**: `rax`

### Sintaxe Intel vs AT&T
```asm
; Intel Syntax (mais legível)
mov rax, rdi
add rax, rsi

; AT&T Syntax (padrão GCC)
movq %rdi, %rax
addq %rsi, %rax
```

## 💻 Implementação

### Arquivo C (`main.c`)
```c
#include <stdio.h>

// Declaração da função Assembly externa
int addNumbers(int a, int b);

int main(){
    printf("Sum is %d\n", addNumbers(5, 5));
    return 0;
}
```

### Arquivo Assembly (`ext.s`)
```asm
.intel_syntax noprefix    # Usar sintaxe Intel (mais clara)

.global addNumbers        # Tornar função visível para o linker

.text                     # Seção de código

addNumbers:
    add rdi, rsi         # rdi = rdi + rsi (soma os parâmetros)
    mov rax, rdi         # rax = rdi (valor de retorno)
    ret                  # retorna ao caller
```

## 🔄 Processo de Compilação

### Passo a Passo:
```bash
# 1. Compilar Assembly para objeto
as --64 ext.s -o ext.o

# 2. Compilar C e linkar com objeto Assembly
gcc main.c ext.o -o programa

# 3. Executar
./programa
```

### Compilação Alternativa:
```bash
# Compilar tudo de uma vez
gcc main.c ext.s -o programa
```

## 📊 Análise do Assembly

### Visualizar Símbolos no Objeto:
```bash
nm ext.o
# Saída: 0000000000000000 T addNumbers

objdump -d ext.o
# Mostra o disassembly da função
```

### Debug com GDB:
```bash
gcc -g main.c ext.s -o programa
gdb programa
(gdb) break addNumbers
(gdb) run
(gdb) info registers
```

## 🎯 Análise da Função Assembly

```asm
addNumbers:
    add rdi, rsi    # Soma: rdi (parâmetro a) + rsi (parâmetro b)
    mov rax, rdi    # Move resultado para rax (valor de retorno)
    ret             # Retorna ao código C
```

### Fluxo de Execução:
1. **C chama** `addNumbers(5, 5)`
2. **Parâmetros**: 5 → rdi, 5 → rsi
3. **Assembly**: rdi = rdi + rsi (5 + 5 = 10)
4. **Retorno**: rax = 10
5. **C recebe**: valor 10

## 🔧 Registradores x86_64

### Registradores de Propósito Geral:
| 64-bit | 32-bit | 16-bit | 8-bit | Uso |
|--------|--------|--------|-------|-----|
| RAX | EAX | AX | AL | Acumulador, retorno |
| RDI | EDI | DI | DIL | 1º parâmetro |
| RSI | ESI | SI | SIL | 2º parâmetro |
| RDX | EDX | DX | DL | 3º parâmetro |
| RCX | ECX | CX | CL | 4º parâmetro |

### Registradores Especiais:
- **RSP**: Stack Pointer
- **RBP**: Base Pointer
- **RIP**: Instruction Pointer

## 🚀 Vantagens do Assembly Externo

### ✅ Prós:
- **Organização**: Código Assembly separado
- **Reutilização**: Funções podem ser usadas por múltiplos programas
- **Debugging**: Mais fácil de debugar que inline assembly
- **Manutenção**: Código Assembly isolado
- **Performance**: Controle total sobre otimizações

### ❌ Contras:
- **Complexidade**: Processo de build mais complexo
- **Portabilidade**: Específico da arquitetura
- **Conhecimento**: Requer domínio de Assembly e ABI

## 🎨 Exemplos Avançados

### Função com Múltiplos Parâmetros:
```asm
; int multiply(int a, int b, int c, int d);
multiply:
    imul rdi, rsi    # a * b
    imul rdx, rcx    # c * d  
    imul rdi, rdx    # (a*b) * (c*d)
    mov rax, rdi     # resultado
    ret
```

### Função com Controle de Fluxo:
```asm
; int max(int a, int b);
max:
    cmp rdi, rsi     # compara a com b
    jge return_a     # se a >= b, retorna a
    mov rax, rsi     # senão, retorna b
    ret
return_a:
    mov rax, rdi
    ret
```

## 🛠️ Ferramentas Úteis

### Análise e Debug:
```bash
# Ver símbolos
nm arquivo.o

# Disassembly
objdump -d arquivo.o

# Hexdump
hexdump -C arquivo.o

# Strings
strings arquivo.o

# Debug com GDB
gdb programa
```

## 🎓 Conceitos C/Assembly Demonstrados

- **Linking**: Ligação entre código C e Assembly
- **ABI**: Interface binária entre linguagens
- **Calling Conventions**: Como funções são chamadas
- **Symbol Table**: Tabela de símbolos para linking
- **Object Files**: Arquivos objeto compilados
- **Cross-Language**: Integração entre linguagens

## 📚 Casos de Uso Reais

1. **Kernels**: Código crítico de sistema operacional
2. **Drivers**: Interface com hardware específico
3. **Criptografia**: Implementações otimizadas de algoritmos
4. **DSP**: Processamento digital de sinais
5. **Games**: Loops críticos de performance
6. **Embedded**: Código para microcontroladores

## 🔍 Comparação: Inline vs Externo

| Aspecto | Inline Assembly | Assembly Externo |
|---------|----------------|------------------|
| **Organização** | Misturado com C | Arquivos separados |
| **Reutilização** | Limitada | Alta |
| **Debug** | Mais difícil | Mais fácil |
| **Build** | Simples | Mais complexo |
| **Manutenção** | Difícil | Melhor |

## 🎬 Material de Referência

📺 **Tutorial em Vídeo**: [Assembly Integration with C](https://www.youtube.com/watch?v=d8eDTE_MaEQ)

Este método demonstra uma abordagem profissional para integrar Assembly em projetos C, mantendo organização e permitindo reutilização de código otimizado.