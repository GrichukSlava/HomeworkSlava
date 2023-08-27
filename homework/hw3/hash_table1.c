#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct hash_item {
    int count;
};

struct hash_table {
    struct hash_item *items;
};

int hash_function(char key) {
    return ('a' - key);
}

bool isIsomorphic(char *s, char *t) {
    int len_s = strlen(s);
    int len_t = strlen(t);
    if (len_s != len_t) {
        return false;
    }
    struct hash_table table_s;
    struct hash_table table_t;
    table_s.items = (struct hash_item*)calloc(26, sizeof(struct hash_item));
    table_t.items = (struct hash_item*)calloc(26, sizeof(struct hash_item));

    for (int i = 0; i < len_s; i++) {
        int index_s = hash_function(s[i]);
        int index_t = hash_function(t[i]);
        table_s.items[index_s].count++;
        table_t.items[index_t].count++;
    }

    for (int i = 0; i < len_s; i++) {
        int index_s = hash_function(s[i]);
        int index_t = hash_function(t[i]);
        if (table_s.items[index_s].count != table_t.items[index_t].count) {
            free(table_s.items);
            free(table_t.items);
            return false;
        }
    }

    free(table_s.items);
    free(table_t.items);
    return true;
}

int main() {
    char s[] = "egg";
    char t[] = "add";

    if (isIsomorphic(s, t)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    return 0;
}