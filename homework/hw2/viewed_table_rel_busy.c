//
// Created by 79690 on 11.08.2023.
//
//просматриваемая таблица с занятостью и версиями список
#include <stdio.h>
#include <stdlib.h>
struct RelItem{
    int rel;
    int busy;
    char* info;
    struct RelItem* next;
};
struct Item{
    int key;
    struct Item* next;
    struct RelItem* rel_items;
};
struct Table{
    struct Item* items;
};

int find_last_rel( struct Item* head, int key){
    struct Item* current = head;
    while( current != NULL){
        if( current->key == key) {
            return current->rel_items->rel;
        }
        current = current->next;
    }
    return -1;
}

struct Item* find( struct Table* table, int key) {
    struct Item *curr = table->items;
    while (curr != NULL) {
        if (curr->key == key) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}
int insert( struct Table* table, int key, char* info){
    int last_rel = find_last_rel( table->items, key);
    if( last_rel == -1){
        struct Item* newItem = (struct Item*)calloc( 1, sizeof(struct Item));
        struct RelItem* relItem = (struct RelItem*)calloc( 1, sizeof(struct RelItem));
        relItem->info = info;
        relItem->rel = 1;
        relItem->busy = 1;
        newItem->key = key;
        newItem->rel_items = relItem;
        newItem->next = table->items;
        table->items = newItem;
    }else{
        struct RelItem* relItem = (struct RelItem*)calloc( 1, sizeof(struct RelItem));
        struct Item* current = find(table, key);
        relItem->info = info;
        relItem->rel = last_rel+1;
        relItem->busy = 1;
        relItem->next = NULL;
        relItem->next = current->rel_items;
        current->rel_items = relItem;
    }
    return 0;
}
struct RelItem* find_elem( struct Table* table, int key, int rel ){
    struct Item* current = find( table, key);
    if( current == NULL){
        return NULL;
    }
    struct RelItem* rel_item = current->rel_items;
    while( rel_item != NULL){
        if( rel_item->rel == rel){
            return rel_item;
        }
        rel_item = rel_item->next;
    }
    return NULL;
}
int delete( struct Table* table, int key){
    struct Item* current = table->items;
    int ind = find_last_rel( current ,  key);
    if( ind == -1){
        return -1;  //нет такого ключа
    }else{
        table->items->rel_items->busy = 0;
    }
    return 0;
}

void print_table(struct Table *table) {
    struct Item *item = table->items;
    while (item) {
        printf("%d ", item->key);
        item = item->next;
    }
}


int main() {
    struct Table *table = (struct Table *) malloc(sizeof(struct Table));
    struct Item* item1 = (struct Item *) malloc( sizeof(struct Item));
    item1->next = NULL;
    item1->key = 1;
    struct RelItem* rel_item1 = (struct RelItem *) malloc( sizeof(struct RelItem));
    rel_item1->next = NULL;
    rel_item1->info = "ads";
    rel_item1->rel = 1;
    rel_item1->busy = 1;
    item1->rel_items = rel_item1;
    table->items = item1;


    insert(table, 31, "asjgsh");

    printf("\nElem = %d", find_last_rel(table->items, 31));

    printf("\nElem = %d", find_last_rel(table->items, 4));
    insert(table, 31, "kiol");
    printf("\nElem = %s", find_elem(table, 31, 1)->info);
    printf("\nElem = %s", find_elem(table, 31, 2)->info);
    int k = delete(table, 31);

    printf("\n %d", k);
    printf("\nElem = %d", find_last_rel(table->items, 31));
    struct Item* curr = table->items;
    while( curr != NULL){
        struct RelItem* curr1 = curr->rel_items;
        struct Item* temp = curr;
        while( curr1 != NULL){
            struct RelItem* temp = curr1;
            curr1 = curr1->next;
            temp->next = NULL;
            free(temp);
        }
        curr = curr->next;
        temp->next = NULL;
        free(temp);
    }
    free(table);

    return 0;
}