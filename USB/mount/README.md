# 💾 USB Mount - Montagem de Dispositivos USB

Este módulo demonstra como montar dispositivos USB programaticamente em C usando syscalls do Linux.

## 📝 Descrição

O programa utiliza a syscall `mount()` para montar um dispositivo USB em um ponto de montagem especificado, criando o diretório se necessário.

## 📁 Estrutura

```
mount/
└── main.c      # Montagem de USB
```

## 🔧 Como Funciona

### Montagem de Dispositivo

```c
#include <sys/mount.h>
#include <sys/stat.h>

char *source = "/dev/sda1";      // Dispositivo
char *target = "/mnt/usb";       // Ponto de montagem
char *filesystem = "vfat";       // Sistema de arquivos

// Criar ponto de montagem
mkdir(target, 0777);

// Montar
int result = mount(source, target, filesystem, MS_MGC_VAL, NULL);

if (result == 0) {
    printf("USB montado com sucesso!\n");
} else {
    perror("mount");
}
```

## 🚀 Compilação e Execução

```bash
gcc -o mount_usb main.c
sudo ./mount_usb  # Requer root!
```

## ⚠️ Requer Privilégios de Root

A syscall `mount()` requer permissões de superusuário.

## 💡 Parâmetros do mount()

```c
int mount(
    const char *source,      // Dispositivo (/dev/sda1)
    const char *target,      // Ponto de montagem (/mnt/usb)
    const char *filesystemtype,  // Tipo (vfat, ext4, ntfs)
    unsigned long mountflags,    // Flags de montagem
    const void *data         // Opções específicas
);
```

### Flags Comuns

| Flag | Descrição |
|------|-----------|
| `MS_RDONLY` | Somente leitura |
| `MS_NOEXEC` | Não permite executáveis |
| `MS_NOSUID` | Ignora bits SUID |
| `MS_NODEV` | Não permite dispositivos especiais |
| `MS_SYNCHRONOUS` | Escrita síncrona |

## 📊 Sistemas de Arquivos Comuns

| Tipo | Descrição |
|------|-----------|
| `vfat` | FAT32 (mais compatível) |
| `ntfs` | Windows NTFS |
| `ext4` | Linux ext4 |
| `exfat` | exFAT (arquivos grandes) |

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `mount()` | Syscall de montagem |
| `mkdir()` | Criação de diretório |
| Sistema de arquivos | Tipos e compatibilidade |
| Permissões | Root necessário |

## 🔄 Detectar Dispositivos USB

```c
#include <libudev.h>

// Listar dispositivos USB
struct udev *udev = udev_new();
struct udev_enumerate *enumerate = udev_enumerate_new(udev);
udev_enumerate_add_match_subsystem(enumerate, "block");
udev_enumerate_scan_devices(enumerate);
```

## ⚠️ Tratamento de Erros

```c
if (mount(source, target, fs, flags, NULL) != 0) {
    switch(errno) {
        case EBUSY:
            printf("Dispositivo já montado\n");
            break;
        case ENOENT:
            printf("Dispositivo não encontrado\n");
            break;
        case EPERM:
            printf("Permissão negada (precisa de root)\n");
            break;
        default:
            perror("mount");
    }
}
```

## 📚 Referências

- [mount - Linux man](https://man7.org/linux/man-pages/man2/mount.2.html)
- [Filesystem Hierarchy Standard](https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html)
