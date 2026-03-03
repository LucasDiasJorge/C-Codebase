# Leitura de Porta Serial em C

Este é um projeto simples em C para configurar e ler dados de uma porta serial. Ele utiliza a biblioteca `termios` para configurar a porta e garantir a leitura de dados de maneira bloqueante. A aplicação pode ser útil para comunicação com dispositivos serializados, como sensores, modems ou microcontroladores.

## Funcionalidades

- Configuração de uma porta serial (por exemplo, `/dev/ttyS1`) para uma comunicação básica de 9600 bps.
- Leitura de dados recebidos pela porta serial.
- Exibição dos dados recebidos no console.
- Tratamento de erros básicos durante a configuração da porta serial e leitura.

## Como Funciona

1. **Configuração da Porta Serial**: O código configura a porta serial com parâmetros típicos:
   - Taxa de transmissão de 9600 bps.
   - 8 bits de dados.
   - Sem paridade e 1 bit de parada.
   - Desativação de controle de fluxo por hardware e software.
   - Leitura bloqueante de pelo menos 1 caractere.

2. **Leitura de Dados**: Após a configuração, o programa entra em um loop de leitura da porta serial, exibindo no console os dados recebidos.

## Dependências

- Sistema operacional Unix/Linux (devido ao uso da API `termios` e manipulação de dispositivos como `/dev/ttyS1`).
- Compilador C (como `gcc`).
  
## Compilação

Para compilar o código, basta usar um compilador C como o `gcc`:

```bash
gcc -o serial_reader serial_reader.c
```

## Execução

Após compilar o código, você pode executar o programa da seguinte forma:

```bash
./serial_reader
```

O programa tentará abrir a porta serial especificada (`/dev/ttyS1` neste exemplo) e configurá-la para comunicação. Caso a porta seja aberta e configurada com sucesso, ele irá começar a ler os dados recebidos.

## Ajustes Necessários

- **Porta Serial**: O código está configurado para usar a porta `/dev/ttyS1`, mas pode ser necessário ajustar o nome da porta serial, dependendo do sistema e do dispositivo. No Linux, portas seriais geralmente têm o formato `/dev/ttySx` ou `/dev/ttyUSBx` (para dispositivos USB-to-serial).
  
- **Permissões**: Certifique-se de que o usuário tenha permissão para acessar a porta serial. Você pode adicionar o usuário ao grupo `dialout` para obter as permissões necessárias:

  ```bash
  sudo usermod -aG dialout $USER
  ```

## Tratamento de Erros

- Se o programa não conseguir abrir a porta serial ou configurar suas propriedades, ele exibirá uma mensagem de erro.
- Se ocorrer um erro ao ler os dados, ele também será exibido na tela.