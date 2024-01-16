#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to convert ISO 8601 formatted string to timestamp with milliseconds
time_t convertToTimestamp(const char *isoString) {
    struct tm tmStruct;
    memset(&tmStruct, 0, sizeof(struct tm));

    // Parse the input string using strptime
    if (strptime(isoString, "%Y-%m-%dT%H:%M:%S", &tmStruct) == NULL) {
        fprintf(stderr, "Error parsing date string\n");
        exit(EXIT_FAILURE);
    }

    // Extract the fractional seconds and add them to tmStruct.tm_sec
    char *fractionalSecondsStr = strchr(isoString, '.');
    if (fractionalSecondsStr != NULL) {
        // Extract milliseconds and convert to an integer
        int milliseconds;
        sscanf(fractionalSecondsStr, ".%3d", &milliseconds);

        // Add milliseconds to tmStruct.tm_sec
        tmStruct.tm_sec += milliseconds / 1000;
    }

    // Convert the struct tm to a timestamp
    time_t timestamp = mktime(&tmStruct);
    if (timestamp == -1) {
        fprintf(stderr, "Error converting struct tm to timestamp\n");
        exit(EXIT_FAILURE);
    }

    return timestamp;
}

int main() {
    const char *isoString = "2024-01-16T20:08:11.427442398Z";
    time_t timestamp = convertToTimestamp(isoString);

    printf("Timestamp: %ld\n", timestamp);

    return 0;
}
