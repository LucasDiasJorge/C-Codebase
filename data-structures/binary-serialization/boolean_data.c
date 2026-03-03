#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to save data to a binary file
void saveDataToFile(const char* filename, bool* data, int size) {
    FILE *file = fopen(filename, "wb"); // Open the file for writing in binary mode
    if (file != NULL) {
        fwrite(data, sizeof(bool), size, file); // Write the data array to the file
        fclose(file);
    }
}

// Function to load data from a binary file
bool* loadDataFromFile(const char* filename, int* size) {
    FILE *file = fopen(filename, "rb"); // Open the file for reading in binary mode
    if (file != NULL) {
        // Get the size of the file
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        rewind(file);
        
        // Calculate the number of elements
        *size = fileSize / sizeof(bool);
        
        // Allocate memory for the data array
        bool* boolean = (bool*)malloc((*size) * sizeof(bool));
        
        // Read the data from the file
        fread(boolean, sizeof(bool), *size, file);
        
        fclose(file);
        return boolean;
    }
    return NULL;
}

int main() {

    bool b = false;

    int dataSize = sizeof(b) / sizeof(bool);

    // Save data to a binary file
    saveDataToFile("data.bin", &b, dataSize);

    // Load data from the binary file
    int loadedSize;
    bool* b_loaded = loadDataFromFile("data.bin", &loadedSize);

    // Print loaded data
    if (b_loaded != NULL) {
        printf("Loaded Data:\n");
        printf("%s\n", *b_loaded ? "true" : "false");
        free(b_loaded); // Free allocated memory
    } else {
        printf("Failed to load data from file.\n");
    }

    return 0;
}
