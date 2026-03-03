File Copier

Este projeto é uma aplicação simples escrita em C que realiza a cópia de arquivos de um diretório de origem para um diretório de destino. Ele pode ser útil para fazer backup de arquivos ou transferi-los de um local para outro, como de um diretório do sistema para um pendrive.

Funcionalidades

Cópia de arquivos de um diretório de origem para um diretório de destino.

Criação de arquivos no destino caso não existam.

Tratamento básico de erros, como falhas ao abrir arquivos ou diretórios.


Requisitos

Sistema operacional baseado em Unix (Linux ou macOS).

Compilador C (como gcc).

Permissões adequadas para acessar o diretório de origem e gravar no diretório de destino.


Estrutura do Código

Função copyFile

Responsável por copiar o conteúdo de um arquivo de origem para um arquivo de destino.

Parâmetros:

srcPath: Caminho do arquivo de origem.

destPath: Caminho do arquivo de destino.


Retorno:

0 em caso de sucesso.

-1 em caso de erro.



Função main

1. Define os diretórios de origem e destino.


2. Abre o diretório de origem e lista os arquivos nele.


3. Para cada arquivo encontrado, chama a função copyFile para copiá-lo para o diretório de destino.


4. Exibe mensagens de sucesso ou erro para cada arquivo processado.



Configuração e Execução

1. Clone ou copie o código para o seu computador.


2. Compile o programa usando o comando:

gcc -o file_copier file_copier.c


3. Execute o programa com permissões adequadas:

./file_copier



Nota: Certifique-se de que os caminhos dos diretórios de origem e destino (sourceDir e destinationDir) estejam configurados corretamente no código.


Personalização

Caminho de origem e destino: Modifique as variáveis sourceDir e destinationDir no código para apontar para os diretórios desejados.

Permissões: Verifique se você tem permissões de leitura no diretório de origem e de escrita no diretório de destino.

Filtragem de arquivos: Para copiar apenas determinados tipos de arquivos, adicione lógica de filtragem com base na extensão ou outros critérios.


Erros Comuns

"Failed to open source file": Verifique se o arquivo de origem existe e se você tem permissão para lê-lo.

"Failed to open destination file": Verifique se o caminho de destino é válido e se você tem permissão para escrever no diretório de destino.

"Read error" ou "Write error": Pode indicar problemas no sistema de arquivos ou falta de espaço no diretório de destino.


Melhorias Futuras

Adicionar suporte para copiar diretórios recursivamente.

Implementar um log detalhado em um arquivo externo.

Permitir a configuração de origem e destino via argumentos de linha de comando.

Adicionar opções para sobrescrever ou ignorar arquivos existentes.


Licença

Este projeto é fornecido como está, sem garantias. Use-o por sua conta e risco.

