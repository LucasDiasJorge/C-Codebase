# open vs fopen

Em C, tanto `open` quanto `fopen` são usados para abrir arquivos, mas fazem parte de diferentes bibliotecas e têm propósitos e características distintas.

### `open`:
- **Biblioteca**: `open` é uma chamada de sistema fornecida pelo padrão POSIX (Portable Operating System Interface), normalmente encontrada no cabeçalho `unistd.h`.
- **Retorno**: Retorna um descritor de arquivo (um número inteiro) que identifica exclusivamente o arquivo aberto dentro do processo. Esse descritor de arquivo é usado com outras chamadas de sistema como `read`, `write` e `close`.
- **Uso**:
  - É de baixo nível e oferece mais controle sobre como o arquivo é aberto.
  - Pode ser usado com várias flags para especificar o modo de acesso ao arquivo (por exemplo, `O_RDONLY` para leitura, `O_WRONLY` para escrita, `O_RDWR` para leitura e escrita) e outras opções, como `O_CREAT` para criar um arquivo se ele não existir.
  - Exemplo:
    ```c
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1) {
        // Tratar erro
    }
    ```

### `fopen`:
- **Biblioteca**: `fopen` faz parte da biblioteca padrão de C (`stdio.h`).
- **Retorno**: Retorna um ponteiro para um objeto `FILE`, que é usado para rastrear o arquivo e seu fluxo de E/S associado. Esse ponteiro é usado com funções como `fread`, `fwrite`, `fprintf`, `fscanf` e `fclose`.
- **Uso**:
  - É de nível mais alto e mais fácil de usar, fornecendo E/S com buffer e funções convenientes para ler e escrever dados.
  - O modo de abertura é especificado como uma string (por exemplo, `"r"` para leitura, `"w"` para escrita).
  - Exemplo:
    ```c
    FILE *file = fopen("file.txt", "r");
    if (file == NULL) {
        // Tratar erro
    }
    ```

### Resumo:
- Use `open` para operações de arquivo de baixo nível, onde você precisa de mais controle sobre descritores de arquivo e modos específicos de acesso ao arquivo.
- Use `fopen` para operações de nível mais alto, onde a conveniência e o uso de E/S com buffer são importantes.