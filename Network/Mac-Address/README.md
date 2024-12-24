# Projeto para Obter o Endereço MAC de uma Interface de Rede

Este é um simples projeto em C que recupera o endereço MAC (Media Access Control) de uma interface de rede específica em um sistema Linux. O programa usa funções de socket e ioctl para interagir com o sistema operacional e obter as informações necessárias.

## Requisitos

- Sistema operacional Linux.
- Compilador C (como `gcc`).
- Permissões para acessar informações de rede (geralmente requer permissões de superusuário ou um grupo adequado).

## Como Funciona

1. O programa cria um socket de rede.
2. Utiliza a chamada de sistema `ioctl` para obter o endereço MAC da interface de rede especificada.
3. O endereço MAC é então formatado e exibido no formato tradicional `XX:XX:XX:XX:XX:XX`.
4. O programa imprime o endereço MAC da interface no terminal.

## Como Usar

1. Clone o repositório ou baixe o código-fonte.
2. Abra o terminal e navegue até o diretório do projeto.
3. Compile o código usando o compilador C. Por exemplo, com `gcc`:
   ```bash
   gcc -o obter_mac obter_mac.c
   ```
4. Execute o programa passando o nome da interface de rede. O nome padrão da interface no código é `enp2s0`, mas você pode modificá-lo conforme necessário.
   ```bash
   ./obter_mac
   ```

   O programa irá exibir o endereço MAC da interface de rede especificada.

## Personalizando a Interface

Se você quiser verificar o endereço MAC de uma interface diferente, altere a variável `interface` no código-fonte:

```c
char* interface = "enp2s0"; // Altere para o nome da interface desejada
```

Para encontrar o nome da interface de rede no seu sistema, você pode usar o comando `ifconfig` ou `ip a` no terminal.

## Exemplo de Saída

Se a interface de rede `enp2s0` tiver o endereço MAC `00:14:22:01:23:45`, a saída será:

```bash
MAC address of enp2s0: 00:14:22:01:23:45
```

## Dependências

- `sys/socket.h`: Para trabalhar com sockets de rede.
- `sys/ioctl.h`: Para chamadas de controle de dispositivo, como obter o endereço MAC.
- `net/if.h`: Para definições de interface de rede.
- `stdlib.h` e `stdio.h`: Para alocação de memória e manipulação de strings.