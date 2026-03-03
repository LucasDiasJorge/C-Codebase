#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char buffer[1024];
    int status = 0;
    char path[64] = ""; // Initialize path buffer to an empty string

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
                // No need to break here; continue searching for other keys
            }
        }

        // Check if the line contains the "path" key
        if (strstr(buffer, "\"path\":") != NULL) {
            // Extract the value associated with the "path" key
            if (sscanf(buffer, "%*[^:]:%s", path) == 1) {
                // No need to break here; continue searching for other keys
            }
        }
    }

    fclose(fp);

    printf("status = %d\n", status);
    printf("path = %s\n", path);

    return 0;
}
