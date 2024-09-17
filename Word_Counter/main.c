#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

int count_words(const char *str) {
    regex_t regex;
    int reti;
    regmatch_t matches[1];
    int word_count = 0;

    // Expressão regular para corresponder a uma palavra (sequência alfanumérica)
    const char *pattern = "[a-zA-Z0-9]+";

    // Compilando a expressão regular
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Erro ao compilar regex\n");
        return 0;
    }

    // Procurando as palavras na string
    const char *current_position = str;
    while (regexec(&regex, current_position, 1, matches, 0) == 0) {
        word_count++;
        // Move o ponteiro de posição para depois da palavra encontrada
        current_position += matches[0].rm_eo;
    }

    // Liberando a memória usada pelo regex
    regfree(&regex);

    return word_count;
}

int main() {
    FILE *file;
    char *buffer;
    long file_size;

    // Abrir o arquivo para leitura
    file = fopen("texto.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return 1;
    }

    // Ir para o final do arquivo para descobrir seu tamanho
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    // Alocar memória para armazenar o conteúdo do arquivo
    buffer = (char *)malloc((file_size + 1) * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        fclose(file);
        return 1;
    }

    // Ler o conteúdo do arquivo
    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = '\0'; // Certificar-se de que o buffer termina com '\0'

    // Fechar o arquivo
    fclose(file);

    // Contar as palavras no conteúdo do arquivo
    int word_count = count_words(buffer);
    
    printf("Número de palavras: %d\n", word_count);

    // Liberar a memória alocada
    free(buffer);

    return 0;
}
