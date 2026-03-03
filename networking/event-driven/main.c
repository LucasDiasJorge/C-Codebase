#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h> // for sleep()

// Function to perform the CURL request
int perform_curl_request() {
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) {
        fprintf(stderr, "Error initializing libcurl\n");
        return 1;
    }

    // Create a curl handle
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error creating libcurl handle\n");
        curl_global_cleanup(); // Cleanup global state before returning
        return 1;
    }

    // Set the URL to stream data from
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8891/api/v2/ping");

    // Set the username and password for basic authentication
    curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");

    // Perform the request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl); // Cleanup before returning
        curl_global_cleanup(); // Cleanup global state before returning
        return 1;
    }

    // Clean up libcurl handle
    curl_easy_cleanup(curl);

    // Cleanup global state
    curl_global_cleanup();

    return 0;
}

// Function to simulate an event
int event() {
    printf("Event occurred: Request was sent\n");
    return 1;
}

// Function to trigger the event (perform CURL request)
int trigger() {
    printf("Triggering event...\n");
    return perform_curl_request();
}

// Function to handle events
void event_handler() {
    // Simulate waiting for 5 seconds
    printf("Handling event...\n");
    sleep(5);
}

int main() {
    int event_status;

    // Trigger the event (perform CURL request)
    if (trigger() != 0) {
        printf("Event trigger failed.\n");
        return 1;
    }

    // Event loop
    do {
        event_status = event(); // Simulate event
        event_handler(); // Handle the event
    } while (event_status != 0); // Continue event loop until event status is 0

    return 0;
}
