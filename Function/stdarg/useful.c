#include <stdio.h>
#include <stdarg.h>
  
int multiplica(int nTermos, ...) {
    va_list listaTermos;
    va_start(listaTermos, nTermos);
  
    int resultado = 1;
  
    for (int i = 0; i < nTermos; i++)
        resultado = resultado*va_arg(listaTermos, int);
  
    va_end(listaTermos);
  
    return resultado;
}
  
int main() {
    printf("8! = %d\n", multiplica(7, 8, 7, 6, 5, 4, 3, 2)); // Primeiro 7 eh o numero de termos
  
    return 0;
}
     