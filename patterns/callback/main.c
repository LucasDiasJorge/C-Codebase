#include <stdio.h>

typedef int (*operation_callback)(int,int);

int add(int a, int b){
    return a+b;
}

int multiply(int a, int b){
    return a*b;
}

void calculate(int a, int b, operation_callback callback){
    int resutl = callback(a,b);
    printf("The result is: %d\n", resutl);
}

int main() {
    calculate(5, 3, add);
    calculate(5, 3, multiply);
    return 0;
}