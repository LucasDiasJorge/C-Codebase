#include <stdio.h>
#include <stdlib.h>

int read_integer_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Indica erro na abertura do arquivo
    }

    int value;
    if (fscanf(file, "%d", &value) != 1) {
        fclose(file);
        perror("Error reading integer from file");
        return -1; // Indica erro na leitura do valor
    }

    fclose(file);
    return value;
}

int update_integer_in_file(const char *filename, int new_value) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Indica erro na abertura do arquivo
    }

    if (fprintf(file, "%d", new_value) < 0) {
        fclose(file);
        perror("Error writing integer to file");
        return -1; // Indica erro na escrita do valor
    }

    fclose(file);
    return 0; // Indica sucesso
}
