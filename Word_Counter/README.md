# Word Counter

## Descrição

Este projeto tem como objetivo contar o número de palavras em um arquivo de texto. O programa utiliza expressões regulares (regex) para identificar palavras dentro do conteúdo do arquivo, e exibe o total de palavras encontradas. Ele foi implementado em C, utilizando a biblioteca POSIX `<regex.h>` para manipulação de expressões regulares e funções padrão da linguagem para leitura de arquivos.

## Funcionalidades

- Abertura e leitura de arquivos de texto.
- Utilização de expressão regular para contar palavras.
- Contagem de palavras alfanuméricas (sequências de caracteres e números).
- Exibição do número total de palavras encontradas.

## Como Usar

1. **Compilação**:
   Para compilar o código, utilize um compilador de C como o `gcc`. No terminal, execute:

   ```bash
   gcc -o word_counter word_counter.c
   ```

2. **Execução**:
   Após compilar, execute o programa informando o arquivo de texto para análise:

   ```bash
   ./word_counter
   ```

   O programa irá contar o número de palavras no arquivo "texto.txt" e exibir o resultado no terminal.

3. **Alterando o arquivo de entrada**:
   O programa está configurado para ler um arquivo chamado `texto.txt`. Se desejar analisar outro arquivo, altere o nome do arquivo no código na linha:

   ```c
   file = fopen("texto.txt", "r");
   ```

## Explicação do Código

- **Função `count_words`**: A função `count_words` utiliza uma expressão regular para contar palavras em uma string. A expressão regular `[a-zA-Z0-9]+` identifica sequências alfanuméricas, consideradas como palavras.
  
- **Leitura de arquivo**: O arquivo é aberto em modo leitura e seu conteúdo é carregado na memória. O código também verifica erros de alocação de memória e abertura do arquivo.
  
- **Contagem das palavras**: O conteúdo do arquivo é analisado palavra por palavra usando o `regexec`, que executa a expressão regular em cada parte da string até o final do arquivo.

- **Uso de memória**: O código aloca dinamicamente memória suficiente para armazenar o conteúdo completo do arquivo, e a memória é liberada após o uso.

## Exemplo de Saída

Se o arquivo `texto.txt` contiver:

```
Este é um exemplo de texto.
Ele contém palavras que serão contadas.
```

A saída será:

```
Número de palavras: 9
```

## Dependências

- **Sistema operacional**: O código foi desenvolvido para sistemas que oferecem suporte à biblioteca POSIX `<regex.h>`, como Linux e macOS.
- **Compilador**: Um compilador que suporte C99 ou versões mais recentes, como o `gcc` ou `clang`.