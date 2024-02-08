#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "time.h"
#include "tag.h"
#include <stdbool.h>

#define MAX_EPC 24
#define TABLE_SIZE 11000

extern tag *hash_table[TABLE_SIZE];

unsigned int hash(char *name);

void init_hash_table();

void print_table();

bool hash_table_insert(tag *t);

tag *hash_table_delete(char *name);

tag *hash_table_lookup(char *name);

#endif  // HASHTABLE_H
