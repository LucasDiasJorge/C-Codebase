#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

void get_my_ip(char *buffer, size_t buffer_len) {
    int sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in local_addr;
    socklen_t addr_len = sizeof(local_addr);

    // Create a socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Define the server address to connect to
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(53); // DNS port
    inet_pton(AF_INET, "8.8.8.8", &server_addr.sin_addr); // Google DNS

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Get the local IP address
    if (getsockname(sock, (struct sockaddr *)&local_addr, &addr_len) < 0) {
        perror("getsockname");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Convert the local IP address to a string
    inet_ntop(AF_INET, &local_addr.sin_addr, buffer, buffer_len);

    // Close the socket
    close(sock);
}

int main() {
    char ip_buffer[INET_ADDRSTRLEN];

    get_my_ip(ip_buffer, sizeof(ip_buffer));
    printf("My IP address is: %s\n", ip_buffer);

    return 0;
}
