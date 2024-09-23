In C, **pass by value** and **pass by reference** refer to how arguments are passed to functions:

### Pass by Value:
- When a function is called with arguments passed by value, **a copy** of the actual data is passed to the function.
- Changes made to the parameter inside the function do **not** affect the original variable.
- Example:

```c
#include <stdio.h>

void modifyValue(int x) {
    x = 10;  // This change won't affect the original value
}

int main() {
    int a = 5;
    modifyValue(a);
    printf("a = %d\n", a);  // Output: a = 5 (unchanged)
    return 0;
}
```
In this case, the value of `a` is copied into the function, and any modifications to `x` do not affect `a`.

### Pass by Reference (using pointers in C):
- C doesn't support direct pass by reference, but you can simulate it by passing the **address** of the variable (i.e., a pointer).
- In this case, the function operates on the original variable through its pointer, so changes made inside the function will affect the original variable.
- Example:

```c
#include <stdio.h>

void modifyValue(int *x) {
    *x = 10;  // This changes the original value
}

int main() {
    int a = 5;
    modifyValue(&a);  // Pass the address of 'a'
    printf("a = %d\n", a);  // Output: a = 10 (changed)
    return 0;
}
```
Here, the function changes the value of `a` directly by using its address.

### Summary:
- **Pass by Value:** A copy of the variable is passed; the original value remains unchanged.
- **Pass by Reference (using pointers):** The memory address of the variable is passed, allowing the function to modify the original value.