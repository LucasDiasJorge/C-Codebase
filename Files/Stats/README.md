# File Time Inspector

Este projeto é um programa em C que exibe informações sobre os tempos associados a um arquivo especificado. Ele utiliza a função `stat` para obter os dados do sistema de arquivos e apresenta informações como:

- Hora da última modificação do arquivo.
- Hora da última alteração de status do arquivo.
- (Se suportado pelo sistema) Hora de criação do arquivo.

## Requisitos

- Um sistema com suporte a funções POSIX, como Linux ou macOS.
- Um compilador C, como `gcc`.

## Como usar

1. Compile o programa:

   ```bash
   gcc -o file_time_inspector file_time_inspector.c
   ```

2. Execute o programa especificando o caminho para um arquivo:

   ```bash
   ./file_time_inspector <caminho_para_o_arquivo>
   ```

   Exemplo:

   ```bash
   ./file_time_inspector exemplo.txt
   ```

3. O programa exibira os tempos associados ao arquivo, como:

   ```plaintext
   Last modification time: Wed Jan  1 12:34:56 2025
   Last status change time: Wed Jan  1 12:34:56 2025
   Creation time not supported on this system.
   ```

## Notas Importantes

- **Compatibilidade**: A informação sobre o tempo de criação (`st_birthtim`) não é amplamente suportada em sistemas POSIX. O programa verificará automaticamente se esta funcionalidade está disponível e notificará o usuário, caso não esteja.

- **Erros comuns**:
  - Se o caminho para o arquivo estiver incorreto ou o arquivo não existir, o programa exibirá uma mensagem de erro.
  - Certifique-se de fornecer exatamente um argumento na linha de comando.

## Expansões Futuras

- Adicionar suporte para sistemas que utilizam APIs diferentes para consultar o tempo de criação, como Windows.
- Melhorar o suporte multiplataforma.
- Adicionar a opção de exibir os tempos em outros formatos (como timestamps UNIX).