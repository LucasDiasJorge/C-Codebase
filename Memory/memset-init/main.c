#include <stdio.h>
#include <string.h>

#define initMem(p) memset((p), 0, sizeof(p))

void printMemory(const char *name, const char *p, size_t size) {
    printf("%s (Hexadecimal):\n", name);
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", (unsigned char)p[i]);
    }
    printf("\n\n");
}

int main() {
    char buffer[1024];
    char container[1024];
    char total_response[1024];

    printf("Before initMem()\n");
    printMemory("Buffer", buffer, sizeof(buffer));
    printMemory("Container", container, sizeof(container));
    printMemory("Total Response", total_response, sizeof(total_response));

    initMem(buffer);
    initMem(container);
    initMem(total_response);

    printf("\nAfter initMem()\n");
    printMemory("Buffer", buffer, sizeof(buffer));
    printMemory("Container", container, sizeof(container));
    printMemory("Total Response", total_response, sizeof(total_response));

    return 0;
}
