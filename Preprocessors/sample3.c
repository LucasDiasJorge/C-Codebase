#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "aaa.txt"

//int GLOB = 8;
//int func (int e);

int main (void) { 
   while (GLOB <= 64) {
      printf ("%d\n", GLOB);
      GLOB *= 2;
   }
   return EXIT_SUCCESS;
}

int func (int i) { // calcula GLOB^3
   return pow(GLOB,i);
}