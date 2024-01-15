#include <stdio.h>

#define MAX_SIZE 256

int main() {
    FILE* ptr;
    char s[MAX_SIZE];
    
    // Opening file in reading mode
    ptr = fopen("string.txt", "r");

    if (NULL == ptr) {
        printf("File can't be opened \n");
        return 1; // Sair do programa com código de erro
    }

    printf("Content of this file:\n");

    int aux = 0;

    while (aux < MAX_SIZE - 1 && (s[aux] = fgetc(ptr)) != EOF) {
        aux++;
    }

    s[aux] = '\0'; // Adicionar terminador nulo para formar uma string válida

    printf("%s\n", s);

    fclose(ptr); // Fechar o arquivo

    return 0;
}
