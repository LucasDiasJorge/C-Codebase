#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char buffer[1024];
    int status = 0;

    fp = fopen("example.json", "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo");
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        // Check if the line contains the "status" key
        if (strstr(buffer, "\"status\":") != NULL) {
            // Extract the value associated with the "status" key
            if (sscanf(buffer, "%*[^:]:%d", &status) == 1) {
                break;
            }
        } else{
            perror("Key was not found");
        }
    }

    fclose(fp);

    printf("status = %d\n", status);

    return 0;
}
