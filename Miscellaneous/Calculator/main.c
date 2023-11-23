#include <stdio.h>

// Function to add two numbers
double add(double a, double b) {
    return a + b;
}

// Function to subtract two numbers
double subtract(double a, double b) {
    return a - b;
}

// Function to multiply two numbers
double multiply(double a, double b) {
    return a * b;
}

// Function to divide two numbers
double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        printf("Error: Cannot divide by zero\n");
        return 0;
    }
}

int main() {
    double num1, num2;
    char operator;

    printf("Enter an expression (e.g., 5 + 7): ");
    scanf("%lf %c %lf", &num1, &operator, &num2);

    switch (operator) {
        case '+':
            printf("Result: %.2f\n", add(num1, num2));
            break;
        case '-':
            printf("Result: %.2f\n", subtract(num1, num2));
            break;
        case '*':
            printf("Result: %.2f\n", multiply(num1, num2));
            break;
        case '/':
            printf("Result: %.2f\n", divide(num1, num2));
            break;
        default:
            printf("Error: Invalid operator\n");
            break;
    }

    return 0;
}
