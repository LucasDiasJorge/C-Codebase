#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define MAC_ADDR_LEN 6

char* get_mac_address(const char* interface) {
    int sock;
    struct ifreq ifr;
    unsigned char mac_addr[MAC_ADDR_LEN];
    char* mac_addr_str = (char*)malloc(18); // MAC address string format is "XX:XX:XX:XX:XX:XX\0"

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    strcpy(ifr.ifr_name, interface);

    if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
        perror("ioctl");
        exit(1);
    }

    close(sock);

    // Copy MAC address to buffer
    memcpy(mac_addr, ifr.ifr_hwaddr.sa_data, MAC_ADDR_LEN);

    // Format MAC address as string
    snprintf(mac_addr_str, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);

    return mac_addr_str;
}

int main() {
    char* interface = "enp2s0"; // Change this to your interface name
    char* mac_address = get_mac_address(interface);
    printf("MAC address of %s: %s\n", interface, mac_address);
    free(mac_address);
    return 0;
}
