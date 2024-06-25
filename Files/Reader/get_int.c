#include <stdio.h>

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

