#include <stdio.h>
#include <stdlib.h>

// Define a structure for your data
typedef struct {
    int id;
    float value;
} Data;

// Function to save data to a binary file
void saveDataToFile(const char* filename, Data* data, int size) {
    FILE *file = fopen(filename, "wb"); // Open the file for writing in binary mode
    if (file != NULL) {
        fwrite(data, sizeof(Data), size, file); // Write the data array to the file
        fclose(file);
    }
}

// Function to load data from a binary file
Data* loadDataFromFile(const char* filename, int* size) {
    FILE *file = fopen(filename, "rb"); // Open the file for reading in binary mode
    if (file != NULL) {
        // Get the size of the file
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        rewind(file);
        
        // Calculate the number of elements
        *size = fileSize / sizeof(Data);
        
        // Allocate memory for the data array
        Data* data = (Data*)malloc((*size) * sizeof(Data));
        
        // Read the data from the file
        fread(data, sizeof(Data), *size, file);
        
        fclose(file);
        return data;
    }
    return NULL;
}

int main() {
    // Example data
    Data myData[] = {
        {1, 10.5},
        {2, 20.3},
        {3, 30.8}
    };
    int dataSize = sizeof(myData) / sizeof(Data);

    // Save data to a binary file
    saveDataToFile("data.bin", myData, dataSize);

    // Load data from the binary file
    int loadedSize;
    Data* loadedData = loadDataFromFile("data.bin", &loadedSize);

    // Print loaded data
    if (loadedData != NULL) {
        printf("Loaded Data:\n");
        for (int i = 0; i < loadedSize; i++) {
            printf("ID: %d, Value: %.2f\n", loadedData[i].id, loadedData[i].value);
        }
        free(loadedData); // Free allocated memory
    } else {
        printf("Failed to load data from file.\n");
    }

    return 0;
}
