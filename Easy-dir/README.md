Projeto: Leitura de Conteúdo de Arquivos em Diretórios

Este projeto implementa um programa em C que permite listar os arquivos presentes em um ou mais diretórios e imprime o conteúdo de cada um deles.

Funcionalidades

Listar Arquivos: O programa abre um diretório informado pelo usuário e exibe o conteúdo de todos os arquivos regulares presentes.

Leitura de Arquivos: Para cada arquivo no diretório, o conteúdo é lido e exibido no terminal.

Suporte a Múltiplos Diretórios: O programa aceita uma lista de diretórios (separados por espaços) e processa cada um deles.


Como Usar

1. Compile o código:

gcc -o listar_arquivos listar_arquivos.c


2. Execute o programa:

./listar_arquivos


3. Quando solicitado, insira uma lista de diretórios separados por espaços.

Exemplo:

Digite uma lista de diretórios separados por espaço: /caminho/para/diretorio1 /caminho/para/diretorio2

O programa irá listar os arquivos em cada diretório e exibir o conteúdo de cada um.



Estrutura do Código

imprimirConteudoArquivo: Função que abre e imprime o conteúdo de um arquivo.

listarArquivos: Função que percorre o diretório fornecido, identifica arquivos regulares e chama a função imprimirConteudoArquivo.

main: Função principal que solicita uma lista de diretórios ao usuário, e os processa separadamente.


Requisitos

GCC ou qualquer outro compilador C compatível.

Acesso a diretórios e arquivos para leitura.


Possíveis Melhorias

Suporte para tratamento de diferentes tipos de arquivos (não apenas arquivos regulares).

Controle de erros mais robusto para lidar com exceções (como arquivos corrompidos ou diretórios inacessíveis).

Exibir também subdiretórios, se necessário.


Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir um pull request ou relatar problemas.