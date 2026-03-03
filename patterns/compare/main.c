#include <stdio.h>

// Função para comparar e retornar o maior valor entre dois inteiros
int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

// Função para comparar e retornar o maior valor entre dois longs
long maxLong(long a, long b) {
    return (a > b) ? a : b;
}

int main() {
    int int1 = 10, int2 = 20;
    long long1 = 1000L, long2 = 2000L;

    // Comparando e imprimindo o maior valor entre dois inteiros
    printf("O maior entre %d e %d é: %d\n", int1, int2, maxInt(int1, int2));

    // Comparando e imprimindo o maior valor entre dois longs
    printf("O maior entre %ld e %ld é: %ld\n", long1, long2, maxLong(long1, long2));

    return 0;
}
