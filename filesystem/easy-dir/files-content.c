#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void imprimirConteudoArquivo(const char *caminhoArquivo) {
    FILE *arquivo;
    char linha[1000];

    // Abre o arquivo
    arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", caminhoArquivo);
        return;
    }

    // Lê e imprime cada linha do arquivo
    printf("Conteúdo do arquivo %s:\n", caminhoArquivo);
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
}

void listarArquivos(const char *diretorio) {
    DIR *dir;
    struct dirent *entrada;
    char caminhoArquivo[500];

    // Abre o diretório
    dir = opendir(diretorio);
    if (dir == NULL) {
        printf("Erro ao abrir o diretório %s\n", diretorio);
        return;
    }

    // Lê e imprime o conteúdo de cada arquivo no diretório
    while ((entrada = readdir(dir)) != NULL) {
        if (entrada->d_type == DT_REG) { // Verifica se é um arquivo regular
            sprintf(caminhoArquivo, "%s/%s", diretorio, entrada->d_name);
            imprimirConteudoArquivo(caminhoArquivo);
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
