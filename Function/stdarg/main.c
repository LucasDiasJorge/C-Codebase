#include <stdio.h>
#include <stdarg.h>

void myFunction(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == 'd') {  // Espera um inteiro
            int i = va_arg(args, int);
            printf("Integer: %d\n", i);
        } else if (*format == 'c') {  // Espera um caractere
            int c = va_arg(args, int);  // Char promovido para int
            printf("Char: %c\n", c);
        } else if (*format == 'f') {  // Espera um float
            double d = va_arg(args, double);
            printf("Double: %f\n", d);
        } else if (*format == 's') {  // Espera uma string
            const char *str = va_arg(args, const char *);
            printf("String: %s\n", str);
        } else {  // Apenas imprime o caractere do formato (ex. 'd', 'f', 'c', 's')
            putchar(*format);
        }
        format++;
    }

    va_end(args);
}

int main() {
    myFunction("dfcs", 3, 1.23, 'a', "Hello, World!");
    return 0;
}
