#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool starts_with(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}

int main()
{

    printf("Bool is %d\n", starts_with("Lucas","Luisa Dias Jorge"));
    printf("Bool is %d\n", starts_with("Lucas","Lucas Dias Jorge"));

    return 0;   
}