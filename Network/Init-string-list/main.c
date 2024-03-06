#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_RESPONSE_SIZE 10000

// Function to parse the response string and initialize the variable
void initialize_variable(char *response) {
    char *token;
    char *delimiter = "\n"; // Assuming each list element is separated by a newline character

    // Use strtok to split the response string into individual list elements
    token = strtok(response, delimiter);

    // Iterate through the list elements and initialize the variable accordingly
    while (token != NULL) {
        // Assuming your variable is an array of strings
        printf("Initializing variable with list element: %s\n", token);

        // You can store each list element in your variable here
        // For example, you can copy it to an array or add it to a linked list

        // Get the next token
        token = strtok(NULL, delimiter);
    }
}

// Callback function to receive data from the request
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    strncat(data, (char *)ptr, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL *curl;
    CURLcode res;

    // Initialization of libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        char response[MAX_RESPONSE_SIZE] = "";

        // URL of the GET request
        char url[] = "http://localhost:8891/api/v2/event/items/001625152b59?lastModifiedDate=0";

        // Configuration of the request
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        // Execution of the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Error performing the request: %s\n", curl_easy_strerror(res));
        } else {
            // Displaying the obtained response
            printf("Response of the GET request: %s\n", response);

            // Initializing the variable using the response
            initialize_variable(response);
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