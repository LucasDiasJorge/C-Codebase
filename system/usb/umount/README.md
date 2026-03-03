# 💾 USB Unmount - Desmontagem de Dispositivos USB

Este módulo demonstra como desmontar dispositivos USB programaticamente em C usando syscalls do Linux.

## 📝 Descrição

O programa utiliza a syscall `umount()` para desmontar um dispositivo USB de forma segura.

## 📁 Estrutura

```
umount/
└── main.c      # Desmontagem de USB
```

## 🔧 Como Funciona

### Desmontagem de Dispositivo

```c
#include <sys/mount.h>

char *target = "/mnt/usb";  // Ponto de montagem

int result = umount(target);

if (result == 0) {
    printf("USB desmontado com sucesso!\n");
} else {
    perror("umount");
}
```

## 🚀 Compilação e Execução

```bash
gcc -o umount_usb main.c
sudo ./umount_usb  # Requer root!
```

## ⚠️ Requer Privilégios de Root

A syscall `umount()` requer permissões de superusuário.

## 💡 Variantes do umount

### umount()
```c
int umount(const char *target);
```
Desmontagem simples.

### umount2()
```c
int umount2(const char *target, int flags);
```
Desmontagem com flags.

### Flags do umount2()

| Flag | Descrição |
|------|-----------|
| `MNT_FORCE` | Forçar desmontagem (perigoso) |
| `MNT_DETACH` | Lazy unmount - desconecta do filesystem |
| `MNT_EXPIRE` | Marca como expirado |
| `UMOUNT_NOFOLLOW` | Não segue symlinks |

## 📊 Exemplo com Flags

```c
#include <sys/mount.h>

// Lazy unmount - não espera processos terminarem
if (umount2("/mnt/usb", MNT_DETACH) != 0) {
    perror("umount2");
}
```

## ⚠️ Tratamento de Erros

```c
if (umount(target) != 0) {
    switch(errno) {
        case EBUSY:
            printf("Dispositivo em uso!\n");
            printf("Feche todos os programas que usam o USB.\n");
            break;
        case EINVAL:
            printf("Não está montado.\n");
            break;
        case EPERM:
            printf("Permissão negada (precisa de root)\n");
            break;
        default:
            perror("umount");
    }
}
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `umount()` | Syscall de desmontagem |
| `umount2()` | Desmontagem com opções |
| Tratamento de erros | Casos comuns |
| Permissões | Root necessário |

## 🔄 Verificar Processos Usando o Dispositivo

```bash
# Antes de desmontar, verificar quem usa
lsof /mnt/usb
fuser -m /mnt/usb
```

### Em C:
```c
#include <stdlib.h>

// Verificar se em uso
int check_usage(const char *mount_point) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "lsof %s 2>/dev/null | wc -l", mount_point);
    FILE *fp = popen(cmd, "r");
    int count = 0;
    fscanf(fp, "%d", &count);
    pclose(fp);
    return count > 1;  // 1 = header only
}
```

## 🔒 Desmontagem Segura

```c
int safe_umount(const char *target) {
    // Sync para garantir que dados foram gravados
    sync();
    
    // Tentar desmontagem normal
    if (umount(target) == 0) {
        return 0;
    }
    
    // Se EBUSY, tentar lazy unmount
    if (errno == EBUSY) {
        printf("Dispositivo em uso, fazendo lazy unmount...\n");
        return umount2(target, MNT_DETACH);
    }
    
    return -1;
}
```

## 📚 Referências

- [umount - Linux man](https://man7.org/linux/man-pages/man2/umount.2.html)
- [sync - Linux man](https://man7.org/linux/man-pages/man2/sync.2.html)
