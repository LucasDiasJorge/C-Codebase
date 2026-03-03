#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server;
    char message[] = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
    char buffer[BUFFER_SIZE];
    
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_addr.s_addr = inet_addr("93.184.216.34"); // IP address of www.example.com
    server.sin_family = AF_INET;
    server.sin_port = htons(80); // HTTP port

    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send the HTTP request
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }

    // Receive the server's response
    while (recv(sock, buffer, BUFFER_SIZE, 0) > 0) {
        printf("%s", buffer);
        memset(buffer, 0, BUFFER_SIZE);
    }

    if (recv < 0) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }

    // Close the socket
    close(sock);

    return 0;
}
