// insert.c
#include <stdio.h>
#include "hashtable.h"
#include <string.h>
#include <stdlib.h>

void insert_bb(){
    tag* t = (tag*)malloc(sizeof(tag));

    strncpy(t->epc, "94CD0E818ABD27C6DC4E9932", sizeof(t->epc) - 1);
    strncpy(t->antenna_port, "2", sizeof(t->antenna_port) - 1);
    strncpy(t->time_datetime, "3", sizeof(t->time_datetime) - 1);

    hash_table_insert(t);
}