#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool starts_with(const char *pre, const char *str) {
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

int main() {
    const char *httpHeader = "GET /index.html HTTP/1.1\r\n"
                             "Host: www.example.com\r\n"
                             "User-Agent: Mozilla/5.0\r\n"
                             "Connection: close\r\n\r\n";

    /*

    TO-DO Tree decision (or hashtable !?)

    if(starts_with("GET", httpHeader))
    if(starts_with("POST", httpHeader))
    if(starts_with("DELETE", httpHeader))
    if(starts_with("PUT", httpHeader))

    */

    if(starts_with("GET /index.html", httpHeader)) printf("Hello GET /index.html\n");
    if(starts_with("POST /index.html", httpHeader)) printf("Hello POST /index.html\n");
    if(starts_with("DELETE /index.html", httpHeader)) printf("Hello DELETE /index.html\n");
    if(starts_with("PUT /index.html", httpHeader)) printf("Hello PUT /index.html\n");

    return 0;
}
