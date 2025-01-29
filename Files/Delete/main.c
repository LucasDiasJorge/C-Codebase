#include <stdio.h>
#include <unistd.h>

int main() {
    const char *file = "data/file1.txt";

    if (unlink(file) == 0) {
        printf("Arquivo %s removido com sucesso!\n", file);
    } else {
        perror("Erro ao remover o arquivo");
    }

    return 0;
}
