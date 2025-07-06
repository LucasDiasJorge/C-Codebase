# 📁 Criação e Escrita de Arquivos em C

## 📖 Conceito

Este projeto demonstra como **criar arquivos e escrever dados** usando as funções de I/O da biblioteca padrão do C. É uma introdução fundamental à manipulação de arquivos, um conceito essencial em programação.

## 🎯 Objetivos de Aprendizado

- Entender o conceito de streams de arquivo
- Aprender sobre ponteiros de arquivo (`FILE*`)
- Dominar funções de I/O: `fopen()`, `fputs()`, `fgets()`, `fclose()`
- Compreender modos de abertura de arquivo
- Implementar tratamento de erro robusto

### Manipulação de arquivos

![Alt text](image.png)

## 🏗️ Estrutura do Programa

### Fluxo Principal
```
1. Abrir arquivo para escrita (criar se não existir)
2. Verificar se abertura foi bem-sucedida
3. Ler dados do usuário
4. Escrever dados no arquivo
5. Fechar arquivo (flush + liberação de recursos)
```

### Estruturas Principais
```c
FILE *fPtr;           // Ponteiro para stream de arquivo
char data[DATA_SIZE]; // Buffer para dados do usuário
```

## 💻 Implementação Detalhada

### 1. Abertura do Arquivo
```c
FILE *fPtr = fopen("data/file1.txt", "w");

if(fPtr == NULL) {
    printf("Unable to create file.\n");
    exit(EXIT_FAILURE);
}
```

**Modo "w"**:
- **Write mode**: Escrita
- **Comportamento**: Se arquivo existe, é truncado (esvaziado)
- **Criação**: Se não existe, é criado
- **Posição**: Início do arquivo

### 2. Entrada de Dados
```c
printf("Enter contents to store in file : \n");
fgets(data, DATA_SIZE, stdin);
```

**`fgets()` vs `gets()`**:
- `fgets()`: **Seguro** - especifica tamanho máximo
- `gets()`: **Perigoso** - pode causar buffer overflow
- `fgets()`: Inclui newline (`\n`) no final

### 3. Escrita no Arquivo
```c
fputs(data, fPtr);
```

**`fputs()`**:
- Escreve string no arquivo
- **Não adiciona** newline automaticamente
- Retorna número de caracteres ou EOF em erro

### 4. Fechamento do Arquivo
```c
fclose(fPtr);
```

**Importância**:
- **Flush**: Força escrita de dados em buffer
- **Liberação**: Libera recursos do sistema
- **Consistência**: Garante que dados sejam salvos

## 🔧 Modos de Abertura de Arquivo

| Modo | Descrição | Posição Inicial | Se Existe | Se Não Existe |
|------|-----------|-----------------|-----------|---------------|
| `"r"` | Leitura | Início | Abre | Erro |
| `"w"` | Escrita | Início | Trunca | Cria |
| `"a"` | Append | Final | Abre | Cria |
| `"r+"` | Leitura/Escrita | Início | Abre | Erro |
| `"w+"` | Leitura/Escrita | Início | Trunca | Cria |
| `"a+"` | Leitura/Append | Final | Abre | Cria |

### Flags Adicionais:
- **`"b"`**: Modo binário (ex: `"rb"`, `"wb"`)
- **`"t"`**: Modo texto (padrão, ex: `"rt"`, `"wt"`)

### fprintf x fputs

```c
// fputs - escreve string simples
fputs(data, fPtr);

// fprintf - escreve com formatação
fprintf(fPtr, "Este é um número formatado: %d\n", 42);
    fputs("Esta é uma string simples.\n", fPtr);
```

Reference material:

https://codeforwin.org/c-programming/c-program-create-file-write-contents <br>
http://wiki.icmc.usp.br/images/8/82/Manipulacao_arquivos.pdf