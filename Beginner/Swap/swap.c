#include <stdio.h>

void arithmetic_swap(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void bitwise_swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void temp_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}