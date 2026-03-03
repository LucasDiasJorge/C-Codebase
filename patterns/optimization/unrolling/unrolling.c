#include <stdio.h>

void sum_array_unrolled(int *array, int size, int *result) {
    int sum = 0;
    int i;
    
    // Unrolling loop to process 4 elements per iteration
    for (i = 0; i <= size - 4; i += 4) {
        sum += array[i] + array[i + 1] + array[i + 2] + array[i + 3];
    }

    // Process remaining elements
    for (; i < size; i++) {
        sum += array[i];
    }

    *result = sum;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result;
    sum_array_unrolled(array, 10, &result);
    printf("Sum: %d\n", result);
    return 0;
}
