#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;

    data.i = 10;
    printf("data.i: %d\n", data.i);

    data.f = 220.5;
    printf("data.f: %.2f\n", data.f);

    // Atribuir um valor para `str` sobrescreve os valores anteriores
    snprintf(data.str, sizeof(data.str), "C Programming");
    printf("data.str: %s\n", data.str);

    return 0;
}