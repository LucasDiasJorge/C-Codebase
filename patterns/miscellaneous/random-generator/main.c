#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>
  
int main(){
  
    int i;    

    /* Seed the random number generator with the given number.  */
    srand(time(NULL));

    /* It returns the same sequence of random number on every execution of the program. */  
    printf(" Random Numbers are: \n");   
    for (i = 0; i <5; i++){  
        printf(" %d \n", rand());  
    }

    return 0;  
}  