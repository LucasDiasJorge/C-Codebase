#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a JSON object
typedef struct JSON {
    char *key;
    char *value;
    struct JSON *next;
} JSON;

// Function to get the value associated with a given key
const char *getValue(const JSON *head, const char *key) {
    while (head != NULL) {
        if (strcmp(head->key, key) == 0) {
            return head->value;
        }
        head = head->next;
    }
    return NULL; // Key not found
}

// Function to create a new JSON object
JSON *createJSON(const char *key, const char *value) {
    JSON *new_json = (JSON *)malloc(sizeof(JSON));
    if (new_json == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_json->key = strdup(key);
    new_json->value = strdup(value);
    new_json->next = NULL;
    return new_json;
}

// Function to add a JSON object to the end of a linked list
void addJSON(JSON **head, const char *key, const char *value) {
    JSON *new_json = createJSON(key, value);
    if (*head == NULL) {
        *head = new_json;
    } else {
        JSON *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_json;
    }
}

// Function to free memory allocated to JSON objects
void freeJSON(JSON *head) {
    while (head != NULL) {
        JSON *temp = head;
        head = head->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
}

// Function to print JSON objects
void printJSON(JSON *head) {
    printf("{\n");
    while (head != NULL) {
        printf("\t\"%s\": \"%s\",\n", head->key, head->value);
        head = head->next;
    }
    printf("}\n");
}

int main() {
    JSON *json = NULL;

    // Adding JSON objects
    addJSON(&json, "name", "John");
    addJSON(&json, "age", "30");
    addJSON(&json, "city", "New York");

    // Printing JSON objects
    printJSON(json);

    // Retrieving values
    const char *name = getValue(json, "name");
    const char *age = getValue(json, "age");
    const char *city = getValue(json, "city");

    if (name != NULL) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found\n");
    }

    if (age != NULL) {
        printf("Age: %s\n", age);
    } else {
        printf("Age not found\n");
    }

    if (city != NULL) {
        printf("City: %s\n", city);
    } else {
        printf("City not found\n");
    }

    // Freeing allocated memory
    freeJSON(json);

    return 0;
}

