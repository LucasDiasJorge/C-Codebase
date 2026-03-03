#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void listarArquivos(const char *diretorio) {
    DIR *dir;
    struct dirent *entrada;

    // Abre o diretório
    dir = opendir(diretorio);
    if (dir == NULL) {
        printf("Erro ao abrir o diretório %s\n", diretorio);
        return;
    }

    // Lê e imprime cada arquivo no diretório
    while ((entrada = readdir(dir)) != NULL) {
        if (entrada->d_type == DT_REG) { // Verifica se é um arquivo regular
            printf("%s/%s\n", diretorio, entrada->d_name);
        }
    }

    closedir(dir);
}

int main() {
    char diretorio[100]; // Buffer para armazenar o diretório
    char *token;

    printf("Digite uma lista de diretórios separados por espaço: ");
    fgets(diretorio, sizeof(diretorio), stdin);

    // Separa a lista de diretórios usando espaço como delimitador
    token = strtok(diretorio, " ");
    while (token != NULL) {
        // Remove o caractere de quebra de linha do final de cada diretório
        token[strcspn(token, "\n")] = 0;
        listarArquivos(token);
        token = strtok(NULL, " ");
    }

    return 0;
}
