#include <stdio.h>
#include <regex.h>
#include <string.h>

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
    const char *text = "Este é um exemplo de texto, com várias palavras 123.";
    int word_count = count_words(text);
    
    printf("Número de palavras: %d\n", word_count);

    return 0;
}
