#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tag {
    char epc[256];  
    char antenna_port[256];  
    char time_datetime[256];  
    int time_timestamp;
    struct tag *next;
} tag;

void print_tag(tag t){
    printf("\n\t==== TAG ====\n");
    printf("\tEPC: %s\n", t.epc);
    printf("\tAntenna: %s\n", t.antenna_port);
    printf("\tTime: %s\n", t.time_datetime);
    printf("\tTime (stamp): %i\n", t.time_timestamp);
}