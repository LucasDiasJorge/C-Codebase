#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *htmlFilePath = "index.html";
    const char *pdfFilePath = "output.pdf";

    // Construct the command string
    char command[256];
    snprintf(command, sizeof(command), "wkhtmltopdf %s %s", htmlFilePath, pdfFilePath);

    // Execute the command
    int result = system(command);

    // Check if the command was executed successfully
    if (result == 0) {
        printf("PDF successfully created: %s\n", pdfFilePath);
    } else {
        printf("Failed to create PDF. Error code: %d\n", result);
    }

    return 0;
}
