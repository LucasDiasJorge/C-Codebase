#include <stdio.h>

#define  message_for(a, b)  \
   printf(#a " and " #b ": We love you!\n")

#define numberpaster(n) printf ("number" #n " = %d\n", number##n)

#define loop while(1)

#define square(x) ((x) * (x)) // int square(int x) {
                              //   return x * x;
                              // }

#define MAX(x,y) ((x) > (y) ? (x) : (y))


int main() {

    printf("File :%s\n", __FILE__ );
    printf("Date :%s\n", __DATE__ );
    printf("Time :%s\n", __TIME__ );
    printf("Line :%d\n", __LINE__ );
    printf("ANSI :%d\n", __STDC__ );

    int number1 = 10;

    /*
    loop {
        message_for(Carole, Debra);
        numberpaster(1);
    }
    */

    square(16);

    printf("Max between 20 and 10 is %d\n", MAX(10, 20));  

   return 0;

}