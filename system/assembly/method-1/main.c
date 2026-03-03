#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;
    int result;

    asm("movl %1, %%eax;   # Move o valor de 'b' para o registrador eax\n"
        "addl %2, %%eax;   # Adiciona o valor de 'a' ao registrador eax\n"
        "movl %%eax, %0;   # Move o resultado de volta para 'result'\n"
        : "=r" (result)    // Saída: result
        : "r" (b),          // Entrada: b
          "r" (a)           // Entrada: a
        : "%eax"           // Registrador usado (neste caso, eax)
    );

    printf("Resultado: %d\n", result);

    return 0;
}
