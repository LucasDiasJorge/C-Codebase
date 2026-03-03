#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* ptr;
    char* str = NULL;
    size_t len = 0;

    ptr = fopen("test.txt", "r");

    if (NULL == ptr) {
        printf("O arquivo não pode ser aberto.\n");
        return 1;
    }

    printf("Conteúdo do arquivo:\n");

    // Nesta versão, getline é utilizada para ler cada linha do arquivo dinamicamente, 
    // ajustando automaticamente o tamanho do buffer conforme necessário. Além disso, 
    // a memória alocada para a string str é liberada no final do programa usando free. 
    // Isso ajuda a garantir que não haja vazamentos de memória.
    while (getline(&str, &len, ptr) != -1) {
        printf("%s", str);
    }

    printf("\n");

    fclose(ptr);
    free(str);  // Libera a memória alocada pela getline

    return 0;
}
