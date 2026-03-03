#include <stdio.h>
#include <stdlib.h>

#define swap (A, B) {int t = A; A = B; B = t;} 

int main(){

    // a[] declaration

    for (int i = 0; i < 100; ++i) {
        int k = i;
        for (int j = i+1; j <= 100; ++j) 
            if (a[j] < a[k]) k = j;
        swap (a[i], a[k]); // {int t = a[i]; a[i] = a[k]; a[k] = t;}
    } 

}
