# 🔧 Assembly Inline em C - Método 1

## 📖 Conceito

Este diretório demonstra como integrar código Assembly diretamente em programas C usando **inline assembly**. Esta técnica permite otimizações específicas e acesso direto aos recursos do processador.

## 🎯 Objetivos de Aprendizado

- Entender a sintaxe de inline assembly no GCC
- Aprender sobre registradores do processador
- Compreender syscalls de sistema
- Dominar as restrições de entrada e saída

## 📁 Arquivos

### 1. `main.c` - Operações Aritméticas
Demonstra soma de dois números usando assembly inline.

### 2. `hello.c` - Syscalls Diretas
Mostra como fazer syscalls diretamente sem usar a libc.

## 🧠 Conceitos Fundamentais

### Sintaxe do Inline Assembly (GCC)
```c
asm [volatile] (
    "assembly_code"
    : output_operands     // %0, %1, %2...
    : input_operands      // parâmetros de entrada
    : clobbered_registers // registradores modificados
);
```

### Tipos de Restrições
- `"=r"`: Saída em qualquer registrador
- `"r"`: Entrada em qualquer registrador
- `"m"`: Operando na memória
- `"i"`: Constante imediata

## 💻 Exemplo 1: Soma em Assembly

```c
int a = 10, b = 20, result;

asm("movl %1, %%eax;     # Move b para eax\n"
    "addl %2, %%eax;     # Adiciona a ao eax\n"
    "movl %%eax, %0;     # Move resultado para result\n"
    : "=r" (result)      // %0 = result (saída)
    : "r" (b),           // %1 = b (entrada)
      "r" (a)            // %2 = a (entrada)
    : "%eax"             // eax será modificado
);
```

### Explicação Detalhada:
1. **`movl %1, %%eax`**: Move o valor de `b` para o registrador EAX
2. **`addl %2, %%eax`**: Adiciona `a` ao valor em EAX
3. **`movl %%eax, %0`**: Move o resultado de EAX para `result`
4. **`%%eax`**: Notation com duplo % para registradores reais

## 🔧 Exemplo 2: Syscall Direta

```c
asm volatile (
    "movl $4, %%eax\n"    // sys_write (syscall 4)
    "movl $1, %%ebx\n"    // stdout (file descriptor 1)
    "movl %0, %%ecx\n"    // endereço da mensagem
    "movl $13, %%edx\n"   // tamanho da mensagem
    "int $0x80\n"         // interrupção do sistema
    :
    : "r" (msg)           // entrada: ponteiro para mensagem
    : "%eax", "%ebx", "%ecx", "%edx"  // registradores modificados
);
```

### Registradores x86 (32-bit):
- **EAX**: Acumulador, usado para valores de retorno e syscall number
- **EBX**: Base, primeiro parâmetro de syscall
- **ECX**: Counter, segundo parâmetro de syscall
- **EDX**: Data, terceiro parâmetro de syscall

## 📊 Syscalls Linux Comuns

| Número | Nome | Função |
|--------|------|---------|
| 1 | sys_exit | Terminar processo |
| 3 | sys_read | Ler dados |
| 4 | sys_write | Escrever dados |
| 5 | sys_open | Abrir arquivo |
| 6 | sys_close | Fechar arquivo |

## 🛠️ Compilação

```bash
# Compilar exemplo de soma
gcc -o main main.c

# Compilar exemplo de syscall
gcc -o hello hello.c

# Compilar com debug info
gcc -g -o main main.c

# Ver assembly gerado
gcc -S main.c
objdump -d main
```

## ⚡ Execução

```bash
# Executar soma
./main
# Saída: Resultado: 30

# Executar hello
./hello
# Saída: Hello, World!
```

## 🔍 Análise do Assembly

### Visualizar Assembly Gerado:
```bash
gcc -S -masm=intel main.c
cat main.s
```

### Debugging com GDB:
```bash
gcc -g -o main main.c
gdb main
(gdb) disassemble main
(gdb) info registers
(gdb) step
```

## 🎯 Quando Usar Inline Assembly

### ✅ Bons Casos de Uso:
- Operações críticas de performance
- Instruções específicas do processador (SSE, AVX)
- Acesso direto a hardware
- Syscalls otimizadas
- Operações atômicas

### ❌ Evitar Quando:
- Código simples que o compilador otimiza bem
- Portabilidade é importante
- Manutenibilidade é prioridade
- Time não tem experiência com assembly

## 🚨 Cuidados Importantes

1. **Portabilidade**: Código assembly é específico da arquitetura
2. **Otimização**: Compiladores modernos são muito eficientes
3. **Debugging**: Assembly inline é mais difícil de debugar
4. **Manutenção**: Código assembly é menos legível

## 🎓 Conceitos C Demonstrados

- **Inline Assembly**: Integração C/Assembly
- **Registradores**: Uso direto de registradores CPU
- **Syscalls**: Chamadas de sistema de baixo nível
- **Memory Constraints**: Restrições de memória e registradores
- **Volatile**: Prevenir otimizações indevidas

## 📚 Material Complementar

- Intel x86 Instruction Set Reference
- System V ABI (Application Binary Interface)
- GCC Inline Assembly Documentation
- Linux System Call Table

Este exemplo demonstra a ponte entre C e Assembly, mostrando como ter controle total sobre o hardware quando necessário, mas sempre com consciência dos trade-offs envolvidos.
