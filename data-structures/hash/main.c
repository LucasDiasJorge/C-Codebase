#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void generateHash(const char *input, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);
}

int main() {
    char input[100];
    printf("Digite a string para gerar o hash: ");
    fgets(input, sizeof(input), stdin);
    
    // Remover o caractere de nova linha (\n) da entrada
    input[strcspn(input, "\n")] = 0;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    generateHash(input, hash);

    printf("Hash gerado: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}
