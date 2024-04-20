#include <stdio.h>

// Declaração da função que recebe um ponteiro para uma função como parâmetro
void executa_funcao(void (*funcao)(int), int valor);

// Função de exemplo que será passada como parâmetro
void funcao_exemplo(int numero) {
    printf("A função exemplo foi chamada com o número: %d\n", numero);
}

int main() {
    // Chamando a função executa_funcao e passando a função funcao_exemplo como parâmetro
    executa_funcao(funcao_exemplo, 10);

    return 0;
}

// Definição da função que recebe um ponteiro para uma função como parâmetro
void executa_funcao(void (*funcao)(int), int valor) {
    // Chamando a função recebida como parâmetro
    (*funcao)(valor);
}
