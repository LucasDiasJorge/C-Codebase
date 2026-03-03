#include <stdio.h>

// https://stackoverflow.com/questions/64844634/c-how-to-convert-user-char-input-to-ascii
int main(){

    char string;

    scanf("%c",&string);
    printf("Ascii code of %c is %d\n", string, (int) string);

    return 0;
}