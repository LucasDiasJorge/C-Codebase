#include <stdio.h>
#include <stdlib.h>

void convert_to_pdf(const char *input_file) {
    char command[256];
    snprintf(command, sizeof(command), "libreoffice --headless --convert-to pdf \"%s\"", input_file);
    int result = system(command);

    if (result == 0) {
        printf("File '%s' converted to PDF successfully.\n", input_file);
    } else {
        printf("Failed to convert file '%s' to PDF.\n", input_file);
    }
}

int main() {
    const char *file_to_convert = "file.xlms"; // Replace with your input file
    convert_to_pdf(file_to_convert);

    return 0;
}
