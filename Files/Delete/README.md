# 🗑️ Delete File - Remoção de Arquivos

Este módulo demonstra como deletar arquivos do sistema de arquivos usando C.

## 📝 Descrição

O programa utiliza a função `unlink()` para remover arquivos do sistema, com tratamento adequado de erros.

## 📁 Estrutura

```
Delete/
└── main.c      # Implementação da remoção de arquivos
```

## 🔧 Como Funciona

### Função `unlink()`

```c
#include <unistd.h>

if (unlink(file) == 0) {
    printf("Arquivo %s removido com sucesso!\n", file);
} else {
    perror("Erro ao remover o arquivo");
}
```

**Comportamento:**
- Retorna `0` em caso de sucesso
- Retorna `-1` em caso de erro (e define `errno`)
- Remove a entrada do diretório
- O arquivo só é realmente deletado quando não há mais referências a ele

## 🚀 Compilação e Execução

```bash
gcc -o delete main.c
./delete arquivo.txt
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `unlink()` | System call para remover arquivos |
| `perror()` | Exibe mensagem de erro com descrição |
| `errno` | Código de erro do sistema |

## ⚠️ Códigos de Erro Comuns

| Errno | Descrição |
|-------|-----------|
| `ENOENT` | Arquivo não existe |
| `EACCES` | Permissão negada |
| `EBUSY` | Arquivo em uso |
| `EISDIR` | É um diretório (use `rmdir()`) |
| `EROFS` | Sistema de arquivos somente leitura |

## 🔄 Alternativas

### Usando `remove()` (mais portável):
```c
#include <stdio.h>

if (remove(file) == 0) {
    printf("Arquivo removido!\n");
}
```

### Deletar diretório vazio:
```c
#include <unistd.h>

rmdir("/caminho/diretorio");
```

## ⚠️ Observações

- `unlink()` só funciona com arquivos, não diretórios
- Para diretórios, use `rmdir()` (vazio) ou implemente remoção recursiva
- O arquivo pode permanecer até que todos os processos fechem seus handles
- Requer permissões de escrita no diretório pai

## 📚 Referências

- [unlink - Linux man page](https://man7.org/linux/man-pages/man2/unlink.2.html)
- [remove - C Reference](https://en.cppreference.com/w/c/io/remove)
