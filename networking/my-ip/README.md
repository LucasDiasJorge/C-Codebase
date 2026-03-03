# README - Projeto para Obter o Endereço IP Local

## Descrição

Este é um programa em C que determina o endereço IP local da máquina em que está sendo executado. O programa usa uma técnica simples de criar um socket e se conectar a um servidor remoto (neste caso, o servidor DNS do Google em 8.8.8.8) para descobrir o endereço IP local. A partir da conexão, ele utiliza a função `getsockname()` para obter o IP atribuído à interface de rede local que será usado para se conectar ao servidor.

## Funcionalidade

- O programa cria um socket UDP e tenta se conectar a um servidor DNS (8.8.8.8).
- Usando a função `getsockname()`, o IP local da máquina é recuperado.
- O endereço IP local é então exibido como saída.

## Requisitos

- Sistema operacional compatível com sockets, como Linux ou macOS.
- Compilador C (exemplo: GCC).

## Como compilar e executar

### Passo 1: Compilação

Para compilar o código, use o seguinte comando no terminal:

```bash
gcc -o obter_ip obter_ip.c
```

Onde `obter_ip.c` é o nome do arquivo que contém o código fornecido.

### Passo 2: Execução

Após a compilação, execute o programa da seguinte forma:

```bash
./obter_ip
```

Isso irá exibir o endereço IP local da máquina na qual o programa está sendo executado.

### Exemplo de Saída:

```bash
My IP address is: 192.168.1.10
```

## Explicação do Código

1. **Função `get_my_ip`**:
   - Cria um socket UDP para se conectar ao servidor DNS 8.8.8.8 na porta 53.
   - A função `connect()` é usada para definir a rota de rede, mas o dado de conexão não é realmente transmitido.
   - A função `getsockname()` obtém o endereço local atribuído ao socket, que é o IP da interface de rede usada para se comunicar com o servidor.
   - O endereço IP local é convertido para uma string legível usando `inet_ntop()`.

2. **Função `main`**:
   - Chama `get_my_ip()` para obter o IP e imprimir na tela.

## Possíveis Melhorias

- Suporte a redes IPv6.
- Adicionar suporte para interfaces de rede específicas (por exemplo, Ethernet ou Wi-Fi).
- Adicionar tratamento de erros mais robusto.