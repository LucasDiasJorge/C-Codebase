# Projeto de Conexão SSH e Transferência de Arquivos SCP

Este projeto demonstra como estabelecer uma conexão SSH e realizar uma transferência de arquivos via SCP usando a biblioteca `libssh` em C.

## Pré-requisitos

- Fedora (ou outra distribuição Linux)
- `libssh` instalada (incluindo arquivos de desenvolvimento)

### Instalação da `libssh` no Fedora

Para instalar a biblioteca `libssh`, execute o seguinte comando:

```bash
sudo dnf install libssh-devel
```

## Compilação

Use o seguinte comando para compilar o código:

```bash
gcc -o ssh_scp main.c -lssh
```

Certifique-se de que a biblioteca `libssh` está linkada corretamente. O parâmetro `-lssh` é necessário para vincular a biblioteca durante a compilação.

## Execução

Após compilar, você pode executar o programa:

```bash
./ssh_scp
```

O programa irá:

1. Conectar a um servidor SSH na porta 22.
2. Autenticar usando o nome de usuário e senha fornecidos no código.
3. Transferir o arquivo `response.json` do host local para o servidor remoto via SCP.
4. Desconectar após a transferência.

### Modificação do código

- **Endereço IP e Porta:** Altere o IP `"10.0.1.105"` e a porta `22` para o endereço do seu servidor SSH, se necessário.
- **Caminho de destino remoto:** No código, o caminho de destino remoto para o arquivo é especificado como `"/remote/path/to/"`. Atualize isso conforme necessário.

## Estrutura do Código

- **Conexão SSH:** A conexão é estabelecida usando a função `ssh_connect`.
- **Autenticação:** A autenticação é feita usando senha através da função `ssh_userauth_password`.
- **Transferência SCP:** A função `ssh_scp_push_file` é usada para iniciar a transferência de arquivos via SCP.
  
## Dependências

- `libssh` (você pode instalar as dependências de desenvolvimento com `dnf`)
