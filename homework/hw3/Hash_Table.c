#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 10

typedef struct item {
    int key;
    char *value;
    struct item *next;
} item;

typedef struct hash_item {
    item *list;
} hash_item;

typedef struct hash_table {
    int size;
    hash_item *items;
} hash_table;

int hash_func(int key) {
    return key % MAX_SIZE;
}

int insert(hash_table *table, int key, char *value) {
    int index = hash_func(key);
    hash_item *hash_item = &(table->items[index]);
    item* current_item = hash_item->list;
    item* new_item = (item*)malloc(sizeof(item));
    new_item->key = key;
    new_item->value = strdup(value);
    new_item->next = NULL;
    if (current_item == NULL) {
        hash_item->list = new_item;
    } else {
        while (current_item->next != NULL) {
            if (current_item->key == key) {
                free(current_item->value);
                current_item->value = strdup(value);
                return 0;
            }
            current_item = current_item->next;
        }
        current_item->next = new_item;
    }
    return 0;
}

int delete(hash_table *table, int key) {
    int index = hash_func(key);
    hash_item *hash_item = &(table->items[index]);
    item* curr_item = hash_item->list;
    item* prev_item = NULL;
    while (curr_item != NULL) {
        if (curr_item->key == key) {
            if (prev_item == NULL) {
                hash_item->list = curr_item->next;
            } else {
                prev_item->next = curr_item->next;
            }
            free(curr_item->value);
            free(curr_item);
            return 0;
        }
        prev_item = curr_item;
        curr_item = curr_item->next;
    }
    return -1;
}

char* find(hash_table* table, int key) {
    int index = hash_func(key);
    hash_item *hash_item = &(table->items[index]);
    item *curr_item = hash_item->list;
    while (curr_item != NULL) {
        if (curr_item->key == key) {
            return curr_item->value;
        }
        curr_item = curr_item->next;
    }
    return NULL;
}

int main() {
    hash_table *table = (hash_table*) malloc(sizeof(hash_table));
    table->size = MAX_SIZE;
    table->items = (hash_item*) malloc(MAX_SIZE * sizeof(hash_item));
    for (int i = 0; i < MAX_SIZE; i++) {
        table->items[i].list = NULL;
    }
    insert(table, 1, "afwe");
    insert(table, 2, "wetwt");
    insert(table, 5, "mdsfh");
    delete(table, 11);
    delete(table, 2);
    printf("result: %s\n ", find(table, 5));
    printf("result: %s\n ", find(table, 3));
    for (int i = 0; i < MAX_SIZE; i++) {
        item *curr_item = table->items[i].list;
        while (curr_item != NULL) {
            printf("key: %d, value: %s\n", curr_item->key, curr_item->value);
            curr_item = curr_item->next;
        }
    }
    return 0;
}
