#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define _DATE_

int main (void) {
   
   int v[MAX]; // int v[1000];
   
   for (int i = 0; i < MAX; ++i) { // for (int i = 0; i < 1000; ++i)
      printf("%i\n",i);
   }

   return EXIT_SUCCESS;
} 