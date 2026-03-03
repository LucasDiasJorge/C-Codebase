// main.c
#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "insert.h"

int main(){

    init_hash_table();

    if(hash_table[hash("94CD0E818ABD27C6DC4E9932")] == NULL){
        printf("Is empty\n");
    }

    insert_bb();    

    if(hash_table[hash("94CD0E818ABD27C6DC4E9932")] != NULL){
        printf("Is not empty\n");
    }

    return 0;
}