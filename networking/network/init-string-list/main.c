#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_RESPONSE_SIZE 100000

// Callback function to receive data from the request
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    strncat(data, (char *)ptr, size * nmemb);
    return size * nmemb;
}

// Function to extract string variables from the response
void extract_strings_from_response(char *response, char *strings[], int max_strings) {
    char *token;
    char *delimiter = "\",\"";
    char *quote = "\"";

    // Remove square brackets from the response
    response[strcspn(response, "[")] = ' ';
    response[strcspn(response, "]")] = ' ';

    // Use strtok to split the response string into individual strings
    token = strtok(response, delimiter);

    int count = 0;
    // Iterate through the strings and store them in the array
    while (token != NULL && count < max_strings) {
        // Remove quotes from the token
        token += strspn(token, quote); // Skip initial quotes
        char *end_quote = strstr(token, quote); // Find the closing quote
        if (end_quote != NULL) {
            *end_quote = '\0'; // Replace closing quote with null terminator
        }
        strings[count++] = strdup(token); // Duplicate the string and store it in the array
        token = strtok(NULL, delimiter);
    }
}

int main() {
    CURL *curl;
    CURLcode res;

    // Initialization of libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {

        char response[MAX_RESPONSE_SIZE] = "";
        // Get current time
        time_t timeNow = time(NULL);

        // URL of the GET request
        char url[] = "http://localhost:8891/api/v2/portal/event/items/001625152b59?lastModifiedDate=";

        // Calculate the length of the URL string and time string
        int url_length = sizeof(url) - 1; // excluding null terminator
        int time_length = 20; // assuming 20 characters is enough to represent the time_t

        // Calculate the total length required for the complete URL
        int total_length = url_length + time_length;

        // Create a buffer to hold the complete URL
        char complete_url[total_length + 1]; // +1 for null terminator

        // Format the complete URL string
        snprintf(complete_url, sizeof(complete_url), "%s%d", url, (int)timeNow);

        // Configuration of the request
        curl_easy_setopt(curl, CURLOPT_URL, complete_url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, "portal:RFIDBrasil");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        // Execution of the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Error performing the request: %s\n", curl_easy_strerror(res));
        } else {
            // Displaying the obtained response
            printf("Response of the GET request: %s\n", response);

            // Extracting each string from the response
            char *strings[MAX_RESPONSE_SIZE]; // Array to store the strings
            extract_strings_from_response(response, strings, MAX_RESPONSE_SIZE);
            
            // Print the extracted strings
            printf("Strings extracted from the response:\n");
            for (int i = 0; strings[i] != NULL; i++) {
                printf("%s\n", strings[i]);
                free(strings[i]); // Free the dynamically allocated memory
            }
        }

        // Cleanup of libcurl
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Error initializing libcurl.\n");
        return 1;
    }

    // Cleanup of global libcurl
    curl_global_cleanup();

    return 0;
}
