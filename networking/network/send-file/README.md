# 📤 Send File - Transferência de Arquivos

Este módulo demonstra diferentes métodos para transferir arquivos em C.

## 📝 Descrição

Implementações de transferência de arquivos usando diferentes protocolos e tecnologias de rede.

## 📁 Estrutura

```
send-file/
├── Sockets/    # Servidor HTTP usando sockets TCP
└── SSH/        # Transferência via SCP/SSH
```

## 📚 Métodos Incluídos

### 1. [Sockets](Sockets/)
Servidor HTTP mínimo que serve arquivos estáticos usando a syscall `sendfile()` para transferência eficiente zero-copy.

**Características:**
- Socket TCP na porta 8080
- Função `sendfile()` para performance
- Serve arquivos HTML

### 2. [SSH](SSH/)
Cliente SCP que transfere arquivos de forma segura via SSH usando a biblioteca libssh.

**Características:**
- Conexão SSH segura
- Autenticação por senha ou chave
- Protocolo SCP para transferência

## 💡 Comparação

| Método | Segurança | Performance | Complexidade |
|--------|-----------|-------------|--------------|
| Sockets HTTP | ❌ Baixa | ⭐⭐⭐ Alta | ⭐ Baixa |
| SSH/SCP | ✅ Alta | ⭐⭐ Média | ⭐⭐ Média |

## 🔧 Dependências

### Sockets
- Nenhuma dependência externa
- API POSIX padrão

### SSH
```bash
# Ubuntu/Debian
sudo apt-get install libssh-dev

# Compilação
gcc -o scp_client main.c -lssh
```

## 🚀 Quando Usar

| Cenário | Método Recomendado |
|---------|-------------------|
| LAN interna | Sockets |
| Internet | SSH/SCP |
| Performance crítica | Sockets |
| Dados sensíveis | SSH/SCP |

## 📚 Referências

- [sendfile - zero-copy](https://man7.org/linux/man-pages/man2/sendfile.2.html)
- [libssh Documentation](https://www.libssh.org/documentation/)
