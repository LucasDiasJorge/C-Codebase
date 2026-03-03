#ifndef TAG_H
#define TAG_H

typedef struct tag {
    char epc[256];  
    char antenna_port[256];  
    char time_datetime[256];  
    int time_timestamp;
    struct tag *next;
} tag;

void print_tag(tag);

#endif
