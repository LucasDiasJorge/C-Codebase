#include <stdio.h>
#include <stdlib.h>

int check_internet_connection() {
    // Executa o comando "ping -c 1 8.8.8.8" e redireciona a saída para /dev/null
    // -c 1: envia apenas 1 pacote de ping
    int status = system("ping -c 1 8.8.8.8 > /dev/null 2>&1");
    return status == 0; // Retorna 1 se o comando foi bem-sucedido, 0 caso contrário
}

int main() {
    if (check_internet_connection()) {
        printf("Connected ...\n");
    } else {
        printf("Disconnected\n");
    }
    return 0;
}
