#include <stdio.h>
#include <stdlib.h>

//просматриваемая таблица с занятостью и версиями вектор

struct Item {
    int busy;
    int rel;
    int key;
    char *info;
};
struct Table {
    int max_size;
    int curr_size;
    struct Item *items;
};

void clean_garbage(struct Table *table) {
    int j = 0;

    for (int i = 0; i < table->curr_size; i++) {
        if (table->items[i].busy) {
            table->items[j] = table->items[i];
            j++;
        }
    }
    table->curr_size = j;
}

int find(struct Table *table, int key) {
    for (int i = 0; i < table->curr_size; i++) {
        if ((table->items[i].busy == 1) && table->items[i].key == key) {
            return i;
        }
    }
    return -1;
}

int find_last_rel(struct Table *table, int key) {
    int count = 0;
    for (int i = 0; i < table->curr_size; i++) {
        if (table->items[i].key == key) {
            if (count < table->items[i].rel) {
                count = table->items[i].rel;
            }
        }
    }
    return count;
}

int insert(struct Table *table, int key, char *info) {
    if (table->curr_size == table->max_size) {
        clean_garbage(table);
        if (table->curr_size == table->max_size) {
            return -3;
        }
    }
    table->items[table->curr_size].key = key;
    table->items[table->curr_size].info = info;
    table->items[table->curr_size].busy = 1;
    table->items[table->curr_size].rel = find_last_rel(table, key) + 1;
    table->curr_size++;
    return 0;
}

int delete(struct Table *table, int key) {
    int index = find(table, key);
    if (index != -1) {
        table->items[index].busy = 0;
    } else {
        return -2;
    }
    return 0;
}

int main() {
    struct Table *table = (struct Table *) calloc(1, sizeof(struct Table));
    table->max_size = 10;
    table->curr_size = 2;
    table->items = (struct Item *) calloc(table->max_size, sizeof(struct Item));

    table->items[0].key = 1;
    table->items[0].info = "aaahjj";
    table->items[0].rel = 1;
    table->items[0].busy = 1;

    table->items[1].key = 3;
    table->items[1].info = "yuui";
    table->items[1].rel = 1;
    table->items[1].busy = 1;

    insert(table, 1, "fsafd");
    //printf("\n%d", find(table, 1));
    //printf("\n%d", insert(table, 4, "sls"));
    printf("\n%d", find_last_rel(table, 1));
    delete(table, 3);
    printf("\n%d", find(table, 4));
    return 0;
}
