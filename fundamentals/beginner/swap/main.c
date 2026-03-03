#include <stdio.h>
#include "swap.h"

int main() {
    
    int x = 5, y = 10;
    printf("Before swap: x = %d, y = %d\n", x, y);

    temp_swap(&x, &y);
    printf("After swap: x = %d, y = %d\n", x, y);

    arithmetic_swap(&x, &y);
    printf("After arithmetic swap: x = %d, y = %d\n", x, y);

    bitwise_swap(&x, &y);
    printf("After bitwise swap: x = %d, y = %d\n", x, y);

    return 0;
}