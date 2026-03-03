#include <stdio.h>
#include <string.h>

int extractJsonValue(const char *json, const char *key, char *value, size_t max_length) {
    // Construct the search pattern with quotes around the key
    char pattern[256];
    snprintf(pattern, sizeof(pattern), "\"%s\":\"", key);

    const char *start = strstr(json, pattern);

    if (start != NULL) {
        start += strlen(pattern); // Move past the key and the characters `":`

        const char *end = strchr(start, '\"');
        if (end != NULL) {
            // Calculate the length of the value
            size_t length = end - start;

            // Check if the value fits in the buffer, including the null terminator
            if (length < max_length) {
                // Copy the value to the output buffer
                strncpy(value, start, length);
                value[length] = '\0'; // Add the null terminator

                printf("%s\n", value);

                return 0; // Success
            } else {
                fprintf(stderr, "Value size exceeds the provided buffer.\n");
            }
        } else {
            fprintf(stderr, "Invalid JSON format.\n");
        }
    } else {
        fprintf(stderr, "Key '%s' not found in JSON.\n", key);
    }

    return 1; // Failure
}

int main() {
    char *json = "{\"email\":\"asdvgakhsvdbajsk\",\"pass\":\"pass\"}";

    char string_return[64] = ""; // Increased buffer size to 64 to match the check in the function

    return extractJsonValue(json, "email", string_return, sizeof(string_return));
}
