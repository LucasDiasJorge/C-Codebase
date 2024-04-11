#include <stdio.h>

void add_to_int(int &r)
{
    r+=5;
}

int main() 
{

    int i = 0; // original value, to be referenced
    int &ri = i; // alias to i, the reference

    i++; // i = 1;
    ri++; // i = 2;

    add_to_int(ri); // i = i + 5 

    printf("i = %d\n",ri); // 7

    return 0;
}
