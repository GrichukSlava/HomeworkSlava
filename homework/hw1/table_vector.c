//
// Created by 79690 on 11.08.2023.
//
//Упорядоченная таблица(вектор)
#include <stdio.h>
#include <stdlib.h>
typedef struct Item {
    int key;
    char *info;
} Item;

struct Table {
    int max_size;
    int curr_size;
    struct Item *items;
};


int find(struct Table *table, int key) {
    int n = 0;
    int m = table->curr_size;
    int middle = -1;
    while (n <= m) {
        middle = (m + n) / 2;
        if (table->items[middle].key == key) {
            return middle;
        }
        if (table->items[middle].key > key) {
            n = middle + 1;
        } else {
            m = middle - 1;
        }
    }
    return -1;
}


int insert(struct Table *table, struct Item *element) {
    int index = find(table, element->key);
    if (index != -1) {
        return -1;
    }
    if (table->curr_size < table->max_size) {
        //Мой код
        index = table->curr_size; //место куда должен сохранится новый элемент
        for (int i = 0; i < table->curr_size; i++) {
            if (table->items[i].key > element->key) {
                index = i;
                break;
            }
        }
        for (  int j = (table->curr_size)-1; j >= index; j--){
            table->items[j+1] = table->items[j];
        }
        table->items[index].key = element->key;
        table->items[index].info = element->info;
        (table->curr_size)++;
    }else{
        return -2;
    }
    return 0;
}


int delete(struct Table *table, int key) {
    int index = find(table, key);
    if (index == -1) {
        return -3;//не найден
    }
    (table->curr_size)--;
    for (int i = index; i < table->curr_size; i++) {
        table->items[i] = table->items[i+1];
    }
    return 0;
}

int main() {

    struct Table *table = (struct Table *) calloc(1, sizeof(struct Table));
    table->max_size = 10;
    table->items = (struct Item *) calloc(table->max_size, sizeof(struct Item));

    //Тест на insert
    struct Item *item = (struct Item *) calloc(1,sizeof(struct Item));
    item->key = 1;
    item->info = "bdkd";
    insert(table, item);
    printf("\nElem = %d", find(table, 3));
/*
  //Тест на find
    printf("\nElem = %d", find(table, 1));

    //Тест на delete
    int res = delete(table, 2);
    printf("\nElem = %d", find(table, 2));
*/
    /*free(table->items);
    free(table);
     */
    return 0;
}


