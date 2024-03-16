#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tag.h"

#define MAX_EPC 24
#define TABLE_SIZE 1000000

tag * hash_table[TABLE_SIZE];

unsigned int hash(char *name){
    int length = strnlen(name,MAX_EPC);
    unsigned int hash_value = 0;
    for(int i = 0; i < length; i++){
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table(){
    for(int i = 0; i < TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
    // Table is empty
}

void print_table(){
    printf("START\n");
    for(int i = 0; i < TABLE_SIZE; i++){
        if(hash_table[i] == NULL){
            printf("\t%i\t---\n",i);
        } else{ 
            printf("\t%i\t ", i);
            tag *tmp = hash_table[i];
            while (tmp != NULL){
                printf("%s - ", tmp->epc);
                printf("%s - ", tmp->time_datetime);
                tmp = tmp->next;
            }
            
            printf("\n");
        }
    }
    printf("END\n");
}

tag *hash_table_delete(char *name) {
    int index = hash(name);
    tag *tmp = hash_table[index];
    tag *prev = NULL;

    while (tmp != NULL && strncmp(tmp->epc, name, MAX_EPC) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        // Tag not found
        return NULL;
    }

    if (prev == NULL) {
        // Tag is at the head of the list
        hash_table[index] = tmp->next;
    } else {
        // Tag is in the middle or at the end of the list
        prev->next = tmp->next;
    }

    // Save the reference to the deleted tag
    tag *deleted_tag = tmp;

    // Free dynamically allocated fields if any
    free(tmp->epc);
    free(tmp->time_datetime);
    free(tmp->antenna_port);
    // Do not free tmp->time_timestamp; it's not a pointer, and it was not dynamically allocated

    // Free the tag structure
    free(tmp);

    return deleted_tag;  // Return the deleted tag
}

bool hash_table_insert(tag *t) {
    if (t == NULL) return false;
    int index = hash(t->epc);
    t->next = hash_table[index];
    hash_table[index] = t;
    return true;
} 

tag *hash_table_lookup(char *name){
    int index = hash(name);
    tag *tmp = hash_table[index];
    while(tmp != NULL && strncmp(tmp->epc, name, MAX_EPC) != 0){
        tmp = tmp->next;
    }
    return tmp;
}

void reset_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tag *current = hash_table[i];
        while (current != NULL) {
            tag *next = current->next;
            free(current);
            current = next;
        }
        hash_table[i] = NULL;
    }
}