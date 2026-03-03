#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

int main(void) {
    char* str = malloc(strlen("XX:XX:XX:XX:XX:XX")+1);
    strcpy(str, "XX:XX:XX:XX:XX:XX");
    removeChar(str, ':');
    printf("%s\n", str);
    free(str);
    return 0;
}