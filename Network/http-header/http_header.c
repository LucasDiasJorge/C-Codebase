#include <stdio.h>
#include <string.h>

#define MAX_HEADER_SIZE 1024

void parseHttpHeader(const char *header) {
    char headerCopy[MAX_HEADER_SIZE];
    char *token;
    
    // Make a copy of the header to avoid modifying the original string
    strncpy(headerCopy, header, sizeof(headerCopy));
    
    // Split the header into lines
    token = strtok(headerCopy, "\r\n");
    
    while (token != NULL) {
        // Check for the "Host" header
        if (strncmp(token, "Host: ", 6) == 0) {
            printf("Host: %s\n", token + 6);
        }
        
        // Check for the "User-Agent" header
        if (strncmp(token, "User-Agent: ", 12) == 0) {
            printf("User-Agent: %s\n", token + 12);
        }
        
        // Add more headers as needed
        
        // Get the next line
        token = strtok(NULL, "\r\n");
    }
}

int main() {
    const char *httpHeader = "GET /index.html HTTP/1.1\r\n"
                             "Host: www.example.com\r\n"
                             "User-Agent: Mozilla/5.0\r\n"
                             "Connection: close\r\n\r\n";
    
    parseHttpHeader(httpHeader);
    
    return 0;
}
