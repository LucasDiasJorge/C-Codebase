#include <stdio.h>

// Função para substituir todas as ocorrências de um caractere em uma string
void replace_char(char *str, char find, char replace) {
    if (str == NULL) {
        return; // Proteção contra ponteiro nulo
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == find) {
            str[i] = replace;
        }
    }
}

int main(){

    char str[] = "Lucas Dias Borge";

    replace_char(str,'B','J');

    printf("Result: %s\n",str);

    return 0;
}