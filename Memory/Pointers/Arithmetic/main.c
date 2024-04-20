#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;

    // Print array elements using pointer arithmetic
    printf("Array elements using pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");

    // Demonstrate pointer increment
    ptr++; // Move pointer to the next element
    printf("Next element: %d\n", *ptr);

    // Demonstrate pointer decrement
    ptr--; // Move pointer back to the previous element
    printf("Previous element: %d\n", *ptr);

    return 0;
}
