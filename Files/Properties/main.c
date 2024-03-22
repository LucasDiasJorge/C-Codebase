#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int main() {
    FILE *file = fopen("example.properties", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char auth_path[MAX_LINE_LENGTH];
    char auth_user[MAX_LINE_LENGTH];

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, " =\n");
        if (token != NULL) {
            if (strcmp(token, "AUTH_PATH") == 0) {
                token = strtok(NULL, " =\n");
                if (token != NULL) {
                    strcpy(auth_path, token);
                }
            } else if (strcmp(token, "AUTH_USER") == 0) {
                token = strtok(NULL, " =\n");
                if (token != NULL) {
                    strcpy(auth_user, token);
                }
            }
        }
    }

    fclose(file);

    printf("AUTH_PATH: %s\n", auth_path);
    printf("AUTH_USER: %s\n", auth_user);

    return 0;
}
