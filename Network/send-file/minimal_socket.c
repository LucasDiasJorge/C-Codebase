#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>

void main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {
        AF_INET,
        0x901f, // 8080 hex inverted
        0
    };

    bind(s, &addr, sizeof(addr));

    printf("Debug\n");

    listen(s, 10); // Listen max of 10 connections

    printf("Debug\n");


    int client_fd = accept(s, 0, 0);

    printf("Debug\n");


    char buffer[256] = {0};
    recv(client_fd, buffer, 256, 0);

    // GET /file.html ..... filter

    printf("Debug\n");


    char* f = buffer + 5;
    *strchr(f, ' ') = 0;
    int opened_fd = open(f, O_RDONLY);
    
    // File sender

    printf("Debug\n");


    sendfile(client_fd, opened_fd, 0, 256);

    printf("Debug\n");

    close(opened_fd);
    close(client_fd);
    close(s);
}